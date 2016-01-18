#ifndef GAMESCENE_H
#define GAMASCENE_H


#include "Scene.h"
#include <d3dx9.h>
#include "Tex.h"


class Library;
class SceneChangeListener;
class ModeManager;
class Map;
class CollisionChecker;
class ClientBrother;
class ClientYoungerBrother;
class DrawPositionSetter;
class GameTimeManager;
class Text;
class Shadow;


typedef struct
{
	LPVOID pGameScene;
	char portnum[16];
}GameThread;

typedef struct
{
	char CData[6];
	short Yposx;
	short Yposy;
}ClientSendData;

typedef struct
{
	char SData[6];
	short Bposx;
	short Bposy;
}ClientRecvData;


class ClientGameScene : public Scene
{
private:
	SceneChangeListener*	m_pSceneChangeListener;
	ModeManager*			m_pModeManager;
	Map*					m_pMap;
	CollisionChecker*		m_pCollisionChecker;
	ClientBrother*			m_pBrother;
	ClientYoungerBrother*	m_pYoungerBrother;
	DrawPositionSetter*		m_pDrawPositionSetter;
	GameTimeManager*		m_pGameTimeManager;
	Text*					m_pText;
	Shadow*					m_pShadow;
	HWND					m_hWnd;
	GameThread				Gamemain;
	bool*					m_pisGameClear;


public:
	ClientGameScene(Library* pLibrary, HWND hWnd, char* IPadd, bool* pisGameClear);
	virtual ~ClientGameScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

	void GetYoungBrotherPos(short* posx, short* posy);
	void SetBrotherPos(short* posx, short* posy);

	static DWORD WINAPI Connect(LPVOID pGameScene);
	bool m_isGameScene;
	bool isConnect;

	//ClientSendData m_SendData;
	//ClientRecvData m_RecvData;
	char CData[6];
	char SData[6];

	//ƒeƒXƒg
	LPD3DXFONT pFont;
};


#endif