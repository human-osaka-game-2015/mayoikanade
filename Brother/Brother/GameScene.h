#ifndef _GAMESCENE_H_
#define _GAMASCENE_H_
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


//今は別に分けている
enum GIMMICK_ID
{
	SWITCH_01,
	SWITCH_02,
};

class GameScene : public Scene
{
private:
	SCENE_NUM				m_NextScene;
	
	Library*				m_pLibrary;
	SceneChangeListener*	m_pSceneChangeListener;
	ModeManager*			m_pModeManager;
	Map*					m_pMap;
	CollisionChecker*		m_pCollisionChecker;
	Brother*				m_pBrother;
	YoungerBrother*			m_pYoungerBrother;//使わない
	LPDIRECT3DTEXTURE9  	m_pTexture;



public:
	GameScene(Library* pLibrary);
	virtual ~GameScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();
	int GetTime();




	//テスト
	LPD3DXFONT pFont;

	

};

#endif