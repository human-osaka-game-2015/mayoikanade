#include "CollisionChecker.h"
#include "GameScene.h"
#include "Map.h"

CollisionChecker::CollisionChecker(Map* pMap)
{
	m_pMap = pMap;
}

CollisionChecker::~CollisionChecker()
{

}

bool CollisionChecker::HitCheck(float x,float y)
{
	int Chip;

	//�o�b�N�O���E���h�̓`�F�b�N���Ȃ�


	Chip = m_pMap->GimmickCheck(x, y);
	switch (Chip)
	{
	case SWITCH_01:
		//�X�C�b�`�����Ƃ�

		break;
	case SWITCH_02:
		//������Ă�X�C�b�`�Ȃ̂ŉ����������Ȃ��Ƃ�

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
	}

	return false;
}
