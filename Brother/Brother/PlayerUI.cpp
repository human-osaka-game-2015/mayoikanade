#include "PlayerUI.h"
#include "Library.h"
#include "GameScene.h"


PlayerUI::PlayerUI(Library* pLibrary, const int& Hp, int frameTexId, int barTexId, float x, float y)
	:m_pLibrary(pLibrary), m_PlayerHp(Hp), m_FrameTexId(frameTexId), m_BarTexId(barTexId)
{
	m_FrameUiPos.x = x;
	m_FrameUiPos.y = y;

	m_BarUiPos.x = x;
	m_BarUiPos.y = y;
}

PlayerUI::~PlayerUI()
{
	
}

void PlayerUI::Control()
{

}

void PlayerUI::Draw()
{
	int Damage = int(240 - (m_PlayerHp * 2.4));
	CustomVertex frameUi[4];
	CustomVertex barUi[4];

	//�̗̓o�[�̍��W�ݒ�
	m_pLibrary->MakePosition(m_BarTexId, &m_BarUiPos);
	m_pLibrary->MakeVertex(m_BarTexId, barUi);
	m_pLibrary->xySet(m_BarUiPos, barUi);

	//�t���[���̍��W�ݒ�
	m_pLibrary->MakePosition(m_FrameTexId, &m_FrameUiPos);
	m_pLibrary->MakeVertex(m_FrameTexId, frameUi);
	m_pLibrary->xySet(m_FrameUiPos, frameUi);

	
	//�̗͂̌������o�[��Z������
	barUi[1].x -= Damage;
	barUi[2].x -= Damage;


	//���C�t�o�[�ƃt���[���̕`��
	m_pLibrary->DrawTexture(TEX_GAME, frameUi);
	m_pLibrary->DrawTexture(TEX_GAME, barUi);

}
