#include <iostream>
    #include <fstream>
    #include <string>
    using namespace std;
    
    int main () {
        //Identifica el archivo inicial y externos (paso 1)
        ifstream config("data/config.txt");
        ofstream partidos("data/partidos.txt", ios::app);
        ofstream fechas("data/fechas.txt", ios::app);
        ifstream registros("data/registros.txt");
         ifstream fechas_in("data/fechas.txt");
        //variables de configuracion (paso 1)
        string liga;
        int victoria, empate, derrota;
        string equipos[5];
        string local;
        string visitante;
        int marcadorlocal, marcadorvisitante;
        int NumPartidos = 0;
        int NumFecha;
        char respuesta;
        char registro;
        char verjornada;
        //ver si config esta abierto y si no poner error (paso 2)
        if (config.is_open()) {
          config >> liga >> victoria >> empate >> derrota;
          for (int i = 0; i < 5; i++) {
              config >> equipos[i];
          }
          if (registros.is_open()){
              registros>>NumPartidos;
              registros.close();
        do { //Menu (paso 3)
            cout<<"Hola, bienvenido a la liga "<<liga<<"! Que desearia hacer?\n";
            cout<<"Presione m si quiere ver este menu de nuevo\n";
            cout<<"Presione t si quiere ver la tabla de posiciones\n";
            cout<<"Presione r si quiere registrar el resultado de un partido\n";
            cout<<"Presione h si quiere ver el historial de jornadas\n";
            cout<<"Presione p si quiere ver todos los partidos jugados\n";
            cout<<"Presione s si quiere salir\n";
            cin>>respuesta;
            
        //Hacer cada opción (paso 4)
        if (respuesta == 'm') {//paso 5
            
        //Registrar resultados
        } else if (respuesta == 'r') { //paso 5
        do { //paso 7 do
        //el if de si pone si empieza aqui
        cout<<"Equipos Disponibles:\n";
        //lista de equipos
        for (int i = 0; i <5; i++) {
            cout<<equipos[i]<<", ";
        }
        cout<<"\n";
        //Equipo Local
        cout<<"Elige el equipo local:\n";
        //Elegir equipo
        cin>>local;
        //Equipo Visitante
        cout<<"Elige el equipo visitante:\n";
        //Elegir equipo
        cin>>visitante;
        //poner que porfavor ponga otra cosa
        
        //Marcador final
        cout<<"Pon el marcador final del equipo local (espacio) equipo visitante:\n";
        //marcador
        cin>>marcadorlocal >> marcadorvisitante;
        //Fecha
        cout<<"Cual es la fecha de este partido? (Coloque un numero entero desde el 1):\n";
        //NumFecha
        cin>>NumFecha;
        
        //validar que equipo local sea distinto 
        if (local == visitante){
            cout<<"Los equipos no pueden ser los mismos\n";
            respuesta = 'm';
        } else if(
            (local != equipos[0] &&
            local != equipos[1] &&
            local != equipos[2] &&
            local != equipos[3] &&
            local != equipos[4]) ||
            (visitante != equipos[0] &&
            visitante != equipos[1] &&
            visitante != equipos[2] &&
            visitante != equipos[3] &&
            visitante != equipos[4])
            ) {
            cout<<"Porfavor seleccione equipos que esten en la liga\n";
            respuesta = 'm';
            } else if (marcadorlocal < 0 || marcadorvisitante < 0){
            cout<<"Porfavor ingrese marcadores no sean numeros negativos\n";
            respuesta = 'm';
            } else if (NumFecha < 1) {
                cout<<"Coloque una fecha desde uno en adelante\n";
                respuesta = 'm';
        
        //Que pasa si se dieron bien las instrucciones   
        } else {
            if (partidos.is_open()) {
                //liga;ganador;perdedor;goles del ganador;goles del perdedor;dif de goles;puntos ganador; puntos perdedor"
    	    partidos<<liga<<" ";
    	    //Gana el local
                if (marcadorlocal > marcadorvisitante) {
                    int dif = marcadorlocal - marcadorvisitante;
                    partidos<<local<<" ";
                    partidos<<visitante<<" ";
                    partidos<<marcadorlocal<<" ";
                    partidos<<marcadorvisitante<<" ";
                    partidos<<dif<<" ";
                    partidos<<victoria<<" ";
                    partidos<<derrota<<"\n";
                    partidos.flush();
            //Gana el visitante
                } else if (marcadorlocal < marcadorvisitante) {
                    int dif = marcadorvisitante - marcadorlocal;
                    partidos<<visitante<<" ";
                    partidos<<local<<" ";
                    partidos<<marcadorvisitante<<" ";
                    partidos<<marcadorlocal<<" ";
                    partidos<<dif<<" ";
                    partidos<<victoria<<" ";
                    partidos<<derrota<<"\n";
                    partidos.flush();
            //empate (Recuerda que para hacer la tabla debes usar el dif para determinar si hubo empate o no)
                } else {
                    int dif = marcadorvisitante - marcadorlocal;
                    partidos<<visitante<<" ";
                    partidos<<local<<" ";
                    partidos<<marcadorvisitante<<" ";
                    partidos<<marcadorlocal<<" ";
                    partidos<<dif<<" ";
                    partidos<<empate<<" ";
                    partidos<<empate<<"\n";
                    partidos.flush();
                }
                NumPartidos++;
                ofstream registros_out("data/registros.txt");
                if (registros_out.is_open()) {
                    registros_out << NumPartidos;
                    registros_out.close();
                }
                if (fechas.is_open()) {
                fechas<<NumFecha<<" ";
                fechas<<local<<" ";
                fechas<<visitante<<"\n";
                fechas<<marcadorlocal<<endl;
                fechas<<marcadorvisitante<<endl;
                
                fechas.flush();
                } else {
                    cout<<"No se puede crear fechas.txt\n";
                    respuesta = 'm';
                }
                cout << "Partido #" << NumPartidos << " creado." << endl;
                
            } else {
                cout<<"partidos.txt no se pudo crear\n";
                respuesta = 'm';
            }
        }
        cout<<"Quiere crear un nuevo partido? Ponga y/n:\n";
        cin>>registro;
        if (registro =='n') {
            respuesta = 'm';
        } else if (registro == 'y'){
    
        } else {
            cout<<"Se ingreso un comando invalido, volviendo al menu\n";
            respuesta = 'm';
        }
        } while (registro == 'y');
        cout << "Total de partidos creados: " << NumPartidos << endl;
        
        //Aqui termina el r
        
        //hacer la tabla
        }else if (respuesta == 't') { //paso 5
    
         //Ver historial de jornadas
        }else if (respuesta == 'h') {
    
        
         //Ver lista de partidos
        }else if (respuesta == 'p') { //paso 5

        //salir
        }else if (respuesta == 's') { //paso 5
            cout<<"Adios";
            //si coloca una respuesta ninguna de las anteriores
        }else{
            cout<<"Porfavor ingrese un comando valido\n";
            respuesta = 'm';
        }
            
        } while (respuesta == 'm');
         
          } else {
            cout<<"registros.txt no se puede abrir, reinicie el codigo\n";
          }
       
       
        } else {
            cout<<"No se puede leer configuracion.txt, reinicie el codigo\n";
        }
        
        return 0;
    }