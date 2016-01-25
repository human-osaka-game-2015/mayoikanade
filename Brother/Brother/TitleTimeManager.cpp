#include "TitleTimeManager.h"
#include "TitleScene.h"


/**
 * TitleTimeManagerクラスのコンストラクタ
 * @param[in]  pLibrary	ライブラリクラス
 * @param[out] GameTime	Sceneのtimeを渡す
 */
TitleTimeManager::TitleTimeManager(Library* pLibrary, unsigned int& GameTime) :
m_pLibrary(pLibrary), 
m_GameTime(GameTime),
m_alpha(COLORMAX)
{
	m_GameTime = TIME_INIT;

	//初期位置に設定
	m_Pos.x = TITLEBLACKOUT_X;
	m_Pos.y = TITLEBLACKOUT_Y;

	//大きさも設定
	m_Pos.w = TITLEBLACKOUT_W;
	m_Pos.h = TITLEBLACKOUT_H;
}

/**
 * TitleSceneクラスのデストラクタ
 */
TitleTimeManager::~TitleTimeManager()
{

}

/**
 * TitleTimeManagerクラスのコンストラクタ
 * @param[in] pLibrary	ライブラリクラス
 * @param[in] hWnd		ウィンドウハンドル
 * @return フェードアウトしたらtrueを返す
 */
bool TitleTimeManager::Control()
{
	//タイムのカウント
	m_GameTime++;
	

	if (m_GameTime > FADEOUT_TIME)
	{
		m_alpha++;
		if (m_alpha == COLORMAX)
		{
			return true;
		}
	}
	else if (m_alpha != COLORMIN)
	{
		m_alpha--;
	}

	return false;
}

/**
 * TitleTimeManagerの描画関数
 */
void TitleTimeManager::Draw()
{
	CustomVertex blackout[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(TITLE_BLACK, blackout);
	m_pLibrary->xySet(m_Pos, blackout);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		blackout[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_TITLE, blackout);
}

