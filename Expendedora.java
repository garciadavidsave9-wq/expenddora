import java.util.Scanner;

public class Expendedora {

    
    static int[] codigos = {1, 2, 3, 4};
    static String[] nombres = {"Agua", "Soda", "Papas", "Chocolate"};
    static double[] precios = {10.0, 15.0, 12.5, 18.0};
    static int[] stocks = {5, 5, 5, 5};

    static int[] denominaciones = {10, 5, 1};


    static void mostrarCatalogo() {
        System.out.println("\n--- CATALOGO ---");
        for (int i = 0; i < codigos.length; i++) {
            System.out.printf("[%d] %-10s L. %.2f  (stock: %d)%n",
                    codigos[i], nombres[i], precios[i], stocks[i]);
        }
    }

    static double insertarDinero(double saldoActual, double monto) {
        if (monto <= 0) {
            System.out.println("Monto invalido.");
            return saldoActual;
        }
        return saldoActual + monto;
    }

    static int buscarProducto(int codigo) {
        for (int i = 0; i < codigos.length; i++) {
            if (codigos[i] == codigo) {
                return i;
            }
        }
        return -1;
    }


    static boolean validarSaldo(double precio, double saldo) {
        return saldo >= precio;
    }

    static void calcularVuelto(double monto, int idx) {
        if (monto <= 0 || idx >= denominaciones.length) {
            return; 
        }

        int denom = denominaciones[idx];

        if (monto >= denom) {
            System.out.println("  -> L. " + denom);
            calcularVuelto(monto - denom, idx); 
        } else {
            calcularVuelto(monto, idx + 1); 
        }
    }

    static double seleccionarProducto(int codigo, double saldo) {
        int idx = buscarProducto(codigo);

        if (idx == -1) {
            System.out.println("Producto no encontrado.");
            return saldo;
        }

        if (stocks[idx] <= 0) {
            System.out.println("Producto agotado.");
            return saldo;
        }

        if (!validarSaldo(precios[idx], saldo)) {
            System.out.printf("Saldo insuficiente. Faltan L. %.2f%n", precios[idx] - saldo);
            return saldo;
        }

        stocks[idx]--;
        System.out.println("Entregando: " + nombres[idx]);

        double vuelto = saldo - precios[idx];
        if (vuelto > 0) {
            System.out.printf("Su vuelto es L. %.2f:%n", vuelto);
            calcularVuelto(vuelto, 0);
        }

        return 0.0; 
    }

    static double cancelarTransaccion(double saldo) {
        if (saldo > 0) {
            System.out.printf("Transaccion cancelada. Se devuelven L. %.2f%n", saldo);
        } else {
            System.out.println("No hay saldo que devolver.");
        }
        return 0.0;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double saldo = 0.0;
        int opcion;

        do {
            System.out.println("\n===== MAQUINA EXPENDEDORA =====");
            System.out.printf("Saldo actual: L. %.2f%n", saldo);
            System.out.println("1. Ver catalogo");
            System.out.println("2. Insertar dinero");
            System.out.println("3. Seleccionar producto");
            System.out.println("4. Cancelar / pedir vuelto");
            System.out.println("0. Salir");
            System.out.print("Opcion: ");
            opcion = sc.nextInt();

            switch (opcion) {
                case 1:
                    mostrarCatalogo();
                    break;
                case 2:
                    System.out.print("Ingrese monto a insertar: ");
                    double monto = sc.nextDouble();
                    saldo = insertarDinero(saldo, monto);
                    break;
                case 3:
                    System.out.print("Ingrese codigo de producto: ");
                    int codigo = sc.nextInt();
                    saldo = seleccionarProducto(codigo, saldo);
                    break;
                case 4:
                    saldo = cancelarTransaccion(saldo);
                    break;
                case 0:
                    System.out.println("Gracias por su compra.");
                    break;
                default:
                    System.out.println("Opcion invalida.");
            }
        } while (opcion != 0);

        sc.close();
    }
}
