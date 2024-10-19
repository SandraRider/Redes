#ifndef SERVIDORA_HPP
#define SERVIDORA_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

#include <iostream>

using namespace std;
#define MAX_CLIENTES 30
#define MAX_LINEA 100

/* El fichero .txt se guarda como usuario contrasena */

struct jugadores
{
    string usuario;
    string contraseña;
    bool turno;
    int estado; // 0 = no conectado, 1 = usuario conectado, 2 = contraseña bien, 3 = quiere empezar partida y 4 = jugando en una partida
    vector<string> cartas;
    int suma;
    // bool quiereOtraCarta;
    int identificadorPartida;
    int identificadorUsuario;
};
struct barajas // Yo pondría un vector con todos los tipos de la baraja posibles
{
    vector<string> cartaBaraja;
    int identificadorBaraja;
};
struct partidas
{
    struct jugadores jugador1;
    struct jugadores jugador2;
    struct barajas baraja;
    int turno;
};

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

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// CREA TODAS LAS CARTAS DE UNA BARAJA
struct barajas crearBaraja()
{
    struct barajas b;

    b.cartaBaraja.push_back("As de Corazones");
    b.cartaBaraja.push_back("2 de Corazones");
    b.cartaBaraja.push_back("3 de Corazones");
    b.cartaBaraja.push_back("4 de Corazones");
    b.cartaBaraja.push_back("5 de Corazones");
    b.cartaBaraja.push_back("6 de Corazones");
    b.cartaBaraja.push_back("7 de Corazones");
    b.cartaBaraja.push_back("8 de Corazones");
    b.cartaBaraja.push_back("9 de Corazones");
    b.cartaBaraja.push_back("10 de Corazones");
    b.cartaBaraja.push_back("Jota de Corazones");
    b.cartaBaraja.push_back("Reina de Corazones");
    b.cartaBaraja.push_back("Rey de Corazones");

    b.cartaBaraja.push_back("As de Diamantes");
    b.cartaBaraja.push_back("2 de Diamantes");
    b.cartaBaraja.push_back("3 de Diamantes");
    b.cartaBaraja.push_back("4 de Diamantes");
    b.cartaBaraja.push_back("5 de Diamantes");
    b.cartaBaraja.push_back("6 de Diamantes");
    b.cartaBaraja.push_back("7 de Diamantes");
    b.cartaBaraja.push_back("8 de Diamantes");
    b.cartaBaraja.push_back("9 de Diamantes");
    b.cartaBaraja.push_back("10 de Diamantes");
    b.cartaBaraja.push_back("Jota de Diamantes");
    b.cartaBaraja.push_back("Reina de Diamantes");
    b.cartaBaraja.push_back("Rey de Diamantes");

    b.cartaBaraja.push_back("As de Tréboles");
    b.cartaBaraja.push_back("2 de Tréboles");
    b.cartaBaraja.push_back("3 de Tréboles");
    b.cartaBaraja.push_back("4 de Tréboles");
    b.cartaBaraja.push_back("5 de Tréboles");
    b.cartaBaraja.push_back("6 de Tréboles");
    b.cartaBaraja.push_back("7 de Tréboles");
    b.cartaBaraja.push_back("8 de Tréboles");
    b.cartaBaraja.push_back("9 de Tréboles");
    b.cartaBaraja.push_back("10 de Tréboles");
    b.cartaBaraja.push_back("Jota de Tréboles");
    b.cartaBaraja.push_back("Reina de Tréboles");
    b.cartaBaraja.push_back("Rey de Tréboles");

    b.cartaBaraja.push_back("As de Picas");
    b.cartaBaraja.push_back("2 de Picas");
    b.cartaBaraja.push_back("3 de Picas");
    b.cartaBaraja.push_back("4 de Picas");
    b.cartaBaraja.push_back("5 de Picas");
    b.cartaBaraja.push_back("6 de Picas");
    b.cartaBaraja.push_back("7 de Picas");
    b.cartaBaraja.push_back("8 de Picas");
    b.cartaBaraja.push_back("9 de Picas");
    b.cartaBaraja.push_back("10 de Picas");
    b.cartaBaraja.push_back("Jota de Picas");
    b.cartaBaraja.push_back("Reina de Picas");
    b.cartaBaraja.push_back("Rey de Picas");

    return b;
}

/*struct barajas crearBaraja()
{
    struct barajas b;
    b.cartaBaraja.push_back("As de Corazones");
    b.cartaBaraja[1] = "2 de Corazones";
    b.cartaBaraja[2] = "3 de Corazones";
    b.cartaBaraja[3] = "4 de Corazones";
    b.cartaBaraja[4] = "5 de Corazones";
    b.cartaBaraja[5] = "6 de Corazones";
    b.cartaBaraja[6] = "7 de Corazones";
    b.cartaBaraja[7] = "8 de Corazones";
    b.cartaBaraja[8] = "9 de Corazones";
    b.cartaBaraja[9] = "10 de Corazones";
    b.cartaBaraja[10] = "Jota de Corazones";
    b.cartaBaraja[11] = "Reina de Corazones";
    b.cartaBaraja[12] = "Rey de Corazones";

    b.cartaBaraja[13] = "As de Diamantes";
    b.cartaBaraja[14] = "2 de Diamantes";
    b.cartaBaraja[15] = "3 de Diamantes";
    b.cartaBaraja[16] = "4 de Diamantes";
    b.cartaBaraja[17] = "5 de Diamantes";
    b.cartaBaraja[18] = "6 de Diamantes";
    b.cartaBaraja[19] = "7 de Diamantes";
    b.cartaBaraja[20] = "8 de Diamantes";
    b.cartaBaraja[21] = "9 de Diamantes";
    b.cartaBaraja[22] = "10 de Diamantes";
    b.cartaBaraja[23] = "Jota de Diamantes";
    b.cartaBaraja[24] = "Reina de Diamantes";
    b.cartaBaraja[25] = "Rey de Diamantes";

    b.cartaBaraja[26] = "As de Treboles";
    b.cartaBaraja[27] = "2 de Treboles";
    b.cartaBaraja[28] = "3 de Treboles";
    b.cartaBaraja[29] = "4 de Treboles";
    b.cartaBaraja[30] = "5 de Treboles";
    b.cartaBaraja[31] = "6 de Treboles";
    b.cartaBaraja[32] = "7 de Treboles";
    b.cartaBaraja[33] = "8 de Treboles";
    b.cartaBaraja[34] = "9 de Treboles";
    b.cartaBaraja[35] = "10 de Treboles";
    b.cartaBaraja[36] = "Jota de Treboles";
    b.cartaBaraja[37] = "Reina de Treboles";
    b.cartaBaraja[38] = "Rey de Treboles";

    b.cartaBaraja[39] = "As de Picas";
    b.cartaBaraja[40] = "2 de Picas";
    b.cartaBaraja[41] = "3 de Picas";
    b.cartaBaraja[42] = "4 de Picas";
    b.cartaBaraja[43] = "5 de Picas";
    b.cartaBaraja[44] = "6 de Picas";
    b.cartaBaraja[45] = "7 de Picas";
    b.cartaBaraja[46] = "8 de Picas";
    b.cartaBaraja[47] = "9 de Picas";
    b.cartaBaraja[48] = "10 de Picas";
    b.cartaBaraja[49] = "Jota de Picas";
    b.cartaBaraja[50] = "Reina de Picas";
    b.cartaBaraja[51] = "Rey de Picas";
    return b;
}*/

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// COMPRUEBA QUE EL JUGADOR ESTÁ CONECTADO CON SU USUARIO (PARA QUE EL USUARIO PUEDA METER SU CONTRASENA)
bool ConectadoConUsuario(vector<struct jugadores> &vjugadores, int id, const char *jugador)
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

/*----------------------------------------------------------------------------------------------------------------------------------------*/
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
int IntroducirUsuarioRegistrado(vector<struct jugadores> &vjugadores, int id, const char *jugador)
{
    FILE *fichero;
    char linea[MAX_LINEA];

    fichero = fopen("usuarios.txt", "r");
    if (fichero == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return false;
    }

    if (vjugadores.size() < MAX_CLIENTES)
    {
        while (fgets(linea, MAX_LINEA, fichero) != NULL)
        {
            char usuarioArchivo[MAX_LINEA];
            char contrasenaArchivo[MAX_LINEA];

            sscanf(linea, "%s %s", usuarioArchivo, contrasenaArchivo);

            if (strcmp(usuarioArchivo, jugador) == 0)
            {
                struct jugadores j;
                j.usuario = jugador;
                j.contraseña = string(contrasenaArchivo);
                j.estado = 1; // Conectado con usuario
                j.turno = false;
                j.suma = 0;
                // j.quiereOtraCarta = false;
                j.identificadorPartida = -1;
                j.identificadorUsuario = id;
                printf("%d\n", j.identificadorUsuario);
                vjugadores.push_back(j);
                fclose(fichero);
                return 3; // El usuario es correcto y se ha introducido el jugador en el vector
            }
        }

        fclose(fichero);
        return 2; // El usuario introducido no es correcto
    }
    else
    {
        fclose(fichero);
        return 1; // No hay espacio en el vector para que se introduzca
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// COMPRUEBA QUE EL JUGADOR HA INTRODUCIDO LA CONTRASEÑA CORRECTA Y LO INTRODUCE EN EL VECTOR
bool IntroducirContraseña(vector<struct jugadores> &vjugadores, int id, const char *contrasena)
{
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
            // cout << "Comparando " << vjugadores[i].contraseña << " y " << string(contrasena) << endl;
            if (vjugadores[i].contraseña == string(contrasena))
            {
                vjugadores[i].estado = 2; // Conectado con la contraseña
                return true;
            }
        }
    }
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

        sscanf(linea, "%s %s", usuarioArchivo, contrasenaArchivo);

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

    fprintf(fichero, "%s %s\n", jugador, contrasena); // Escribir el nuevo usuario seguido de espacio y su contrasena

    fclose(fichero);
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// HACER UN BUCLE HASTA QUE EL JUGADOR QUE QUIERE INICIAR PARTIDA ENCUENTRE A OTRO
/*
bool BuscarOponente(vector<struct jugadores> &vjugadores, int id)
{
    int posicionvectorjugador1 = -1, posicionvectorjugador2 = -1;
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if ((vjugadores[i].identificadorUsuario == id) && (vjugadores[i].estado == 2))
        {
            vjugadores[i].estado = 3; // Cambiamos el estado a "listo para jugar"
            posicionvectorjugador1 = i;
            break;
        }
    }

    int cont = 0;
    do
    {
        for (int i = 0; i < vjugadores.size(); i++)
        {
            if ((vjugadores[i].identificadorUsuario != id) && (vjugadores[i].estado == 3)) // Jugador listo para iniciar partida
            {
                posicionvectorjugador2 = i;
                cont++;
                break;
            }
        }
    } while (cont == 0);

    if (posicionvectorjugador2 != -1) // Si se ha encontrado otro jugador
    {
        int idPartida = rand();
        vjugadores[posicionvectorjugador1].estado = 4;
        vjugadores[posicionvectorjugador1].identificadorPartida = idPartida;
        vjugadores[posicionvectorjugador2].estado = 4;
        vjugadores[posicionvectorjugador2].identificadorPartida = idPartida;
        return true;
    }
    return false;
}
*/

int meterJugadorEnPartida(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja, int *id2, int *b)
{
    // Comprueba si hay un jugador solo esperando pareja
    for (int i = 0; i < vpartidas.size(); i++)
    {
        if (vpartidas[i].jugador1.estado == 3)
        {
            for (int j = 0; j < vjugadores.size(); j++)
            {
                if (vjugadores[j].identificadorUsuario == id)
                {

                    vpartidas[i].jugador2 = vjugadores[j];
                    vpartidas[i].jugador1.suma = 0;
                    vpartidas[i].jugador2.suma = 0;

                    // Crear baraja

                    struct barajas c = crearBaraja();

                    vbaraja.push_back(c);
                    vpartidas[i].baraja = vbaraja[vbaraja.size() - 1]; // size() devuelve el n total del vector, pero el índice empiezan desde 0
                    vpartidas[i].baraja.identificadorBaraja = vbaraja.size();
                    (*b) = vpartidas[i].baraja.identificadorBaraja;

                    // Cambiar el estado a jugando (4) del jugador 1
                    for (int j2 = 0; j2 < vjugadores.size(); j2++)
                    {
                        if (vjugadores[j2].identificadorUsuario == vpartidas[i].jugador1.identificadorUsuario)
                        {
                            vjugadores[j2].estado = 4;
                            (*id2) = vjugadores[j2].identificadorUsuario;
                        }
                    }

                    // Cambiar el estado a jugando (4) y el identificador de la partida del jugador 2
                    vjugadores[j].estado = 4;
                    vjugadores[j].turno = false;
                    vjugadores[j].identificadorPartida = i;
                    printf("meterJugadorEnPartida. SEGUNDO JUGADOR id: %d\n", vjugadores[j].identificadorUsuario);
                    printf("meterJugadorEnPartida. SEGUNDO JUGADOR estado: %d\n", vjugadores[j].estado);
                    printf("meterJugadorEnPartida. SEGUNDO JUGADOR idPartida: %d\n", vjugadores[j].identificadorPartida);
                    printf("meterJugadorEnPartida. SEGUNDO JUGADOR turno: %d\n", vjugadores[j].turno);
                    return 1;
                }
            }
        }
    }
    // Crea una nueva partida
    if (vpartidas.size() < 10)
    {
        partidas p;
        for (int j = 0; j < vjugadores.size(); j++)
        {
            if (vjugadores[j].identificadorUsuario == id)
            {
                vjugadores[j].estado = 3;
                vjugadores[j].turno = true;
                vjugadores[j].identificadorPartida = vpartidas.size();
                printf("meterJugadorEnPartida. PRIMER JUGADOR id: %d\n", vjugadores[j].identificadorUsuario);
                printf("meterJugadorEnPartida. PRIMER JUGADOR estado: %d\n", vjugadores[j].estado);
                printf("meterJugadorEnPartida. PRIMER JUGADOR idPartida: %d\n", vjugadores[j].identificadorPartida);
                printf("meterJugadorEnPartida. PRIMER JUGADOR turno: %d\n", vjugadores[j].turno);
                p.jugador1 = vjugadores[j];
            }
        }
        vpartidas.push_back(p);
        return 2;
    }
    return 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// ELIMINA UN JUGADOR DEL VECTOR CUANDO SE DESCONECTA
void eliminaJugador(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja)
{
    // Elimino el vector de la partida
    for (int i = 0; i < vpartidas.size(); i++)
    {
        if (vpartidas[i].jugador1.identificadorUsuario == id)
        {
            vpartidas[i].jugador1.estado = 0;
            // borrar baraja
            for (int j = 0; j < vbaraja.size(); j++)
            {
                if (vpartidas[i].baraja.identificadorBaraja == vbaraja[j].identificadorBaraja)
                {
                    vbaraja.erase(vbaraja.begin() + j);
                }
            }
            vpartidas[i].jugador2.estado = 3;
        }
        if (vpartidas[i].jugador2.identificadorUsuario == id)
        {
            vpartidas[i].jugador2.estado = 0;
            // borrar baraja
            for (int j = 0; j < vbaraja.size(); j++)
            {
                if (vpartidas[i].baraja.identificadorBaraja == vbaraja[j].identificadorBaraja)
                {
                    vbaraja.erase(vbaraja.begin() + j);
                }
            }
            vpartidas[i].jugador1.estado = 3;
        }
    }

    // Elimino al jugador del vector jugadores
    for (size_t i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
            vjugadores.erase(vjugadores.begin() + i);
        }
    }
}

void asignarCarta(vector<struct jugadores> &vjugadores, int id, vector<struct barajas> &vbaraja, int b)
{
    // printf("AsignarCarta1. i: %d\n", id);
    // printf("AsignarCarta. B: %d\n", b);
    b--;
    int tam = vbaraja[b].cartaBaraja.size();
    // printf("AsignarCarta2. tambaraja: %d\n", tam);
    int numero = 0;
    // printf("AsignarCarta3. numero: %d\n", numero);
    numero = rand() % tam;

    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
            // printf("AsignarCarta4. numero: %d\n", numero);
            vjugadores[i].cartas.push_back(vbaraja[b].cartaBaraja[numero]);
            vbaraja[b].cartaBaraja.erase(vbaraja[b].cartaBaraja.begin() + numero);
        }
    }
}

int calcularSuma(vector<struct jugadores> &vjugadores, int i)
{
    int ident;
    for (int a = 0; a < vjugadores.size(); a++)
    {
        if (vjugadores[a].identificadorUsuario == i)
        {
            ident=a;
            vjugadores[a].suma = 0;
            for (int j = 0; j < vjugadores[a].cartas.size(); j++)
            {
                // Corazones
                if (vjugadores[a].cartas[j] == "2 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 2;
                }
                else if (vjugadores[a].cartas[j] == "3 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 3;
                }
                else if (vjugadores[a].cartas[j] == "4 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 4;
                }
                else if (vjugadores[a].cartas[j] == "5 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 5;
                }
                else if (vjugadores[a].cartas[j] == "6 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 6;
                }
                else if (vjugadores[a].cartas[j] == "7 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 7;
                }
                else if (vjugadores[a].cartas[j] == "8 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 8;
                }
                else if (vjugadores[a].cartas[j] == "9 de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 9;
                }
                else if (vjugadores[a].cartas[j] == "10 de Corazones" || vjugadores[a].cartas[j] == "Jota de Corazones" || vjugadores[a].cartas[j] == "Reina de Corazones" || vjugadores[a].cartas[j] == "Rey de Corazones")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 10;
                } // Diamantes
                else if (vjugadores[a].cartas[j] == "2 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 2;
                }
                else if (vjugadores[a].cartas[j] == "3 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 3;
                }
                else if (vjugadores[a].cartas[j] == "4 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 4;
                }
                else if (vjugadores[a].cartas[j] == "5 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 5;
                }
                else if (vjugadores[a].cartas[j] == "6 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 6;
                }
                else if (vjugadores[a].cartas[j] == "7 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 7;
                }
                else if (vjugadores[a].cartas[j] == "8 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 8;
                }
                else if (vjugadores[a].cartas[j] == "9 de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 9;
                }
                else if (vjugadores[a].cartas[j] == "10 de Diamantes" || vjugadores[a].cartas[j] == "Jota de Diamantes" || vjugadores[a].cartas[j] == "Reina de Diamantes" || vjugadores[a].cartas[j] == "Rey de Diamantes")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 10;
                }
                // Tréboles
                else if (vjugadores[a].cartas[j] == "2 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 2;
                }
                else if (vjugadores[a].cartas[j] == "3 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 3;
                }
                else if (vjugadores[a].cartas[j] == "4 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 4;
                }
                else if (vjugadores[a].cartas[j] == "5 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 5;
                }
                else if (vjugadores[a].cartas[j] == "6 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 6;
                }
                else if (vjugadores[a].cartas[j] == "7 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 7;
                }
                else if (vjugadores[a].cartas[j] == "8 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 8;
                }
                else if (vjugadores[a].cartas[j] == "9 de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 9;
                }
                else if (vjugadores[a].cartas[j] == "10 de Treboles" || vjugadores[a].cartas[j] == "Jota de Treboles" || vjugadores[a].cartas[j] == "Reina de Treboles" || vjugadores[a].cartas[j] == "Rey de Treboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 10;
                }
                // Picas
                else if (vjugadores[a].cartas[j] == "2 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 2;
                }
                else if (vjugadores[a].cartas[j] == "3 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 3;
                }
                else if (vjugadores[a].cartas[j] == "4 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 4;
                }
                else if (vjugadores[a].cartas[j] == "5 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 5;
                }
                else if (vjugadores[a].cartas[j] == "6 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 6;
                }
                else if (vjugadores[a].cartas[j] == "7 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 7;
                }
                else if (vjugadores[a].cartas[j] == "8 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 8;
                }
                else if (vjugadores[a].cartas[j] == "9 de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 9;
                }
                else if (vjugadores[a].cartas[j] == "10 de Picas" || vjugadores[a].cartas[j] == "Jota de Picas" || vjugadores[a].cartas[j] == "Reina de Picas" || vjugadores[a].cartas[j] == "Rey de Picas")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 10;
                }
            }
            // Ahora un for para los As
            for (int j = 0; j < vjugadores[a].cartas.size(); j++)
            {
                if (vjugadores[a].cartas[j] == "As de Corazones" || vjugadores[a].cartas[j] == "As de Diamantes" || vjugadores[a].cartas[j] == "As de Treboles" || vjugadores[a].cartas[j] == "As de Picas")
                {
                    if (vjugadores[a].suma + 11 > 21)
                    {
                        vjugadores[a].suma = vjugadores[a].suma + 1;
                    }
                    else
                    {
                        vjugadores[a].suma = vjugadores[a].suma + 11;
                    }
                }
            }
        }
    }
    return vjugadores[ident].suma;
}

/*void asignarCarta(vector<struct jugadores> &vjugadores, int i, vector<struct barajas> &vbaraja, int b)
{
    int tam = vbaraja[b].cartaBaraja.size();
    srand(time(0));
    int numero;
    numero = rand() % tam;

    vjugadores[i].cartas.push_back(vbaraja[b].cartaBaraja[numero]);
    vbaraja[b].cartaBaraja.erase(vbaraja[b].cartaBaraja.begin() + numero);
}*/

#endif
