/**
 * @file Vertex.cpp
 * @brief Vertexクラス
 * @author 森本
 * @date 11月9日
 */

#include"D3DManager.h"
#include "Vertex.h"



/**
 * Vertexクラスのコンストラクタ
 */
Vertex::Vertex()
{
	
}

/**
 * Vertexクラスのデストラクタ
 */
Vertex::~Vertex()
{

}


/**
 * CustomVertexをスケーリングする関数
 * @param[out] pVertex スケーリングするCustomVertex
 * @param[in] Pos Position構造体
 * @param[in] x x方向の倍率
 * @param[in] y y方向の倍率
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
 * 頂点座標の回転関数
 * @param[out] pVertex 回転する頂点
 * @param[in] pos その頂点の位置
 * @param[in] angle 回転する角度
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
 * Position構造体からxy情報を取得してpVertexに出力する
 * @param[in] pos xy情報を取得するposition構造体
 * @param[out] pVertex xy情報を出力するCustomVertex
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
