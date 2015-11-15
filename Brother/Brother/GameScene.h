#ifndef _GAMESCENE_H_
#define _GAMASCENE_H_

#include "Scene.h"
#include <d3dx9.h>
class Library;
class SceneChangeListener;
class ModeManager;
class Map;
class CollisionChecker;
class Brother;
class YoungerBrother;


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
	LPDIRECT3DTEXTURE9  	m_pTexture[3];



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