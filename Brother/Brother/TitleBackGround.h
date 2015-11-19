#ifndef _TITLEBACKGROUND_H_
#define _TITLEBACKGROUND_H_
#define TITLEBACKGROUNDPOS_X 686
#define TITLEBACKGROUNDPOS_Y 398
#include "Library.h"


class TitleBackGround
{
private:
	Library*			m_pLibrary;
	LPDIRECT3DTEXTURE9	m_pTexture;
	Position			m_Pos;

public:
	TitleBackGround(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture);
	~TitleBackGround();
	void Control();
	void Draw();
};


#endif