#include "DrawPositionSetter.h"
#include "Map.h"


/**
 * DrawPositionSetterクラスのコンストラクタ
 * param[in] pMap
 */
DrawPositionSetter::DrawPositionSetter(Map* pMap) :
m_pMap(pMap)
{

}

/**
 * DrawPositionSetterクラスのデストラクタ
 */
DrawPositionSetter::~DrawPositionSetter()
{

}

/**
 * X座標の描画位置をセットする関数
 * @param[in] x セットする座標
 */
void DrawPositionSetter::DrawPositionXSet(float x)
{
	m_pMap->m_DrawPositionX = x;
}

/**
 * Y座標の描画位置をセットする関数
 * @param[in] y セットする座標
 */
void DrawPositionSetter::DrawPositionYSet(float y)
{
	m_pMap->m_DrawPositionY= y;
}