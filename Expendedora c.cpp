#include <stdio.h>
#define MAX_PRODUCTOS 4
#define MAX_DENOMINACIONES 3

int    codigos[MAX_PRODUCTOS]  = {1, 2, 3, 4};
char   nombres[MAX_PRODUCTOS][20] = {"Agua", "Soda", "Papas", "Chocolate"};
float  precios[MAX_PRODUCTOS]  = {10.0, 15.0, 12.5, 18.0};
int    stocks[MAX_PRODUCTOS]   = {5, 5, 5, 5};

int denominaciones[MAX_DENOMINACIONES] = {10, 5, 1};


void mostrarCatalogo() {
    printf("\n--- CATALOGO ---\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("[%d] %-10s L. %.2f  (stock: %d)\n",
               codigos[i], nombres[i], precios[i], stocks[i]);
    }
}

float insertarDinero(float saldoActual, float monto) {
    if (monto <= 0) {
        printf("Monto invalido.\n");
        return saldoActual;
    }
    return saldoActual + monto;
}

int buscarProducto(int codigo) {
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        if (codigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

int validarSaldo(float precio, float saldo) {
    if (saldo >= precio) {
        return 1;
    }
    return 0;
}

void calcularVuelto(float monto, int idx) {
    if (monto <= 0 || idx >= MAX_DENOMINACIONES) {
        return; 
    }

    int denom = denominaciones[idx];

    if (monto >= denom) {
        printf("  -> L. %d\n", denom);
        calcularVuelto(monto - denom, idx); 
    } else {
        calcularVuelto(monto, idx + 1); 
    }
}

float seleccionarProducto(int codigo, float saldo) {
    int idx = buscarProducto(codigo);

    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return saldo;
    }

    if (stocks[idx] <= 0) {
        printf("Producto agotado.\n");
        return saldo;
    }

    if (!validarSaldo(precios[idx], saldo)) {
        printf("Saldo insuficiente. Faltan L. %.2f\n", precios[idx] - saldo);
        return saldo;
    }

    stocks[idx] = stocks[idx] - 1;
    printf("Entregando: %s\n", nombres[idx]);

    float vuelto = saldo - precios[idx];
    if (vuelto > 0) {
        printf("Su vuelto es L. %.2f:\n", vuelto);
        calcularVuelto(vuelto, 0);
    }

    return 0.0;
}

float cancelarTransaccion(float saldo) {
    if (saldo > 0) {
        printf("Transaccion cancelada. Se devuelven L. %.2f\n", saldo);
    } else {
        printf("No hay saldo que devolver.\n");
    }
    return 0.0;
}

int main() {
    float saldo = 0.0;
    int opcion;

    do {
        printf("\n===== MAQUINA EXPENDEDORA =====\n");
        printf("Saldo actual: L. %.2f\n", saldo);
        printf("1. Ver catalogo\n");
        printf("2. Insertar dinero\n");
        printf("3. Seleccionar producto\n");
        printf("4. Cancelar / pedir vuelto\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarCatalogo();
                break;
            case 2: {
                float monto;
                printf("Ingrese monto a insertar: ");
                scanf("%f", &monto);
                saldo = insertarDinero(saldo, monto);
                break;
            }
            case 3: {
                int codigo;
                printf("Ingrese codigo de producto: ");
                scanf("%d", &codigo);
                saldo = seleccionarProducto(codigo, saldo);
                break;
            }
            case 4:
                saldo = cancelarTransaccion(saldo);
                break;
            case 0:
                printf("Gracias por su compra.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
