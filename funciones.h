#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void buscarPorTamano(int *numHabitacion, char habitaciones[9][3][40], double precios[9]);
void buscarHotel(int *numHabitacion, char habitaciones[9][3][40], double precios[9]);
void realizarReserva(int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4], double precios[9]);
void buscarReservaPorCedula(int *numReserva, char clientes[5][2][40], int reservas[10][4]);
void imprimirReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]);
void pagarReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]);
void guardarReservaEnArchivo(FILE *archivo, int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4], double precios[9]);
void cargarReservasDesdeArchivo(FILE *archivo, char clientes[5][2][40], int reservas[10][4]);

#endif 

