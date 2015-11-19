#ifndef _STAFFBACKGROUND_H_
#define _STAFFBACKGROUND_H_
#define STAFFBACKGROUNDPOS_X 686
#define STAFFBACKGROUNDPOS_Y 398
#include "Library.h"

class StaffBackGround
{
private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	Library*				m_pLibrary;
	Position				m_Pos;


public:
	StaffBackGround(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture);
	~StaffBackGround();
	void Control();
	void Draw();

};



#endif