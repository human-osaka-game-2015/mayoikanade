#include "StaffBackGround.h"
#include "StaffScene.h"

StaffBackGround::StaffBackGround(Library* pLibrary) :m_pLibrary(pLibrary)
{
	//�����ɗ���悤�ɏ����l�ݒ�
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

	m_pLibrary->DrawTexture(TEX_STAFF, background);
}
