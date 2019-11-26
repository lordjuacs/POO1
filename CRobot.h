#include <iostream>
#include "Tipos.h"
using namespace std;

class CRobot{
public:
	TipoString m_Nombre;
	TipoCaracter  m_Color;
	void moverse(TipoEntero altura, TipoEntero ancho);
	void moverseRand(TipoEntero altura, TipoEntero ancho);
public:
	CRobot();
	CRobot(TipoString pNombre, TipoCaracter pColor,
		TipoEntero pPosX, TipoEntero pPosY);
	virtual ~CRobot();
	TipoEntero    m_PosX;
	TipoEntero    m_PosY;
	void setNombre(TipoString pNombre);
	TipoString getNombre();
	TipoEntero getPosX();
	TipoEntero getPosY();
	TipoCaracter getColor();
	TipoString mostrarPosicion();
};