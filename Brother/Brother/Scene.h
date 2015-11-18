#ifndef _SCENE_H_
#define _SCENE_H_
#define FILE_INFO 7

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

enum GAMEPADSTATE
{
	PAD_UP,
	PAD_DOWN,
	PAD_LEFT,
	PAD_RIGHT,
	PAD_MAX
};

class Scene
{
private:

public:
	Scene();
	virtual ~Scene();
	virtual SCENE_NUM Control() = 0;
	virtual void Draw() = 0;
	virtual void PadCheck() = 0;
	bool	m_PadState[PAD_MAX];
	bool	m_PadOldState[PAD_MAX];
};


#endif