#ifndef GAMESCENE_H
#define GAMASCENE_H

#define PORT_MAX 16		//Port番号を格納する配列の大きさ
#define IP_MAX 16		//IPアドレスを格納する配列の大きさ

#include "Scene.h"
#include <d3dx9.h>
#include "Tex.h"
class Library;
class SceneChangeListener;
class ModeManager;
class Map;
class CollisionChecker;
class ServerBrother;
class ServerYoungerBrother;
class DrawPositionSetter;
class GameTimeManager;
class Text;
class Shadow;
class Mutex;

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
	ModeManager*				m_pModeManager;
	Map*						m_pMap;
	CollisionChecker*			m_pCollisionChecker;
	ServerBrother*				m_pBrother;
	ServerYoungerBrother*		m_pYoungerBrother;
	DrawPositionSetter*			m_pDrawPositionSetter;
	GameTimeManager*			m_pGameTimeManager;
	Text*						m_pText;
	Shadow*						m_pShadow;
	HWND						m_hWnd;
	Mutex*						m_pMutex;
	bool*						m_pisGameClear;
	bool						m_KeyCheckOK;
	bool						m_RecvSend;

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