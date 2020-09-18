#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

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

    vector<pair<int, int>> locales(n, make_pair(0, 0));
    for (int i = 0; i < n; ++i) {
        int beneficio = 0;
        int costo = 0;
        cin >> beneficio >> costo;
        locales[i] = make_pair(beneficio, costo);
    }

    // Corremos el algoritmo
    if (algorithm == "FB") {
        cout << "No implementado aun :(" << endl;
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