/**
 * @file cliente.cc
 * @author Laura Muñoz Jurado y Sandra Rider Gómez
 * @brief Cliente para un sistema de juego de cartas BlackJack.
 * @date 2024
 *
 * Este programa implementa el cliente de un sistema de juego de cartas BlackJack.
 * Se conecta a un servidor mediante sockets, envía y recibe mensajes en un bucle
 * hasta que el servidor se desconecta o el usuario decide salir.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

/**
 * @fn int main()
 * @brief Función principal del cliente BlackJack.
 *
 * Establece la conexión con el servidor de BlackJack, luego entra en un bucle
 * donde espera mensajes del servidor o del usuario. Los mensajes se envían al servidor
 * y las respuestas se reciben para su visualización. El cliente finaliza cuando
 * el servidor se apaga o el usuario ingresa el comando "SALIR".
 *
 * @return int Si la ejecución fue exitosa retorna 0 y retorna otro valor si hubo un error.
 */
int main()
{
    int sd;                      // Descriptor del socket
    struct sockaddr_in sockname; // Estructura para almacenar la dirección del servidor
    char buffer[250];            // Buffer para la comunicación
    socklen_t len_sockname;
    fd_set readfds, auxfds;
    int salida;
    int fin = 0;

    // Se abre el socket para la conexión
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("No se puede abrir el socket cliente\n");
        exit(1);
    }

    // Configuración del servidor
    sockname.sin_family = AF_INET;
    sockname.sin_port = htons(2060); // El servidor aceptará servicios en el puerto 2060
    sockname.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Solicitud de conexión con el servidor
    len_sockname = sizeof(sockname);

    if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
    {
        perror("Error de conexión");
        exit(1);
    }

    // Inicializamos las estructuras
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);

    FD_SET(0, &readfds);
    FD_SET(sd, &readfds);

    // Bucle de comunicación
    do
    {
        auxfds = readfds;
        salida = select(sd + 1, &auxfds, NULL, NULL, NULL);

        // Si hay mensaje desde el servidor
        if (FD_ISSET(sd, &auxfds))
        {

            bzero(buffer, sizeof(buffer));
            int bytesRecibidos = recv(sd, buffer, sizeof(buffer), 0);

            if (bytesRecibidos == 0)
            {
                printf("El servidor de BlackJack se ha apagado.\n\n");
                fin = 1;
            }
            else if (bytesRecibidos > 0)
            {
                printf("\n%s\n", buffer);

                if (strcmp(buffer, "Demasiados clientes conectados\n") == 0)
                    fin = 1;

                if (strcmp(buffer, "El servidor de BlackJack se ha apagado.\n") == 0)
                    fin = 1;

                if (strcmp(buffer, "Desconexión servidor\n") == 0)
                    fin = 1;
            }
        }
        else
        {

            // Si ha introducido información por teclado
            if (FD_ISSET(0, &auxfds))
            {
                bzero(buffer, sizeof(buffer));

                fgets(buffer, sizeof(buffer), stdin);

                if (strcmp(buffer, "SALIR\n") == 0)
                {
                    fin = 1;
                }

                send(sd, buffer, sizeof(buffer), 0);
            }
        }

    } while (fin == 0);

    close(sd); // Cierra el socket

    return 0;
}
