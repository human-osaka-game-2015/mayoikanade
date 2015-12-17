#ifndef TEXTURE_H
#define TEXTURE_H

#define COLORMAX 255
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <map>

class Texture
{
private:
	std::map<int, LPDIRECT3DTEXTURE9> m_textureMap;

public:
	Texture();
	~Texture();
	int Tex_Load(const char* name, LPDIRECT3DTEXTURE9* pTexture);
	int Tex_Load_EX(const char* name, LPDIRECT3DTEXTURE9* pTexture, int alpha, int red, int green, int blue);
	int LoadEx(const char* name, int key, int alpha, int red, int green, int blue);
	void Release(int key);
	void SetTexture(int key);

};

#endif