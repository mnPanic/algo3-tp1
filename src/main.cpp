#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <map>

// https://github.com/nlohmann/json
#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

constexpr int INVALID_INSTANCE = 0;
constexpr int INF = 1e6;

struct Local {
    int beneficio;
    int contagio;
};

constexpr int MEM_UNDEFINED = -1;

/** Funciones auxiliares **/

vector<bool>& set(vector<bool>& v, int i) {
    v[i] = true;
    return v;
}

vector<bool>& unset(vector<bool>& v, int i) {
    v[i] = false;
    return v;
}

// Para debug
string pertenenciaToString(vector<bool> &vs) {
    string res = "";
    bool first = true;
    for (bool v : vs) {
        if (first) {
            first = false;
            continue;
        }

        res += v? "1 " : "0 ";
    }

    return res;
}

void printMem(vector<vector<int>> &m) {
    for (vector<int> fila : m) {
        for (int val : fila) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Devuelve true si A deberia ir antes que B en el ordenamiento.
// (A > B)
bool compareLocales(Local A, Local B) {
    return A.beneficio > B.beneficio;
}

// Da una cota superior para el maximo beneficio restante.
// Complejidad temporal: O(n)
int maximoBeneficioRestante(vector<Local>& locales, int i) {
    // Recorremos los locales sumando al beneficio
    // O(n)
    int beneficio = 0;
    for (int j = 1; j < i + 1; j++) {
        beneficio += locales[j].beneficio;
    }

    return beneficio;
}

/** Funciones principales **/

// fuerzaBruta
// Algoritmo recursivo de fuerza bruta
// Complejidad temporal: O(n * 2^n)
//
// Asumimos que existe al menos un local que tenga contagio inferior a M
int npm_fb(vector<Local> &locales, int n, int M, vector<bool> &pertenencia, int i) {
//    cout << "Estamos recorriendo el local: " << i << " con el vector " << pertenenciaToString(pertenencia) << endl;
    if (i == n + 1) {
        int beneficioAcumulado = 0;
        int contagioAcumulado = 0;

        for (int j = 1; j <= n; ++j) {
            if (j != n && pertenencia[j] && pertenencia[j+1]) {
                return INVALID_INSTANCE;
            }

            if (pertenencia[j]) {
                beneficioAcumulado += locales[j].beneficio;
                contagioAcumulado += locales[j].contagio;
            }

            if (contagioAcumulado > M) {
                return INVALID_INSTANCE;
            }
        }

        return beneficioAcumulado;
    }

    return max(
        npm_fb(locales, n, M, unset(pertenencia, i), i+1),
        npm_fb(locales, n, M, set(pertenencia, i), i+1)
    );
}

// NPM con backtracking con podas de factibilidad
// Complejidad temporal: O(2^n)
int npm_bt_poda_fact(int i, int M, vector<bool> &vecinos, vector<Local> &ls) {
    /* Podas de factibilidad */
    // Si nos pasamos del limite de contagio no es una instancia valida
    if (M < 0) return -INF;

    // Si los dos ultimos vecinos estan siendo contemplados no es una
    // instancia valida.
    if (i < (ls.size() - 1) && vecinos[i + 1] && vecinos[i + 2]) return -INF;

    // Caso base
    if (i == 0) return 0;

    // Llamado recursivo
    return max(
        npm_bt_poda_fact(i-1, M - ls[i].contagio, set(vecinos, i), ls) + ls[i].beneficio,
        npm_bt_poda_fact(i-1, M, unset(vecinos, i), ls)
    );
}

// NPM con backtracking con podas de optimalidad, con el maximo beneficio
// restante cacheado.
// Complejidad temporal: O(n * 2^n)
int npm_bt_poda_opt_cache(int i, int M, vector<bool> &vecinos, vector<Local> &ls, int B, int &maxB, vector<int>& cacheB) {
    // Caso base
    if (i == 0) {
        // Si nos pasamos del limite de contagio no es una instancia valida
        if (M < 0) return -INF;

        // No tiene que haber dos vecinos consecutivos
        for (int j = 1; j < ls.size() - 1; ++j) {
            if (vecinos[j] && vecinos[j+1]) {
                return -INF;
            }
        }

        return B;
    }

    // Poda por optimalidad
    // El máximo beneficio restante no puede cortar en casos incorrectos debido
    // a que es una sobreestimación del máximo beneficio real que se puede
    // obtener si se continúa por esta rama.
    if (cacheB[i] + B < maxB) return -INF;

    // Llamado recursivo
    int maxBLocal = max(
        npm_bt_poda_opt_cache(i-1, M - ls[i].contagio, set(vecinos, i), ls, B + ls[i].beneficio, maxB, cacheB),
        npm_bt_poda_opt_cache(i-1, M, unset(vecinos, i), ls, B, maxB, cacheB)
    );

    maxB = max(maxB, maxBLocal);

    return maxBLocal;
}

// NPM con backtracking con podas de optimalidad
// Complejidad temporal: O(n * 2^n)
int npm_bt_poda_opt(int i, int M, vector<bool> &vecinos, vector<Local> &ls, int B, int &maxB) {
    // Caso base
    if (i == 0) {
        // Si nos pasamos del limite de contagio no es una instancia valida
        if (M < 0) return -INF;

        // No tiene que haber dos vecinos consecutivos
        for (int j = 1; j < ls.size() - 1; ++j) {
            if (vecinos[j] && vecinos[j+1]) {
                return -INF;
            }
        }

        return B;
    }

    // Poda por optimalidad
    // El máximo beneficio restante no puede cortar en casos incorrectos debido
    // a que es una sobreestimación del máximo beneficio real que se puede
    // obtener si se continúa por esta rama.
    // O(n)
    if (maximoBeneficioRestante(ls, i) + B <= maxB) return -INF;

    // Llamado recursivo
    int maxBLocal = max(
        npm_bt_poda_opt(i-1, M - ls[i].contagio, set(vecinos, i), ls, B + ls[i].beneficio, maxB),
        npm_bt_poda_opt(i-1, M, unset(vecinos, i), ls, B, maxB)
    );

    maxB = max(maxB, maxBLocal);

    return maxBLocal;
}

// NPM con backtracking con podas de optimalidad Y factibilidad
// Complejidad temporal: O(2^n)
int npm_bt(int i, int M, vector<bool> &vecinos, vector<Local> &ls, int B, int &maxB, vector<int>& cacheB) {
    /* Podas de factibilidad */
    // Si nos pasamos del limite de contagio no es una instancia valida
    if (M < 0) return -INF;

    // Si los dos ultimos vecinos estan siendo contemplados no es una
    // instancia valida.
    if (i < (ls.size() - 1) && vecinos[i + 1] && vecinos[i + 2]) return -INF;

    // Caso base
    if (i == 0) return B;

    /** Poda por optimalidad **/
    // El máximo beneficio restante no puede cortar en casos incorrectos debido
    // a que es una sobreestimación del máximo beneficio real que se puede
    // obtener si se continúa por esta rama.
    if (cacheB[i] + B < maxB) return -INF;

    // Llamado recursivo
    int maxBLocal = max(
        npm_bt(i-1, M - ls[i].contagio, set(vecinos, i), ls, B + ls[i].beneficio, maxB, cacheB),
        npm_bt(i-1, M, unset(vecinos, i), ls, B, maxB, cacheB)
    );

    maxB = max(maxB, maxBLocal);

    return maxBLocal;
}

// NPM por programacion dinamica
// Complejidad temporal: O(n * M)
int npm_pd(int i, int M, vector<Local> &ls, vector<vector<int>> &mem) {
    // Si nos pasamos del limite de contagio no es una instancia valida
    if (M < 0) return -INF;

    // Caso base
    // Menor a 0 ya que a veces decrementamos de a 2.
    if (i < 0) return 0;

    // Llamado recursivo
    if (mem[i][M] == MEM_UNDEFINED) {
        mem[i][M] = max(
            // Para ponernos a nosotros, directamente salteamos el siguiente ya
            // que sabemos que no va a ser una solución factible.
            npm_pd(i - 2, M - ls[i].contagio, ls, mem) + ls[i].beneficio,
            npm_pd(i - 1, M, ls, mem)
        );
    }

    return mem[i][M];
}

void grado_solapamiento(int i, int M, vector<Local> &ls, vector<vector<int>> &llamados) {
    if(i == 0 || M < 0) return;

    llamados[i][M]++;

    grado_solapamiento(i-1, M-ls[i].contagio, ls, llamados);
    grado_solapamiento(i-1, M, ls, llamados);
}

int main(int argc, char** argv) {
	map<string, string> algorithms = {
		{"FB", "Fuerza Bruta"},
        {"BT", "Backtracking con podas"},
        {"BT-F", "Backtracking con poda por factibilidad"}, 
		{"BT-O", "Backtracking con poda por optimalidad"},
        {"BT-O-C", "Backtracking con poda por optimalidad cacheado"},
        {"DP", "Programacion dinámica"},
        {"GR", "Calificar el grado de solapamiento de una instancia"},
	};

	// Leo el argumento que indica el algoritmo. Tiene que haber al menos dos
	// porque el primero es el nombre del programa.
    if (argc < 2) {
        cout << "Uso:\n\t$ ./tp1 <algorithm>" << endl;
        return -1;
    }

    string algorithm = argv[1];
    if(algorithms.find(algorithm) == algorithms.end()) {
        cout << "Algoritmo no encontrado: " << algorithm << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto& alg_desc: algorithms) cerr << "- " << alg_desc.first << "\t" << alg_desc.second << endl;
		return -1;
    }

    // Leemos el input.
    int n = 0; // Cantidad de locales en la avenida
    int M = 0; // Limite de contagio
    std::cin >> n >> M;

    vector<Local> locales(n+1, Local{0,0});
    vector<bool> vecinos(n+1, false);
    for (int i = 1; i <= n; ++i) {
        std::cin >> locales[i].beneficio >> locales[i].contagio;
    }

    // Corremos el algoritmo
    int maximum;
    auto start = chrono::steady_clock::now();

    // mem
    if (algorithm == "FB") {
        maximum = npm_fb(locales, n, M, vecinos, 0);
    } else if (algorithm == "BT") {
        int maximoBeneficio = 0;
        // Generamos la cache (en realidad no es una cache, ya sabemos, pero no
        // encontramos mejor nombre) utilizada por el algoritmo
        // O(n)
        vector<int> cacheB(n+1, 0);
        for (int j = 1; j <= n; j++) {
            cacheB[j] = cacheB[j-1] + locales[j].beneficio;
        }

        maximum = npm_bt(n, M, vecinos, locales, 0, maximoBeneficio, cacheB);
    } else if (algorithm == "BT-F") {
        int maximoBeneficio = 0;
        maximum = npm_bt_poda_fact(n, M, vecinos, locales);
    } else if (algorithm == "BT-O") {
        int maximoBeneficio = 0;
        maximum = npm_bt_poda_opt(n, M, vecinos, locales, 0, maximoBeneficio);
    } else if (algorithm == "BT-O-C") {
        int maximoBeneficio = 0;
        // Generamos la cache (en realidad no es una cache, ya sabemos, pero no
        // encontramos mejor nombre) utilizada por el algoritmo
        // O(n)
        vector<int> cacheB(n+1, 0);
        for (int j = 1; j <= n; j++) {
            cacheB[j] = cacheB[j-1] + locales[j].beneficio;
        }

        maximum = npm_bt_poda_opt_cache(n, M, vecinos, locales, 0, maximoBeneficio, cacheB);
    } else if (algorithm == "DP") {
        auto mem = vector<vector<int>>(n+1, vector<int>(M+1, MEM_UNDEFINED));
        bool initial_vecino = true;
        maximum = npm_pd(n, M, locales, mem);
    } else if (algorithm == "GR") {
        vector<vector<int>> accesses(n+1, vector<int>(M+1, 0));
        grado_solapamiento(n, M, locales, accesses);
        json result = {{"pd_accesses", accesses}};
        clog << result << endl;
    }

    // roba2 de gonza
    auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecucion por stderr
    clog << total_time << endl;

    // Imprimimos el resultado por stdout
    cout << maximum << endl;
}