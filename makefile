
all: saluda ServidorBlackjack ClienteBlackjack

saluda:
	@echo "Compilando el archivo Servidor y Cliente de Blackjack"

ServidorBlackjack: Servidor.cc ServidorFunciones.cc Servidor.hpp
	g++ Servidor.cc ServidorFunciones.cc -o servidor

ClienteBlackjack: cliente.cc
	g++ cliente.cc -o cliente