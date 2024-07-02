#include <stdio.h>
#include "funciones.h"

int main() {
    char clientes[5][2][40] = { {"Juan", "1789654123"},
                                {"", ""},
                                {"", ""},
                                {"", ""},
                                {"", ""} };

    char habitaciones[9][3][40] = { {"1", "simple", "Dan Carlton"},
                                    {"2", "doble", "Dan Carlton"},
                                    {"3", "triple", "Dan Carlton"},
                                    {"4", "simple", "Swissotel"},
                                    {"5", "doble", "Swissotel"},
                                    {"6", "triple", "Swissotel"},
                                    {"7", "simple", "Sheraton"},
                                    {"8", "doble", "Sheraton"},
                                    {"9", "triple", "Sheraton"} };

    double precios[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};

    int reservas[10][4] = { {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0},
                            {-1, -1, -1, 0} };

    int opcion, numHabitacion, numReserva;

    FILE *archivo = fopen("reservas.txt", "a+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        return -1;
    }

    cargarReservasDesdeArchivo(archivo, clientes, reservas);
    fclose(archivo);

    do {
        printf("Escoja una opcion:\n 1.Buscar Habitacion\n 2.Realizar Reserva\n 3.Ver reservas\n 4.Pagar Reserva\n>>");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("1.Por tamano\n2.Por Hotel\n>>");
                scanf("%d", &opcion);
                switch (opcion) {
                    case 1:
                        buscarPorTamano(&numHabitacion, habitaciones, precios);
                        break;
                    case 2:
                        buscarHotel(&numHabitacion, habitaciones, precios);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                realizarReserva(numHabitacion, habitaciones, clientes, reservas, precios);
                archivo = fopen("reservas.txt", "a+");
                guardarReservaEnArchivo(archivo, numHabitacion, habitaciones, clientes, reservas, precios);
                fclose(archivo);
                break;
            case 3:
                buscarReservaPorCedula(&numReserva, clientes, reservas);
                imprimirReserva(numReserva, reservas, habitaciones, precios);
                break;
            case 4:
                buscarReservaPorCedula(&numReserva, clientes, reservas);
                pagarReserva(numReserva, reservas, habitaciones, precios);
                archivo = fopen("reservas.txt", "a+");
                guardarReservaEnArchivo(archivo, numReserva, habitaciones, clientes, reservas, precios);
                fclose(archivo);
                break;
            default:
                break;
        }
        printf("Desea elegir otra opcion\n1. Si\n2. No\n>>");
        scanf("%d", &opcion);
    } while (opcion == 1);

    return 0;
}
