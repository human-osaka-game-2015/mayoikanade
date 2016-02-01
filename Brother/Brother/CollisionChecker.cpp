#include "CollisionChecker.h"
#include "ServerGameScene.h"
#include "Map.h"



/**
 * CollisionCheckerクラスのコンストラクタ
 * @param[in] pMap マップクラスのポインタ
 */
CollisionChecker::CollisionChecker(Map* pMap):
m_pMap(pMap)
{
	
}


/**
 * CollisionCheckerクラスのデストラクタ
 */
CollisionChecker::~CollisionChecker()
{

}


/**
 * Mapとのあたり判定をとる関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 当たっていればtrueが返る
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
 * 木箱があるかをチェックする関数
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 木箱があればtrueが返る
 */
bool CollisionChecker::WoodBoxCheck(float x, float y)
{
	return m_pMap->WoodBoxCheck(x, y);
}


/**
 * 木箱をセットする関数
 * @param[in] x セットするx座標
 * @param[in] y セットするy座標
 * @return セットできたらtrueが返る
 */
bool CollisionChecker::WoodBoxSet(float x, float y)
{
	return m_pMap->WoodBoxSet(x, y);
}


/**
 * スイッチを押す関数(兄が使う)
 * @param[in] x スイッチを押すx座標
 * @param[in] y スイッチを押すy座標
 * @return 成功すればtrueが返る
 */
void CollisionChecker::SwitchOn(float x, float y)
{
	m_pMap->SwitchOn(x, y);
}


/**
 * スイッチを押す関数(弟が使う)
 * @param[in] x スイッチを押すx座標
 * @param[in] y スイッチを押すy座標
 * @return 成功すればtrueが返る
 */
void CollisionChecker::SwitchOnYoung(float x, float y)
{
	m_pMap->SwitchOnYoung(x, y);
}


/**
 * 草結び(横向き)があるかチェックする
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 成功したかが返る
 */
bool CollisionChecker::GrassCheck(float x, float y)
{
	return m_pMap->GrassCheck(x, y);
}


/**
 * 草結び(縦向き)があるかチェックする
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 成功したかが返る
 */
bool CollisionChecker::GrassPortRaitCheck(float x, float y)
{
	return m_pMap->GrassPortRaitCheck(x, y);
}


/**
 * リンゴがあるかをチェックする
 * @param[in] x チェックするx座標
 * @param[in] y チェックするy座標
 * @return 成功したかが返る
 */
bool CollisionChecker::AppleCheck(float x, float y)
{
	return m_pMap->AppleCheck(x, y);
}
