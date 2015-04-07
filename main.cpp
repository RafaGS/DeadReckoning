#include "DeadReckoning.h"

#include <iostream>
#include <fstream>
using namespace std;


int main()
{
    int nc;
    DeadReckoning trazaRuta(42.0, 84.0, 8);
    ofstream myfile;
    myfile.open ("ruta.txt");

    // ángulo recto: 4 puntos / cout << trazaRuta.getContadorTheta(M_PI * 0.5)<<"\n";

    int dx;
    cout << "- Introduzca coordenada X destino: ";
    cin >> dx;
    int dy;
    cout << "- Introduzca coordenada Y destino: ";
    cin >> dy;

    trazaRuta.setObjetivo(dx, dy);
    myfile << trazaRuta.getActualX() << "\t" << trazaRuta.getActualY() << "\t\t" 
        << trazaRuta.getIzqX() << "\t" << trazaRuta.getIzqY() << "\t\t" 
        << trazaRuta.getDerX() << "\t" << trazaRuta.getDerY() << "\t\t"
        << dx << "\t" << dy << "\t\t"
        << (trazaRuta.getActualTheta()*180.0/M_PI) << "\t"
        << (trazaRuta.getOrientacionObjetivo()*180.0/M_PI) << "\n";

    do {
        int i;
        cout << "- Introduzca lecturas a la izquierda: ";
        cin >> i;
        int d;
        cout << "- Introduzca lecturas a la derecha: ";
        cin >> d;
        cout << "- Introduzca número de ciclos: ";
        cin >> nc;


        for(int j=0; j<nc; j++) {
            trazaRuta.calculaDesplazamiento(d, i);
            myfile << trazaRuta.getActualX() << "\t" << trazaRuta.getActualY() << "\t\t" 
                << trazaRuta.getIzqX() << "\t" << trazaRuta.getIzqY() << "\t\t" 
                << trazaRuta.getDerX() << "\t" << trazaRuta.getDerY() << "\t\t"
                << dx << "\t" << dy << "\t\t"
                << (trazaRuta.getActualTheta()*180.0/M_PI) << "\t"
                << (trazaRuta.getOrientacionObjetivo()*180.0/M_PI) << "\n";
        }
    } while(nc != 0);

    myfile.close();

    return 0;
}
