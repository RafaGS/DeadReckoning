/*
   DeadReckoning.h - Library that implements dead-reckoning algorithm 
   Created by Rafa Gomez, 2015
   Licensed under GPL v3
*/

#include "DeadReckoning.h"

DeadReckoning::DeadReckoning(float diametro_rueda, float distancia_eje, int resolucionEncoder) // Constructor para clase DeadReckoning
{
    _diametro_rueda = diametro_rueda;
    _resolucionEncoder = resolucionEncoder;
    _distancia_eje = distancia_eje;

    _distancia_paso = M_PI * _diametro_rueda / (float)_resolucionEncoder; // mm
    _anguloPorLectura = 2.0 * _distancia_paso / _distancia_eje; // rads

    _objetivoX = 0;
    _objetivoY = 0;

    resetDesplazamiento();
}


DeadReckoning::~DeadReckoning()
{
    // Nop
}


bool DeadReckoning::calculaDesplazamiento(int pulsosD, int pulsosI)
{

    float theta_i = 0.0;
    float deltaTheta = 0.0;
    float deltaX = 0.0;
    float deltaY = 0.0;
    float deltaRecRuedas = 0.0;

    float recRuedaI = _distancia_paso * pulsosI;
    float recRuedaD = _distancia_paso * pulsosD;

    bool isMov = false;

    if( recRuedaD != 0.0 || recRuedaI != 0.0) // se ha registrado movimiento
    {
        isMov = true;

        if( (fabs(recRuedaD - recRuedaI)) < _distancia_paso ) { // se aproxima a línea recta
            deltaRecRuedas = 0.5 * (recRuedaD + recRuedaI);
            deltaX = deltaRecRuedas * cos(_curTheta);
            deltaY = deltaRecRuedas * sin(_curTheta);
            theta_i = _curTheta;
        }
        else if( fabs(recRuedaD + recRuedaI) < _distancia_paso ) { // se considera giro en su propio eje
            deltaTheta = (recRuedaD - recRuedaI) / _distancia_eje;
            theta_i = fmod((_curTheta + deltaTheta), 2.0 * M_PI);
        } 
        else { // desplazamiento normal con giro
            float radio = 0.5 * _distancia_eje * (recRuedaD + recRuedaI) / (recRuedaD - recRuedaI);
            deltaTheta = (recRuedaD - recRuedaI) / _distancia_eje;
            theta_i = fmod((_curTheta + deltaTheta), 2.0 * M_PI);
            deltaRecRuedas = (recRuedaD + recRuedaI) / 2.0;
            deltaX = radio * (sin(theta_i) - sin(_curTheta));
            deltaY = radio * (cos(_curTheta) - cos(theta_i));
        }

        _totalRecorrido += deltaRecRuedas;
        _curTheta = theta_i;
        _curX += deltaX;
        _curY += deltaY;
    }

    return isMov;
}


void DeadReckoning::resetDesplazamiento()
{
    _curX = 0.0;
    _curY = 0.0;
    _curTheta = 0.0;
    _totalRecorrido = 0.0;
}


float DeadReckoning::getActualX()
{
    return _curX;
}


float DeadReckoning::getActualY()
{
    return _curY;
}


float DeadReckoning::getActualTheta()
{
    return _curTheta;
}


float DeadReckoning::getDistanciaRecorrida()
{
    return _totalRecorrido;
}


float DeadReckoning::getIzqX()
{
    return _curX - 0.5 * _distancia_eje * sin(_curTheta);
}


float DeadReckoning::getIzqY()
{
    return _curY + 0.5 * _distancia_eje * cos(_curTheta);
}


float DeadReckoning::getDerX()
{
    return _curX + 0.5 * _distancia_eje * sin(_curTheta);
}


float DeadReckoning::getDerY()
{
    return _curY - 0.5 * _distancia_eje * cos(_curTheta);    
}


float DeadReckoning::getContadorTheta(float angulo)
{
    return angulo / _anguloPorLectura;
}


void DeadReckoning::setObjetivo(float x, float y)
{
    _objetivoX = x;
    _objetivoY = y;
}


bool DeadReckoning::isFinal()
{
    if(sqrt( (_objetivoX - _curX) * (_objetivoX - _curX) + (_objetivoY - _curY) * (_objetivoY - _curY) ) <= _RADIO_POSICION )
        return true;
    else
        return false;
}


float DeadReckoning::getOrientacionObjetivo()
{
    float angulo = atan2( _objetivoY - _curY, _objetivoX - _curX);
    angulo = fmod((angulo + 2 * M_PI), 2.0 * M_PI);
    return angulo;
}

