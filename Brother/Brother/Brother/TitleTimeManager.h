#ifndef TITLETIMEMANAGER_H
#define TITLETIMEMANAGER_H

#define TITLEBLACKOUT_X 686
#define TITLEBLACKOUT_Y 398
#define TITLEBLACKOUT_W 1373
#define	TITLEBLACKOUT_H 797
#include "Library.h"

class TitleTimeManager
{
private:
	Library*			m_pLibrary;
	Position			m_Pos;
	int					m_TitleSceneTime = 0;
	int					m_alpha = 255;

public:
	TitleTimeManager(Library* pLibrary);
	~TitleTimeManager();
	bool Control();
	void Draw();
};


#endif