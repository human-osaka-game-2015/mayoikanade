#include "TitleName.h"
#include "TitleScene.h"


/**
 * TitleTimeManager�N���X�̃R���X�g���N�^
 * param[in] pLibrary ���C�u�����N���X
 */
TitleName::TitleName(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//�����ɗ���悤�ɏ����l�ݒ�
	m_Pos.x = TITLENAMEPOS_X;
	m_Pos.y = TITLENAMEPOS_Y;
}


/**
 * TitleName�N���X�̃f�X�g���N�^
 */
TitleName::~TitleName()
{

}

/**
 * TitleName�̃R���g���[���֐�
 */
void TitleName::Control()
{

}

/**
 * TitleName�̕`��֐�
 */
void TitleName::Draw()
{
	CustomVertex titlename[SQUARE_VERTEX];

	m_pLibrary->MakePosition(TITLE_NAME, &m_Pos);

	m_pLibrary->MakeVertex(TITLE_NAME, titlename);
	m_pLibrary->xySet(m_Pos, titlename);

	m_pLibrary->DrawTexture(TEX_TITLE, titlename);
}
