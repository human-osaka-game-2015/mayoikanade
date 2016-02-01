#include "OpeningScene.h"
#include <Vmr9.h>


/**
 * OpeningScene�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X
 * @param[in] hWnd �E�B���h�E�n���h��
 */
OpeningScene::OpeningScene(Library* pLibrary, HWND hWnd) :
Scene(pLibrary),
m_pGB(NULL),
m_pVMR9(NULL),
m_pCGB2(NULL),
m_pMediaCont(NULL),
m_hWnd(hWnd)
{
	//time�̏�����
	m_time = INIT_TIME;

	WCHAR wFileName[] = L"A.avi";

	//COM�R���|�[�l���g���g����ŕK�v
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		MessageBox(NULL, "COM�̏������Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
	}

	//�t�B���^�O���t�I�u�W�F�N�g���쐬����IgraphInterface�̃|�C���^�擾
	//IGraphBuilder�̓t�B���^�O���t�̊Ǘ��ƃC���^�[�t�F�[�X�̒�
	if (FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, reinterpret_cast<void**>(&m_pGB))))
	{
		MessageBox(NULL, "�O���t�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		CoUninitialize();
	}

	//VRM9�t�B���^�̍쐬�Ɠo�^
	//VRM9�̓����_�����O��S�����Ă����
	if (FAILED(CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&m_pVMR9))))
	{
		MessageBox(NULL, "VMR9�t�B���^�̍쐬�Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		CoUninitialize();
	}

	//�t�B���^�O���t�o�^
	m_pGB->AddFilter(m_pVMR9, L"VMR9");

	// VRM9���E�B���h�E���X���[�h�ɂ���
	IVMRFilterConfig* pVMRCfg = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&pVMRCfg))))
	{
		MessageBox(NULL, "IVMRFilterConfig�̍쐬�Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}
	
	//�E�B���h�E���X���[�h�ɕύX����
	pVMRCfg->SetRenderingMode(VMRMode_Windowless);

	// IVMRFilterConfig�̓E�B���h�E���X���[�h�ɂ��邽�߂����̂��̂Ȃ̂ŉ������
	pVMRCfg->Release();


	// �`��E�B���h�E�̎w��
	IVMRWindowlessControl9* pVMRWndCont = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRWindowlessControl9, reinterpret_cast<void**>(&pVMRWndCont))))
	{
		MessageBox(NULL, "IVMRWindowlessControl9�̍쐬�Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}
	pVMRWndCont->SetVideoClippingWindow(hWnd);


	// �\�[�X�t�B���^�̐����Ɠo�^
	IBaseFilter* pSource = NULL;
	m_pGB->AddSourceFilter(wFileName, wFileName, &pSource);


	//CaptureGraphBuilder2�C���^�[�t�F�C�X�̎擾
	//CaptureGraphBuilder2�̓t�B���^�ڑ���������x���������Ă���邢�����
	if (FAILED(CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, reinterpret_cast<void**>(&m_pCGB2))))
	{
		MessageBox(NULL, "CaptureGraphBuilder2�̎擾�Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}

	//ICaptureGraphBuilder2�̏�����
	//IGraphBuilder��n�������ł��܂�����Ă����
	m_pCGB2->SetFiltergraph(m_pGB);



	// �t�B���^�̐ڑ�
	if (FAILED(m_pCGB2->RenderStream(0, 0, pSource, 0, m_pVMR9)))
	{
		MessageBox(NULL, "�t�B���^�ڑ��Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		m_pCGB2->Release();
		m_pGB->Release();
		CoUninitialize();
	}

	if (FAILED(m_pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0)))
	{
		MessageBox(NULL, "�t�B���^�ڑ��Ɏ��s���܂���", "OpeningScene.cpp", MB_OK);
		m_pCGB2->Release();
		m_pGB->Release();
		CoUninitialize();
	}



	// �`��̈�̐ݒ�
	LONG W, H;
	RECT SrcRect, ClientRect;

	//����̃T�C�Y���擾
	pVMRWndCont->GetNativeVideoSize(&W, &H, NULL, NULL);

	//SrcRect�Ɉڂ�
	SetRect(&SrcRect, MOVIE_LEFT, MOVIE_TOP, W, H);

	//�N���C�A���g�̈�擾
	GetClientRect(hWnd, &ClientRect);

	//����T�C�Y�ƃN���C�A���g�̈��n���āA�N���C�A���g�̈�S�̂ɕ\�������悤�ɂ���
	pVMRWndCont->SetVideoPosition(&SrcRect, &ClientRect);


	// �E�B���h�E���X�R���g���[���͕s�v
	pVMRWndCont->Release();



	//���f�B�A�R���g���[���C���^�[�t�F�C�X�̎擾
	//�����g���ē���Đ��Ƃ�����
	if (FAILED(m_pGB->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&m_pMediaCont))))
	{
		m_pCGB2->Release();
		m_pGB->Release();
		CoUninitialize();
	}


	//�Đ�
	m_pMediaCont->Run();
}

/**
 * OpeningScene�̃f�X�g���N�^
 */
OpeningScene::~OpeningScene()
{
	// �����~
	m_pMediaCont->Stop();

	//�������
	m_pMediaCont->Release();
	m_pVMR9->Release();
	m_pCGB2->Release();
	m_pGB->Release();

	//Com�͂����g��Ȃ�
	CoUninitialize();
}

/**
 * OpeningScene�̃R���g���[��
 * @return �J�ڐ�̃V�[��
 */
SCENE_NUM OpeningScene::Control()
{
	m_time = INIT_TIME;
	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(ONE_MILLISECOND);

	
	while (m_time <= OPENING_TIME)
	{
		Sleep(ONE_MILLISECOND);
		SyncNow = timeGetTime();
		if (SyncNow - SyncOld >= ONE_FRAME)
		{
			PadCheck();

			//B�{�^���������ꂽ�甲����
			if (m_ButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
			{
				break;
			}


			m_time++;
			SyncOld = SyncNow;
		}
	}

	timeEndPeriod(ONE_MILLISECOND);

	return TITLE_SCENE;
}

/**
 * OpeningScene�̕`��֐�
 */
void OpeningScene::Draw()
{

}

/**
 * OpeningScene�ł�GamePad�̃`�F�b�N�֐�
 */
void OpeningScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}
