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



void Vertex::Scaling(CustomVertex* pvertex, Position* Pos, float x, float y)
{
	pvertex[0].x = pvertex[0].x - ((Pos->w / 2) * x);
	pvertex[0].y = pvertex[0].y - ((Pos->h / 2) * y);
	pvertex[1].x = pvertex[1].x + ((Pos->w / 2) * x);
	pvertex[1].y = pvertex[1].y - ((Pos->h / 2) * y);
	pvertex[2].x = pvertex[2].x + ((Pos->w / 2) * x);
	pvertex[2].y = pvertex[2].y + ((Pos->h / 2) * y);
	pvertex[3].x = pvertex[3].x - ((Pos->w / 2) * x);
	pvertex[3].y = pvertex[3].y + ((Pos->h / 2) * y);

}



/**
* ��]�������摜��CustomVertex�̃A�h���X��n��
* ���x��]���邩�̒l��n���B
* ��]�͉E���ŁA�֐����Ń��W�A���ɕϊ����Ă���B
*
*/
void Vertex::Turn(CustomVertex* pvertex,Position* Pos, double angle)
{

	double rad;
	rad = angle * (3.141592 / 180);

	pvertex[0].x = float(-Pos->w * cos(rad) - -Pos->h * sin(rad));
	pvertex[0].y = float(-Pos->h * cos(rad) + -Pos->w * sin(rad));

	pvertex[1].x = float( Pos->w * cos(rad) - -Pos->h * sin(rad));
	pvertex[1].y = float(-Pos->h * cos(rad) +  Pos->w * sin(rad));

	pvertex[2].x = float( Pos->w * cos(rad) -  Pos->h * sin(rad));
	pvertex[2].y = float( Pos->h * cos(rad) +  Pos->w * sin(rad));

	pvertex[3].x = float(-Pos->w * cos(rad) -  Pos->h * sin(rad));
	pvertex[3].y = float( Pos->h * cos(rad) + -Pos->w * sin(rad));
}

void Vertex::xySet(Position pos, CustomVertex* pvertex)
{
	pvertex[0].x = pos.x - (pos.w / 2);
	pvertex[0].y = pos.y - (pos.h / 2);

	pvertex[1].x = pos.x + (pos.w / 2);
	pvertex[1].y = pos.y - (pos.h / 2);

	pvertex[2].x = pos.x + (pos.w / 2);
	pvertex[2].y = pos.y + (pos.h / 2);

	pvertex[3].x = pos.x - (pos.w / 2);
	pvertex[3].y = pos.y + (pos.h / 2);

}


//�e�N�X�`���̃Z�b�g
void Vertex::Set_Tex(LPDIRECT3DTEXTURE9 pTexture)
{
	//�摜�̕`��
	D3DManager::pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
	D3DManager::pD3Device->SetTexture(0, pTexture);
}


void Vertex::Draw_Tex(CustomVertex* pvertex)
{
	D3DManager::pD3Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pvertex,
		sizeof(CustomVertex));
}

void Vertex::Set_Draw_Tex(LPDIRECT3DTEXTURE9 pTexture, CustomVertex* pvertex)
{
	Set_Tex(pTexture);

	D3DManager::pD3Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pvertex,
		sizeof(CustomVertex));
}

