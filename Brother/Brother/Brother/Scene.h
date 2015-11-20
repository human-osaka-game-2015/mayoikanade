#ifndef SCENE_H
#define SCENE_H

#define FILE_INFO 7
#include "Library.h"

enum SCENE_NUM
{
	SCENE_NONE,
	LOGO_SCENE,
	OPENING_SCENE,
	TITLE_SCENE,
	CONNECTING_SCENE,
	GAME_SCENE,
	RESULT_SCENE,
	END_SCENE,
	STAFF_SCENE,
	MAX_SCENE,
};

enum TEXTURE_NUM
{
	TEX_LOGO,
	TEX_TITLE,
	TEX_STAFF,
	TEX_GAME,
};

class Scene
{
private:

protected:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;

public:
	Scene(Library* pLibrary);
	virtual ~Scene();
	virtual SCENE_NUM Control() = 0;
	virtual void Draw() = 0;
	virtual void PadCheck() = 0;
	bool	m_PadState[ANALOG_MAX];
	bool	m_PadOldState[ANALOG_MAX];
};


#endif