#ifndef PLAYERUI_H
#define PLAYERUI_H

#include "Vertex.h"



class Library;



class ClientPlayerUI
{
private:
	Library*	m_pLibrary;
	Position	m_FrameUiPos;
	Position	m_BarUiPos;
	Position	m_FacialExpression;
	const int&	m_PlayerHp;
	const int	m_FrameTexId;
	const int	m_BarTexId;
	const int	m_face1Id;
	const int	m_face2Id;
	const int	m_face3Id;

public:
	ClientPlayerUI(Library* pLibrary, const int& Hp, int frameTexId, int barTexId, int face1id, int face2id, int face3id, float x, float y, float face_x, float face_y);
	~ClientPlayerUI();
	void Control();
	void Draw();

};



#endif