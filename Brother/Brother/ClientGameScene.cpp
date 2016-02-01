#include "Client.h"
#include <Windows.h>
#include "ClientGameScene.h"
#include "Library.h"
#include "ModeManager.h"
#include "SceneChangeListener.h"
#include "ClientYoungerBrother.h"
#include "ClientBrother.h"
#include "Map.h"
#include "CollisionChecker.h"
#include "Text.h"
#include "Shadow.h"
#include "GameTimeManager.h"
#include "DrawPositionSetter.h"

#include "Mutex.h"

/**
 * ClientGameScene�̒ʐM�֐�
 * @param[in,out] Gamemain �Q�[���V�[���ɑ΂��Ẵ|�C���^(�󂯎���������������񂾂�A�ǂݍ��񂾂肷��)
 * @return �֐����������������Ԃ��Ă��邪�A�g�p�͂��Ă��Ȃ�
 */
DWORD WINAPI ClientGameScene::Connect(LPVOID Gamemain)
{
	GameThread* p_GameThread = static_cast<GameThread*>(Gamemain);
	ClientGameScene* pGameScene = static_cast<ClientGameScene*>(p_GameThread->pGameScene);
	Client BrotherClient("51234");
	char IP[16];

	for (int i = 0; i < 16; i++)
	{
		IP[i] = p_GameThread->portnum[i];
	}
	BrotherClient.serverConnect(IP);

	//�ʒu�̓�������^�C�~���O���Ƃ�B�ł������A�g��Ȃ��Ȃ�Ǝv���B
	static int SyncCount = 0;

	//�T�[�o�[�ő���M���鎞�̔z��̃f�[�^���e-------------------------------------------------------------
	// 0 LEFT
	// 1 RIGHT
	// 2 DOWN
	// 3 UP
	// 4 A
	// 5 B
	//-------------------------------------------------------------------------------------------------

	DWORD SyncOld = timeGetTime();
	//DWORD SyncNow;

	timeBeginPeriod(1);

	while (pGameScene->m_isGameScene)
	{
		//SyncNow = timeGetTime();

		//Sleep(1);
		if (pGameScene->isConnect == true && pGameScene->m_KeyCheckOK == true)
		{
			pGameScene->m_pMutex->GetMutexHwnd();
			pGameScene->m_pMutex->WaitMutex();
			for (int i = 0; i < 4; i++)
			{
				if (pGameScene->m_PadState[i] == true)
				{
					pGameScene->CData[i] = 1;
				}
				else
				{
					pGameScene->CData[i] = 0;
				}
			}


			for (int i = 4; i < 6; i++)
			{
				if (pGameScene->m_ButtonState[i - 4] == PAD_PUSH || pGameScene->m_ButtonState[i - 4] == PAD_ON)
				{
					pGameScene->CData[i] = 1;
				}
				else if (pGameScene->m_ButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ButtonState[i - 4] == PAD_OFF)
				{
					pGameScene->CData[i] = 0;
				}
			}
			//�ʒu�𓯊������邽�߂����Ǎ��́A���܂��s���ĂȂ��̂�
			//pGameScene->GetYoungBrotherPos(&pGameScene->m_SendData.Yposx,&pGameScene->m_SendData.Yposy);

			//char* sendptr = reinterpret_cast<char*>(&pGameScene->CData);
			BrotherClient.sendData(pGameScene->CData, sizeof(pGameScene->CData));



			//char* recvptr = reinterpret_cast<char*>(&pGameScene->SData);
			BrotherClient.recvData(pGameScene->SData, sizeof(pGameScene->SData));
			//�ʒu�𓯊������邽�߂����Ǎ��́A���܂��s���ĂȂ��̂�
			//if (SyncCount % 120 == 0)
			//{
			//	pGameScene->SetBrotherPos(&pGameScene->m_RecvData.Bposx, &pGameScene->m_RecvData.Bposy);
			//}


			pGameScene->m_ServerPadOldState[ANALOG_LEFT] = pGameScene->m_ServerPadState[ANALOG_LEFT];
			pGameScene->m_ServerPadOldState[ANALOG_RIGHT] = pGameScene->m_ServerPadState[ANALOG_RIGHT];
			pGameScene->m_ServerPadOldState[ANALOG_DOWN] = pGameScene->m_ServerPadState[ANALOG_DOWN];
			pGameScene->m_ServerPadOldState[ANALOG_UP] = pGameScene->m_ServerPadState[ANALOG_UP];

			for (int i = 0; i < 4; i++)
			{
				if (pGameScene->SData[i] == 1)
				{
					pGameScene->m_ServerPadState[i] = true;
				}
				else
				{
					pGameScene->m_ServerPadState[i] = false;
				}
			}


			//���C�u�����̏C���ɂ��Ȃ�̂ł��܂͂����
			for (int i = 4; i < 6; i++)
			{
				if (pGameScene->SData[i] == 1)
				{
					if (pGameScene->m_ServerButtonState[i - 4] == PAD_PUSH || pGameScene->m_ServerButtonState[i - 4] == PAD_ON)
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_ON;
					}
					else
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_PUSH;
					}
				}
				else if (pGameScene->SData[i] == 0)
				{
					if (pGameScene->m_ServerButtonState[i - 4] == PAD_RELEASE || pGameScene->m_ServerButtonState[i - 4] == PAD_OFF)
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_OFF;
					}
					else
					{
						pGameScene->m_ServerButtonState[i - 4] = PAD_RELEASE;
					}
				}
			}

			ZeroMemory(&pGameScene->CData, sizeof(pGameScene->CData));
			ZeroMemory(&pGameScene->SData, sizeof(pGameScene->SData));
			pGameScene->m_SendRecv = true;
			pGameScene->m_KeyCheckOK = false;
			pGameScene->m_pMutex->MutexRelease();
		}
	}
	timeEndPeriod(1);

	ExitThread(TRUE);
}

/**
 * ClientGameScene�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X
 * @param[in] hWnd �E�B���h�E�n���h��
 * @param[in] IPadd IP�A�h���X���i�[����ϐ�
 * @param[out] pisGameClear �Q�[�����N���A���������i�[����
 */
ClientGameScene::ClientGameScene(Library* pLibrary, HWND hWnd, char* IPadd, bool* pisGameClear) :
Scene(pLibrary), 
m_hWnd(hWnd),
m_pisGameClear(pisGameClear),
m_isGameScene(true),
isConnect(false),
m_KeyCheckOK(false),
m_SendRecv(false)
{
	//GamePad���̏�����
	for (int i = FOR_DEFAULT_INIT; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}

	//GameScene�̉摜��csv�̓ǂݍ���
	m_pLibrary->FileInfoSet("file.csv", FILE_INFO);
	m_pLibrary->VertexInfoSet("GameTex.csv", GAME_VERTEXINFO_MAX);
	m_pLibrary->AnimaInfoSet("Gameanimation.csv", GAMEANIMA_MAX);
	m_pLibrary->LoadTextureEx("GameScene.png", TEX_GAME, COLORMAX, COLORMIN, COLORMAX, COLORMIN);
	m_pLibrary->LoadTextureEx("Ui.png", TEX_UI, COLORMAX, COLORMIN, COLORMAX, COLORMIN);
	m_pLibrary->LoadTextureEx("en.png", STENCIL, COLORMAX, COLORMIN, COLORMAX, COLORMAX);

	//�����̓ǂݍ���
	m_pLibrary->SoundLoad("S_G_BGM.wav", GAME_BGM);

	//�������[�v
	m_pLibrary->SoundOperation(GAME_BGM, SOUND_LOOP);


	//�I�u�W�F�N�g�̐���
	m_pSceneChangeListener	= new SceneChangeListener(&m_NextScene,m_pisGameClear);
	m_pMap					= new Map(m_pLibrary);
	m_pCollisionChecker		= new CollisionChecker(m_pMap);
	m_pDrawPositionSetter	= new DrawPositionSetter(m_pMap);
	m_pGameTimeManager		= new GameTimeManager(&m_time);
	m_pYoungerBrother		= new ClientYoungerBrother(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager);
	m_pBrother				= new ClientBrother(m_pLibrary, m_ServerPadState, m_ServerPadOldState, m_ServerButtonState, m_pCollisionChecker, m_pDrawPositionSetter, m_pGameTimeManager, m_pYoungerBrother);
	m_pShadow				= new Shadow(m_pLibrary, m_pGameTimeManager);
	m_pText					= new Text(m_pLibrary, m_PadState, m_PadOldState, m_ButtonState);
	m_pModeManager			= new ModeManager(m_pSceneChangeListener, m_pBrother, m_pYoungerBrother, m_pGameTimeManager, m_pShadow, m_pText, m_pisGameClear,m_pMap);
	m_pMutex = new Mutex("ClientMutex");


	//ModeManagerSet��Brother�Ȃǂɑ΂���m_ModeManager��n��
	m_pBrother->ModeManagerSet(m_pModeManager);
	m_pYoungerBrother->ModeManagerSet(m_pModeManager);
	m_pShadow->ModeManagerSet(m_pModeManager);
	m_pText->ModeManagerSet(m_pModeManager);
	m_pGameTimeManager->ModeManagerSet(m_pModeManager);

	m_pYoungerBrother->PlayerSet(m_pBrother);

#ifdef _DEBUG
	//Dxfont
	D3DXCreateFont(m_pLibrary->GetDevice(), FONT_HEIGHT, FONT_WIDTH, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahoma", &pFont);
	
#endif

	
	for (int i = FOR_DEFAULT_INIT; i < IP_MAX; i++)
	{
		Gamemain.portnum[i] = IPadd[i];
	}

	//�X���b�h�𗧂Ă�
	DWORD dwID;
	Gamemain.pGameScene = this;
	CreateThread(NULL, STACK_SIZE, Connect, (LPVOID)&Gamemain, THREAD_CREAT_OPTION, &dwID);
}

/**
 * ClientGameScene�N���X�̃f�X�g���N�^
 */
ClientGameScene::~ClientGameScene()
{
	//�摜��uv���̃����[�X
	m_pLibrary->FileInfoRelease();
	m_pLibrary->VertexInfoRelease();
	m_pLibrary->AnimaInfoRelease();

	//�t���O�𗎂Ƃ���Thread�ɓǂ�ł��炤
	m_isGameScene = false;

	//���������ҋ@
	Sleep(SLEEP_TIME);


#ifdef _DEBUG
	pFont->Release();
#endif

	//�I�u�W�F�N�g�j��
	delete m_pMutex;
	delete m_pModeManager;
	delete m_pText;
	delete m_pShadow;
	delete m_pYoungerBrother;
	delete m_pBrother;
	delete m_pGameTimeManager;
	delete m_pDrawPositionSetter;
	delete m_pCollisionChecker;
	delete m_pMap;
	delete m_pSceneChangeListener;

	//�T�E���h�Ɖ摜�̊J��
	m_pLibrary->ReleaseSound(GAME_BGM);
	m_pLibrary->ReleaseTexture(TEX_GAME);
}

/**
 * ClientGameScene�̃R���g���[���֐�
 * @return �J�ڐ�̃V�[��
 */
SCENE_NUM ClientGameScene::Control()
{
	if (m_KeyCheckOK == false)
	{
		PadCheck();		//���͂̃`�F�b�N
		m_KeyCheckOK = true;
	}

	//�I�u�W�F�N�g�̃R���g���[��
	m_pModeManager->Control();
	m_pGameTimeManager->Control();
	m_pMap->Control();
	m_pShadow->Control();
	m_pText->Control();
	m_pBrother->SwitchOn();
	m_pYoungerBrother->SwitchOn();

	m_pMutex->GetMutexHwnd();
	m_pMutex->WaitMutex();
	if (m_SendRecv)
	{
		if (m_pModeManager->m_alpha == COLORMIN)
		{
			m_pBrother->Control();
			m_pYoungerBrother->Control();
		}
		m_SendRecv = false;
	}
	m_pMutex->MutexRelease();

	
	return m_NextScene;
}

/**
 * ClientGameScene�̕`��֐�
 */
void ClientGameScene::Draw()
{
	//�I�u�W�F�N�g�̕`��
	m_pShadow->Draw();
	m_pMap->Draw();
	m_pBrother->Draw();
	m_pYoungerBrother->Draw();
	m_pLibrary->StencilTestEnd();
	m_pBrother->UiDraw();
	m_pYoungerBrother->UiDraw();
	m_pText->Draw();


	//�X�e�[�W�ړ����o
	CustomVertex blackout[SQUARE_VERTEX];
	Position m_Pos = { BLACKOUT_POS_X, BLACKOUT_POS_Y, BLACKOUT_POS_W, BLACKOUT_POS_H };
	m_pLibrary->xySet(m_Pos, blackout);
	m_pLibrary->MakeVertex(BLACKOUT, blackout);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		blackout[i].color = D3DCOLOR_ARGB(m_pModeManager->m_alpha, COLORMIN, COLORMIN, COLORMIN);
	}
	m_pLibrary->DrawTexture(TEX_GAME, blackout);


#ifdef _DEBUG

	RECT rect = { DEBUG_FONT_RECT_LEFT, DEBUG_FONT_RECT_TOP, DEBUG_FONT_RECT_RIGHT, DEBUG_FONT_RECT_BOTTOM };

	pFont->DrawText(NULL, "���̓`�F�b�N", DEBUG_FONT_NUM, &rect, DT_CALCRECT, NULL);
	pFont->DrawText(NULL, "���̓`�F�b�N", DEBUG_FONT_NUM, &rect, DT_LEFT | DT_BOTTOM, DEBUG_FONT_COLOR);
#endif

}


/**
 * ClientGameScene��GamePad�`�F�b�N�֐�
 */
void ClientGameScene::PadCheck()
{
		m_pLibrary->Check(GAMEPAD1);
		isConnect = true;

		m_PadOldState[ANALOG_LEFT] = m_PadState[ANALOG_LEFT];
		m_PadOldState[ANALOG_RIGHT] = m_PadState[ANALOG_RIGHT];
		m_PadOldState[ANALOG_DOWN] = m_PadState[ANALOG_DOWN];
		m_PadOldState[ANALOG_UP] = m_PadState[ANALOG_UP];

		m_PadState[ANALOG_LEFT] = m_pLibrary->GetAnalogState(ANALOG_LEFT, GAMEPAD1);
		m_PadState[ANALOG_RIGHT] = m_pLibrary->GetAnalogState(ANALOG_RIGHT, GAMEPAD1);
		m_PadState[ANALOG_DOWN] = m_pLibrary->GetAnalogState(ANALOG_DOWN, GAMEPAD1);
		m_PadState[ANALOG_UP] = m_pLibrary->GetAnalogState(ANALOG_UP, GAMEPAD1);


		m_ButtonState[0] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
		m_ButtonState[1] = m_pLibrary->GetButtonState(GAMEPAD_B, GAMEPAD1);
}

/**
 * ��̈ʒu���Ƃ�֐�
 * @param [out] posx ���x���W�̈ʒu���i�[�����
 * @param [out] posy ���y���W�̈ʒu���i�[�����
 */
void ClientGameScene::GetYoungBrotherPos(short* posx, short* posy)
{
	*posx = static_cast<short>(m_pYoungerBrother->m_PlayerX);
	*posy = static_cast<short>(m_pYoungerBrother->m_PlayerY);
}

/**
 * Brother�̍��W���Z�b�g����
 * @param [in] posx �Z�b�g����x���W
 * @param [in] posy �Z�b�g����y���W
 */
void ClientGameScene::SetBrotherPos(short* posx, short* posy)
{
	m_pBrother->m_PlayerX = *posx;
	m_pBrother->m_PlayerY = *posy;
}
