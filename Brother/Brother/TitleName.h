#ifndef _TITLENAME_H_
#define _TITLENAME_H_
#define TITLENAMEPOS_X 343
#define TITLENAMEPOS_Y 198
#include "Library.h"

class TitleName
{
private:
	Library*			m_pLibrary;
	LPDIRECT3DTEXTURE9	m_pTexture;
	Position			m_Pos;

public:
	TitleName(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture);
	~TitleName();
	void Control();
	void Draw();

};

#endif