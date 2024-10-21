/**
 * @file ServidorFunciones.cc
 * @author Laura Muñoz Jurado y Sandra Rider Gómez
 * @brief Desarrollo de las funciones para un sistema de juego de cartas BlackJack.
 * @date 2024
 */

#include "Servidor.hpp"

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// CREA TODAS LAS CARTAS DE UNA BARAJA
/*----------------------------------------------------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// COMPRUEBA QUE EL JUGADOR ESTÁ CONECTADO CON SU USUARIO (PARA QUE EL USUARIO PUEDA METER SU CONTRASENA)
/*----------------------------------------------------------------------------------------------------------------------------------------*/
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
// COMPRUEBA SI EL JUGADOR ESTÁ CONECTADO CON SU USUARIO Y CONTRASEÑA (PARA QUE EL USUARIO PUEDA EMPEZAR UNA PARTIDA)
/*----------------------------------------------------------------------------------------------------------------------------------------*/
bool ConectadoConUsuarioYContraseña(vector<jugadores> &vjugadores, int id)
{
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id && vjugadores[i].estado >= 2)
        {
            return true;
        }
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// COMPRUEBA SI HAY SITIO EN EL VECTOR DE JUGADORES
/*----------------------------------------------------------------------------------------------------------------------------------------*/
bool comprobarConexiones(vector<struct jugadores> vjugadores, int id)
{
    if (vjugadores.size() < MAX_CLIENTES)
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// COMPRUEBA QUE HAY HUECO EN EL VECTOR Y EL JUGADOR SE INTRODUCE CON SU USUARIO (METER AL JUGADOR EN EL VECTOR)
/*----------------------------------------------------------------------------------------------------------------------------------------*/
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
                j.plantado = false;
                j.identificadorPartida = -1;
                j.identificadorUsuario = id;
                vjugadores.push_back(j);
                fclose(fichero);
                return 3; // El usuario es correcto y se ha introducido el jugador en el vector jugadores
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
/*----------------------------------------------------------------------------------------------------------------------------------------*/
bool IntroducirContraseña(vector<struct jugadores> &vjugadores, int id, const char *contrasena)
{
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
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
// REGISTRA A UN JUGADOR AL FICHERO DE TEXTO Y COMPRUEBA QUE EL NOMBRE A REGISTAR NO ESTÁ EN EL FICHERO
/*----------------------------------------------------------------------------------------------------------------------------------------*/
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

    if (usuarioEncontrado) // El nombre de usuario ya esta registrado en el fichero de texto
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
// METER UN JUGADOR EN UNA PARTIDA O CREA UNA NUEVA PARTIDA SI NO HAY OTRO JUGADOR ESPERANDO A JUGAR
/*----------------------------------------------------------------------------------------------------------------------------------------*/
int meterJugadorEnPartida(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja, int *id2, int *b)
{
    // Comprueba si hay un jugador esperando emparejamiento
    for (int i = 0; i < vpartidas.size(); i++)
    {
        if (vpartidas[i].jugador1.estado == 3 && vpartidas[i].jugador2.estado == 0)
        {
            for (int j = 0; j < vjugadores.size(); j++)
            {
                if (vjugadores[j].identificadorUsuario == id)
                {

                    vpartidas[i].jugador2 = vjugadores[j];
                    vpartidas[i].jugador1.suma = 0;
                    vpartidas[i].jugador2.suma = 0;

                    // Creamos la baraja
                    struct barajas c = crearBaraja();

                    vbaraja.push_back(c);
                    vpartidas[i].baraja = vbaraja[vbaraja.size() - 1];
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
                    vjugadores[j].plantado = false;
                    vjugadores[j].identificadorPartida = i;
                    return 1;
                }
            }
        }
    }
    // Crea una nueva partida si hay menos de 10 partidas
    if (vpartidas.size() < 10)
    {
        partidas p;
        for (int j = 0; j < vjugadores.size(); j++)
        {
            if (vjugadores[j].identificadorUsuario == id)
            {
                vjugadores[j].estado = 3; // Cambiamos el estado del jugador a buscando partida
                vjugadores[j].turno = true;
                vjugadores[j].plantado = false;
                vjugadores[j].identificadorPartida = vpartidas.size();
                p.jugador1 = vjugadores[j];
                p.jugador2.estado = 0;
            }
        }
        vpartidas.push_back(p);
        return 2;
    }
    return 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// ELIMINA UN JUGADOR DEL VECTOR DE JUGADORES CUANDO SE DESCONECTA
/*----------------------------------------------------------------------------------------------------------------------------------------*/
void eliminaJugador(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja)
{
    // Elimino el vector de la partida
    for (int i = 0; i < vpartidas.size(); i++)
    {
        if (vpartidas[i].jugador1.identificadorUsuario == id)
        {
            // Borrar baraja
            for (int j = 0; j < vbaraja.size(); j++)
            {
                if (vpartidas[i].baraja.identificadorBaraja == vbaraja[j].identificadorBaraja)
                {
                    vbaraja.erase(vbaraja.begin() + j);
                }
            }

            vpartidas.erase(vpartidas.begin() + i);
        }

        if (vpartidas[i].jugador2.identificadorUsuario == id)
        {
            // Borrar baraja
            for (int j = 0; j < vbaraja.size(); j++)
            {
                if (vpartidas[i].baraja.identificadorBaraja == vbaraja[j].identificadorBaraja)
                {
                    vbaraja.erase(vbaraja.begin() + j);
                }
            }

            vpartidas.erase(vpartidas.begin() + i);
        }
    }

    // Elimino al jugador del vector jugadores
    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
            vjugadores.erase(vjugadores.begin() + i);
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// ELIMINA AMBOS JUGADORES DEL VECTOR DE JUGADORES CUANDO ESTÁN EN UNA PARTIDA, LOS ELIMINA DE VPARTIDA Y VJUGADORES Y BORRA LAS CARTAS DE VBARAJA
/*----------------------------------------------------------------------------------------------------------------------------------------*/
void eliminaJugadoresPartida(vector<struct jugadores> &vjugadores, int id1, int id2, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja)
{
    for (int i = 0; i < vpartidas.size(); i++)
    {
        // Ambos jugadores están en la misma partida
        if ((vpartidas[i].jugador1.identificadorUsuario == id1 && vpartidas[i].jugador2.identificadorUsuario == id2) ||
            (vpartidas[i].jugador1.identificadorUsuario == id2 && vpartidas[i].jugador2.identificadorUsuario == id1))
        {
            // Eliminamos la baraja asociada a la partida
            for (int j = 0; j < vbaraja.size(); j++)
            {
                if (vpartidas[i].baraja.identificadorBaraja == vbaraja[j].identificadorBaraja)
                {
                    vbaraja.erase(vbaraja.begin() + j);
                }
            }

            vpartidas.erase(vpartidas.begin() + i); // Eliminamos la partida
        }
    }

    // Eliminar a ambos jugadores del vector de jugadores
    for (int i = 0; i < vjugadores.size();)
    {
        if (vjugadores[i].identificadorUsuario == id1 || vjugadores[i].identificadorUsuario == id2)
        {
            vjugadores.erase(vjugadores.begin() + i); // Eliminar el jugador
        }
        else
        {
            i++; // Incrementar si no se ha eliminado un jugador del vector
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// ASIGNA UNA CARTA RANDOM DEL VECTOR DE CARTAS AL JUGADOR Y LAS INTRODUCE EN SU VECTOR
/*----------------------------------------------------------------------------------------------------------------------------------------*/
void asignarCarta(vector<struct jugadores> &vjugadores, int id, vector<struct barajas> &vbaraja, int b)
{
    b--;
    int tam = vbaraja[b].cartaBaraja.size();
    int numero = 0;
    numero = rand() % tam;

    for (int i = 0; i < vjugadores.size(); i++)
    {
        if (vjugadores[i].identificadorUsuario == id)
        {
            vjugadores[i].cartas.push_back(vbaraja[b].cartaBaraja[numero]);
            vbaraja[b].cartaBaraja.erase(vbaraja[b].cartaBaraja.begin() + numero);
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// CALCULA LA SUMA DE LAS CARTAS DE UN JUGADOR
/*----------------------------------------------------------------------------------------------------------------------------------------*/
int calcularSuma(vector<struct jugadores> &vjugadores, int i)
{
    int posvector;
    for (int a = 0; a < vjugadores.size(); a++)
    {
        if (vjugadores[a].identificadorUsuario == i)
        {
            posvector = a;
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
                }

                // Diamantes
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
                else if (vjugadores[a].cartas[j] == "2 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 2;
                }
                else if (vjugadores[a].cartas[j] == "3 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 3;
                }
                else if (vjugadores[a].cartas[j] == "4 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 4;
                }
                else if (vjugadores[a].cartas[j] == "5 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 5;
                }
                else if (vjugadores[a].cartas[j] == "6 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 6;
                }
                else if (vjugadores[a].cartas[j] == "7 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 7;
                }
                else if (vjugadores[a].cartas[j] == "8 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 8;
                }
                else if (vjugadores[a].cartas[j] == "9 de Tréboles")
                {
                    vjugadores[a].suma = vjugadores[a].suma + 9;
                }
                else if (vjugadores[a].cartas[j] == "10 de Tréboles" || vjugadores[a].cartas[j] == "Jota de Tréboles" || vjugadores[a].cartas[j] == "Reina de Tréboles" || vjugadores[a].cartas[j] == "Rey de Tréboles")
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

            // Ahora para los As
            for (int j = 0; j < vjugadores[a].cartas.size(); j++)
            {
                if (vjugadores[a].cartas[j] == "As de Corazones" || vjugadores[a].cartas[j] == "As de Diamantes" || vjugadores[a].cartas[j] == "As de Tréboles" || vjugadores[a].cartas[j] == "As de Picas")
                {
                    if ((vjugadores[a].suma + 11) > 21)
                    {
                        vjugadores[a].suma = vjugadores[a].suma + 1;
                    }
                    else if ((vjugadores[a].suma + 11) <= 21)
                    {
                        vjugadores[a].suma = vjugadores[a].suma + 11;
                    }
                }
            }
        }
    }

    return vjugadores[posvector].suma;
}