#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//Usa erase para borrar
/*struct jugadores
{
    int socket;
    char estado[250]; //Puede ser cadena de caracteres o no

};*/

struct jugadores
{
    char nombre;
    bool turno;
    char estado[250];
    vector<char> cartas;
    int suma;
    char usuario;
    char contraseña;
    bool quiereOtraCarta;
    bool estaEnPartida;
    int identificadorPartida;
    int identificadorUsuario;
};

/*Con esto inicializo el vector para que todos los huecos estén vacíos:
void LlenarVectorJugadores(vector<struct jugadores> vjugadores)
{
    for(int i=0; i<30; i++)
    {
        strcpy(vjugadores[i].estado, "vacio");
    }
};*/

/*AnadirJugador(vector<struct jugadores> vjugadores, int socket)
{
    for(int i=0; i<30; i++)
    {
        if(strcpy(vjugadores[i].estado, "vacio")==0)
        {
            vjugadores[i].socket=socket;
            strcpy(vjugadores[i].estado, "conectado");
            return;
        }
    }
};*/

bool comprobarConexiones(vector<struct jugadores> vjugadores, int i)
{
    /*for(int i=0; i<30; i++)
    {
        //if(vjugadores[i])
    }*/
    if(vjugadores.size()<30)
    {
        return true;
    }
    return false;
}

bool ExisteJugador(vector<struct jugadores>vjugadores,int socket, char *jugador)
{
    FILE *fich=fopen("usuarios.txt", "r");
    if(fich==NULL)
    {
        char nombreleido[200];
    }
}

#endif
