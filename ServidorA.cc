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

#include "servidora.hpp"

#define MSG_SIZE 250   // El tamaño máximo envío una cadena de longitud 250 caracteres
#define MAX_CLIENTS 30 // El número máximo de clientes conectados será de 30 usuarios

using namespace std;

/*
 * El servidor ofrece el servicio de un juego BlackJack
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
    sockname.sin_port = htons(2060); // El servidor aceptará servicios en el puerto 2060
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

                                printf("Cliente <%d> conectado.\n", new_sd);

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
                        /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                        /* SALIR POR PARTE DEL SERVIDOR */
                        /*---------------------------------------------------------------------------------------------------------------------------------------------------*/

                        // Se ha introducido información de teclado
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer), stdin);

                        // Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                        if (strcmp(buffer, "SALIR\n") == 0)
                        {
                            bzero(buffer, sizeof(buffer));
                            strcpy(buffer, "El servidor de BlackJack se ha apagado.\n");

                            for (j = 0; j < numClientes; j++)
                            {
                                send(arrayClientes[j], buffer, sizeof(buffer), 0);
                                // close(arrayClientes[j]);
                                // FD_CLR(arrayClientes[j], &readfds);
                                salirCliente(arrayClientes[j], &readfds, &numClientes, arrayClientes);
                            }

                            printf("Servidor apagado correctamente.\n");
                            close(sd);
                            exit(0);
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
                            /* SALIR POR PARTE DEL CLIENTE */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            if (strcmp(buffer, "SALIR\n") == 0)
                            {

                                int estadoJugador = 0;
                                // Mira el estado del jugador (si esta en una partida jugando)
                                for (int a = 0; a < vjugadores.size(); a++)
                                {
                                    if (vjugadores[a].identificadorUsuario == i)
                                    {
                                        estadoJugador = vjugadores[a].estado;
                                    }
                                }

                                if (estadoJugador == 4) // Si el jugador esta en una partida
                                {
                                    int idJugador2 = 0;
                                    for (int h = 0; h < vpartidas.size(); h++)
                                    {
                                        if (vpartidas[h].jugador1.identificadorUsuario == i)
                                        {
                                            idJugador2 = vpartidas[h].jugador2.identificadorUsuario;
                                        }
                                        else if (vpartidas[h].jugador2.identificadorUsuario == i)
                                        {
                                            idJugador2 = vpartidas[h].jugador1.identificadorUsuario;
                                        }
                                    }
                                    // Avisa al otro jugador de que se ha salido de la partida
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+Ok. Tu oponente ha terminado la partida");
                                    send(idJugador2, buffer, sizeof(buffer), 0);

                                    // Elimina a ambos jugadores de la partida
                                    eliminaJugadoresPartida(vjugadores, i, idJugador2, vpartidas, vbaraja);
                                }
                                else if (estadoJugador == 3)
                                {
                                    // Elimina al jugador de la lista de espera
                                    eliminaJugador(vjugadores, i, vpartidas, vbaraja);
                                }

                                salirCliente(i, &readfds, &numClientes, arrayClientes);
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* INICIAR SESIÓN USUARIO (INTRODUCE EL USUARIO Y SI HAY HUECO LO INTRODUCE EN EL VECTOR) */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else if (strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0)
                            {
                                // Cojo el nombre del usuario
                                char jugador[250];
                                sscanf(buffer, "USUARIO %s", jugador);
                                int introducir = IntroducirUsuarioRegistrado(vjugadores, i, jugador);

                                if (introducir == 3) // El usuario es correcto y se ha introducido el juagdor en el vector
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+OK. USUARIO correcto.");
                                    send(i, buffer, sizeof(buffer), 0);

                                    printf("Cliente <%d> conectado con usuario correctamente.\n", i);

                                    // for (int h = 0; h < vjugadores.size(); h++)
                                    // {
                                    //     printf("IDUSUARIO: %d\n", vjugadores[h].identificadorUsuario);
                                    //     printf("TAMANO_VJUGADORES; %lu\n", vjugadores.size());
                                    // }
                                }
                                else if (introducir == 2) // El usuario que ha introducido el jugador es incorrecto
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. USUARIO incorrecto.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else if (introducir == 1) // No hay espacio en el vector para que se introduzca
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. Demasiados clientes conectados.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* INTRODUCIR CONTRASEÑA */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else if (strncmp(buffer, "PASSWORD ", strlen("PASSWORD ")) == 0)
                            {

                                char contrasena[250];
                                sscanf(buffer, "PASSWORD %s", contrasena);

                                if (IntroducirContraseña(vjugadores, i, contrasena) == true) // La contraseña es correcto y se actualiza el estado a 2
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+OK. Usuario validado");
                                    send(i, buffer, sizeof(buffer), 0);

                                    printf("Cliente <%d> conectado con contraseña correctamente.\n", i);
                                }
                                else // La contraseña que ha introducido el jugador es incorrecta
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. Error en la validacion");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* REGISTRARSE UN USUARIO NUEVO (METERLO EN EL FICHERO DE TEXTO) */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else if (strncmp(buffer, "REGISTRO ", strlen("REGISTRO ")) == 0)
                            {

                                char contrasena[250];
                                char usuario[250];
                                sscanf(buffer, "REGISTRO -u %s -p %s", usuario, contrasena);

                                if (RegistrarJugadorFichero(usuario, contrasena) == true) // El usuario ha sido registrado en el fichero de texto
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "+OK. Usuario registrado correctamente");
                                    send(i, buffer, sizeof(buffer), 0);

                                    printf("Cliente <%d> registrado correctamente.\n", i);
                                }
                                else // El usuario introducido ya esta en el fichero de texto
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. El nombre de usuario ya ha sido utilizado");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* INICIAR PARTIDA -> el usuario solicita jugar una partida de blackjack */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else if (strncmp(buffer, "INICIAR-PARTIDA", strlen("INICIAR-PARTIDA")) == 0)
                            {
                                // Comprobamos que el jugador está logueado en el servidor con su usuario y contraseña
                                bool conectado = false;
                                conectado = ConectadoConUsuarioYContraseña(vjugadores, i);

                                if (conectado)
                                {
                                    // IniciarPartida(vjugadores, i, vpartidas);
                                    int aux, j, b;

                                    aux = meterJugadorEnPartida(vjugadores, i, vpartidas, vbaraja, &j, &b);

                                    printf("Cliente <%d> buscando partida.\n", i);

                                    if (aux == 1)
                                    {
                                        printf("Los clientes <%d> y <%d> han encontrado partida.\n", i, j);

                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "+Ok. Empieza la partida.\n-> Repartiendo cartas...");
                                        send(i, buffer, sizeof(buffer), 0);

                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "+Ok. Empieza la partida.\n-> Repartiendo cartas...");
                                        send(j, buffer, sizeof(buffer), 0);

                                        // Asignamos las cartas al jugador 1
                                        asignarCarta(vjugadores, i, vbaraja, b);
                                        asignarCarta(vjugadores, i, vbaraja, b);

                                        // Decirle al jugador 1 que cartas tiene
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-> Tus cartas son:");
                                        send(i, buffer, sizeof(buffer), 0);

                                        for (int l = 0; l < vjugadores.size(); l++)
                                        {
                                            if (vjugadores[l].identificadorUsuario == i)
                                            {
                                                for (int c = 0; c < vjugadores[l].cartas.size(); c++)
                                                {
                                                    bzero(buffer, sizeof(buffer));
                                                    sprintf(buffer, "\t%s", vjugadores[l].cartas[c].c_str());
                                                    send(i, buffer, sizeof(buffer), 0);
                                                }
                                            }
                                        }
                                        // Decirle al jugador 1 la suma de las cartas que tiene
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-> Suma de tus cartas: %d", calcularSuma(vjugadores, i));
                                        send(i, buffer, sizeof(buffer), 0);

                                        // Asignamos las cartas al jugador 2
                                        asignarCarta(vjugadores, j, vbaraja, b);
                                        asignarCarta(vjugadores, j, vbaraja, b);

                                        // Decirle al jugador 2 que cartas tiene
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-> Tus cartas son:");
                                        send(j, buffer, sizeof(buffer), 0);

                                        for (int l = 0; l < vjugadores.size(); l++)
                                        {
                                            if (vjugadores[l].identificadorUsuario == j)
                                            {
                                                for (int c = 0; c < vjugadores[l].cartas.size(); c++)
                                                {
                                                    bzero(buffer, sizeof(buffer));
                                                    sprintf(buffer, "\t%s", vjugadores[l].cartas[c].c_str());
                                                    send(j, buffer, sizeof(buffer), 0);
                                                }
                                            }
                                        }

                                        // Decirle al jugador 2 la suma de las cartas que tiene
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-> Suma de tus cartas: %d", calcularSuma(vjugadores, j));
                                        send(j, buffer, sizeof(buffer), 0);


                                        // Decirle al jugador 1 la primera carta del jugador 2
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-> Tu oponente ha recibido la carta:");
                                        send(i, buffer, sizeof(buffer), 0);
                                        for (int l = 0; l < vjugadores.size(); l++)
                                        {
                                            if (vjugadores[l].identificadorUsuario == j)
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "\t%s", vjugadores[l].cartas[0].c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                        }

                                        // Decirle al jugador 2 la primera carta del jugador 1
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-> Tu oponente ha recibido la carta:");
                                        send(j, buffer, sizeof(buffer), 0);
                                        for (int l = 0; l < vjugadores.size(); l++)
                                        {
                                            if (vjugadores[l].identificadorUsuario == i)
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "\t%s", vjugadores[l].cartas[0].c_str());
                                                send(j, buffer, sizeof(buffer), 0);
                                            }
                                        }


                                        if (calcularSuma(vjugadores, i) == 21) // BLACKJACK del jugador 1
                                        {
                                            bzero(buffer, sizeof(buffer));
                                            sprintf(buffer, "-> ¡BLACKJACK!");
                                            send(i, buffer, sizeof(buffer), 0);
                                        }
                                        if (calcularSuma(vjugadores, j) == 21) // BLACKJACK del jugador 2
                                        {
                                            bzero(buffer, sizeof(buffer));
                                            sprintf(buffer, "-> ¡BLACKJACK!");
                                            send(j, buffer, sizeof(buffer), 0);
                                        }
                                    }
                                    else if (aux == 2)
                                    {
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "+Ok. Esperando otro jugador");
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                }
                                else if (!conectado)
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. No puedes iniciar partida sin antes loguearte.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* PEDIR CARTA -> el usuario pide una nueva carta si no ha superado los 21 puntos */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else if (strncmp(buffer, "PEDIR-CARTA", strlen("PEDIR-CARTA")) == 0)
                            {
                                // Comprobamos que el jugador está logueado en el servidor con su usuario y contraseña
                                bool conectado = false;
                                conectado = ConectadoConUsuarioYContraseña(vjugadores, i);

                                if (conectado) // Si el jugador está logueado
                                {
                                    bool turnoJugador, plantadoJugador;
                                    int estadoJugador = 0;
                                    // Mira el turno del jugador
                                    for (int a = 0; a < vjugadores.size(); a++)
                                    {
                                        if (vjugadores[a].identificadorUsuario == i)
                                        {
                                            estadoJugador = vjugadores[a].estado;
                                            turnoJugador = vjugadores[a].turno;
                                            plantadoJugador = vjugadores[a].plantado;
                                        }
                                    }

                                    if (estadoJugador == 4) // Si el jugador ha iniciado una partida
                                    {
                                        if (!plantadoJugador) // Si el jugador no se ha plantado (plantado = false)
                                        {
                                            if (turnoJugador) // Si es el turno del jugador (turno = true)
                                            {
                                                int idbaraja = 0, idJugador2 = 0;
                                                bool plantadoJugador2;
                                                for (int h = 0; h < vpartidas.size(); h++)
                                                {
                                                    if (vpartidas[h].jugador1.identificadorUsuario == i)
                                                    {
                                                        idbaraja = vpartidas[h].baraja.identificadorBaraja;
                                                        idJugador2 = vpartidas[h].jugador2.identificadorUsuario;
                                                        plantadoJugador2 = vpartidas[h].jugador2.plantado;
                                                    }
                                                    else if (vpartidas[h].jugador2.identificadorUsuario == i)
                                                    {
                                                        idbaraja = vpartidas[h].baraja.identificadorBaraja;
                                                        idJugador2 = vpartidas[h].jugador1.identificadorUsuario;
                                                        plantadoJugador2 = vpartidas[h].jugador1.plantado;
                                                    }
                                                }

                                                for (int l = 0; l < vjugadores.size(); l++)
                                                {
                                                    if (vjugadores[l].identificadorUsuario == i)
                                                    {
                                                        if (calcularSuma(vjugadores, i) < 21) // El jugador puede pedir cartas
                                                        {
                                                            asignarCarta(vjugadores, i, vbaraja, idbaraja);

                                                            // Decirle al jugador que cartas tiene
                                                            bzero(buffer, sizeof(buffer));
                                                            sprintf(buffer, "-> Tus cartas son:");
                                                            send(i, buffer, sizeof(buffer), 0);
                                                            // Imprime las cartas del jugador
                                                            for (int c = 0; c < vjugadores[l].cartas.size(); c++)
                                                            {
                                                                bzero(buffer, sizeof(buffer));
                                                                sprintf(buffer, "\t%s", vjugadores[l].cartas[c].c_str());
                                                                send(i, buffer, sizeof(buffer), 0);
                                                            }
                                                            // Imprime la suma de las cartas del jugador
                                                            bzero(buffer, sizeof(buffer));
                                                            sprintf(buffer, "-> Suma de tus cartas: %d", calcularSuma(vjugadores, i));
                                                            send(i, buffer, sizeof(buffer), 0);
                                                        }
                                                        else if (calcularSuma(vjugadores, i) == 21) // El jugador no puede pedir más cartas, ya tiene 21 puntos
                                                        {
                                                            bzero(buffer, sizeof(buffer));
                                                            sprintf(buffer, "-ERR. No puedes pedir más cartas, ya que tu suma es igual a 21.");
                                                            send(i, buffer, sizeof(buffer), 0);
                                                        }
                                                        else if (calcularSuma(vjugadores, i) > 21) // El jugador no puede pedir más cartas, se ha pasado de 21 puntos
                                                        {
                                                            bzero(buffer, sizeof(buffer));
                                                            sprintf(buffer, "-ERR. Excedido el valor de 21.");
                                                            send(i, buffer, sizeof(buffer), 0);
                                                        }

                                                        /*------------------------------------------------------------------------------------------------------------------------------------------------*/
                                                        /* NO FUNCIONA CUANDO UN JUGADOR SE PLANTA Y EL OTRO PIDE MÁS CARTAS (FUNCIONA SOLO 1 VEZ, LA SEGUNDA VEZ QUE PIDE CARTAS DICE QUE NO ES SU TURNO)*/
                                                        /*------------------------------------------------------------------------------------------------------------------------------------------------*/

                                                        /*
                                                        if (!plantadoJugador2) // Si no se ha plantado el Jugador 2
                                                        {
                                                            vjugadores[l].turno = false; // Cambia el turno del jugador 1 a false, ya que ha pedido una carta
                                                        }
                                                        */
                                                    }/*
                                                    else if ((vjugadores[l].identificadorUsuario == idJugador2) && (!vjugadores[l].plantado))
                                                    {
                                                        // Cambia el turno del jugador 2 a true, ya que el jugador 1 ya ha pedido carta
                                                        vjugadores[l].turno = true;
                                                    }*/
                                                }
                                            }
                                            else if (!turnoJugador) // Si no es el turno del jugador (turno = false)
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "-ERR. Turno del jugador contrario. Espera al otro jugador.");
                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                        }
                                        else if (plantadoJugador) // Si el jugador se ha plantado
                                        {
                                            bzero(buffer, sizeof(buffer));
                                            sprintf(buffer, "-ERR. No puedes pedir carta. Te has plantado.");
                                            send(i, buffer, sizeof(buffer), 0);
                                        }
                                    }
                                    else if (estadoJugador != 4) // Si el jugador no ha iniciado una partida
                                    {
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-ERR. No puedes pedir carta sin antes iniciar partida.");
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                }
                                else // Si el jugador no está logueado
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. No puedes pedir carta sin antes loguearte.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* PLANTARME -> el usuario indica que ya no quiere más cartas y se planta con las que tiene */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else if (strncmp(buffer, "PLANTARME", strlen("PLANTARME")) == 0)
                            {
                                // Comprobamos que el jugador está logueado en el servidor con su usuario y contraseña
                                bool conectado = false;
                                conectado = ConectadoConUsuarioYContraseña(vjugadores, i);

                                if (conectado) // El usuario esta logueado
                                {
                                    int estadoJugador = 0;
                                    // Mira el estado del jugador (si esta en una partida jugando)
                                    for (int a = 0; a < vjugadores.size(); a++)
                                    {
                                        if (vjugadores[a].identificadorUsuario == i)
                                        {
                                            estadoJugador = vjugadores[a].estado;
                                        }
                                    }

                                    if (estadoJugador == 4) // Si el jugador esta en una partida
                                    {
                                        int idJugador2 = 0;
                                        for (int h = 0; h < vpartidas.size(); h++)
                                        {
                                            if (vpartidas[h].jugador1.identificadorUsuario == i)
                                            {
                                                idJugador2 = vpartidas[h].jugador2.identificadorUsuario;
                                            }
                                            else if (vpartidas[h].jugador2.identificadorUsuario == i)
                                            {
                                                idJugador2 = vpartidas[h].jugador1.identificadorUsuario;
                                            }
                                        }

                                        // Cambia el jugador a plantado (plantado = true) y cambia el turno del otro jugador a true
                                        for (int a = 0; a < vjugadores.size(); a++)
                                        {
                                            if (vjugadores[a].identificadorUsuario == i) // El jugador 1 se planta
                                            {
                                                vjugadores[a].plantado = true;
                                                vjugadores[a].turno = false;

                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Te has plantado.");
                                                send(i, buffer, sizeof(buffer), 0);
                                            }
                                            else if (vjugadores[a].identificadorUsuario == idJugador2) // El jugador 2 puede seguir jugando
                                            {
                                                vjugadores[a].turno = true;
                                            }
                                        }

                                        int aux = 0; // Auxiliar para comprobar si se han plantado los dos
                                        for (int a = 0; a < vjugadores.size(); a++)
                                        {
                                            if ((vjugadores[a].identificadorUsuario == i) && (vjugadores[a].plantado))
                                                aux++;

                                            else if ((vjugadores[a].identificadorUsuario == idJugador2) && (vjugadores[a].plantado))
                                                aux++;
                                        }

                                        if (aux == 1)
                                        {
                                            bzero(buffer, sizeof(buffer));
                                            sprintf(buffer, "+Ok. Esperando que finalice el otro jugador");
                                            send(i, buffer, sizeof(buffer), 0);
                                        }
                                        else if (aux == 2) // Si se han plantado los dos, comparamos quien ha ganado
                                        {
                                            int sumaJugador1 = 0, sumaJugador2 = 0;
                                            string usuario1, usuario2;

                                            for (int a = 0; a < vjugadores.size(); a++)
                                            {
                                                if (vjugadores[a].identificadorUsuario == i)
                                                {
                                                    sumaJugador1 = vjugadores[a].suma;
                                                    usuario1 = vjugadores[a].usuario;
                                                }
                                                else if (vjugadores[a].identificadorUsuario == idJugador2)
                                                {
                                                    sumaJugador2 = vjugadores[a].suma;
                                                    usuario2 = vjugadores[a].usuario;
                                                }
                                            }

                                            // Han empatado los jugadores
                                            if ((sumaJugador1 == sumaJugador2) && (sumaJugador1 <= 21))
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s y Jugador %s habéis empatado la partida", usuario1.c_str(), usuario2.c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s y Jugador %s habéis empatado la partida", usuario1.c_str(), usuario2.c_str());
                                                send(idJugador2, buffer, sizeof(buffer), 0);
                                            }
                                            // Jugador 2 ha ganado la partida y ninguno ha superado 21 puntos
                                            else if ((sumaJugador1 < sumaJugador2) && (sumaJugador1 <= 21) && (sumaJugador2 <= 21))
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario2.c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario2.c_str());
                                                send(idJugador2, buffer, sizeof(buffer), 0);
                                            }
                                            // Jugador 1 ha ganado la partida y ninguno ha superado 21 puntos
                                            else if ((sumaJugador1 > sumaJugador2) && (sumaJugador1 <= 21) && (sumaJugador2 <= 21))
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario1.c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario1.c_str());
                                                send(idJugador2, buffer, sizeof(buffer), 0);
                                            }
                                            // Jugador 1 ha ganado la partida porque el Jugador 2 ha superado los 21 puntos
                                            else if ((sumaJugador1 <= 21) && (sumaJugador2 > 21))
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario1.c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario1.c_str());
                                                send(idJugador2, buffer, sizeof(buffer), 0);
                                            }
                                            // Jugador 2 ha ganado la partida porque el Jugador 1 ha superado los 21 puntos
                                            else if ((sumaJugador1 > 21) && (sumaJugador2 <= 21))
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario2.c_str());
                                                send(i, buffer, sizeof(buffer), 0);
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. Jugador %s ha ganado la partida", usuario2.c_str());
                                                send(idJugador2, buffer, sizeof(buffer), 0);
                                            }
                                            // Ninguno ha ganado, los dos ha superado los 21 puntos
                                            else if ((sumaJugador1 > 21) && (sumaJugador2 > 21))
                                            {
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. No hay ganadores");
                                                send(i, buffer, sizeof(buffer), 0);
                                                bzero(buffer, sizeof(buffer));
                                                sprintf(buffer, "+Ok. No hay ganadores");
                                                send(idJugador2, buffer, sizeof(buffer), 0);
                                            }

                                            // Elimina a ambos jugadores de la partida
                                            eliminaJugadoresPartida(vjugadores, i, idJugador2, vpartidas, vbaraja);
                                        }
                                    }
                                    else if (estadoJugador != 4) // Si el jugador no ha iniciado una partida
                                    {
                                        bzero(buffer, sizeof(buffer));
                                        sprintf(buffer, "-ERR. No puedes plantarte sin antes iniciar partida.");
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                }
                                else // Si el jugador no está logueado
                                {
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "-ERR. No puedes plantarte sin antes loguearte.");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            /* EL USUARIO INTRODUCE UN COMANDO QUE NO SON LOS ANTERIORES */
                            /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                            else // El usuario ha introducido un mensaje que no puede
                            {
                                bzero(buffer, sizeof(buffer));
                                sprintf(buffer, "-ERR. No te permite enviar este mensaje");
                                send(i, buffer, sizeof(buffer), 0);
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
                        /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                        /* EL USUARIO INTRODUCE ctrl+c */
                        /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
                        if (recibidos == 0)
                        {
                            printf("El Cliente <%d> ha salido del servidor\n", i);

                            int estadoJugador = 0;
                            // Mira el estado del jugador (si esta en una partida jugando)
                            for (int a = 0; a < vjugadores.size(); a++)
                            {
                                if (vjugadores[a].identificadorUsuario == i)
                                {
                                    estadoJugador = vjugadores[a].estado;
                                }
                            }

                            if (estadoJugador == 4) // Si el jugador esta en una partida
                            {
                                int idJugador2 = 0;
                                for (int h = 0; h < vpartidas.size(); h++)
                                {
                                    if (vpartidas[h].jugador1.identificadorUsuario == i)
                                    {
                                        idJugador2 = vpartidas[h].jugador2.identificadorUsuario;
                                    }
                                    else if (vpartidas[h].jugador2.identificadorUsuario == i)
                                    {
                                        idJugador2 = vpartidas[h].jugador1.identificadorUsuario;
                                    }
                                }
                                // Avisa al otro jugador de que se ha salido de la partida
                                bzero(buffer, sizeof(buffer));
                                sprintf(buffer, "+Ok. Tu oponente ha terminado la partida");
                                send(idJugador2, buffer, sizeof(buffer), 0);

                                // Elimina a ambos jugadores de la partida
                                eliminaJugadoresPartida(vjugadores, i, idJugador2, vpartidas, vbaraja);
                            }
                            else if (estadoJugador == 3)
                            {
                                // Elimina al jugador de la lista de espera
                                eliminaJugador(vjugadores, i, vpartidas, vbaraja);
                            }

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
    printf("Cliente <%d> desconectado.\n", socket);

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
