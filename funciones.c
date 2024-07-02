#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorTamano(int *numHabitacion, char habitaciones[9][3][40], double precios[9]) {
    char tipo[20];
    printf("Ingrese el tipo de habitacion que desea buscar: ");
    scanf("%s", tipo);
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0){
            printf("Habitacion: %s en %s. Precio: %.2f\n", habitaciones[i][0], habitaciones[i][2], precios[i]);
        }
    }
    printf("Ingrese el numero de habitacion que desea reservar: ");
    scanf("%d", numHabitacion);
}

void buscarHotel(int *numHabitacion, char habitaciones[9][3][40], double precios[9]) {
    char hotel[40];
    printf("Ingrese el nombre del hotel: ");
    scanf("%s", hotel);

    printf("Habitaciones disponibles en %s:\n", hotel);
    int found = 0; 
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], hotel) == 0) {
            printf("Habitacion %s (%s) cuesta %.2f\n", habitaciones[i][0], habitaciones[i][1], precios[i]);
            found = 1;
        }
    }

    if (found) {
        printf("Ingrese el numero de habitacion que desea buscar: ");
        scanf("%d", numHabitacion);
    } else {
        printf("No se encontraron habitaciones disponibles en el hotel %s.\n", hotel);
        *numHabitacion = -1;  
    }
}

void realizarReserva(int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4], double precios[9]) {
    if (numHabitacion < 1 || numHabitacion > 9) {
        printf("Numero de habitación invalido.\n");
        return;
    }

    char nombre[40];
    char cedula[40];

    printf("Ingresa tu nombre por favor: ");
    scanf("%s", nombre);
    printf("Ingresa tu cedula por favor: ");
    scanf("%s", cedula);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = numHabitacion;
            strcpy(clientes[i][0], nombre);
            strcpy(clientes[i][1], cedula);
            reservas[i][1] = i;  
            reservas[i][2] = 0;  
            reservas[i][3] = 1;  

            printf("Reserva realizada con exito.\n");
            printf("Detalle de la reserva:\n");
            printf("Cliente: %s\n", nombre);
            printf("Cedula: %s\n", cedula);
            printf("Habitacion: %s (%s) en %s\n", habitaciones[numHabitacion - 1][0], habitaciones[numHabitacion - 1][1], habitaciones[numHabitacion - 1][2]);
            printf("Precio: %.2f\n", precios[numHabitacion - 1]);

            return;
        }
    }

    printf("No se pudo realizar la reserva, reservas agotadas.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[5][2][40], int reservas[10][4]) {
    char cedula[40];
    printf("Ingresa tu cedula: ");
    scanf("%s", cedula);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] != -1 && strcmp(clientes[reservas[i][1]][1], cedula) == 0) {
            *numReserva = i + 1; 
            printf("Reserva encontrada para %s con cedula %s.\n", clientes[reservas[i][1]][0], cedula);
            return;
        }
    }

    *numReserva = -1; 
    printf("No se encontro ninguna reserva.\n");
}

void imprimirReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1 || reservas[numReserva - 1][0] == -1) {
        printf("Reserva no encontrada.\n");
        return;
    }

    int numHabitacion = reservas[numReserva - 1][0];
    printf("Detalle de la Reserva:\n");
    printf("Numero de Reserva: %d\n", numReserva);
    printf("Habitacion: %s\n", habitaciones[numHabitacion - 1][0]);
    printf("Tipo de Habitacion: %s\n", habitaciones[numHabitacion - 1][1]);
    printf("Hotel: %s\n", habitaciones[numHabitacion - 1][2]);
    printf("Precio: %.2f\n", precios[numHabitacion - 1]);

    if (reservas[numReserva - 1][3] == 1) {
        printf("Estado de reserva: Activa\n");
    } else {
        printf("Estado de reserva: Pagada\n");
    }
}

void pagarReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1 || reservas[numReserva - 1][0] == -1) {
        printf("Reserva no encontrada.\n");
        return;
    }

    int numHabitacion = reservas[numReserva - 1][0];
    printf("Detalles de la reserva:\n");
    printf("Numero de Reserva: %d\n", numReserva);
    printf("Habitacion: %s\n", habitaciones[numHabitacion - 1][0]);
    printf("Tipo de Habitación: %s\n", habitaciones[numHabitacion - 1][1]);
    printf("Hotel: %s\n", habitaciones[numHabitacion - 1][2]);
    printf("Precio: %.2f\n", precios[numHabitacion - 1]);

    if (reservas[numReserva - 1][3] == 0) {
        printf("La reserva ya ha sido pagada anteriormente.\n");
        return;
    }

    printf("Desea pagar esta reserva? (1: Si, 0: No)\n>>");
    int confirmacion;
    scanf("%d", &confirmacion);

    if (confirmacion == 1) {
        reservas[numReserva - 1][3] = 0;
        printf("Reserva pagada con exito.\n");
    } else {
        printf("Pago cancelado.\n");
    }
}

void guardarReservaEnArchivo(FILE *archivo, int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4], double precios[9]) {
    fseek(archivo, 0, SEEK_END);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] != -1) {
            fprintf(archivo, "Reserva realizada:\nCliente: %s\nCedula: %s\nHabitacion: %s (%s) en %s\nPrecio: %.2f\n\n",
                    clientes[reservas[i][1]][0], clientes[reservas[i][1]][1],
                    habitaciones[reservas[i][0] - 1][0], habitaciones[reservas[i][0] - 1][1],
                    habitaciones[reservas[i][0] - 1][2], precios[reservas[i][0] - 1]);
        }
    }
}

void cargarReservasDesdeArchivo(FILE *archivo, char clientes[5][2][40], int reservas[10][4]) {
    char buffer[200];
    int i = 0;

    fseek(archivo, 0, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        if (strncmp(buffer, "Reserva realizada:", 18) == 0) {
            fgets(buffer, sizeof(buffer), archivo);
            sscanf(buffer, "Cliente: %s", clientes[i][0]);

            fgets(buffer, sizeof(buffer), archivo);
            sscanf(buffer, "Cedula: %s", clientes[i][1]);

            fgets(buffer, sizeof(buffer), archivo);
            int numHabitacion;
            sscanf(buffer, "Habitacion: %d", &numHabitacion);

            fgets(buffer, sizeof(buffer), archivo); 
            fgets(buffer, sizeof(buffer), archivo);

            reservas[i][0] = numHabitacion; 
            reservas[i][1] = i; 
            reservas[i][2] = 0; 
            reservas[i][3] = 1; 

            i++;
        }
    }
}
