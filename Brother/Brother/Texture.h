#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <d3dx9.h>
#include <d3dx9tex.h>



class Texture
{
private:

public:
	Texture();
	~Texture();
	int Tex_Load(const char* name, LPDIRECT3DTEXTURE9* pTexture);
	int Tex_Load_EX(const char* name, LPDIRECT3DTEXTURE9* pTexture, int alpha, int red, int grren, int blue);

};

#endif