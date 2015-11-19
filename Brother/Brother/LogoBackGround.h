#ifndef _LOGOBACKGROUND_H_
#define _LOGOBACKGROUND_H_
#define LOGOBACKGROUNDPOS_X 686
#define LOGOBACKGROUNDPOS_Y 398
#include "Library.h"

class LogoBackGround
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	Library*			m_pLibrary;
	Position			m_Pos;
	int					m_alpha = 0;
	bool				m_isFadeIn = true;

public:
	LogoBackGround(Library* pLibrary,LPDIRECT3DTEXTURE9 pTexture);
	~LogoBackGround();

	bool Control();
	void Draw();

};

#endif