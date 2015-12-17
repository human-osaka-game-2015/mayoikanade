#ifndef STAFFSCENE_H
#define STAFFSCENE_H

#include "Scene.h"

class StaffBackGround;
class Library;


enum STAFF_VERTEXINFO_ID
{
	STAFF,
	STAFF_VERTEXINFO_MAX
};

class StaffScene :public Scene
{
private:
	StaffBackGround*		m_pStaffBackGround;

public:
	StaffScene(Library* pLibrary);
	~StaffScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif