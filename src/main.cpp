#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

constexpr int INVALID_INSTANCE = 0;
constexpr int MEM_UNDEFINED = -1;

struct Local {
    int beneficio;
    int contagio;
};

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
    stable_sort(locales.begin()+(i+1), locales.end(), compareLocales);
    int contagioAcumulado = 0;
    int beneficioMaximo = 0;
    for (Local local : locales) {
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

// backtracking()
// Complejidad temporal: O(n^2 * 2^n)
int BT(vector<Local> &locales, int n, int M, vector<bool> &pertenencia, int i, bool podaFactibilidad, bool podaOptimalidad, int beneficioAcumulado, int &maximoBeneficio) {
    // Poda de factibilidad
    if (podaFactibilidad && M < 0) return INVALID_INSTANCE;

    if (i == n+1) {
        if (M < 0) return INVALID_INSTANCE;

        for (int j = 1; j < n; ++j) {
            if (pertenencia[j] && pertenencia[j+1]) return INVALID_INSTANCE;
        }

        return beneficioAcumulado;
    }

    // El máximo beneficio restante no puede cortar en casos incorrectos debido a que es una sobreestimación del
    // máximo beneficio real que se puede obtener si se continúa por esta rama.
    if (podaOptimalidad && maximoBeneficioRestante(locales, i, M) + beneficioAcumulado < maximoBeneficio) return INVALID_INSTANCE;

    int maximoBeneficioLocal = max(
            BT(locales, n, M, unset(pertenencia, i), i+1, podaFactibilidad, podaOptimalidad, beneficioAcumulado, maximoBeneficio),
            BT(locales, n, M-locales[i].contagio, set(pertenencia, i), i+1, podaFactibilidad, podaOptimalidad, beneficioAcumulado + locales[i].beneficio, maximoBeneficio)
    );

    maximoBeneficio = max(maximoBeneficio, maximoBeneficioLocal);

    return maximoBeneficioLocal;
}

// programacionDinamica va de i=n a i=0
// PD(locales, M, <pertenencia>, i=n, <mem>, beneficio=0)
int PD(vector<Local> &locales, int M, vector<bool> &pertenencia, int i, vector<vector<int>> &mem) {
    // Poda por factibilidad: si nos pasamos el limite de contagio, no es
    // necesario seguir viendo esta rama (propiedad dominó)
    if (M < 0) return INVALID_INSTANCE;

    // Parte 1: lectura de la tabla de memoización
    if (mem[i][M] == MEM_UNDEFINED) {
        if (i == 0) {
            // Caso base
            mem[i][M] = 0;
        } else {
            // Caso recursivo
            bool tieneLocalVecino = (i < pertenencia.size() && pertenencia[i+1]);

            mem[i][M] = max(
                    PD(locales, M, unset(pertenencia, i), i - 1, mem),
                    tieneLocalVecino ?
                        INVALID_INSTANCE :
                        PD(locales, M - locales[i].contagio, set(pertenencia, i), i - 1, mem) + locales[i].beneficio
            );
        }
    }

    return mem[i][M];
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

    vector<bool> pertenencia(n+1, false); // Acumulador de los locales incluidos en la solución parcial
    vector<Local> locales(n+1, Local{0,0});
    for (int i = 1; i <= n; ++i) {
        std::cin >> locales[i].beneficio >> locales[i].contagio;
    }

    // Corremos el algoritmo
    if (algorithm == "FB") {
        cout << fuerzaBruta(locales, n, M, pertenencia, 0) << endl;
    } else if (algorithm == "BT") {
        int maximoBeneficio = 0;
        cout << BT(locales, n, M, pertenencia, 0, true, true, 0, maximoBeneficio) << endl;
    } else if (algorithm == "BT-F") {
        int maximoBeneficio = 0;
        cout << BT(locales, n, M, pertenencia, 0, true, false, 0, maximoBeneficio) << endl;
    } else if (algorithm == "BT-O") {
        int maximoBeneficio = 0;
        cout << BT(locales, n, M, pertenencia, 0, false, true,  0, maximoBeneficio) << endl;
    } else if (algorithm == "DP") {
        auto mem = vector<vector<int>>(n+1, vector<int>(M+1, MEM_UNDEFINED));
        for (int i = 0; i < M+1; ++i) {
            mem[0][i] = 0;
        }
        for (int j = 0; j < n+1; ++j) {
            mem[j][0] = 0;
        }
        cout << PD(locales, M, pertenencia, n, mem) << endl;
    }
}