#include "ClientCollisionChecker.h"
#include "ClientGameScene.h"
#include "ClientMap.h"

ClientCollisionChecker::ClientCollisionChecker(ClientMap* pMap)
{
	m_pMap = pMap;
}

ClientCollisionChecker::~ClientCollisionChecker()
{

}


//ƒLƒƒƒ‰ˆÈŠO‚Ì‚ ‚½‚è”»’è‚É‚ÍŽg‚¦‚È‚­‚È‚Á‚Ä‚¢‚é
bool ClientCollisionChecker::HitCheck(float x, float y)
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


bool ClientCollisionChecker::WoodBoxCheck(float x, float y)
{
	return m_pMap->WoodBoxCheck(x, y);
}


bool ClientCollisionChecker::WoodBoxSet(float x, float y)
{
	return m_pMap->WoodBoxSet(x, y);
}


void ClientCollisionChecker::SwitchOn(float x, float y)
{
	m_pMap->SwitchOn(x, y);
}


void ClientCollisionChecker::SwitchOnYoung(float x, float y)
{
	m_pMap->SwitchOnYoung(x, y);
}


bool ClientCollisionChecker::GrassCheck(float x, float y)
{
	return m_pMap->GrassCheck(x, y);
}


bool ClientCollisionChecker::GrassPortRaitCheck(float x, float y)
{
	return m_pMap->GrassPortRaitCheck(x, y);
}


bool ClientCollisionChecker::AppleCheck(float x, float y)
{
	return m_pMap->AppleCheck(x, y);
}