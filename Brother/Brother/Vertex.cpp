/**
 * @file Vertex.cpp
 * @brief Vertexクラス
 * @author 森本
 * @date 11月9日
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
* 回転したい画像のCustomVertexのアドレスを渡す
* 何度回転するかの値を渡す。
* 回転は右回りで、関数内でラジアンに変換している。
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


//テクスチャのセット
void Vertex::Set_Tex(LPDIRECT3DTEXTURE9 pTexture)
{
	//画像の描画
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

