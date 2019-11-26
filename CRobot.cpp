#include "CRobot.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

CRobot::CRobot() : m_Color{}, m_PosX{}, m_PosY{}  {}

CRobot::CRobot(TipoString pNombre, TipoCaracter pColor,
	TipoEntero pPosX, TipoEntero pPosY) :
	m_Nombre{ pNombre }, m_Color{ pColor },
	m_PosX{ pPosX }, m_PosY{ pPosY } {
}
CRobot::~CRobot() {}
void CRobot::setNombre(TipoString pNombre) { this->m_Nombre = pNombre; }
void CRobot::moverse(TipoEntero altura, TipoEntero ancho) {
	int ch = _getch();
	if (ch == 0 || ch == 224)
	{
		switch (_getch())
		{
		case UP:
			if (m_PosY != 0) m_PosY--;	//key up
			break;
		case DOWN:
			if (m_PosY != altura-1) m_PosY++;   // key down
			break;
		case LEFT:
			if (m_PosX != 0) m_PosX--;  // key left
			break;
		case RIGHT:
			if (m_PosX != ancho-1) m_PosX++;  // key right
			break;
		default:
			break;	// not arrow
		}
	}
}

void CRobot::moverseRand(TipoEntero altura, TipoEntero ancho) {
	int ch = rand() % 4 + 1;
	switch (ch)
	{
	case 1:
		if (m_PosY != 0) m_PosY--;	//key up
		break;
	case 2:
		if (m_PosY != altura - 1) m_PosY++;   // key down
		break;
	case 3:
		if (m_PosX != 0) m_PosX--;  // key left
		break;
	case 4:
		if (m_PosX != ancho - 1) m_PosX++;  // key right
		break;
	default:
		break;	// not arrow
	}
}

TipoString   CRobot::getNombre() { return m_Nombre; }
TipoEntero   CRobot::getPosX() { return m_PosX; }
TipoEntero   CRobot::getPosY() { return m_PosY; }
TipoCaracter CRobot::getColor() { return m_Color; }
TipoString CRobot::mostrarPosicion() {
	return "X = " + to_string(m_PosX) + " Y = " + to_string(m_PosY);
}
