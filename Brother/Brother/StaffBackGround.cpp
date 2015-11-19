#include "StaffBackGround.h"
#include "StaffScene.h"

StaffBackGround::StaffBackGround(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture) :m_pLibrary(pLibrary), m_pTexture(pTexture)
{
	//’†‰›‚É—ˆ‚é‚æ‚¤‚É‰Šú’lÝ’è
	m_Pos.x = STAFFBACKGROUNDPOS_X;
	m_Pos.y = STAFFBACKGROUNDPOS_Y;
}

StaffBackGround::~StaffBackGround()
{

}

void StaffBackGround::Control()
{

}

void StaffBackGround::Draw()
{
	CustomVertex background[4];

	m_pLibrary->MakePosition(STAFF, &m_Pos);

	m_pLibrary->MakeVertex(STAFF, background);
	
	m_pLibrary->xySet(m_Pos, background);

	m_pLibrary->Set_Draw_Tex(m_pTexture, background);
}
