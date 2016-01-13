#ifndef TEXTURE_H
#define TEXTURE_H

#define COLORMAX 255
#define COLORMIN 0

#include <d3dx9.h>
#include <d3dx9tex.h>
#include <map>


typedef struct _CustomVertex_ CustomVertex, *PCutomVertex;;

class Texture
{
private:
	std::map<int, LPDIRECT3DTEXTURE9> m_textureMap;

public:
	Texture();
	~Texture();
	int LoadTexture(const char* name, int key);
	int LoadTextureEx(const char* name, int key, int alpha, int red, int green, int blue);
	void ReleaseTexture(int key);
	void SetTexture(int key);
	void DrawTexture(int key, CustomVertex* pVertex);


};

#endif