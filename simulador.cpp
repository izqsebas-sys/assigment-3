#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int MAX_CYL = 5000;
const int NUM_REQ = 1000;

//---------------------------------------------------------
// ALGORTIMOS DE PLANIFICACIÓN DE DISCO
//---------------------------------------------------------

int algoritmo_fcfs(const vector<int>& solicitudes, int inicio, vector<int>& recorrido) {
    int desplazamiento = 0;
    int pos = inicio;

    recorrido.push_back(pos);

    for (int s : solicitudes) {
        desplazamiento += abs(pos - s);
        pos = s;
        recorrido.push_back(pos);
    }

    return desplazamiento;
}

int algoritmo_scan(vector<int> solicitudes, int inicio, vector<int>& recorrido) {
    int desplazamiento = 0;
    int pos = inicio;

    vector<int> menores, mayores;

    for (int s : solicitudes) {
        (s < inicio ? menores : mayores).push_back(s);
    }

    sort(menores.rbegin(), menores.rend());
    sort(mayores.begin(), mayores.end());

    recorrido.push_back(pos);

    // Recorriendo hacia la derecha
    for (int s : mayores) {
        desplazamiento += abs(pos - s);
        pos = s;
        recorrido.push_back(pos);
    }

    // Llegar al final del disco
    if (pos != MAX_CYL - 1) {
        desplazamiento += abs(pos - (MAX_CYL - 1));
        pos = MAX_CYL - 1;
        recorrido.push_back(pos);
    }

    // Recorriendo hacia la izquierda
    for (int s : menores) {
        desplazamiento += abs(pos - s);
        pos = s;
        recorrido.push_back(pos);
    }

    return desplazamiento;
}

int algoritmo_cscan(vector<int> solicitudes, int inicio, vector<int>& recorrido) {
    int desplazamiento = 0;
    int pos = inicio;

    vector<int> menores, mayores;
    for (int s : solicitudes) {
        (s < inicio ? menores : mayores).push_back(s);
    }

    sort(menores.begin(), menores.end());
    sort(mayores.begin(), mayores.end());

    recorrido.push_back(pos);

    // Recorrer hacia arriba
    for (int s : mayores) {
        desplazamiento += abs(pos - s);
        pos = s;
        recorrido.push_back(pos);
    }

    // Llegar al extremo derecho
    if (pos != MAX_CYL - 1) {
        desplazamiento += abs(pos - (MAX_CYL - 1));
        pos = MAX_CYL - 1;
        recorrido.push_back(pos);
    }

    // Salto circular
    desplazamiento += (MAX_CYL - 1);
    pos = 0;
    recorrido.push_back(pos);

    // Atender solicitudes menores
    for (int s : menores) {
        desplazamiento += abs(pos - s);
        pos = s;
        recorrido.push_back(pos);
    }

    return desplazamiento;
}

//---------------------------------------------------------
// GENERACIÓN DE SALIDA PARA GNUPLOT
//---------------------------------------------------------

void exportar_recorrido(const string& archivo, const vector<int>& datos) {
    ofstream out(archivo);
    for (int i = 0; i < datos.size(); i++)
        out << i << " " << datos[i] << "\n";
}

void exportar_rendimiento(const string& archivo, int fcfs, int scan, int cscan) {
    ofstream out(archivo);
    out << "FCFS " << fcfs << "\n";
    out << "SCAN " << scan << "\n";
    out << "C-SCAN " << cscan << "\n";
}

void mostrar_graficas() {
    system("start gnuplot -p plot_paths.gp");
    system("start gnuplot -p plot_bars.gp");
}

//---------------------------------------------------------
// PROGRAMA PRINCIPAL
//---------------------------------------------------------

int main() {
    srand(time(NULL));

    int inicio;
    cout << "Posición inicial del cabezal (0 - " << MAX_CYL - 1 << "): ";
    cin >> inicio;

    if (inicio < 0 || inicio >= MAX_CYL) {
        cout << "Error: posición fuera de rango.\n";
        return 1;
    }

    vector<int> solicitudes(NUM_REQ);
    for (int& x : solicitudes)
        x = rand() % MAX_CYL;

    vector<int> ruta_fcfs, ruta_scan, ruta_cscan;

    int d_fcfs = algoritmo_fcfs(solicitudes, inicio, ruta_fcfs);
    int d_scan = algoritmo_scan(solicitudes, inicio, ruta_scan);
    int d_cscan = algoritmo_cscan(solicitudes, inicio, ruta_cscan);

    exportar_recorrido("fcfs.dat", ruta_fcfs);
    exportar_recorrido("scan.dat", ruta_scan);
    exportar_recorrido("cscan.dat", ruta_cscan);
    exportar_rendimiento("performance.dat", d_fcfs, d_scan, d_cscan);

    mostrar_graficas();

    cout << "\n=== RESULTADOS DEL SIMULADOR ===\n";
    cout << "FCFS   desplazamiento: " << d_fcfs << " cilindros\n";
    cout << "SCAN   desplazamiento: " << d_scan << " cilindros\n";
    cout << "C-SCAN desplazamiento: " << d_cscan << " cilindros\n";

    return 0;
}
