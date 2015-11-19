#ifndef _TITLESELECTMANAGER_H_
#define _TITLESELECTMANAGER_H_
#define STARTPOS_X 1100
#define STARTPOS_Y 500
#define STAFFPOS_X 1100
#define STAFFPOS_Y 650
#define ENDPOS_X 200
#define ENDPOS_Y 600
#include "Library.h"

enum TITLEANIMA_ID;

//アナログパッドの入力でStartを指すか　Endを指すかが変化して、Aボタンを押したらTitleSceneに現在選択されてるものが何かを伝える
enum TITLESELECT_ID
{
	GAME_START,
	GAME_STAFF,
	GAME_END,
	TITLESELECT_NONE,
};


class TitleSelectManager
{
private:
	Library*			m_pLibrary;
	LPDIRECT3DTEXTURE9	m_pTexture;
	Position			m_StartPos;
	Position			m_StaffPos;
	Position			m_EndPos;
	Position			m_CursolPos;
	TITLESELECT_ID		m_CurrentSelect;
	TITLEANIMA_ID		m_CursolCurrentAnima;


	bool*				m_PadState;
	bool*				m_PadOldState;
	int					m_alpha = 255;
	bool				m_isSelectFadeout = true;

public:
	TitleSelectManager(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture, bool* pPadState, bool* pPadOldState);
	~TitleSelectManager();
	TITLESELECT_ID Control();
	void Draw();

};


#endif