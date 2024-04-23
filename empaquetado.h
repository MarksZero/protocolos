#define byte unsigned char
#define LEN 15

struct datos {
    byte cmd;
    byte id;
    byte len;
    byte data[LEN];
    byte FCS;
};


void llenarDatos(datos &d);
void llenarBuffer(datos &d, byte buffer[]);
void calcularFCS(datos &d, byte buffer[]);
void imprimirBuffer(byte buffer[]);
void menu();