#ifndef MAP_H
#define MAP_H

#define MAP_HEIGHT 60
#define MAP_WIDTH 70
#define MAP_DEFAULT_HEIGHT 0
#define MAP_DEFAULT_WIDTH 0
#define MAPTIP_DEFAULT_POSX 32
#define MAPTIP_DEFAULT_POSY 32
#define TOTAL_TEX_NUM 24
#define MAPTIP_SIZE 64

#define SCREEN_SIZEX 1280
#define SCREEN_SIZEY 1024

#define OBJECT_MAX 4
#define BACKGROUND_MAX 2
#define GIMMICK_MAX 2

#include"Vertex.h"


class Library;
class CollisionChecker;
class ServerMapObject;
class ServerMapGimmick;
class ServerMapBackGround;

enum MAP_ID
{
	MAP_OBJECT,
	MAP_GIMMICK,
	MAP_BACKGROUND,
	MAP_MAX
};


class ServerMap
{
private:
	Library*		m_pLibrary;
	ServerMapObject*		m_pMapObject;
	ServerMapGimmick*		m_pMapGimmick;
	ServerMapBackGround*	m_pMapBackGround;
	

public:
	ServerMap(Library* pLibrary);
	~ServerMap();
	int GimmickCheck(float x, float y);
	void SwitchOn(float x, float y);
	void SwitchOff(float x, float y);

	int ObjectCheck(float x, float y);
	int BackGroundCheck(float x, float y);
	bool WoodBoxCheck(float x, float y);
	bool WoodBoxSet(float x, float y);

	void Control();
	void Draw();
	bool StageInit(const char* Objname, const char* Gimmickname, const char* Backname);


	float	m_DrawPositionX;
	float	m_DrawPositionY;
};

#endif