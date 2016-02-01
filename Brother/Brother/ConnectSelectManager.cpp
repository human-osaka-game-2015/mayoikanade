#include "ConnectSelectManager..h"
#include "ConnectingScene.h"
#include "Scene.h"

#define SERVERPOS_X 1100
#define SERVERPOS_Y 500
#define CLIENTPOS_X 1100
#define CLIENTPOS_Y 650


ConnectSelectManager::ConnectSelectManager(Library* pLibrary, bool* pPadState, bool* pPadOldState) 
	:m_pLibrary(pLibrary), m_PadState(pPadState), m_PadOldState(pPadOldState)
{

	m_ClientPos.x = SERVERPOS_X;
	m_ClientPos.y = SERVERPOS_Y;
	m_ServerPos.x = CLIENTPOS_X;
	m_ServerPos.y = CLIENTPOS_Y;
	m_CursolPos.w = 100;
	m_CursolPos.h = 130;

	m_ConnectType = SERVER_TYPE;
}

ConnectSelectManager::~ConnectSelectManager()
{
}

CONNECT_TYPE ConnectSelectManager::Control()
{
	m_pLibrary->KeyCheck(&Key[KEY_UP], DIK_UP);
	m_pLibrary->KeyCheck(&Key[KEY_DOWN], DIK_DOWN);
	m_pLibrary->KeyCheck(&Key[KEY_FIRE], DIK_RETURN);

	//コントローラーの入力で状態を変更して
	//カーソル位置なんかが変わるようにしている
	if (m_PadState[ANALOG_UP] == true && m_PadOldState[ANALOG_UP] == false || Key[KEY_UP] == PUSH)
	{
		switch (m_ConnectType)
		{
		case SERVER_TYPE:
			m_ConnectType = CLIENT_TYPE;

			break;
		case CLIENT_TYPE:
			m_ConnectType = SERVER_TYPE;

			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_DOWN] == true && m_PadOldState[ANALOG_DOWN] == false || Key[KEY_DOWN] == PUSH)
	{
		switch (m_ConnectType)
		{
		case SERVER_TYPE:
			m_ConnectType = CLIENT_TYPE;

			break;
		case CLIENT_TYPE:
			m_ConnectType = SERVER_TYPE;

			break;
		default:

			break;
		}
	}

	//ボタンが押されたら現在指している選択項目を返す
	if (m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1) == PAD_PUSH || Key[KEY_FIRE] == PUSH)
	{
		return m_ConnectType;
	}

	return CONNECTSELECT_NONE;
}

void ConnectSelectManager::Draw()
{
	CustomVertex ServerButton[4];
	CustomVertex ClientButton[4];
	CustomVertex Cursol[4];

	switch (m_ConnectType)
	{
	case SERVER_TYPE:
		m_CursolPos.x = SERVERPOS_X - 180;
		m_CursolPos.y = SERVERPOS_Y - 10;

		break;
	case CLIENT_TYPE:
		m_CursolPos.x = CLIENTPOS_X - 180;
		m_CursolPos.y = CLIENTPOS_Y - 10;

		break;
	}

	//カーソルのアニメーション
	int CursolId;
	CursolId = m_pLibrary->AnimaControl(m_CursolCurrentAnima);


	//positionの幅高さ設定
	m_pLibrary->MakePosition(CONNECT_START, &m_ServerPos);
	m_pLibrary->MakePosition(CONNECT_STAFF, &m_ClientPos);


	//tu　tvの設定
	m_pLibrary->MakeVertex(CONNECT_START, ServerButton);
	m_pLibrary->MakeVertex(CONNECT_STAFF, ClientButton);
	m_pLibrary->MakeVertex(CursolId, Cursol);


	//X yの設定
	m_pLibrary->xySet(m_ServerPos, ServerButton);
	m_pLibrary->xySet(m_ClientPos, ClientButton);
	m_pLibrary->xySet(m_CursolPos, Cursol);


	m_pLibrary->DrawTexture(TEX_CONNECT, ServerButton);
	m_pLibrary->DrawTexture(TEX_CONNECT, ClientButton);
	m_pLibrary->DrawTexture(TEX_CONNECT, Cursol);


}