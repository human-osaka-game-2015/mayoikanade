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

	//バックグラウンドはチェックしない


	Chip = m_pMap->GimmickCheck(x, y);
	switch (Chip)
	{
	case SWITCH_01:
		//スイッチ処理とか

		break;
	case SWITCH_02:
		//押されてるスイッチなので何も処理しないとか

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
