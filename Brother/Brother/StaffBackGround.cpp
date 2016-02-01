#include "StaffBackGround.h"
#include "StaffScene.h"


/**
 * StaffBackGround�N���X�̃R���X�g���N�^
 * @param[in] pLibrary	���C�u�����N���X
 */
StaffBackGround::StaffBackGround(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//�����ɗ���悤�ɏ����l�ݒ�
	m_Pos.x = STAFFBACKGROUNDPOS_X;
	m_Pos.y = STAFFBACKGROUNDPOS_Y;
}

/**
 * StaffBackGround�N���X�̃f�X�g���N�^
 */
StaffBackGround::~StaffBackGround()
{

}

/**
 * StaffBackGround�̕`��֐�
 */
void StaffBackGround::Draw()
{
	CustomVertex background[SQUARE_VERTEX];

	m_pLibrary->MakePosition(STAFF, &m_Pos);

	m_pLibrary->MakeVertex(STAFF, background);
	
	m_pLibrary->xySet(m_Pos, background);

	m_pLibrary->DrawTexture(TEX_STAFF, background);
}
