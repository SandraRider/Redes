/**
 * @file Servidor.hpp
 * @author Laura Muñoz Jurado y Sandra Rider Gómez
 * @brief Prototipo de las funciones para un sistema de juego de cartas BlackJack.
 * @date 2024
 */

#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Define el número máximo de clientes.
 */
#define MAX_CLIENTES 30

/**
 * @brief Define el tamaño máximo de línea.
 */
#define MAX_LINEA 100

/**
 * @struct jugadores
 * @brief Estructura de un jugador.
 *
 * @param usuario Nombre del jugador.
 * @param contraseña Contraseña del jugador.
 * @param turno Indica si es el turno del jugador (true) o es el turno del oponente (false).
 * @param estado Estado de conexión del jugador (0 = no conectado, 1 = usuario conectado, 2 = contraseña correcta, 3 = quiere empezar partida y 4 = jugando en una partida).
 * @param cartas Vector de cartas que tiene el jugador.
 * @param suma Suma de los valores de las cartas del jugador.
 * @param plantado Indica si el jugador se ha plantado (true) o no (false).
 * @param identificadorPartida ID de la partida en la que está el jugador.
 * @param identificadorUsuario ID único del jugador (socket).
 */
struct jugadores
{
    string usuario;
    string contraseña;
    bool turno;
    int estado;
    vector<string> cartas;
    int suma;
    bool plantado;
    int identificadorPartida;
    int identificadorUsuario;
};

/**
 * @struct barajas
 * @brief Estructura de una baraja de cartas.
 *
 * @param cartaBaraja Vector que contiene las cartas de la baraja.
 * @param identificadorBaraja ID de la baraja.
 */
struct barajas
{
    vector<string> cartaBaraja;
    int identificadorBaraja;
};

/**
 * @struct partidas
 * @brief Estructura de una partida.
 *
 * @param jugador1 Primer jugador de la partida.
 * @param jugador2 Segundo jugador de la partida.
 * @param baraja Baraja utilizada en la partida.
 */
struct partidas
{
    struct jugadores jugador1;
    struct jugadores jugador2;
    struct barajas baraja;
};

/**
 * @fn struct barajas crearBaraja()
 * @brief Crea y retorna una baraja de cartas completa.
 * 
 * @return struct barajas Una estructura barajas que contiene todas las cartas.
 */
struct barajas crearBaraja();

/**
 * @fn bool ConectadoConUsuario(vector<struct jugadores> &vjugadores, int id, const char *jugador)
 * @brief Comprueba si un jugador está conectado con su usuario.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * @param jugador Nombre del jugador.
 * 
 * @return bool Si el jugador está conectado con su usuario (true) o si no lo está (false).
 */
bool ConectadoConUsuario(vector<struct jugadores> &vjugadores, int id, const char *jugador);

/**
 * @fn bool ConectadoConUsuarioYContraseña(vector<jugadores> &vjugadores, int id)
 * @brief Comprueba si un jugador está conectado con su usuario y contraseña.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * 
 * @return bool Si el jugador está conectado con su usuario y contraseña (true) o si no lo está (false).
 */
bool ConectadoConUsuarioYContraseña(vector<jugadores> &vjugadores, int id);

/**
 * @fn bool comprobarConexiones(vector<struct jugadores> vjugadores, int id)
 * @brief Comprueba si hay espacio en el vector de jugadores.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * 
 * @return bool Si hay espacio disponible (true) o si no hay espacio (false).
 */
bool comprobarConexiones(vector<struct jugadores> vjugadores, int id);

/**
 * @fn int IntroducirUsuarioRegistrado(vector<struct jugadores> &vjugadores, int id, const char *jugador)
 * @brief Introduce un usuario registrado en el vector de jugadores.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * @param jugador Nombre del jugador.
 * 
 * @return int Estado de la operación: 1 si no hay espacio en el vector, 2 si el usuario es incorrecto, 3 si se introdujo correctamente.
 */
int IntroducirUsuarioRegistrado(vector<struct jugadores> &vjugadores, int id, const char *jugador);

/**
 * @fn bool IntroducirContraseña(vector<struct jugadores> &vjugadores, int id, const char *contrasena)
 * @brief Comprueba que la contraseña de un jugador sea correcta y lo introduce en el vector de jugadores.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * @param contrasena Contraseña del jugador.
 * 
 * @return bool Si la contraseña es correcta (true) o si es incorrecta (false).
 */
bool IntroducirContraseña(vector<struct jugadores> &vjugadores, int id, const char *contrasena);

/**
 * @fn bool RegistrarJugadorFichero(char *jugador, char *contrasena)
 * @brief Registra un nuevo jugador en el fichero de texto y comprueba que el nombre no esté registrado.
 * 
 * @param jugador Nombre del jugador.
 * @param contrasena Contraseña del jugador.
 * 
 * @return bool Si el jugador fue registrado con éxito (true) o si el jugador ya está registrado o hubo un error (false).
 */
bool RegistrarJugadorFichero(char *jugador, char *contrasena);

/**
 * @fn int meterJugadorEnPartida(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja, int *id2, int *b)
 * @brief Añade un jugador a una partida o crea una nueva partida si no hay jugadores esprando jugar.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * @param vpartidas Vector que contiene las partidas.
 * @param vbaraja Vector que contiene las barajas.
 * @param id2 Puntero al identificador del segundo jugador (socket).
 * @param b Puntero al identificador de la baraja.
 * 
 * @return int Estado de la operación: 1 si el jugador fue añadido, 2 si se creó una nueva partida, 0 si falló.
 */
int meterJugadorEnPartida(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja, int *id2, int *b);

/**
 * @fn void eliminaJugador(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja)
 * @brief Elimina a un jugador del vector de jugadores cuando se desconecta.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * @param vpartidas Vector que contiene las partidas.
 * @param vbaraja Vector que contiene las barajas.
 * 
 * @return void No retorna nada.
 */
void eliminaJugador(vector<struct jugadores> &vjugadores, int id, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja);

/**
 * @fn void eliminaJugadoresPartida(vector<struct jugadores> &vjugadores, int id1, int id2, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja)
 * @brief Elimina ambos jugadores de la partida y del vector de jugadores actualizando las estructuras correspondientes.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id1 Identificador del primer jugador (socket).
 * @param id2 Identificador del segundo jugador (socket).
 * @param vpartidas Vector que contiene las partidas.
 * @param vbaraja Vector que contiene las barajas.
 * 
 * @return void No retorna nada.
 */
void eliminaJugadoresPartida(vector<struct jugadores> &vjugadores, int id1, int id2, vector<struct partidas> &vpartidas, vector<struct barajas> &vbaraja);

/**
 * @fn void asignarCarta(vector<struct jugadores> &vjugadores, int id, vector<struct barajas> &vbaraja, int b)
 * @brief Asigna una carta al azar de la baraja a un jugador.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param id Identificador del jugador (socket).
 * @param vbaraja Vector que contiene las barajas.
 * @param b Identificador de la baraja.
 * 
 * @return void No retorna nada.
 */
void asignarCarta(vector<struct jugadores> &vjugadores, int id, vector<struct barajas> &vbaraja, int b);

/**
 * @fn int calcularSuma(vector<struct jugadores> &vjugadores, int i)
 * @brief Calcula la suma de las cartas de un jugador.
 * 
 * @param vjugadores Vector que contiene los jugadores.
 * @param i Identificador del jugador (socket).
 * 
 * @return int La suma total de las cartas del jugador.
 */
int calcularSuma(vector<struct jugadores> &vjugadores, int i);

#endif
