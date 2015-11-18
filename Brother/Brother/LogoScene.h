#ifndef _LOGOSCENE_H_
#define _LOGOSCENE_H_
#include"Scene.h"
class Library;
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;
class LogoBackGround;

enum LOGO_VERTEXINFO_ID
{
	TEAMLOGO,
	LOGO_VERTEXINFO_MAX
};

class LogoScene:public Scene
{
private:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;
	LPDIRECT3DTEXTURE9		m_pTexture;
	LogoBackGround*			m_pLogoBackGround;

public:
	LogoScene(Library* pLibrary);
	~LogoScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};


#endif