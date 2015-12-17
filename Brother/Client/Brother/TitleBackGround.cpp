#include "TitleBackGround.h"
#include "TitleScene.h"

TitleBackGround::TitleBackGround(Library* pLibrary) :m_pLibrary(pLibrary)
{
	//’†‰›‚É—ˆ‚é‚æ‚¤‚É‰Šú’lÝ’è
	m_Pos.x = TITLEBACKGROUNDPOS_X;
	m_Pos.y = TITLEBACKGROUNDPOS_Y;
}

TitleBackGround::~TitleBackGround()
{

}

void TitleBackGround::Control()
{

}

void TitleBackGround::Draw()
{
	CustomVertex background[4];

	m_pLibrary->MakePosition(TITLE_BACKGROUND, &m_Pos);

	m_pLibrary->MakeVertex(TITLE_BACKGROUND, background);
	m_pLibrary->xySet(m_Pos, background);

	m_pLibrary->DrawTexture(TEX_TITLE, background);
}