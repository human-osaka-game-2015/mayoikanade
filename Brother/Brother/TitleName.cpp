#include "TitleName.h"
#include "TitleScene.h"

TitleName::TitleName(Library* pLibrary) :m_pLibrary(pLibrary)
{
	//’†‰›‚É—ˆ‚é‚æ‚¤‚É‰Šú’lÝ’è
	m_Pos.x = TITLENAMEPOS_X;
	m_Pos.y = TITLENAMEPOS_Y;
}

TitleName::~TitleName()
{

}

void TitleName::Control()
{

}

void TitleName::Draw()
{
	CustomVertex titlename[4];

	m_pLibrary->MakePosition(TITLE_NAME, &m_Pos);

	m_pLibrary->MakeVertex(TITLE_NAME, titlename);
	m_pLibrary->xySet(m_Pos, titlename);

	m_pLibrary->DrawTexture(TEX_TITLE, titlename);
}
