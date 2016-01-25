#include "OpeningScene.h"
#include <Vmr9.h>


/**
 * OpeningSceneクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラス
 * @param[in] hWnd ウィンドウハンドル
 */
OpeningScene::OpeningScene(Library* pLibrary, HWND hWnd) :
Scene(pLibrary),
m_pGB(NULL),
m_pVMR9(NULL),
m_pCGB2(NULL),
m_pMediaCont(NULL),
m_hWnd(hWnd)
{
	//timeの初期化
	m_time = INIT_TIME;

	WCHAR wFileName[] = L"A.avi";

	//COMコンポーネントを使う上で必要
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		MessageBox(NULL, "COMの初期化に失敗しました", "OpeningScene.cpp", MB_OK);
	}

	//フィルタグラフオブジェクトを作成してIgraphInterfaceのポインタ取得
	//IGraphBuilderはフィルタグラフの管理とインターフェースの提供
	if (FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, reinterpret_cast<void**>(&m_pGB))))
	{
		MessageBox(NULL, "グラフインターフェースの取得に失敗しました", "OpeningScene.cpp", MB_OK);
		CoUninitialize();
	}

	//VRM9フィルタの作成と登録
	//VRM9はレンダリングを担当してくれる
	if (FAILED(CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&m_pVMR9))))
	{
		MessageBox(NULL, "VMR9フィルタの作成に失敗しました", "OpeningScene.cpp", MB_OK);
		CoUninitialize();
	}

	//フィルタグラフ登録
	m_pGB->AddFilter(m_pVMR9, L"VMR9");

	// VRM9をウィンドウレスモードにする
	IVMRFilterConfig* pVMRCfg = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&pVMRCfg))))
	{
		MessageBox(NULL, "IVMRFilterConfigの作成に失敗しました", "OpeningScene.cpp", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}
	
	//ウィンドウレスモードに変更する
	pVMRCfg->SetRenderingMode(VMRMode_Windowless);

	// IVMRFilterConfigはウィンドウレスモードにするためだけのものなので解放する
	pVMRCfg->Release();


	// 描画ウィンドウの指定
	IVMRWindowlessControl9* pVMRWndCont = NULL;
	if (FAILED(m_pVMR9->QueryInterface(IID_IVMRWindowlessControl9, reinterpret_cast<void**>(&pVMRWndCont))))
	{
		MessageBox(NULL, "IVMRWindowlessControl9の作成に失敗しました", "OpeningScene.cpp", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}
	pVMRWndCont->SetVideoClippingWindow(hWnd);


	// ソースフィルタの生成と登録
	IBaseFilter* pSource = NULL;
	m_pGB->AddSourceFilter(wFileName, wFileName, &pSource);


	//CaptureGraphBuilder2インターフェイスの取得
	//CaptureGraphBuilder2はフィルタ接続をある程度自動化してくれるいいやつ
	if (FAILED(CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, reinterpret_cast<void**>(&m_pCGB2))))
	{
		MessageBox(NULL, "CaptureGraphBuilder2の取得に失敗しました", "OpeningScene.cpp", MB_OK);
		m_pGB->Release();
		CoUninitialize();
	}

	//ICaptureGraphBuilder2の初期化
	//IGraphBuilderを渡すだけでうまくやってくれる
	m_pCGB2->SetFiltergraph(m_pGB);



	// フィルタの接続
	if (FAILED(m_pCGB2->RenderStream(0, 0, pSource, 0, m_pVMR9)))
	{
		MessageBox(NULL, "フィルタ接続に失敗しました", "OpeningScene.cpp", MB_OK);
		m_pCGB2->Release();
		m_pGB->Release();
		CoUninitialize();
	}

	if (FAILED(m_pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0)))
	{
		MessageBox(NULL, "フィルタ接続に失敗しました", "OpeningScene.cpp", MB_OK);
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
	SetRect(&SrcRect, MOVIE_LEFT, MOVIE_TOP, W, H);

	//クライアント領域取得
	GetClientRect(hWnd, &ClientRect);

	//動画サイズとクライアント領域を渡して、クライアント領域全体に表示されるようにする
	pVMRWndCont->SetVideoPosition(&SrcRect, &ClientRect);


	// ウィンドウレスコントロールは不要
	pVMRWndCont->Release();



	//メディアコントロールインターフェイスの取得
	//こいつ使って動画再生とかする
	if (FAILED(m_pGB->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&m_pMediaCont))))
	{
		m_pCGB2->Release();
		m_pGB->Release();
		CoUninitialize();
	}


	//再生
	m_pMediaCont->Run();
}

/**
 * OpeningSceneのデストラクタ
 */
OpeningScene::~OpeningScene()
{
	// 動画停止
	m_pMediaCont->Stop();

	//解放処理
	m_pMediaCont->Release();
	m_pVMR9->Release();
	m_pCGB2->Release();
	m_pGB->Release();

	//Comはもう使わない
	CoUninitialize();
}

/**
 * OpeningSceneのコントロール
 * @return 遷移先のシーン
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

			//Bボタンが押されたら抜ける
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
 * OpeningSceneの描画関数
 */
void OpeningScene::Draw()
{

}

/**
 * OpeningSceneでのGamePadのチェック関数
 */
void OpeningScene::PadCheck()
{
	m_pLibrary->Check(GAMEPAD1);
	m_ButtonState[XINPUT_BUTTON_A] = m_pLibrary->GetButtonState(GAMEPAD_A, GAMEPAD1);
}
