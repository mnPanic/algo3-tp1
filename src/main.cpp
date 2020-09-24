#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

constexpr int INVALID_INSTANCE = 0;
constexpr int INF = 1e6;

struct Local {
    int beneficio;
    int contagio;
};

struct Resultado {
    int set;
    int unset;
};

Resultado MEM_UNDEFINED = Resultado{-1, -1};
bool mem_undefined(Resultado r) {
    return r.set == MEM_UNDEFINED.set && r.unset == MEM_UNDEFINED.unset;
}

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

bool compareLocales(Local A, Local B) {
    float ratioA = A.beneficio/A.contagio;
    float ratioB = B.beneficio/B.contagio;

    return (ratioA < ratioB);
}

int maximoBeneficioRestante(vector<Local> locales, int i, int M) {
    stable_sort(locales.begin()+1, locales.begin()+1+i, compareLocales);
    int contagioAcumulado = 0;
    int beneficioMaximo = 0;
    for (int j = 1; j < i + 1; j++) {
        Local local = locales[j];
        contagioAcumulado += local.contagio;
        if (contagioAcumulado < M) return beneficioMaximo;
        beneficioMaximo += local.beneficio;
    }

    return beneficioMaximo;
}

/** Funciones principales **/

// fuerzaBruta
// Algoritmo recursivo de fuerza bruta
// Complejidad temporal: O(n * 2^n)
//
// Asumimos que existe al menos un local que tenga contagio inferior a M
int fuerzaBruta(vector<Local> &locales, int n, int M, vector<bool> &pertenencia, int i) {
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
        fuerzaBruta(locales, n, M, unset(pertenencia, i), i+1),
        fuerzaBruta(locales, n, M, set(pertenencia, i), i+1)
    );
}

// NPM con backtracking con podas de factibilidad
// Complejidad temporal: O(n^2 * 2^n)
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

// NPM con backtracking con podas de optimalidad
// Complejidad temporal: O(n^2 * 2^n)
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
    if (maximoBeneficioRestante(ls, i, M) + B < maxB) return -INF;

    // Llamado recursivo
    int maxBLocal = max(
        npm_bt_poda_opt(i-1, M - ls[i].contagio, set(vecinos, i), ls, B + ls[i].beneficio, maxB),
        npm_bt_poda_opt(i-1, M, unset(vecinos, i), ls, B, maxB)
    );

    maxB = max(maxB, maxBLocal);

    return maxBLocal;
}

// NPM con backtracking con podas de optimalidad Y factibilidad
// Complejidad temporal: O(n^2 * 2^n)
int npm_bt(int i, int M, vector<bool> &vecinos, vector<Local> &ls, int B, int &maxB) {
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
    if (maximoBeneficioRestante(ls, i, M) + B < maxB) return -INF;

    // Llamado recursivo
    int maxBLocal = max(
        npm_bt_poda_opt(i-1, M - ls[i].contagio, set(vecinos, i), ls, B + ls[i].beneficio, maxB),
        npm_bt_poda_opt(i-1, M, unset(vecinos, i), ls, B, maxB)
    );

    maxB = max(maxB, maxBLocal);

    return maxBLocal;
}

// NPM por programacion dinamica
// Complejidad temporal: O(n * M)
int npm_pd(int i, int M, bool vecino, vector<Local> &ls, vector<vector<Resultado>> &mem) {
    // Si nos pasamos del limite de contagio no es una instancia valida
    if (M < 0) return -INF;

    // Caso base
    if (i == 0) return 0;

    // Llamado recursivo
    if (mem_undefined(mem[i][M])) {
        // Memoizamos siempre el valor "feliz", sin importarnos del contexto de
        // donde venimos, para que asi este caso sea independiente de los
        // anteriores.
        mem[i][M] = Resultado{
            .set   = npm_pd(i-1, M - ls[i].contagio, true /* vecino */, ls, mem) + ls[i].beneficio,
            .unset = npm_pd(i-1, M, false /* vecino */, ls, mem)
        };
    }

    Resultado res = mem[i][M];

    // Pero antes de retornar lo memoizado, debemos verificar que la
    // solución devuelta cumpla con la restricción de locales vecinos.
    // Esto solo puede suceder si la "ganadora" del llamado recursivo fue en
    // la que nos pusimos, y en caso de que nuestro vecino tambien este,
    // volvemos atras y retornamos el valor de la rama opuesta.
    if (res.set > res.unset && vecino) {
        return res.unset;
    }

    return max(res.set, res.unset);
}

int main(int argc, char** argv) {
	map<string, string> algorithms = {
		{"FB", "Fuerza Bruta"},
        {"BT", "Backtracking con podas"},
        {"BT-F", "Backtracking con poda por factibilidad"}, 
		{"BT-O", "Backtracking con poda por optimalidad"},
        {"DP", "Programacion dinámica"},
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
    if (algorithm == "FB") {
        cout << fuerzaBruta(locales, n, M, vecinos, 0) << endl;
    } else if (algorithm == "BT") {
        int maximoBeneficio = 0;
        cout << npm_bt(n, M, vecinos, locales, 0, maximoBeneficio) << endl;
    } else if (algorithm == "BT-F") {
        int maximoBeneficio = 0;
        cout << npm_bt_poda_fact(n, M, vecinos, locales) << endl;
    } else if (algorithm == "BT-O") {
        int maximoBeneficio = 0;
        cout << npm_bt_poda_opt(n, M, vecinos, locales, 0, maximoBeneficio) << endl;
    } else if (algorithm == "DP") {
        auto mem = vector<vector<Resultado>>(n+1, vector<Resultado>(M+1, MEM_UNDEFINED));
        bool initial_vecino = true;
        cout << npm_pd(n, M, false, locales, mem) << endl;
    }
}