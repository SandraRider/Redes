// Este fichero hay que pasarlo al servidor
//(Es a sucio para ir pasándo las cosas)

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

struct carta
{
    char nombre;
    int valor;
};
struct jugadores
{
    char nombre;
    bool turno;
    vector<string> cartas; // No sería un vector<struct carta> cartas;
    int suma;
    char usuario; // Se supone que el usuario es lo mismo que el nombre
    char contraseña;
    bool quiereOtraCarta;
    bool estaEnPartida;
    int identificadorPartida;
    int identificadorUsuario;
};
struct barajas // Yo pondría un vector con todos los tipos de la baraja posibles
{
    struct carta cartaBaraja;
};
struct partida
{
    struct jugadores jugador1;
    struct jugadores jugador2;
    struct barajas baraja; // Yo pondría que identificadorPartida que sea el mismo que el del jugador
    int turno;
};

bool comprobarLogin(struct jugadores jugador)
{
    string nombrefichero = "archivo.txt";

    ifstream fich(nombrefichero);
    fich.open(nombrefichero, std::ios::in);

    if (fich.is_open())
    {
        string linea;

        bool encontrado = false;
        while (getline(fich, linea))
        {
            if (linea == &jugador.usuario)
            {
                encontrado = true;
            }
        }

        fich.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo: " << nombrefichero << endl;
    }
}

bool comprobarPassword() // Tendríamos que pasarle el usuario
{
    /* Tenemos que ver de que forma están guardados los usuarios: 1ªforma: el nombre espacio y la contraseña
    2ªforma: el nombre en una línea y la contraseña en otra. Por ejemplo:
    Nombre Contraseña
    o
    Nombre
    Contraseña
    */
}

bool comprobarEstado(struct jugadores *v, int id)
{
    for (int i = 0; i < 30; i++) // Porque pones <30? Por el numero máximos de clientes? Si
    {
        if (v[i].id == id && v[i].estado == X)
        {
            return 1;
        }
    }
    return 0;
}

struct barajas crearBaraja(vector<string> vbaraja)
{
    vbaraja[0] = "As de Corazones";
    vbaraja[1] = "2 de Corazones";
    vbaraja[2] = "3 de Corazones";
    vbaraja[3] = "4 de Corazones";
    vbaraja[4] = "5 de Corazones";
    vbaraja[5] = "6 de Corazones";
    vbaraja[6] = "7 de Corazones";
    vbaraja[7] = "8 de Corazones";
    vbaraja[8] = "9 de Corazones";
    vbaraja[9] = "10 de Corazones";
    vbaraja[10] = "Jota de Corazones";
    vbaraja[11] = "Reina de Corazones";
    vbaraja[12] = "Rey de Corazones";

    vbaraja[13] = "As de Diamantes";
    vbaraja[14] = "2 de Diamantes";
    vbaraja[15] = "3 de Diamantes";
    vbaraja[16] = "4 de Diamantes";
    vbaraja[17] = "5 de Diamantes";
    vbaraja[18] = "6 de Diamantes";
    vbaraja[19] = "7 de Diamantes";
    vbaraja[20] = "8 de Diamantes";
    vbaraja[21] = "9 de Diamantes";
    vbaraja[22] = "10 de Diamantes";
    vbaraja[23] = "Jota de Diamantes";
    vbaraja[24] = "Reina de Diamantes";
    vbaraja[25] = "Rey de Diamantes";

    vbaraja[26] = "As de Treboles";
    vbaraja[27] = "2 de Treboles";
    vbaraja[28] = "3 de Treboles";
    vbaraja[29] = "4 de Treboles";
    vbaraja[30] = "5 de Treboles";
    vbaraja[31] = "6 de Treboles";
    vbaraja[32] = "7 de Treboles";
    vbaraja[33] = "8 de Treboles";
    vbaraja[34] = "9 de Treboles";
    vbaraja[35] = "10 de Treboles";
    vbaraja[36] = "Jota de Treboles";
    vbaraja[37] = "Reina de Treboles";
    vbaraja[38] = "Rey de Treboles";

    vbaraja[39] = "As de Picas";
    vbaraja[40] = "2 de Picas";
    vbaraja[41] = "3 de Picas";
    vbaraja[42] = "4 de Picas";
    vbaraja[43] = "5 de Picas";
    vbaraja[44] = "6 de Picas";
    vbaraja[45] = "7 de Picas";
    vbaraja[46] = "8 de Picas";
    vbaraja[47] = "9 de Picas";
    vbaraja[48] = "10 de Picas";
    vbaraja[49] = "Jota de Picas";
    vbaraja[50] = "Reina de Picas";
    vbaraja[51] = "Rey de Picas";
}

void asignarCarta(vector<struct jugadores> vjugadores, int i, vector<string> vbaraja)
{
    int tam=vbaraja.size();
    srand(time(0));
    int numero;
    numero = rand() % tam;
    vjugadores[i].cartas.push_back(vbaraja[numero]);
    vbaraja[numero].erase();
}

void calcularSuma(vector<struct jugadores> vjugadores, int i)
{
    vjugadores[i].suma=0;
    for(int j=0; j<vjugadores[i].cartas.size(); j++)
    {
        //Corazones
        if (vjugadores[i].cartas[j]== "2 de Corazones")
        {
            vjugadores[i].suma=vjugadores[i].suma+2;
        }
        else if (vjugadores[i].cartas[j]== "3 de Corazones")
        {
            vjugadores[i].suma=vjugadores[i].suma+3;
        }
        else if (vjugadores[i].cartas[j]== "4 de Corazones")
        {
            vjugadores[i].suma=vjugadores[i].suma+4;
        } else if (vjugadores[i].cartas[j] == "5 de Corazones")
        {
            vjugadores[i].suma =vjugadores[i].suma+5;
        } else if (vjugadores[i].cartas[j] == "6 de Corazones")
        {
            vjugadores[i].suma =vjugadores[i].suma+6;
        } else if (vjugadores[i].cartas[j] == "7 de Corazones")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 7;
        } else if (vjugadores[i].cartas[j] == "8 de Corazones")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 8;
        } else if (vjugadores[i].cartas[j] == "9 de Corazones")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 9;
        } else if (vjugadores[i].cartas[j] == "10 de Corazones" || vjugadores[i].cartas[j] == "Jota de Corazones" || vjugadores[i].cartas[j] == "Reina de Corazones" || vjugadores[i].cartas[j] == "Rey de Corazones")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 10;
        }//Diamantes
        else if (vjugadores[i].cartas[j] == "2 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 2;
        } else if (vjugadores[i].cartas[j] == "3 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma + 3;
        } else if (vjugadores[i].cartas[j] == "4 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 4;
        } else if (vjugadores[i].cartas[j] == "5 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 5;
        } else if (vjugadores[i].cartas[j] == "6 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 6;
        } else if (vjugadores[i].cartas[j] == "7 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 7;
        } else if (vjugadores[i].cartas[j] == "8 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 8;
        } else if (vjugadores[i].cartas[j] == "9 de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 9;
        } else if (vjugadores[i].cartas[j] == "10 de Diamantes" || vjugadores[i].cartas[j] == "Jota de Diamantes" || vjugadores[i].cartas[j] == "Reina de Diamantes" || vjugadores[i].cartas[j] == "Rey de Diamantes")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 10;
        }
        // Tréboles
        else if (vjugadores[i].cartas[j] == "2 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 2;
        } else if (vjugadores[i].cartas[j] == "3 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 3;
        } else if (vjugadores[i].cartas[j] == "4 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 4;
        } else if (vjugadores[i].cartas[j] == "5 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 5;
        } else if (vjugadores[i].cartas[j] == "6 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 6;
        } else if (vjugadores[i].cartas[j] == "7 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 7;
        } else if (vjugadores[i].cartas[j] == "8 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 8;
        } else if (vjugadores[i].cartas[j] == "9 de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 9;
        } else if (vjugadores[i].cartas[j] == "10 de Treboles" || vjugadores[i].cartas[j] == "Jota de Treboles" || vjugadores[i].cartas[j] == "Reina de Treboles" || vjugadores[i].cartas[j] == "Rey de Treboles")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 10;
        }
        // Picas
        else if (vjugadores[i].cartas[j] == "2 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 2;
        } else if (vjugadores[i].cartas[j] == "3 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 3;
        } else if (vjugadores[i].cartas[j] == "4 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 4;
        } else if (vjugadores[i].cartas[j] == "5 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 5;
        } else if (vjugadores[i].cartas[j] == "6 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 6;
        } else if (vjugadores[i].cartas[j] == "7 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 7;
        } else if (vjugadores[i].cartas[j] == "8 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 8;
        } else if (vjugadores[i].cartas[j] == "9 de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 9;
        } else if (vjugadores[i].cartas[j] == "10 de Picas" || vjugadores[i].cartas[j] == "Jota de Picas" || vjugadores[i].cartas[j] == "Reina de Picas" || vjugadores[i].cartas[j] == "Rey de Picas")
        {
            vjugadores[i].suma =vjugadores[i].suma+ 10;
        }
    }
    //Ahora un for para los As
    for(int j=0; j<vjugadores[i].cartas.size(); j++)
    {
        if (vjugadores[i].cartas[j]== "As de Corazones" || vjugadores[i].cartas[j]== "As de Diamantes" || vjugadores[i].cartas[j]== "As de Treboles" || vjugadores[i].cartas[j]== "As de Picas")
        {
            if(vjugadores[i].suma+11>21)
            {
                vjugadores[i].suma=vjugadores[i].suma+1;
            }else{
                vjugadores[i].suma=vjugadores[i].suma+11;
            }
        }
    }
}    

void barajar(struct barajas *baraja) {}

vector<char> cartasdeljugador(struct jugadores *jugador, struct barajas *baraja) {}

void comprobarSuma(struct jugadores *jugador1, struct jugadores *jugador2)
{
}

void ganador(struct jugadores *jugador1, struct jugadores *jugador2)
{
    if ((jugador1->suma) > 21 && (jugador2->suma) <= 21)
    {
        cout << "El ganador es: " << jugador2->nombre << endl;
    }
    else if ((jugador2->suma) > 21 && (jugador1->suma) <= 21)
    {
        cout << "El ganador es: " << jugador1->nombre << endl;
    }
    else if ((jugador1->suma) > 21 && (jugador2->suma) > 21)
    {
        cout << "Ambos jugadores han perdido" << endl;
    }
    else
    {
        if (jugador1->suma > jugador2->suma)
        {
            cout << "El ganador es: " << jugador1->nombre << endl;
        }
        else if (jugador2->suma > jugador1->suma)
        {
            cout << "El ganador es: " << jugador2->nombre << endl;
        }
        else
        {
            cout << "Ha habido un empate, ambos sois buenísimos" << endl;
        }
    }
}

void pedirCartas()
{
    // Compobar estado primero
}

int main()
{
    vector<struct jugadores> vjugadores;
    struct jugadores jugador1, jugador2;
    // Introducir nombres de los jugadores
    // LOGIN
    // Creo que hay que hacer un vector de jugadores y un vector de barajas para todas las partidas que haya a la vez

    struct barajas baraja = crearBaraja();
    barajar(baraja);

    // Repartimos las cartas
    for (int i = 0; i < 2; i++)
    {
        jugador1->cartas[i] = cartasdeljugador(jugador1, baraja);
        jugador2->cartas[i] = cartasdeljugador(jugador2, baraja);
    }

    //

    ganador(jugador1, jugador2);

    return 0;
}
