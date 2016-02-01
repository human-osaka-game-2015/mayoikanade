/**
 * @file Vertex.cpp
 * @brief Vertex�N���X
 * @author �X�{
 * @date 11��9��
 */

#include"D3DManager.h"
#include "Vertex.h"



/**
 * Vertex�N���X�̃R���X�g���N�^
 */
Vertex::Vertex()
{
	
}

/**
 * Vertex�N���X�̃f�X�g���N�^
 */
Vertex::~Vertex()
{

}


/**
 * CustomVertex���X�P�[�����O����֐�
 * @param[out] pVertex �X�P�[�����O����CustomVertex
 * @param[in] Pos Position�\����
 * @param[in] x x�����̔{��
 * @param[in] y y�����̔{��
 */
void Vertex::Scaling(CustomVertex* pVertex, Position* Pos, float x, float y)
{
	pVertex[0].x = pVertex[0].x - ((Pos->w / 2) * x);
	pVertex[0].y = pVertex[0].y - ((Pos->h / 2) * y);
	pVertex[1].x = pVertex[1].x + ((Pos->w / 2) * x);
	pVertex[1].y = pVertex[1].y - ((Pos->h / 2) * y);
	pVertex[2].x = pVertex[2].x + ((Pos->w / 2) * x);
	pVertex[2].y = pVertex[2].y + ((Pos->h / 2) * y);
	pVertex[3].x = pVertex[3].x - ((Pos->w / 2) * x);
	pVertex[3].y = pVertex[3].y + ((Pos->h / 2) * y);

}



/**
 * ���_���W�̉�]�֐�
 * @param[out] pVertex ��]���钸�_
 * @param[in] pos ���̒��_�̈ʒu
 * @param[in] angle ��]����p�x
 */
void Vertex::Turn(CustomVertex* pVertex,Position* Pos, double angle)
{

	double rad;
	rad = angle * (3.141592 / 180);

	pVertex[0].x = float((-Pos->w / 2) * cos(rad) - (-Pos->h / 2) * sin(rad));
	pVertex[0].y = float((-Pos->h / 2) * cos(rad) + (-Pos->w / 2) * sin(rad));

	pVertex[1].x = float((Pos->w / 2) * cos(rad) - (-Pos->h / 2) * sin(rad));
	pVertex[1].y = float((-Pos->h / 2) * cos(rad) + (Pos->w / 2) * sin(rad));

	pVertex[2].x = float((Pos->w / 2) * cos(rad) - (Pos->h / 2) * sin(rad));
	pVertex[2].y = float((Pos->h / 2) * cos(rad) + (Pos->w / 2) * sin(rad));

	pVertex[3].x = float((-Pos->w / 2) * cos(rad) - (Pos->h / 2) * sin(rad));
	pVertex[3].y = float((Pos->h / 2) * cos(rad) + (-Pos->w / 2) * sin(rad));


	pVertex[0].x += Pos->x;
	pVertex[0].y += Pos->y;

	pVertex[1].x += Pos->x;
	pVertex[1].y += Pos->y;

	pVertex[2].x += Pos->x;
	pVertex[2].y += Pos->y;

	pVertex[3].x += Pos->x;
	pVertex[3].y += Pos->y;


}


/**
 * Position�\���̂���xy�����擾����pVertex�ɏo�͂���
 * @param[in] pos xy�����擾����position�\����
 * @param[out] pVertex xy�����o�͂���CustomVertex
 */
void Vertex::xySet(Position pos, CustomVertex* pVertex)
{
	pVertex[0].x = pos.x - (pos.w / 2);
	pVertex[0].y = pos.y - (pos.h / 2);

	pVertex[1].x = pos.x + (pos.w / 2);
	pVertex[1].y = pos.y - (pos.h / 2);

	pVertex[2].x = pos.x + (pos.w / 2);
	pVertex[2].y = pos.y + (pos.h / 2);

	pVertex[3].x = pos.x - (pos.w / 2);
	pVertex[3].y = pos.y + (pos.h / 2);

}
