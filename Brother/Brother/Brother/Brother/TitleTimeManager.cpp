#include "TitleTimeManager.h"
#include "TitleScene.h"

TitleTimeManager::TitleTimeManager(Library* pLibrary, unsigned int& GameTime) :m_pLibrary(pLibrary), m_GameTime(GameTime)
{
	m_GameTime = 0;

	//初期位置に設定
	m_Pos.x = TITLEBLACKOUT_X;
	m_Pos.y = TITLEBLACKOUT_Y;

	//大きさも設定
	m_Pos.w = TITLEBLACKOUT_W;
	m_Pos.h = TITLEBLACKOUT_H;
}

TitleTimeManager::~TitleTimeManager()
{

}

bool TitleTimeManager::Control()
{
	m_GameTime++;
	
	//フェードアウトじゃなくてポケモンフラッシュのほうが面白い
	//alphaは初期値が255
	//20秒以下でalphaが0じゃないときはalphaを引いてだんだん明るくする。
	if (m_GameTime > 1200)
	{
		m_alpha++;
		if (m_alpha == COLORMAX)
		{
			return true;
		}
	}
	else if (m_alpha != 0)
	{
		m_alpha--;
	}

	return false;
}

void TitleTimeManager::Draw()
{
	CustomVertex blackout[4];


	m_pLibrary->MakeVertex(TITLE_BLACK, blackout);
	m_pLibrary->xySet(m_Pos, blackout);

	for (int i = 0; i < 4; i++)
	{
		blackout[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_TITLE, blackout);
}