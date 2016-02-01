#ifndef SCENE_H
#define SCENE_H

#define FILE_INFO 9
#define TIME_INIT 0
#define FOR_DEFAULT_INIT 0

#include "Library.h"


enum CONNECT_TYPE;

enum SCENE_NUM
{
	SCENE_NONE,
	LOGO_SCENE,
	OPENING_SCENE,
	TITLE_SCENE,
	CONNECTING_SCENE,
	SERVER_GAME_SCENE,
	CLIENT_GAME_SCENE,
	RESULT_SCENE,
	END_SCENE,
	STAFF_SCENE,
	MAX_SCENE
};

enum TEXTURE_NUM
{
	TEX_LOGO,
	TEX_TITLE,
	TEX_CONNECT,
	TEX_STAFF,
	TEX_GAME,
	TEX_GAMECLEAR,
	TEX_GAMEOVER,
	CONNECTING_WAIT,
	CONNECTSELECT_WAIT,
	STENCIL,
	TEX_UI
};

enum XINPUT_BUTTON
{
	XINPUT_BUTTON_A,
	XINPUT_BUTTON_B,
	XINPUT_BUTTON_MAX

};


class Scene
{
private:

protected:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;
	static unsigned int		m_time;

public:
	Scene(Library* pLibrary);
	virtual ~Scene();
	virtual SCENE_NUM Control() = 0;
	virtual void Draw() = 0;
	virtual void PadCheck() = 0;
	
	bool		m_PadState[ANALOG_MAX];
	bool		m_PadOldState[ANALOG_MAX];
	PADSTATE	m_ButtonState[XINPUT_BUTTON_MAX];

	bool		m_ClientPadState[ANALOG_MAX];
	bool		m_ClientPadOldState[ANALOG_MAX];
	PADSTATE	m_ClientButtonState[XINPUT_BUTTON_MAX];

	bool		m_ServerPadState[ANALOG_MAX];
	bool		m_ServerPadOldState[ANALOG_MAX];
	PADSTATE	m_ServerButtonState[XINPUT_BUTTON_MAX];
};


#endif