#ifndef GAMESCENE_H
#define GAMASCENE_H


#include "Scene.h"
#include <d3dx9.h>
#include "Tex.h"
class Library;
class SceneChangeListener;
class ServerModeManager;
class ServerMap;
class ServerCollisionChecker;
class ServerBrother;
class ServerYoungerBrother;
class ServerDrawPositionSetter;
class ServerGameTimeManager;
class ServerText;
class ServerShadow;

typedef struct
{
	char SData[6];
	short Bposx;
	short Bposy;
}ServerSendData;

typedef struct
{
	char CData[6];
	short Yposx;
	short Yposy;
}ServerRecvData;

class ServerGameScene : public Scene
{
private:
	SceneChangeListener*		m_pSceneChangeListener;
	ServerModeManager*			m_pModeManager;
	ServerMap*					m_pMap;
	ServerCollisionChecker*		m_pCollisionChecker;
	ServerBrother*				m_pBrother;
	ServerYoungerBrother*		m_pYoungerBrother;
	ServerDrawPositionSetter*	m_pDrawPositionSetter;
	ServerGameTimeManager*		m_pGameTimeManager;
	ServerText*					m_pText;
	ServerShadow*				m_pShadow;
	HWND						m_hWnd;
	bool*						m_pisGameClear;

	char szIP[16];
	HOSTENT* lpHost; 			//  ホスト情報を格納する構造体

public:
	ServerGameScene(Library* pLibrary, HWND hWnd, bool* pisGameClear );
	virtual ~ServerGameScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();
	static DWORD WINAPI Connect(LPVOID pGameScene);
	static DWORD WINAPI Synchro(LPVOID pGameScene);

	void GetBrotherPos(short* posx, short* posy);
	void SetYoungBrotherPos(short* posx, short* posy);

	bool m_isGameScene;
	bool* m_pisConnect;
	bool m_isConnect;
	bool m_ServerConnected;
	char SData[6];
	char CData[6];
	//ServerSendData m_SendData;
	//ServerRecvData m_RecvData;

	//テスト
	LPD3DXFONT pFont;
};

#endif