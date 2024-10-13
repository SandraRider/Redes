#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;
#define MAX_CLIENTES 30

// Usa erase para borrar
/*struct jugadores
{
    int socket;
    char estado[250]; //Puede ser cadena de caracteres o no

};*/

struct jugadores
{
    string usuario;
    string contraseña;
    bool turno;
    int estado; // 0 = no conectado y 1 = conectado
    vector<string> cartas;
    int suma; // Suma de la mano
    bool quiereOtraCarta;
    bool estaEnPartida;
    int identificadorPartida;
    int identificadorUsuario;
};

/* Con esto inicializo el vector para que todos los huecos estén vacíos:
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
void LlenarVectorJugadores(vector<jugadores> &vjugadores)
{
    vjugadores.resize(MAX_CLIENTES); // Redimensionar para 30 jugadores
    for (int i = 0; i < MAX_CLIENTES; i++)
    {
        vjugadores[i].usuario = "";
        vjugadores[i].contraseña = "";
        vjugadores[i].estado = 0; // No conectado
        vjugadores[i].turno = false;
        vjugadores[i].suma = 0;
        vjugadores[i].quiereOtraCarta = false;
        vjugadores[i].estaEnPartida = false;
        vjugadores[i].identificadorPartida = -1;
        vjugadores[i].identificadorUsuario = -1;
    }
}

void AnadirJugador(vector<jugadores> &vjugadores, string &usuario, string &contraseña, int identificadorUsuario)
{
    for (int i = 0; i < MAX_CLIENTES; i++)
    {
        if (vjugadores[i].estado == 0) // Encontrar un hueco libre
        {
            vjugadores[i].usuario = usuario;
            vjugadores[i].contraseña = contraseña;
            vjugadores[i].estado = 1; // Conectado
            vjugadores[i].identificadorUsuario = identificadorUsuario;
        }
    }
}

bool EstaConectado(vector<jugadores> &vjugadores, int idUser)
{
    for (int i = 0; i < MAX_CLIENTES; i++)
    {
        if (vjugadores[i].identificadorUsuario == idUser && vjugadores[i].estado == 1)
        {
            return true; // Jugador está conectado
        }
    }
    return false;
}

bool ExisteJugador(vector<struct jugadores> vjugadores, int socket, char *jugador)
{
    FILE *fich = fopen("usuarios.txt", "r");
    if (fich == NULL)
    {
        char nombreleido[200];
    }
}

#endif
