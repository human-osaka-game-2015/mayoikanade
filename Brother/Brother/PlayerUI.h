#ifndef PLAYERUI_H
#define PLAYERUI_H

#include "Vertex.h"



class Library;



class PlayerUI
{
private:
	Library*	m_pLibrary;
	Position	m_FrameUiPos;
	Position	m_BarUiPos;
	const int&	m_PlayerHp;
	const int	m_FrameTexId;
	const int	m_BarTexId;


public:
	PlayerUI(Library* pLibrary,const int& Hp,int frameTexId,int barTexId,float x, float y);
	~PlayerUI();
	void Control();
	void Draw();

};



#endif