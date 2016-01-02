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
	//timeの初期化
	m_time = 0;
	
	WCHAR wFileName[] = L"A.avi";
	
	//COMコンポーネントを使う上で必要
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		MessageBox(0, "COMの初期化に失敗しました", "", MB_OK);
	}

	//フィルタグラフオブジェクトを作成してIgraphInterfaceのポインタ取得
	//IGraphBuilderはフィルタグラフの管理とインターフェースの提供
	if (FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, reinterpret_cast<void**>(&m_pGB))))
	{
		MessageBox(0, "グラフインターフェースの取得に失敗しました", "", MB_OK);
		CoUninitialize(); 
	}

	//VRM9フィルタの作成と登録
	//VRM9はレンダリングを担当してくれる
	if (FAILED(CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&m_pVMR9))))
	{ 
		MessageBox(0, "VMR9フィルタの作成に失敗しました", "", MB_OK);
		CoUninitialize(); 
	}
	m_pGB->AddFilter(m_pVMR9, L"VMR9");       // フィルタグラフに登録
	

	// VRM9をウィンドウレスモードにする
	IVMRFilterConfig* pVMRCfg = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&pVMRCfg))))
	{ 
		MessageBox(0, "IVMRFilterConfigの作成に失敗しました", "", MB_OK);
		m_pGB->Release(); 
		CoUninitialize();
	}
	//ウィンドウレスモードに変更する
	//フルスクリーンじゃなかったら必要ないと思う
	pVMRCfg->SetRenderingMode(VMRMode_Windowless);
	// IVMRFilterConfigはウィンドウレスモードにするだけなのでもう必要ない
	pVMRCfg->Release();


	// 描画ウィンドウの指定
	IVMRWindowlessControl9* pVMRWndCont = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRWindowlessControl9, reinterpret_cast<void**>(&pVMRWndCont))))
	{
		MessageBox(0, "IVMRWindowlessControl9の作成に失敗しました", "", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}
	pVMRWndCont->SetVideoClippingWindow(hWnd);


	// ソースフィルタの生成と登録
	IBaseFilter* pSource = NULL;
	m_pGB->AddSourceFilter(wFileName, wFileName, &pSource);


	// CaptureGraphBuilder2インターフェイスの取得
	//CaptureGraphBuilder2はフィルタ接続をある程度自動化してくれるいいやつ
	if (FAILED(CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, reinterpret_cast<void**>(&m_pCGB2))))
	{ 
		MessageBox(0, "CaptureGraphBuilder2の取得に失敗しました", "", MB_OK);
		m_pGB->Release(); 
		CoUninitialize(); 
	}

	//ICaptureGraphBuilder2の初期化
	//IGraphBuilderを渡すだけでよい
	m_pCGB2->SetFiltergraph(m_pGB);



	// フィルタの接続
	if (FAILED(m_pCGB2->RenderStream(0, 0, pSource, 0, m_pVMR9)))
	{
		MessageBox(0, "フィルタ接続に失敗しました", "", MB_OK);
		m_pCGB2->Release(); 
		m_pGB->Release(); 
		CoUninitialize(); 
	}

	if (FAILED(m_pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0)))
	{
		MessageBox(0, "フィルタ接続に失敗しました", "", MB_OK);
		m_pCGB2->Release();
		m_pGB->Release();
		CoUninitialize();
	}



	// 描画領域の設定
	LONG W, H;
	RECT SrcRect, ClientRect;
	
	//動画のサイズを取得
	pVMRWndCont->GetNativeVideoSize(&W, &H, NULL, NULL);
	
	//SrcRectに移す
	SetRect(&SrcRect, 0, 0, W, H);
	
	//クライアント領域取得
	GetClientRect(hWnd, &ClientRect);
	
	//動画サイズとクライアント領域を渡して、クライアント領域全体に表示されるようにする
	pVMRWndCont->SetVideoPosition(&SrcRect, &ClientRect);
	

	// ウィンドウレスコントロールは不必要
	pVMRWndCont->Release();



	// メディアコントロールインターフェイスの取得
	//こいつ使って動画再生とかする
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
	// 動画停止
	m_pMediaCont->Stop();
	//NULLチェックとか入れること
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

	//60*43とか、やっつけコードになってる
	//時間があれば終了通知でも取ってやるつもり
	//m_timeも消したい
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
