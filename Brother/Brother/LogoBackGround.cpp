#include "LogoBackGround.h"
#include "LogoScene.h"



/**
 * LogoBackGroundクラスのコンストラクタ
 * @param[in] pLibrary ライブラリクラス
 */
LogoBackGround::LogoBackGround(Library* pLibrary) :
m_pLibrary(pLibrary),
m_alpha(COLORMIN),
m_isFadeIn(true)
{
	//中央に来るように初期値設定
	m_Pos.x = LOGOBACKGROUNDPOS_X;
	m_Pos.y = LOGOBACKGROUNDPOS_Y;
}

/**
 * LogoBackGroundクラスのデストラクタ
 */
LogoBackGround::~LogoBackGround()
{

}

/**
 * LogoBackGroundのコントロール
 * @return フェードアウトが終わったかのフラグ
 */
bool LogoBackGround::Control()
{
	if (m_isFadeIn == true)
	{
		m_alpha++;
		if (m_alpha == COLORMAX)
		{
			m_isFadeIn = false;
		}
	}
	else
	{
		m_alpha--;
		if (m_alpha == COLORMIN)
		{
			return true;
		}
	}

	return false;
}

/**
 * LogoBackGroundの描画関数
 */
void LogoBackGround::Draw()
{
	CustomVertex background[SQUARE_VERTEX];

	m_pLibrary->MakePosition(TEAMLOGO,&m_Pos);
	
	m_pLibrary->MakeVertex(TEAMLOGO, background);
	m_pLibrary->xySet(m_Pos, background);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		background[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_LOGO, background);
}