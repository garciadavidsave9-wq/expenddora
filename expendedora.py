codigos = [1, 2, 3, 4]
nombres = ["Agua", "Soda", "Papas", "Chocolate"]
precios = [10.0, 15.0, 12.5, 18.0]
stocks = [5, 5, 5, 5]

denominaciones = [10, 5, 1]

def mostrar_catalogo():
    print("\n--- CATALOGO ---")
    for i in range(len(codigos)):
        print(f"[{codigos[i]}] {nombres[i]:<10} L. {precios[i]:.2f}  (stock: {stocks[i]})")


def insertar_dinero(saldo_actual, monto):
    """Recibe el saldo actual y el monto a insertar, devuelve el nuevo saldo."""
    if monto <= 0:
        print("Monto invalido.")
        return saldo_actual
    return saldo_actual + monto


def buscar_producto(codigo):
    """Busca un producto por codigo, devuelve el indice o -1 si no existe."""
    for i in range(len(codigos)):
        if codigos[i] == codigo:
            return i
    return -1


def validar_saldo(precio, saldo):
    """Verifica si el saldo alcanza para el precio dado."""
    return saldo >= precio


def calcular_vuelto(monto, idx=0):
    """Calcula el vuelto de forma RECURSIVA usando las denominaciones disponibles."""
    if monto <= 0 or idx >= len(denominaciones):
        return  # caso base: no queda vuelto o no hay mas denominaciones

    denom = denominaciones[idx]

    if monto >= denom:
        print(f"  -> L. {denom}")
        calcular_vuelto(monto - denom, idx)  # seguimos con la misma denominacion
    else:
        calcular_vuelto(monto, idx + 1)  # pasamos a la siguiente denominacion


def seleccionar_producto(codigo, saldo):
    """Entrega el producto: descuenta stock y muestra el vuelto."""
    idx = buscar_producto(codigo)

    if idx == -1:
        print("Producto no encontrado.")
        return saldo

    if stocks[idx] <= 0:
        print("Producto agotado.")
        return saldo

    if not validar_saldo(precios[idx], saldo):
        print(f"Saldo insuficiente. Faltan L. {precios[idx] - saldo:.2f}")
        return saldo

    stocks[idx] -= 1
    print(f"Entregando: {nombres[idx]}")

    vuelto = saldo - precios[idx]
    if vuelto > 0:
        print(f"Su vuelto es L. {vuelto:.2f}:")
        calcular_vuelto(vuelto)

    return 0.0  


def cancelar_transaccion(saldo):
    """Cancela la transaccion y devuelve el dinero insertado."""
    if saldo > 0:
        print(f"Transaccion cancelada. Se devuelven L. {saldo:.2f}")
    else:
        print("No hay saldo que devolver.")
    return 0.0

def main():
    saldo = 0.0
    opcion = -1

    while opcion != 0:
        print("\n===== MAQUINA EXPENDEDORA =====")
        print(f"Saldo actual: L. {saldo:.2f}")
        print("1. Ver catalogo")
        print("2. Insertar dinero")
        print("3. Seleccionar producto")
        print("4. Cancelar / pedir vuelto")
        print("0. Salir")

        opcion = int(input("Opcion: "))

        if opcion == 1:
            mostrar_catalogo()
        elif opcion == 2:
            monto = float(input("Ingrese monto a insertar: "))
            saldo = insertar_dinero(saldo, monto)
        elif opcion == 3:
            codigo = int(input("Ingrese codigo de producto: "))
            saldo = seleccionar_producto(codigo, saldo)
        elif opcion == 4:
            saldo = cancelar_transaccion(saldo)
        elif opcion == 0:
            print("Gracias por su compra.")
        else:
            print("Opcion invalida.")

if __name__ == "__main__":
    main()