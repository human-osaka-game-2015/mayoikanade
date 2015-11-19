#ifndef _STAFFSCENE_H_
#define _STAFFSCENE_H_
#include "Scene.h"

class StaffBackGround;
class Library;
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;


enum STAFF_VERTEXINFO_ID
{
	STAFF,
	STAFF_VERTEXINFO_MAX
};

class StaffScene :public Scene
{
private:
	SCENE_NUM				m_NextScene;
	LPDIRECT3DTEXTURE9		m_pTexture;
	Library*				m_pLibrary;
	StaffBackGround*		m_pStaffBackGround;

public:
	StaffScene(Library* pLibrary);
	~StaffScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif