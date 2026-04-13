//poner cout y cin
#include <iostream>
//leer y escribir archivos
#include <fstream>
//Usar conjuntos de char para palabras
#include <string>
//usar listas dinamicas
#include <vector>
//Usar un string como una base de datos para elegir elementos
#include <sstream>
//Atajo para no usar std::
using namespace std;

//STRUCTS: (Listas vacias para guardar la info de la config, los partidos y los resultados de cada equipo)
struct ConfigLiga {
    string nombre;
    int victoria, empate, derrota;
    vector<string> equipos;
};

struct Partido {
    string liga;
    int jornada;
    string local, visitante;
    int golesLocal, golesVisitante;
};

struct Equipo {
    string nombre;
    int PJ=0, PG=0, PE=0, PP=0, GF=0, GC=0, DG=0, PTS=0;
};

// ── DECLARACIONES DE FUNCIONES ───────────────────────
bool leerConfig(string ruta, ConfigLiga& cfg);
void leerPartidos(string ruta, vector<Partido>& partidos);
void guardarPartido(string ruta, Partido p);
void guardarEnFechas(string ruta, Partido p);
void actualizarEquipo(Equipo* eq, int gf, int gc, int pts); // puntero obligatorio
void construirTabla(vector<Partido>& partidos, ConfigLiga& cfg, vector<Equipo>& tabla);
void ordenarTabla(vector<Equipo>& tabla);
void mostrarTabla(vector<Equipo>& tabla);
void mostrarJornada(string ruta, int jornada, int numPartidos);
char mostrarMenu(string liga);
bool ingresarPartido(ConfigLiga& cfg, Partido& p);

int main() {
    //Crear la copia interna de config.txt
    ConfigLiga cfg;
    //si no puede leerse txt ni crearse la copia, error
    if (!leerConfig("data/config.txt", cfg)) {
        cout << "No se puede leer config.txt, reinicie el codigo\n";
        return 1;
    }
    //Si existe el registros.txt lo lee, si no lo crea y le pone el 0
    int NumPartidos = 0;
    ifstream reg_in("data/registros.txt");
    if (reg_in.is_open()) {
        reg_in >> NumPartidos;
        reg_in.close();
    } else {
        ofstream reg_out("data/registros.txt");
        reg_out << 0;
        reg_out.close();
    }
    //Mostrar Menu
    char opcion;
    do {
        opcion = mostrarMenu(cfg.nombre);
        //Si elige registrar resultados
        if (opcion == 'r') {
            char registro = 'y';
            do {
                Partido p;//Crea un Partido vacío
                if (ingresarPartido(cfg, p)) { //Llama a la funcion ingresar partido y lo valida
                    p.liga = cfg.nombre; //asigna el nombre de la liga la que esta en el struc config
                    guardarPartido("data/partidos.txt", p);//Guarda el registro completo en este
                    guardarEnFechas("data/fechas.txt", p);//Guarda por jornadas en este
                    NumPartidos++;
                    ofstream reg_out("data/registros.txt");//reemplaza en registros el nuevo partido
                    reg_out << NumPartidos;
                    reg_out.close();//Lo cierra para volverlo a remplazar en un futuro
                    cout << "Partido #" << NumPartidos << " creado.\n";
                }
                cout << "Quiere crear un nuevo partido? y/n:\n";
                cin >> registro;
            } while (registro == 'y');
        
        } else if (opcion == 'h') {//Si elige la h
            char verOtra = 'y';//ver otra vez los registros
            do {
                int jornada;
                cout << "Que jornada quiere consultar? ";
                cin >> jornada;
                if (jornada < 1) {
                    cout << "La jornada debe ser 1 o mayor\n";
                } else {
                    mostrarJornada("data/fechas.txt", jornada, NumPartidos);//llamar a la funcion 
                }
                cout << "Quiere ver otra jornada? y/n: ";
                cin >> verOtra;
            } while (verOtra == 'y'); // repetir si pone y si pone cualquier otra cosa vuelve al menu

        } else if (opcion == 'p') {
            vector<Partido> partidos;
            leerPartidos("data/partidos.txt", partidos);
            if (partidos.empty()) {//Si esta en blanco poner lo siguiente
                cout << "No hay partidos registrados aun\n";
            } else {
                cout << "\n#  | Liga           | Local       | Visitante   | GL | GV | Jornada\n";
                cout << "-------------------------------------------------------------------\n";
                for (int i = 0; i < partidos.size(); i++) {//Por cada linea ponder el Num de partido y su info
                    cout << i+1 << "  | "
                         << partidos[i].liga      << " | "
                         << partidos[i].local      << " | "
                         << partidos[i].visitante  << " | "
                         << partidos[i].golesLocal << " | "
                         << partidos[i].golesVisitante << " | "
                         << partidos[i].jornada    << "\n";
                }
            }
        
        
        } else if (opcion == 't') {
            vector<Partido> partidos;
            leerPartidos("data/partidos.txt", partidos);
            if (partidos.empty()) {
                cout << "No hay partidos registrados aun\n";
            } else {
                vector<Equipo> tabla;
                construirTabla(partidos, cfg, tabla);//crea la tabla y la ordena
                ordenarTabla(tabla);
                mostrarTabla(tabla);

                char guardar;
                cout << "\nDesea guardar la tabla en tabla.txt? y/n: ";
                cin >> guardar;
                if (guardar == 'y') {
                    ofstream archivo("data/tabla.txt");//crear tabla si el usuario quiere
                    if (archivo.is_open()) {
                        archivo << "#  | Equipo      | PJ | PG | PE | PP | GF | GC | DG  | PTS\n";
                        archivo << "-------------------------------------------------------------\n";
                        for (int i = 0; i < tabla.size(); i++) {
                            archivo << i+1 << "  | " //Lista de equipos
                                    << tabla[i].nombre << " | "
                                    << tabla[i].PJ << " | "
                                    << tabla[i].PG << " | "
                                    << tabla[i].PE << " | "
                                    << tabla[i].PP << " | "
                                    << tabla[i].GF << " | "
                                    << tabla[i].GC << " | "
                                    << tabla[i].DG << " | "
                                    << tabla[i].PTS << "\n";//Despues de ganar todo eso, saltar de linea y repetir
                        }
                        archivo.close();
                        cout << "Tabla guardada en tabla.txt\n";
                    } else {
                        cout << "No se pudo crear tabla.txt\n";
                    }
                }
            }
        
        } else if (opcion == 's') {
            cout << "Adios\n";

        } else if (opcion != 'm') {
            cout << "Porfavor ingrese un comando valido\n";
        }
        
        

    } while (opcion != 's');

    return 0;
}

//DEFINICIONES DE FUNCIONES:

bool leerConfig(string ruta, ConfigLiga& cfg) {//Leer Configuración y leer el original
    ifstream archivo(ruta);//la ruta del txt
    if (!archivo.is_open()) return false;

    string linea;
    while (getline(archivo, linea)) {// get line del archivo por cada linea
        if (linea.empty() || linea[0] == '#') continue; // Salta lineas vacías y comentarios

        stringstream ss(linea); //Lee todo el documento como un solo string y saca pedazos
        string clave, valor;
        getline(ss, clave, '=');//lee hasta encontrar un =, de ahí lee la clave que es el nombre
        getline(ss, valor);//Lee el resto de la linea y lee el nombre de la liga

        if      (clave == "nombre")   cfg.nombre   = valor; //asigna el valor al campo del struct
        else if (clave == "victoria") cfg.victoria = stoi(valor);//el stoi convierte string a int
        else if (clave == "empate")   cfg.empate   = stoi(valor);
        else if (clave == "derrota")  cfg.derrota  = stoi(valor);
        else if (clave == "equipo")   cfg.equipos.push_back(valor);//Si en la siguiente linea encuentra un (clave == "equipo") entonces agrega un equipo mas
    }
    archivo.close();
    return !cfg.nombre.empty() && !cfg.equipos.empty();//sigue con el getline solo si leyó el siguiente renglon un nombre y equipo
}

char mostrarMenu(string liga) {//mostrar menu de la liga
    char opcion;
    cout << "\n=== Liga " << liga << " ===\n";
    cout << "m - Ver este menu\n";
    cout << "t - Ver tabla de posiciones\n";
    cout << "r - Registrar resultado de un partido\n";
    cout << "h - Ver historial de jornadas\n";
    cout << "p - Ver todos los partidos jugados\n";
    cout << "s - Salir\n";
    cout << "Opcion: ";
    cin >> opcion;
    return opcion;
}

bool ingresarPartido(ConfigLiga& cfg, Partido& p) {//Que el cfg se modifique en el archivo original y partidos igual en partidos.txt
    cout << "\nEquipos disponibles:\n";
    for (int i = 0; i < cfg.equipos.size(); i++) {//Leer los equipos de configuración y darlos
        cout << "  " << cfg.equipos[i] << "\n";
    }

    cout << "Equipo local: ";    cin >> p.local;
    cout << "Equipo visitante: "; cin >> p.visitante;

    // Validar que existan en la liga
    bool localValido = false, visitanteValido = false;
    for (int i = 0; i < cfg.equipos.size(); i++) {
        if (cfg.equipos[i] == p.local)     localValido = true; //Si al menos un nombre coincide con el que se ingresó
        if (cfg.equipos[i] == p.visitante) visitanteValido = true; //igual aqui
    }

    if (!localValido || !visitanteValido) {
        cout << "Uno o ambos equipos no pertenecen a la liga\n";
        return false;
    }
    if (p.local == p.visitante) {//que los equipos no sean los mismos
        cout << "Los equipos no pueden ser los mismos\n";
        return false;
    }

    cout << "Goles local visitante (ej: 3 1): ";
    cin >> p.golesLocal >> p.golesVisitante;
    if (p.golesLocal < 0 || p.golesVisitante < 0) {
        cout << "Los marcadores no pueden ser negativos\n";
        return false;
    }

    cout << "Numero de jornada: ";
    cin >> p.jornada;
    if (p.jornada < 1) {
        cout << "La jornada debe ser 1 o mayor\n";
        return false;
    }

    return true;
}

void guardarPartido(string ruta, Partido p) {
    ofstream archivo(ruta, ios::app);//guardar en append los partidos para que no se reinicie el txt
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << ruta << "\n";
        return;
    }
    // Formato: liga|jornada|local|visitante|golesLocal|golesVisitante
    archivo << p.liga << "|" << p.jornada << "|"
            << p.local << "|" << p.visitante << "|"
            << p.golesLocal << "|" << p.golesVisitante << "\n";//Poner los datos y saltar a siguiente linea
    archivo.close();
}

void guardarEnFechas(string ruta, Partido p) {
    ofstream archivo(ruta, ios::app);//igual para fechas
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << ruta << "\n";
        return;
    }
    // Formato: jornada|local|visitante|golesLocal|golesVisitante
    archivo << p.jornada << "|"
            << p.local << "|" << p.visitante << "|"
            << p.golesLocal << "|" << p.golesVisitante << "\n";
    archivo.close();
}

void leerPartidos(string ruta, vector<Partido>& partidos) {//hacer lista dinamica de partidos
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << ruta << "\n";
        return;
    }
    string linea;
    while (getline(archivo, linea)) {//getline del archivo por cada linea
        if (linea.empty()) continue; //saltar lineas vacias
        stringstream ss(linea); //usar stringstream de todo el documento
        string campo;//ver en que campo esta cada cosa
        Partido p;//cada partido por linea

        getline(ss, p.liga,      '|');//Pone la liga
        getline(ss, campo,       '|'); p.jornada       = stoi(campo);//leer hasta | y despues leer jornada y pasarlo a int
        getline(ss, p.local,     '|');//leer hasta | y poner local
        getline(ss, p.visitante, '|');//leer hasta | y poner visitante
        getline(ss, campo,       '|'); p.golesLocal     = stoi(campo);//Lee primero Gl y pone GL en int
        getline(ss, campo,       '|'); p.golesVisitante = stoi(campo);//Le  e primero GL y pone GV en int

        partidos.push_back(p); //Asegurarse de que en la linea siguiente haya cada una de esas cosas, sino parar
    }
    archivo.close();
}

void mostrarJornada(string ruta, int jornada, int numPartidos) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << ruta << "\n";
        return;
    }

    bool hayPartidos = false;
    string linea;
    cout << "\n--- Jornada " << jornada << " ---\n";

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string campo;
        int numJornada, gl, gv;
        string local, visitante;

        getline(ss, campo,     '|'); numJornada = stoi(campo);
        getline(ss, local,     '|');
        getline(ss, visitante, '|');
        getline(ss, campo,     '|'); gl = stoi(campo);
        getline(ss, campo,     '|'); gv = stoi(campo); //Leer la info con getline

        if (numJornada == jornada) {
            cout << local << " VS " << visitante
                 << " | " << gl << " - " << gv << "\n";
            hayPartidos = true;
        }
    }

    if (!hayPartidos) {
        cout << "No hay partidos registrados para esa jornada\n";
    }
    archivo.close();
}

// Puntero, modifica el Equipo directamente
void actualizarEquipo(Equipo* eq, int gf, int gc, int pts) {  //Muestra la dirección donde este un Equipo
    eq->PJ++;  // el -> es para acceder a campos a traves de un puntero es como decir (*eq).PJ++ (Si se encuentra un equipo de tal nombre que se agregue un partido jugado mas)
    eq->GF += gf;  //Sumar todos los goles a favor
    eq->GC += gc;  //Sumar todos los goles en contra
    eq->DG += (gf - gc);  //Sumar todas las diferencias de goles
    eq->PTS += pts;  //sumar todos los puntos
    if (pts > 0 && gf > gc)       eq->PG++;  // ganó
    else if (gf == gc)             eq->PE++;  // empató
    else                           eq->PP++;  // perdió
}

void construirTabla(vector<Partido>& partidos, ConfigLiga& cfg, vector<Equipo>& tabla) {
    // Crear un Equipo por cada equipo de la config
    for (int i = 0; i < cfg.equipos.size(); i++) {
        Equipo e;
        e.nombre = cfg.equipos[i];
        tabla.push_back(e);  //Asi hasta que se quede sin equipos
    }

    // Por cada partido, actualizar los dos equipos usando puntero leyendo los partidos
    for (int i = 0; i < partidos.size(); i++) {
        int gl = partidos[i].golesLocal;
        int gv = partidos[i].golesVisitante;

        // Buscar equipo local y visitante en la tabla
        for (int j = 0; j < tabla.size(); j++) {
            if (tabla[j].nombre == partidos[i].local) { // Por cada partido, busca al equipo local y al visitante en la tabla, y actualiza sus estadísticas.    
                if (gl > gv)      actualizarEquipo(&tabla[j], gl, gv, cfg.victoria);
                else if (gl == gv) actualizarEquipo(&tabla[j], gl, gv, cfg.empate);
                else              actualizarEquipo(&tabla[j], gl, gv, cfg.derrota);
            }
            if (tabla[j].nombre == partidos[i].visitante) {
                if (gv > gl)      actualizarEquipo(&tabla[j], gv, gl, cfg.victoria);
                else if (gv == gl) actualizarEquipo(&tabla[j], gv, gl, cfg.empate);
                else              actualizarEquipo(&tabla[j], gv, gl, cfg.derrota);
            }
        }
    }
}

//Selection Sort. Compara cada par de elementos y los intercambia si están en el orden incorrecto
// Ordena por puntos; desempate por DG y luego GF
void ordenarTabla(vector<Equipo>& tabla) {
    for (int i = 0; i < tabla.size() - 1; i++) {
        for (int j = i + 1; j < tabla.size(); j++) {
            bool cambiar = false;
            if (tabla[j].PTS > tabla[i].PTS) cambiar = true;
            else if (tabla[j].PTS == tabla[i].PTS && tabla[j].DG > tabla[i].DG) cambiar = true;
            else if (tabla[j].PTS == tabla[i].PTS && tabla[j].DG == tabla[i].DG && tabla[j].GF > tabla[i].GF) cambiar = true;
// Compara por puntos -> Compara por diferencia de goles -> Compara por goles a favor
            if (cambiar) {
                Equipo temp = tabla[i];
                tabla[i] = tabla[j];
                tabla[j] = temp;
            }
        }
    }
}

void mostrarTabla(vector<Equipo>& tabla) {
    cout << "\n#  | Equipo      | PJ | PG | PE | PP | GF | GC | DG  | PTS\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < tabla.size(); i++) {  //Para cada renglon poner la tabla
        cout << i+1 << "  | "
             << tabla[i].nombre << " | "
             << tabla[i].PJ  << " | "
             << tabla[i].PG  << " | "
             << tabla[i].PE  << " | "
             << tabla[i].PP  << " | "
             << tabla[i].GF  << " | "
             << tabla[i].GC  << " | "
             << tabla[i].DG  << " | "
             << tabla[i].PTS << "\n";
    }
}