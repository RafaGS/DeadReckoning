/*
   DeadReckoning.h - Library that implements dead-reckoning algorithm 
   Created by Rafa Gomez, 2015
   Licensed under GPL v3
   */
#ifndef DeadReckoning_h
#define DeadReckoning_h

#ifndef __linux__
#include <Arduino.h>
#endif
#include <math.h>

class DeadReckoning
{
    public:
        DeadReckoning(float diametro_rueda, float distancia_eje, int resolucionEncoder);
        ~DeadReckoning();
        bool calculaDesplazamiento(int pulsosD, int pulsosI); // actualiza los valores de coordenadas y orientación del robot a partir de las lecturas de cada codificador

        void resetDesplazamiento(); // pone a cero los valores de coordenadas y orientación del robot
        void setObjetivo(float x, float y); // indica un objetivo o referencia respecto al punto de partida
        
        float getActualX(); // devuelve el valor actual de x
        float getActualY(); // devuelve el valor actual de y
        float getActualTheta(); // devuelve el valor actual de orientación
        float getDistanciaRecorrida(); // devuelve el valor de la distancia total recorrida por el robot
        float getIzqX(); // posición de las ruedas: devuelve la posición x del lateral izquierdo del robot
        float getIzqY(); // devuelve la posición y del lateral izquierdo del robot
        float getDerX(); // devuelve la posición x del lateral derecho del robot
        float getDerY(); // devuelve la posición y del lateral derecho del robot
        float getContadorTheta(float angulo); // indica las lecturas necesarias de los codificadores (referente al izquierdo) para asegurar el giro indicado en la variable angulo

        bool isFinal(); // indica si se ha alcanzado el objetivo marcado con setObjetivo()
        float getOrientacionObjetivo(); // indica orientación relativa para dirigirse al objetivo

    private:
        static const float _RADIO_POSICION = 10; // 1 cm de radio de alcance de objetivo
            
        float _resolucionEncoder; // cuentas por vuelta del encoder
        float _anguloPorLectura;
        float _diametro_rueda; // diámetro de la rueda (mm)
        float _distancia_eje; // distancia entre ruedas (mm)
        float _distancia_paso; // recorrido por pulso (mm)

        float _curX; // x_(i-1)
        float _curY; // y_(i-1)
        float _curTheta; // theta_(i-1)
        float _totalRecorrido;

        float _objetivoX;
        float _objetivoY;
};

#endif
