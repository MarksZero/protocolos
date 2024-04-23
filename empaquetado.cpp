#include <iostream>
#include <string>
#include "empaquetado.h"
using namespace std;

void llenarDatos(datos &d) {
    d.cmd = 3; // mascara 0x07
    d.id = 4; // mascara 0x0f
    d.len = 4; // mascara 0x0f

    for (int i = 0; i < LEN; i++) {
        d.data[i] = 1;
    }
}

void llenarBuffer(datos &d, byte buffer[]) {
    buffer[0] = (buffer[0] | d.cmd & 0x07) | ((d.id & 0x0f) << 3) | ((d.len & 0x01) << 7);
    buffer[1] = ((d.len & 0x0e) >> 1);

    for (int i = 0; i < LEN; i++) {
        buffer[i + 2] = d.data[i];
    }
}

void calcularFCS(datos &d, byte buffer[]) {
    for (int i = 0; i <= LEN; i++) {
        d.FCS = d.FCS ^ d.data[i];
    }

    for (int i = 0; i < LEN + 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            d.FCS += ((buffer[i] >> j) & 0x01);
            buffer[LEN + 2] = d.FCS;
        }
    }
}

void imprimirBuffer(byte buffer[]) {
    for (int i = 0; i <= LEN + 2; i++) {
        if (i <= 3) {
            cout << int(buffer[i]) << "/";
        } else {
            cout << '\n' << int(buffer[i]) << endl;
        }
    }
}



void menu() {
    int opcion;
    int num_envidados = 0;
    int recibidos_correctos = 0;
    int num_error_detectado = 0;
    int error_no_detectado = 0;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Cerrar programa receptor\n";
        cout << "2. Enviar mensaje de prueba (10 veces)\n";
        cout << "3. Mostrar estadísticas de mensajes\n";
        cout << "4. Enviar mensaje de texto a archivo\n";
        cout << "5. Mostrar contenido de archivo\n";
        cout << "6. Mostrar contador de mensajes enviados\n";
        cout << "7. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Código para cerrar el programa receptor
                break;
            case 2: {
                // Código para enviar mensaje de prueba 10 veces
                // Actualizar contadores de mensajes recibidos
                break;
            }
            case 3: {
                // Calcular porcentajes de acierto y error
                int totalMensajes = recibidos_correctos + num_error_detectado + error_no_detectado;
                double porcentajeCorrectos = (double)recibidos_correctos / totalMensajes * 100;
                double porcentajeErrorDetectado = (double)num_error_detectado / totalMensajes * 100;
                double porcentajeErrorNoDetectado = (double)error_no_detectado / totalMensajes * 100;

                cout << "\nEstadisticas de mensajes:\n";
                cout << "Mensajes recibidos correctamente: " << recibidos_correctos << " (" << porcentajeCorrectos << "%)\n";
                cout << "Mensajes recibidos con error detectado: " << num_error_detectado << " (" << porcentajeErrorDetectado << "%)\n";
                cout << "Mensajes recibidos con error no detectado: " << error_no_detectado << " (" << porcentajeErrorNoDetectado << "%)\n";
                break;
            }
            case 4: {
                string mensaje;
                cout << "Ingrese el mensaje de texto: ";
                getline(cin >> ws, mensaje);

                ofstream archivoMensajes("mensajes.txt", ios::app);
                if (archivoMensajes.is_open()) {
                    archivoMensajes << mensaje << "\n";
                    archivoMensajes.close();
                    cout << "Mensaje guardado en mensajes.txt\n";
                } else {
                    cout << "No se pudo abrir el archivo mensajes.txt\n";
                }
                break;
            }
            case 5: {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo de texto: ";
                getline(cin >> ws, nombreArchivo);

                ifstream archivoTexto(nombreArchivo);
                if (archivoTexto.is_open()) {
                    string linea;
                    while (getline(archivoTexto, linea)) {
                        cout << linea << "\n";
                    }
                    archivoTexto.close();
                } else {
                    cout << "El archivo " << nombreArchivo << " no existe.\n";
                }
                break;
            }
            case 6:
                cout << "Mensajes enviados: " << num_envidados << "\n";
                break;
            case 7:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 7);
}