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


//ƒLƒƒƒ‰ˆÈŠO‚Ì‚ ‚½‚è”»’è‚É‚ÍŽg‚¦‚È‚­‚È‚Á‚Ä‚¢‚é
bool CollisionChecker::HitCheck(float x,float y)
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
	case WOODBOX:
		return true;

		break;
	}

	return false;
}


bool CollisionChecker::WoodBoxCheck(float x,float y)
{
	return m_pMap->WoodBoxCheck(x, y);
}

bool CollisionChecker::WoodBoxSet(float x, float y)
{
	return m_pMap->WoodBoxSet(x, y);
}

void CollisionChecker::SwitchOn(float x, float y)
{
	m_pMap->SwitchOn(x, y);
}

