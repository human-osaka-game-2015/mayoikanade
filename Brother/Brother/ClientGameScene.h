#ifndef GAMESCENE_H
#define GAMASCENE_H


#include "Scene.h"
#include <d3dx9.h>
#include "Tex.h"
class Library;
class SceneChangeListener;
class ClientModeManager;
class ClientMap;
class ClientCollisionChecker;
class ClientBrother;
class ClientYoungerBrother;
class ClientDrawPositionSetter;
class ClientGameTimeManager;
class ClientText;
class ClientShadow;
class ClientGameScene;
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
	ClientModeManager*		m_pModeManager;
	ClientMap*					m_pMap;
	ClientCollisionChecker*		m_pCollisionChecker;
	ClientBrother*			m_pBrother;
	ClientYoungerBrother*	m_pYoungerBrother;
	ClientDrawPositionSetter*		m_pDrawPositionSetter;
	ClientGameTimeManager*		m_pGameTimeManager;
	ClientText*					m_pText;
	ClientShadow*					m_pShadow;
	HWND					m_hWnd;

	GameThread Gamemain;
public:
	ClientGameScene(Library* pLibrary, HWND hWnd, char* IPadd);
	virtual ~ClientGameScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

	void GetYoungBrotherPos(short* posx, short* posy);
	void SetBrotherPos(short* posx, short* posy);

	static DWORD WINAPI Connect(LPVOID pGameScene);
	bool m_isGameScene;
	bool isConnect;
	//char SData[6];
	//char CData[6];

	ClientSendData m_SendData;
	ClientRecvData m_RecvData;

	//ƒeƒXƒg
	LPD3DXFONT pFont;
};

#endif