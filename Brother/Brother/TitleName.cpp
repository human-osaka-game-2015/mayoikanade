#include "TitleName.h"
#include "TitleScene.h"

TitleName::TitleName(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture) :m_pLibrary(pLibrary), m_pTexture(pTexture)
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

	m_pLibrary->Set_Draw_Tex(m_pTexture, titlename);
}
