#include "OpeningScene.h"
#include <Vmr9.h>


OpeningScene::OpeningScene(Library* pLibrary, HWND hWnd) :
Scene(pLibrary),
m_pGB(NULL),
m_pVMR9(NULL),
m_pCGB2(NULL),
m_pMediaCont(NULL),
m_hWnd(hWnd)
{
	//time�̏�����
	m_time = 0;
	
	WCHAR wFileName[] = L"A.avi";
	
	//COM�R���|�[�l���g���g����ŕK�v
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		MessageBox(0, "COM�̏������Ɏ��s���܂���", "", MB_OK);
	}

	//�t�B���^�O���t�I�u�W�F�N�g���쐬����IgraphInterface�̃|�C���^�擾
	//IGraphBuilder�̓t�B���^�O���t�̊Ǘ��ƃC���^�[�t�F�[�X�̒�
	if (FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, reinterpret_cast<void**>(&m_pGB))))
	{
		MessageBox(0, "�O���t�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���", "", MB_OK);
		CoUninitialize(); 
	}

	//VRM9�t�B���^�̍쐬�Ɠo�^
	//VRM9�̓����_�����O��S�����Ă����
	if (FAILED(CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&m_pVMR9))))
	{ 
		MessageBox(0, "VMR9�t�B���^�̍쐬�Ɏ��s���܂���", "", MB_OK);
		CoUninitialize(); 
	}
	m_pGB->AddFilter(m_pVMR9, L"VMR9");       // �t�B���^�O���t�ɓo�^
	

	// VRM9���E�B���h�E���X���[�h�ɂ���
	IVMRFilterConfig* pVMRCfg = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&pVMRCfg))))
	{ 
		MessageBox(0, "IVMRFilterConfig�̍쐬�Ɏ��s���܂���", "", MB_OK);
		m_pGB->Release(); 
		CoUninitialize();
	}
	//�E�B���h�E���X���[�h�ɕύX����
	//�t���X�N���[������Ȃ�������K�v�Ȃ��Ǝv��
	pVMRCfg->SetRenderingMode(VMRMode_Windowless);
	// IVMRFilterConfig�̓E�B���h�E���X���[�h�ɂ��邾���Ȃ̂ł����K�v�Ȃ�
	pVMRCfg->Release();


	// �`��E�B���h�E�̎w��
	IVMRWindowlessControl9* pVMRWndCont = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRWindowlessControl9, reinterpret_cast<void**>(&pVMRWndCont))))
	{
		MessageBox(0, "IVMRWindowlessControl9�̍쐬�Ɏ��s���܂���", "", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}
	pVMRWndCont->SetVideoClippingWindow(hWnd);


	// �\�[�X�t�B���^�̐����Ɠo�^
	IBaseFilter* pSource = NULL;
	m_pGB->AddSourceFilter(wFileName, wFileName, &pSource);


	// CaptureGraphBuilder2�C���^�[�t�F�C�X�̎擾
	//CaptureGraphBuilder2�̓t�B���^�ڑ���������x���������Ă���邢�����
	if (FAILED(CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, reinterpret_cast<void**>(&m_pCGB2))))
	{ 
		MessageBox(0, "CaptureGraphBuilder2�̎擾�Ɏ��s���܂���", "", MB_OK);
		m_pGB->Release(); 
		CoUninitialize(); 
	}

	//ICaptureGraphBuilder2�̏�����
	//IGraphBuilder��n�������ł悢
	m_pCGB2->SetFiltergraph(m_pGB);



	// �t�B���^�̐ڑ�
	if (FAILED(m_pCGB2->RenderStream(0, 0, pSource, 0, m_pVMR9)))
	{
		MessageBox(0, "�t�B���^�ڑ��Ɏ��s���܂���", "", MB_OK);
		m_pCGB2->Release(); 
		m_pGB->Release(); 
		CoUninitialize(); 
	}

	if (FAILED(m_pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0)))
	{
		MessageBox(0, "�t�B���^�ڑ��Ɏ��s���܂���", "", MB_OK);
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
	SetRect(&SrcRect, 0, 0, W, H);
	
	//�N���C�A���g�̈�擾
	GetClientRect(hWnd, &ClientRect);
	
	//����T�C�Y�ƃN���C�A���g�̈��n���āA�N���C�A���g�̈�S�̂ɕ\�������悤�ɂ���
	pVMRWndCont->SetVideoPosition(&SrcRect, &ClientRect);
	

	// �E�B���h�E���X�R���g���[���͕s�K�v
	pVMRWndCont->Release();



	// ���f�B�A�R���g���[���C���^�[�t�F�C�X�̎擾
	//�����g���ē���Đ��Ƃ�����
	if (FAILED(m_pGB->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&m_pMediaCont))))
	{ 
		m_pCGB2->Release(); 
		m_pGB->Release(); 
		CoUninitialize(); 
	}

	

	m_pMediaCont->Run();

}

OpeningScene::~OpeningScene()
{
	// �����~
	m_pMediaCont->Stop();
	//NULL�`�F�b�N�Ƃ�����邱��
	m_pMediaCont->Release();
	m_pVMR9->Release();
	m_pCGB2->Release();
	m_pGB->Release();
	CoUninitialize();
}

SCENE_NUM OpeningScene::Control()
{
	m_time = 0;
	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	//60*43�Ƃ��A������R�[�h�ɂȂ��Ă�
	//���Ԃ�����ΏI���ʒm�ł�����Ă�����
	//m_time����������
	while (m_time <= 60 * 43)
	{
		Sleep(1);
		SyncNow = timeGetTime();
		if (SyncNow - SyncOld >= 1000 / 60)
		{
			PadCheck();
			
			if (m_ButtonState[0] == PAD_PUSH)
			{
				break;
			}
			

			m_time++;
			SyncOld = SyncNow;
		}
	}

	timeEndPeriod(1);

	return TITLE_SCENE;
}

void OpeningScene::Draw()
{

}

void OpeningScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[0] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}
