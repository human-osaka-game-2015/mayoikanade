#ifndef GAMESCENE_H
#define GAMASCENE_H

#define GAME_ANIMA_INFO 6

#include "Scene.h"
#include <d3dx9.h>

class Library;
class SceneChangeListener;
class ModeManager;
class Map;
class CollisionChecker;
class Brother;
class YoungerBrother;
class DrawPositionSetter;
class GameTimeManager;
class Text;
class Shadow;

enum GAME_VERTEXINFO_ID
{
	BROTHER_WAIT_FRONT_01,
	BROTHER_WAIT_FRONT_02,

	BROTHER_WAIT_SIDE_01,
	BROTHER_WAIT_SIDE_02,

	BROTHER_WAIT_BACK_01,
	BROTHER_WAIT_BACK_02,

	BROTHER_WALK_FRONT_01,
	BROTHER_WALK_FRONT_02,
	BROTHER_WALK_FRONT_03,
	BROTHER_WALK_FRONT_04,

	BROTHER_WALK_SIDE_01,
	BROTHER_WALK_SIDE_02,
	BROTHER_WALK_SIDE_03,
	BROTHER_WALK_SIDE_04,

	BROTHER_WALK_BACK_01,
	BROTHER_WALK_BACK_02,
	BROTHER_WALK_BACK_03,
	BROTHER_WALK_BACK_04,

	WOOD_01,
	WOOD_02,
	WOOD_03,
	WOOD_04,

	GRASS_01,
	GROUND_01,
	
	YOUNGERBROTHER_WAIT_FRONT_01,
	YOUNGERBROTHER_WAIT_FRONT_02,
	
	YOUNGERBROTHER_WAIT_SIDE_01,
	YOUNGERBROTHER_WAIT_SIDE_02,

	YOUNGERBROTHER_WAIT_BACK_01,
	YOUNGERBROTHER_WAIT_BACK_02,

	YOUNGERBROTHER_WALK_FRONT_01,
	YOUNGERBROTHER_WALK_FRONT_02,

	YOUNGERBROTHER_WALK_SIDE_01,
	YOUNGERBROTHER_WALK_SIDE_02,

	YOUNGERBROTHER_WALK_BACK_01,
	YOUNGERBROTHER_WALK_BACK_02,

	BROTHER_LIFEFRAME,
	BROTHER_LIFEBAR,
	YOUNGERBROTHER_LIFEFRAME,
	YOUNGERBROTHER_LIFEBAR,

	GAME_VERTEXINFO_MAX
};

enum GAMEANIMA_ID
{
	BROTHER_WAIT_FRONT,
	BROTHER_WAIT_SIDE,
	BROTHER_WAIT_BACK,
	BROTHER_WALK_FRONT,
	BROTHER_WALK_SIDE,
	BROTHER_WALK_BACK,
	BROTHERMAX
};


//ç°ÇÕï Ç…ï™ÇØÇƒÇ¢ÇÈ
enum GIMMICK_ID
{
	SWITCH_01,
	SWITCH_02,
};


class GameScene : public Scene
{
private:
	SceneChangeListener*	m_pSceneChangeListener;
	ModeManager*			m_pModeManager;
	Map*					m_pMap;
	CollisionChecker*		m_pCollisionChecker;
	Brother*				m_pBrother;
	YoungerBrother*			m_pYoungerBrother;
	DrawPositionSetter*		m_pDrawPositionSetter;
	GameTimeManager*		m_pGameTimeManager;
	Text*					m_pText;
	Shadow*					m_pShadow;

public:
	GameScene(Library* pLibrary);
	virtual ~GameScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();
	

	//ÉeÉXÉg
	LPD3DXFONT pFont;
};

#endif