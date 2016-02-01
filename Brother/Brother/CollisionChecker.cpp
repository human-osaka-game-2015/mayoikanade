#include "CollisionChecker.h"
#include "ServerGameScene.h"
#include "Map.h"



/**
 * CollisionChecker�N���X�̃R���X�g���N�^
 * @param[in] pMap �}�b�v�N���X�̃|�C���^
 */
CollisionChecker::CollisionChecker(Map* pMap):
m_pMap(pMap)
{
	
}


/**
 * CollisionChecker�N���X�̃f�X�g���N�^
 */
CollisionChecker::~CollisionChecker()
{

}


/**
 * Map�Ƃ̂����蔻����Ƃ�֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �������Ă����true���Ԃ�
 */
bool CollisionChecker::HitCheck(float x, float y)
{
	int Chip;

	Chip = m_pMap->GimmickCheck(x, y);
	switch (Chip)
	{
	case SWITCH_RED_01:
		break;
	case SWITCH_RED_02:
		break;
	case GATE_01:
		return true;
		break;
	case GATE_02:
		return true;
		break;
	case GATEPOST_01:
		return true;
		break;
	case GATEPOST_02:
		return true;
		break;
	case GATEPOST_PORTRAIT_01:
		return true;
		break;
	case GATEPOST_PORTRAIT_02:
		return true;
		break;
	case GATE_PORTRAIT_01:
		return true;
		break;
	case GATE_PORTRAIT_02:
		return true;
		break;
	case HOLE_01:
		return true;
		break;
	}


	Chip = m_pMap->ObjectCheck(x, y);
	switch (Chip)
	{
	case WOOD_01:
		return true;

		break;
	case WOOD_02:
		return true;

		break;
	case WOOD_03:
		return true;

		break;
	case WOOD_04:
		return true;

		break;
	case WOOD_YELLOW_01:
		return true;

		break;
	case WOOD_YELLOW_02:
		return true;

		break;
	case WOOD_YELLOW_03:
		return true;

		break;
	case WOOD_YELLOW_04:
		return true;

		break;
	case WOODBOX:
		return true;

		break;
	}

	return false;
}


/**
 * �ؔ������邩���`�F�b�N����֐�
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �ؔ��������true���Ԃ�
 */
bool CollisionChecker::WoodBoxCheck(float x, float y)
{
	return m_pMap->WoodBoxCheck(x, y);
}


/**
 * �ؔ����Z�b�g����֐�
 * @param[in] x �Z�b�g����x���W
 * @param[in] y �Z�b�g����y���W
 * @return �Z�b�g�ł�����true���Ԃ�
 */
bool CollisionChecker::WoodBoxSet(float x, float y)
{
	return m_pMap->WoodBoxSet(x, y);
}


/**
 * �X�C�b�`�������֐�(�Z���g��)
 * @param[in] x �X�C�b�`������x���W
 * @param[in] y �X�C�b�`������y���W
 * @return ���������true���Ԃ�
 */
void CollisionChecker::SwitchOn(float x, float y)
{
	m_pMap->SwitchOn(x, y);
}


/**
 * �X�C�b�`�������֐�(�킪�g��)
 * @param[in] x �X�C�b�`������x���W
 * @param[in] y �X�C�b�`������y���W
 * @return ���������true���Ԃ�
 */
void CollisionChecker::SwitchOnYoung(float x, float y)
{
	m_pMap->SwitchOnYoung(x, y);
}


/**
 * ������(������)�����邩�`�F�b�N����
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �������������Ԃ�
 */
bool CollisionChecker::GrassCheck(float x, float y)
{
	return m_pMap->GrassCheck(x, y);
}


/**
 * ������(�c����)�����邩�`�F�b�N����
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �������������Ԃ�
 */
bool CollisionChecker::GrassPortRaitCheck(float x, float y)
{
	return m_pMap->GrassPortRaitCheck(x, y);
}


/**
 * �����S�����邩���`�F�b�N����
 * @param[in] x �`�F�b�N����x���W
 * @param[in] y �`�F�b�N����y���W
 * @return �������������Ԃ�
 */
bool CollisionChecker::AppleCheck(float x, float y)
{
	return m_pMap->AppleCheck(x, y);
}
