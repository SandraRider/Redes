// Esto es servidor.cc
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <vector>

#include "servidorLaura.hpp"

#define MSG_SIZE 250
#define MAX_CLIENTS 50

using namespace std;

/*
 * El servidor ofrece el servicio de un chat
 */

void manejador(int signum);
void salirCliente(int socket, fd_set *readfds, int *numClientes, int arrayClientes[]);

int main()
{
    srand(time(0));
    /*----------------------------------------------------
        Descriptor del socket y buffer de datos
    -----------------------------------------------------*/
    int sd, new_sd;
    struct sockaddr_in sockname, from;
    char buffer[MSG_SIZE];
    socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    int arrayClientes[MAX_CLIENTS];
    int numClientes = 0;
    // contadores
    int i, j, k;
    int recibidos;
    char identificador[MSG_SIZE];

    int on, ret;

    vector<struct jugadores> vjugadores;
    vector<struct partidas> vpartidas;
    vector<struct barajas> vbaraja;
    // Esto también podría ponerlo en su lugar, es también un vector:
    // struct jugadores vjugadores[30];

    // Si usamos vectores de la std no hace falta rellenarlos porque empiezan ya vacíos

    /* --------------------------------------------------
        Se abre el socket
    ---------------------------------------------------*/
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("No se puede abrir el socket cliente\n");
        exit(1);
    }

    // Activaremos una propiedad del socket para permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permite· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on = 1;
    ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sockname.sin_family = AF_INET;
    sockname.sin_port = htons(2000);
    sockname.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&sockname, sizeof(sockname)) == -1)
    {
        perror("Error en la operación bind");
        exit(1);
    }

    /*---------------------------------------------------------------------
        Del las peticiones que vamos a aceptar sólo necesitamos el
        tamaño de su estructura, el resto de información (familia, puerto,
        ip), nos la proporcionará el método que recibe las peticiones.
    ----------------------------------------------------------------------*/
    from_len = sizeof(from);

    if (listen(sd, 1) == -1)
    {
        perror("Error en la operación de listen");
        exit(1);
    }

    printf("El servidor de BlackJack está esperando conexiones...\n"); // Inicializar los conjuntos fd_set

    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd, &readfds);
    FD_SET(0, &readfds);

    // Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT, manejador);

    /*-----------------------------------------------------------------------
        El servidor acepta una petición
    ------------------------------------------------------------------------ */
    while (1)
    {

        // Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

        auxfds = readfds;

        salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

        if (salida > 0)
        {

            for (i = 0; i < FD_SETSIZE; i++)
            {

                // Buscamos el socket por el que se ha establecido la comunicación
                if (FD_ISSET(i, &auxfds))
                {

                    if (i == sd)
                    {

                        if ((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1)
                        {
                            perror("Error aceptando peticiones");
                        }
                        else
                        {
                            if (numClientes < MAX_CLIENTS)
                            {
                                arrayClientes[numClientes] = new_sd;
                                numClientes++;
                                FD_SET(new_sd, &readfds);

                                // strcpy guarda en buffer "Bienvenido al chat"
                                strcpy(buffer, "Bienvenido al servidor de BlackJack:");

                                // Se lo manda a new_sd, que es el nuevo conectado
                                send(new_sd, buffer, sizeof(buffer), 0);

                                bzero(buffer, sizeof(buffer));
                                sprintf(buffer, "------------------ OPCIONES ------------------\nUSUARIO usuario\nPASSWORD contraseña\nREGISTRO -u usuario -p contraseña\nINICIAR-PARTIDA\nPEDIR-CARTA\nPLANTARME\nSALIR\n----------------------------------------------\n");
                                send(new_sd, buffer, sizeof(buffer), 0);
                                /*Avisa a todos los jugadores de que alguien se ha conectado, por eso lo quitamos
                                porque no queremos que avise de eso
                                for(j=0; j<(numClientes-1);j++){

                                    bzero(buffer,sizeof(buffer));
                                    sprintf(buffer, "Nuevo Cliente conectado en <%d>",new_sd);
                                    send(arrayClientes[j],buffer,sizeof(buffer),0);
                                }*/

                                // Tampoco necesito la función de añadir jugadores
                                // AnadirJugador(vjugadores, new_sd);

                                // jugadores u;
                                //  u.socket = new_sd;
                                //  u.estado = "conectado";
                                // vjugadores.push_back(u);
                                // meterJugadorEnPartida(vjugadores, i, vpartidas, vbaraja);
                            }
                            else
                            {
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "Demasiados clientes conectados\n");
                                send(new_sd, buffer, sizeof(buffer), 0);
                                close(new_sd);
                            }
                        }
                    }
                    else if (i == 0)
                    {
                        // Se ha introducido información de teclado
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer), stdin);

                        // Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                        if (strcmp(buffer, "SALIR\n") == 0)
                        {

                            for (j = 0; j < numClientes; j++)
                            {
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "Desconexión servidor\n");
                                send(arrayClientes[j], buffer, sizeof(buffer), 0);
                                close(arrayClientes[j]);
                                FD_CLR(arrayClientes[j], &readfds);
                            }
                            close(sd);
                            exit(-1);
                        }
                        // Mensajes que se quieran mandar a los clientes (implementar)
                    }

                    else
                    {
                        bzero(buffer, sizeof(buffer));

                        recibidos = recv(i, buffer, sizeof(buffer), 0);

                        if (recibidos > 0)
                        {
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* SALIR */
                            if (strcmp(buffer, "SALIR\n") == 0)
                            {
                                salirCliente(i, &readfds, &numClientes, arrayClientes);
                            }
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* INICIAR SESIÓN USUARIO (INTRODUCE EL USUARIO Y SI HAY HUECO LO INTRODUCE EN EL VECTOR) */
                            else if (strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0)
                            {
                                // Cojo el nombre del usuario
                                char jugador[250];
                                sscanf(buffer, "USUARIO %s", jugador);
                                int introducir = IntroducirUsuarioRegistrado(vjugadores, i, jugador);

                                if (introducir == 3) // El usuario es correcto y se ha introducido el juagdor en el vector
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+OK, USUARIO correcto.");
                                    send(i, buffer, sizeof(buffer), 0);

                                    for (int h = 0; h < vjugadores.size(); h++)
                                    {
                                        printf("IDUSUARIO: %d\n", vjugadores[h].identificadorUsuario);
                                        printf("TAMANO_VJUGADORES; %lu\n", vjugadores.size());
                                    }
                                }
                                else if (introducir == 2) // El usuario que ha introducido el jugador es incorrecto
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR, USUARIO incorrecto.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else if (introducir == 1) // No hay espacio en el vector para que se introduzca
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR, demasiados clientes conectados.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* INTRODUCIR CONTRASEÑA */
                            else if (strncmp(buffer, "PASSWORD ", strlen("PASSWORD ")) == 0)
                            {

                                char contrasena[250];
                                sscanf(buffer, "PASSWORD %s", contrasena);

                                if (IntroducirContraseña(vjugadores, i, contrasena) == true) // La contraseña es correcto y se actualiza el estado a 2
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+OK, usuario validado");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else // La contraseña que ha introducido el jugador es incorrecta
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR, error en la validacion");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* REGISTRARSE UN USUARIO NUEVO (METERLO EN EL FICHERO DE TEXTO) */
                            else if (strncmp(buffer, "REGISTRO ", strlen("REGISTRO ")) == 0)
                            {

                                char contrasena[250];
                                char usuario[250];
                                sscanf(buffer, "REGISTRO -u %s -p %s", usuario, contrasena);

                                if (RegistrarJugadorFichero(usuario, contrasena) == true) // El usuario ha sido registrado en el fichero de texto
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+OK, usuario registrado correctamente");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else // El usuario introducido ya esta en el fichero de texto
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR, el nombre de usuario ya ha sido utilizado");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* INICIAR PARTIDA */
                            else if (strncmp(buffer, "INICIAR-PARTIDA", strlen("INICIAR-PARTIDA")) == 0)
                            {
                                // IniciarPartida(vjugadores, i, vpartidas);
                                int aux, j, b;

                                aux = meterJugadorEnPartida(vjugadores, i, vpartidas, vbaraja, &j, &b);

                                if (aux == 1)
                                {

                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-Empezando partida");
                                    send(i, buffer, sizeof(buffer), 0);

                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-Empezando partida");
                                    send(j, buffer, sizeof(buffer), 0);

                                    // Asignamos las cartas al jugador 1
                                    asignarCarta(vjugadores, i, vbaraja, b);
                                    asignarCarta(vjugadores, i, vbaraja, b);

                                    // Decirle al jugador 1 que cartas tiene
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-Tus cartas son:");
                                    send(i, buffer, sizeof(buffer), 0);

                                    for (int l = 0; l < vjugadores.size(); l++)
                                    {
                                        if (vjugadores[l].identificadorUsuario == i)
                                        {
                                            for (int c = 0; c < vjugadores[l].cartas.size(); c++)
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "%s", vjugadores[l].cartas[c].c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                        }
                                    }

                                    // Asignamos las cartas al jugador 2
                                    asignarCarta(vjugadores, j, vbaraja, b);
                                    asignarCarta(vjugadores, j, vbaraja, b);

                                    // Decirle al jugador 2 que cartas tiene
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-Tus cartas son:");
                                    send(j, buffer, sizeof(buffer), 0);

                                    for (int l = 0; l < vjugadores.size(); l++)
                                    {
                                        if (vjugadores[l].identificadorUsuario == j)
                                        {
                                            for (int c = 0; c < vjugadores[l].cartas.size(); c++)
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "%s", vjugadores[l].cartas[c].c_str());
                                                send(j, buffer, sizeof(buffer), 0);
                                            }
                                        }
                                    }
                                }
                                else if (aux == 2)
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-Esperando a otro jugador");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* PEDIR CARTA (HACER) */
                            else if (strncmp(buffer, "PEDIR-CARTA", strlen("PEDIR-CARTA")) == 0)
                            {
                                bool turnoJugador;
                                for (int a = 0; a < vjugadores.size(); a++)
                                {
                                    if (vjugadores[a].identificadorUsuario == i)
                                    {
                                        turnoJugador = vjugadores[a].turno;
                                    }
                                }

                                if (turnoJugador)
                                {
                                    int b = 0;
                                    for (int h = 0; h < vpartidas.size(); h++)
                                    {
                                        // for (int k = 0; k < vjugadores.size(); k++)
                                        //{
                                        if (vpartidas[h].jugador1.identificadorUsuario == i)
                                        {
                                            b = vpartidas[h].baraja.identificadorBaraja;
                                        }
                                        //}
                                    }
                                    asignarCarta(vjugadores, i, vbaraja, b);

                                    // Decirle al jugador que cartas tiene
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-Tus cartas son:");
                                    send(i, buffer, sizeof(buffer), 0);

                                    for (int l = 0; l < vjugadores.size(); l++)
                                    {
                                        if (vjugadores[l].identificadorUsuario == i)
                                        {
                                            for (int c = 0; c < vjugadores[l].cartas.size(); c++)
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "%s", vjugadores[l].cartas[c].c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                            vjugadores[l].turno = false; // Cambia el turno del jugador a false, ya que ha pedido carta
                                        }
                                    }
                                }
                                else if (!turnoJugador)
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "Turno del jugador contrario. Espera al otro jugador.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* PLANTARME (HACER) */
                            else if (strncmp(buffer, "PLANTARME", strlen("PLANTARME")) == 0)
                            {
                            }
                            else
                            {
                                bzero(buffer, sizeof(buffer));
                                sprintf(buffer, "-ERR, no te permite enviar este mensaje");
                                send(i, buffer, sizeof(buffer), 0);
                                /*-------------------------------------------------------------------------------------------------------------------------------------------------*/
                            }

                            /* Esto no:
                                else{

                                sprintf(identificador,"<%d>: %s",i,buffer);
                                bzero(buffer,sizeof(buffer));

                                strcpy(buffer,identificador);

                                printf("%s\n", buffer);

                                for(j=0; j<numClientes; j++)
                                    if(arrayClientes[j] != i)
                                        send(arrayClientes[j],buffer,sizeof(buffer),0);


                            }*/
                        }
                        // Si el cliente introdujo ctrl+c
                        if (recibidos == 0)
                        {
                            printf("El Cliente %d, ha introducido ctrl+c\n", i);
                            // Eliminar ese socket
                            salirCliente(i, &readfds, &numClientes, arrayClientes);
                        }
                    }
                }
            }
        }
    }

    close(sd);
    return 0;
}

void salirCliente(int socket, fd_set *readfds, int *numClientes, int arrayClientes[])
{

    char buffer[250];
    int j;

    close(socket);
    FD_CLR(socket, readfds);

    // Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j + 1]);

    (*numClientes)--;

    // bzero(buffer, sizeof(buffer));
    // sprintf(buffer, "Desconexión del cliente <%d>", socket);

    // for (j = 0; j < (*numClientes); j++)
    // if (arrayClientes[j] != socket)
    // send(arrayClientes[j], buffer, sizeof(buffer), 0);
}

void manejador(int signum)
{
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT, manejador);

    // Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}
