#include "LogoBackGround.h"
#include "LogoScene.h"

LogoBackGround::LogoBackGround(Library* pLibrary) :m_pLibrary(pLibrary)
{
	//中央に来るように初期値設定
	m_Pos.x = LOGOBACKGROUNDPOS_X;
	m_Pos.y = LOGOBACKGROUNDPOS_Y;
}

LogoBackGround::~LogoBackGround()
{

}

//フェードイン　アウトが終わったらtrueを返す
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
		if (m_alpha == 0)
		{
			return true;
		}
	}

	return false;
}

void LogoBackGround::Draw()
{
	CustomVertex background[4];

	m_pLibrary->MakePosition(TEAMLOGO,&m_Pos);
	
	m_pLibrary->MakeVertex(TEAMLOGO, background);
	m_pLibrary->xySet(m_Pos, background);

	for (int i = 0; i < 4; i++)
	{
		background[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_LOGO, background);
}