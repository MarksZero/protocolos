#include "empaquetado.h"


int main() {
    datos d{}; // Se crea el struct de tipo datos
    byte buffer[LEN + 3];

    llenarDatos(d);
    llenarBuffer(d, buffer);
    calcularFCS(d, buffer);
    imprimirBuffer(buffer);


    return 0;
}