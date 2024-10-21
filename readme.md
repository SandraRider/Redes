# Práctica 1 Redes - Servidor Blackjack

Este proyecto implementa un juego de Blackjack que permite a dos jugadores competir entre sí.

## Requisitos

- Tener instalado un compilador de C++ (`g++`).
- Sistema operativo compatible (Linux).

## Organización del Proyecto

La práctica está compuesto por los siguientes archivos:

* `cliente.cc`: Contiene todo el código necesario para el programa cliente.
* `Servidor.cc`: Contiene el código del servidor al que se conectán los clientes.
* `ServidorFunciones.cc`: Contiene el desarrollo de las funciones que utilizará el servidor.
* `Servidor.hpp`: Contiene todas las deifniciones de las funciones y estructuras del servidor.
* `makefile`: Archivo para automatizar la compilación del proyecto.
* `usuarios.txt`: Archivo con los usuarios registrados.

## Primeros Pasos

Para compilar el proyecto, abre una terminal y navega hasta el directorio que contiene el código fuente. Luego, ejecuta el siguiente comando:

```bash
make
```

## Ejecución

Una vez compilado, para ejecutar el proyecto debemos ejecutar los siguientes comandos.
```bash
./cliente
```
```bash
./servidor
```

## Autores

* Laura Muñoz Jurado
* Sandra Rider Gómez
