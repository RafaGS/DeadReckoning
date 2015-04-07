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
#include <cmath>

class DeadReckoning
{
    public:
        DeadReckoning(float diametro_rueda, float distancia_eje, int resolucionEncoder);
        ~DeadReckoning();
        bool calculaDesplazamiento(int pulsosD, int pulsosI);

        void resetDesplazamiento();
        void setObjetivo(float x, float y);
        
        float getActualX();
        float getActualY();
        float getActualTheta();
        float getDistanciaRecorrida();
        float getIzqX(); // posición de las ruedas
        float getIzqY();
        float getDerX();
        float getDerY();
        float getContadorTheta(float angulo);

        bool isFinal();
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
