#ifndef _CUSTOMVERTEX_H_
#define _CUSTOMVERTEX_H_
#include <d3dx9.h>
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)



typedef struct _Position_
{
	float x;
	float y;
	float w;
	float h;
} Position, *PPosition;


typedef struct _CustomVertex_
{
	float      x, y, z;
	float      rhw;
	D3DCOLOR   color;
	float      tu, tv;
} CustomVertex, *PCutomVertex;


class Vertex
{
private:

public:
	Vertex();
	~Vertex();
	void Turn(CustomVertex* pvertex, Position* Pos, double angle);
	void Scaling(CustomVertex* pvertex, Position* Pos, float x, float y);
	void xySet(Position pos, CustomVertex* pvertex);
	void Set_Tex(LPDIRECT3DTEXTURE9 pvertex);
	void Draw_Tex(CustomVertex* pvertex);
	void Set_Draw_Tex(LPDIRECT3DTEXTURE9 pTexture, CustomVertex* pvertex);

};



#endif