#include "DrawPositionSetter.h"
#include "Map.h"


/**
 * DrawPositionSetter�N���X�̃R���X�g���N�^
 * param[in] pMap
 */
DrawPositionSetter::DrawPositionSetter(Map* pMap) :
m_pMap(pMap)
{

}

/**
 * DrawPositionSetter�N���X�̃f�X�g���N�^
 */
DrawPositionSetter::~DrawPositionSetter()
{

}

/**
 * X���W�̕`��ʒu���Z�b�g����֐�
 * @param[in] x �Z�b�g������W
 */
void DrawPositionSetter::DrawPositionXSet(float x)
{
	m_pMap->m_DrawPositionX = x;
}

/**
 * Y���W�̕`��ʒu���Z�b�g����֐�
 * @param[in] y �Z�b�g������W
 */
void DrawPositionSetter::DrawPositionYSet(float y)
{
	m_pMap->m_DrawPositionY= y;
}