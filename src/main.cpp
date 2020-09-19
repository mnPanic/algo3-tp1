#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

constexpr int INVALID_INSTANCE = -1;
constexpr int UNDEFINED = -1;

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

string pertenenciaToString(vector<bool> &vs) {
    string res = "";

    for (bool v : vs) {
        res += v? "1 " : "0 ";
    }

    return res;
}

/** Funciones principales **/

// fuerzaBruta
// Algoritmo recursivo de fuerza bruta
// Complejidad temporal: O(n * 2^n)
//
// Asumimos que existe al menos un local que tenga contagio inferior a M
int fuerzaBruta(vector<Local> &locales, int n, int M, vector<bool> &pertenencia, int i) {
//    cout << "Estamos recorriendo el local: " << i << " con el vector " << pertenenciaToString(pertenencia) << endl;
    if (i == n) {
        int beneficioAcumulado = 0;
        int contagioAcumulado = 0;

        for (int j = 0; j < n; ++j) {
            if (j != n-1 && pertenencia[j] && pertenencia[j+1]) {
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
int backtracking(vector<Local> &locales, int n, int M, vector<bool> &pertenencia, int i) {
    return 0;
}

// programacionDinamica()
int programacionDinamica(vector<Local> &locales, int n, int M, vector<bool> &pertenencia, int i, vector< vector<int>> &mem) {
    if (M < 0) {
        return INVALID_INSTANCE;
    }

    // Parte 1: lectura de la tabla de memoización
    if (mem[M][i] != UNDEFINED) {
        return mem[M][i];
    }

    // Caso base
    if (i == n) {
        int beneficioAcumulado = 0;

        for (int j = 0; j < n; ++j) {
            if (pertenencia[j]) {
                beneficioAcumulado += locales[j].beneficio;
            }
        }

        return beneficioAcumulado;
    }

    int maximoBeneficio = max(
            fuerzaBruta(locales, n, M, unset(pertenencia, i), i+1),
            pertenencia[i] ? fuerzaBruta(locales, n, M, set(pertenencia, i), i+1) : -1
    );

    // Parte 2: escritura de la tabla de memoización
    mem[M][i] = maximoBeneficio;

    return maximoBeneficio;
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
    cin >> n >> M;

    vector<bool> pertenencia(n, false); // Acumulador de los locales incluidos en la solución parcial
    vector<Local> locales(n, Local{0,0});
    for (int i = 0; i < n; ++i) {
        cin >> locales[i].beneficio >> locales[i].contagio;
    }

    // Corremos el algoritmo
    if (algorithm == "FB") {

        cout << fuerzaBruta(locales, n, M, pertenencia, 0) << endl;
    }
    else if (algorithm == "BT") {
        cout << "No implementado aun :(" << endl;
    }
    else if (algorithm == "BT-F") {
        cout << "No implementado aun :(" << endl;
    }
    else if (algorithm == "BT-O") {
        cout << "No implementado aun :(" << endl;
    }
    else if (algorithm == "DP") {
        cout << "No implementado aun :(" << endl;
    }
}