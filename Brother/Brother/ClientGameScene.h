#ifndef GAMESCENE_H
#define GAMASCENE_H

#define PORT_MAX 16				//Port�ԍ����i�[����z��̑傫��
#define IP_MAX 16				//IP�A�h���X���i�[����z��̑傫��
#define FONT_HEIGHT 0			//D3DXFont�̃T�C�Y
#define FONT_WIDTH 8			//D3DXFont�̃T�C�Y
#define STACK_SIZE 0			//�X���b�h�̃X�^�b�N�T�C�Y(0���ƌĂяo������̃T�C�Y�ɍ��킹�Ă����)
#define THREAD_CREAT_OPTION	0	//�X���b�h���쐬����ۂ̃I�v�V�����w��(0���ƍ쐬�Ɠ����ɃX���b�h������)
#define SLEEP_TIME 3000			//�X���b�h�I����҂���
#define BLACKOUT_POS_X 640
#define BLACKOUT_POS_Y 512
#define BLACKOUT_POS_W 1280
#define BLACKOUT_POS_H 1024

#ifdef _DEBUG

#define DEBUG_FONT_RECT_LEFT 10			//�t�H���g�̈ʒu
#define DEBUG_FONT_RECT_TOP 10			//�t�H���g�̈ʒu
#define DEBUG_FONT_RECT_RIGHT 0			//�t�H���g�̈ʒu
#define DEBUG_FONT_RECT_BOTTOM 0		//�t�H���g�̈ʒu
#define DEBUG_FONT_COLOR 0xff00ffff		//�t�H���g�J���[
#define DEBUG_FONT_NUM -1				//�t�H���g�̒���(-1����NULL�܂ł𒷂��Ƃ���)

#endif

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
class Mutex;


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
	Mutex*					m_pMutex;

	HWND					m_hWnd;
	GameThread				Gamemain;
	bool*					m_pisGameClear;
	bool					m_KeyCheckOK;
	bool					m_SendRecv;


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

	//�e�X�g
	LPD3DXFONT pFont;
};


#endif