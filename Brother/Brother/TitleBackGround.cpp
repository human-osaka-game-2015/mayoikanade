#include "TitleBackGround.h"
#include "TitleScene.h"


/**
 * TitleBackGround�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X
 */
TitleBackGround::TitleBackGround(Library* pLibrary) :
m_pLibrary(pLibrary)
{
	//�����ɗ���悤�ɏ����l�ݒ�
	m_Pos.x = TITLEBACKGROUNDPOS_X;
	m_Pos.y = TITLEBACKGROUNDPOS_Y;
}

/**
 * TitleBackGround�N���X�̃f�X�g���N�^
 */
TitleBackGround::~TitleBackGround()
{

}

/**
 * TitleBackGround�̕`��֐�
 */
void TitleBackGround::Draw()
{
	CustomVertex background[SQUARE_VERTEX];

	m_pLibrary->MakePosition(TITLE_BACKGROUND, &m_Pos);

	m_pLibrary->MakeVertex(TITLE_BACKGROUND, background);
	m_pLibrary->xySet(m_Pos, background);

	m_pLibrary->DrawTexture(TEX_TITLE, background);
}