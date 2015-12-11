/**
 * @file Vertex.cpp
 * @brief Vertex�N���X
 * @author �X�{
 * @date 11��9��
 */

#include"D3DManager.h"
#include "Vertex.h"




Vertex::Vertex()
{
	
}

Vertex::~Vertex()
{

}



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
* ��]�������摜��CustomVertex�̃A�h���X��n��
* ���x��]���邩�̒l��n���B
* ��]�͉E���ŁA�֐����Ń��W�A���ɕϊ����Ă���B
*
*/
void Vertex::Turn(CustomVertex* pVertex,Position* Pos, double angle)
{

	double rad;
	rad = angle * (3.141592 / 180);

	pVertex[0].x = float(-Pos->w * cos(rad) - -Pos->h * sin(rad));
	pVertex[0].y = float(-Pos->h * cos(rad) + -Pos->w * sin(rad));

	pVertex[1].x = float( Pos->w * cos(rad) - -Pos->h * sin(rad));
	pVertex[1].y = float(-Pos->h * cos(rad) +  Pos->w * sin(rad));

	pVertex[2].x = float( Pos->w * cos(rad) -  Pos->h * sin(rad));
	pVertex[2].y = float( Pos->h * cos(rad) +  Pos->w * sin(rad));

	pVertex[3].x = float(-Pos->w * cos(rad) -  Pos->h * sin(rad));
	pVertex[3].y = float( Pos->h * cos(rad) + -Pos->w * sin(rad));
}

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