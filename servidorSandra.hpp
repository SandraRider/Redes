#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;
#define MAX_CLIENTES 30
#define MAX_LINEA 100

/* El fichero .txt se guarda como usuario;contrasena */

struct jugadores
{
    string usuario;
    string contraseña;
    bool turno;
    int estado; // 0 = no conectado, 1 = usuario conectado, 2 = contraseña bien, 3 = quiere empezar partida y 4 = jugando en una partida
    vector<string> cartas;
    int suma; // Suma de la mano
    bool quiereOtraCarta;
    int identificadorPartida;
    int identificadorUsuario;
};

// LLENA EL VECTOR DE JUGADORES
void LlenarVectorJugadores(vector<jugadores> &vjugadores)
{
    for (int i = 0; i < MAX_CLIENTES; i++)
    {
        vjugadores[i].usuario = "";
        vjugadores[i].contraseña = "";
        vjugadores[i].estado = 0;
        vjugadores[i].turno = false;
        vjugadores[i].suma = 0;
        vjugadores[i].quiereOtraCarta = false;
        vjugadores[i].identificadorPartida = -1;
        vjugadores[i].identificadorUsuario = -1;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

// COMPRUEBA SI EL JUGADOR ESTÁ CONECTADO CON SU USUARIO Y CONTRASEÑA (PARA QUE EL USUARIO PUEDA EMPEZAR UNA PARTIDA)
bool ConectadoConUsuarioYContraseña(vector<jugadores> &vjugadores, int id)
{
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id && vjugadores[i].estado == 2)
        {
            return true;
        }
    }
    return false;
}

// COMPRUEBA QUE EL JUGADOR ESTÁ CONECTADO CON SU USUARIO (PARA QUE EL USUARIO PUEDA METER SU CONTRASENA)
bool ConectadoConUsuario(vector<struct jugadores> vjugadores, int id, const char *jugador)
{
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if ((vjugadores[i].identificadorUsuario == id) && (strcmp(vjugadores[i].usuario.c_str(), jugador) == 0))
        {
            return true;
        }
    }
    return false;
}

// COMPRUEBA SI HAY SITIO EN EL VECTOR DE JUGADORES
bool comprobarConexiones(vector<struct jugadores> vjugadores, int id)
{
    if (vjugadores.size() < MAX_CLIENTES)
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

// COMPRUEBA QUE HAY HUECO EN EL VECTOR Y EL JUGADOR SE INTRODUCE CON SU USUARIO (METER USUARIO DEL JUGADOR EN EL VECTOR)
int IntroducirUsuarioRegistrado(vector<struct jugadores> vjugadores, int id, const char *jugador)
{
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].estado == 0)
        {
            vjugadores[i].usuario = jugador;
            vjugadores[i].contraseña = "";
            vjugadores[i].estado = 1; // Conectado con usuario
            vjugadores[i].turno = false;
            vjugadores[i].suma = 0;
            vjugadores[i].quiereOtraCarta = false;
            vjugadores[i].identificadorPartida = -1;
            vjugadores[i].identificadorUsuario = id;
        }
    }
}

// COMPRUEBA QUE EL JUGADOR HA INTRODUCIDO LA CONTRASEÑA CORRECTA Y LO INTRODUCE EN EL VECTOR
bool IntroducirContraseña(vector<struct jugadores> vjugadores, int id, const char *contrasena)
{
    FILE *fichero;
    char linea[MAX_LINEA];

    fichero = fopen("usuarios.txt", "r");
    if (fichero == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return false;
    }

    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
            while (fgets(linea, MAX_LINEA, fichero) != NULL)
            {
                char usuarioArchivo[MAX_LINEA];
                char contrasenaArchivo[MAX_LINEA];

                sscanf(linea, "%s;%s", usuarioArchivo, contrasenaArchivo);

                if ((strcmp(usuarioArchivo, vjugadores[i].usuario.c_str()) == 0) && (strcmp(contrasenaArchivo, contrasena) == 0))
                {
                    vjugadores[i].contraseña = contrasena;
                    vjugadores[i].estado = 2;
                    vjugadores[i].turno = false;
                    vjugadores[i].suma = 0;
                    vjugadores[i].quiereOtraCarta = false;
                    vjugadores[i].identificadorPartida = -1;
                    vjugadores[i].identificadorUsuario = id;
                    fclose(fichero);
                    return true;
                }
            }
        }
    }
    fclose(fichero);
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

// REGISTRA A UN JUGADOR AL FICHERO DE TEXTO Y COMPRUEBA QUE NO ESTÁ EN EL FICHERO
bool RegistrarJugadorFichero(char *jugador, char *contrasena)
{
    FILE *fichero;
    char linea[MAX_LINEA];
    bool usuarioEncontrado = false;

    fichero = fopen("usuarios.txt", "r");
    if (fichero == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return false;
    }

    while (fgets(linea, MAX_LINEA, fichero) != NULL)
    {
        char usuarioArchivo[MAX_LINEA];
        char contrasenaArchivo[MAX_LINEA];

        sscanf(linea, "%s;%s", usuarioArchivo, contrasenaArchivo);

        if (strcmp(usuarioArchivo, jugador) == 0)
        {
            usuarioEncontrado = true;
            break;
        }
    }

    fclose(fichero);

    if (usuarioEncontrado)
    {
        return false;
    }

    fichero = fopen("usuarios.txt", "a");
    if (fichero == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return false;
    }

    fprintf(fichero, "%s;%s\n", jugador, contrasena); // Escribir el nuevo usuario seguido de ; y su contrasena

    fclose(fichero);
    return true;
}

// ELIMINA UN JUGADOR DEL VECTOR CUANDO HA JUGADO TODAS LAS PARTIDAS (10)

// ELIMINA UN JUGADOR DEL VECTOR CUANDO SE DESCONECTA

#endif
