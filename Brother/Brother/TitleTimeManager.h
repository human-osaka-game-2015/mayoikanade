#ifndef _TITLETIMEMANAGER_H_
#define _TITLETIMEMANAGER_H_
#define TITLEBLACKOUT_X 686
#define TITLEBLACKOUT_Y 398
#define TITLEBLACKOUT_W 1373
#define	TITLEBLACKOUT_H 797
#include "Library.h"

class TitleTimeManager
{
private:
	Library*			m_pLibrary;
	LPDIRECT3DTEXTURE9	m_pTexture;
	Position			m_Pos;
	int					m_TitleSceneTime = 0;
	int					m_alpha = 255;

public:
	TitleTimeManager(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture);
	~TitleTimeManager();
	bool Control();
	void Draw();
};


#endif