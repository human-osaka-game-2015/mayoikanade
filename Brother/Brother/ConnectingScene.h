#ifndef CONNECTINGSCENE_H
#define CONNECTINGSCENE_H

#define CONNECTBACKGROUNDPOS_X 640
#define CONNECTBACKGROUNDPOS_Y 512
//#include <winsock2.h>

#include "Scene.h"
class Library;
class Client;
class Server;
class ConnectSelectManager;
class IPAddSelectScene;
class ListenServer;
enum CONNECT_VERTEXINFO_ID
{
	CONNECT_BACKGROUND,
	CONNECT_NAME,
	CONNECT_CURSOL01,
	CONNECT_CURSOL02,
	CONNECT_CURSOL03,
	CONNECT_CURSOL04,
	CONNECT_START,
	CONNECT_STAFF,
	CONNECT_IPADD,
	CONNECT_BLACK,
	CONNECT_VERTEXINFO_MAX
};

enum CONNECT_SOUND
{
	CONNECTBGM
};

class ConnectingScene:public Scene
{
private:
	Client*					m_pClient;
	Server*					m_pServer;
	ConnectSelectManager*	m_pConnectSelectManager;
	IPAddSelectScene*		m_pIPAddSelectScene;
	ListenServer*           m_pListenServer;

	Position	m_BackGroundPos;
	int m_alpha;
	char szIP[16];
public:
	HOSTENT* lpHost; 			//  ホスト情報を格納する構造体
	ConnectingScene(Library* pLibrary,char* IPadd);
	~ConnectingScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();
	bool m_Client_isSelect;
	bool m_Server_isSelect;
};

#endif