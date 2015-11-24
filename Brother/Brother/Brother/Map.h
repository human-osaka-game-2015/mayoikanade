#ifndef MAP_H
#define MAP_H

#define MAP_HEIGHT 16
#define MAP_WIDTH 20
#define MAP_DEFAULT_HEIGHT 0
#define MAP_DEFAULT_WIDTH 0
#define MAPTIP_DEFAULT_POSX 32
#define MAPTIP_DEFAULT_POSY 32
#define TOTAL_TEX_NUM 24
#define MAPTIP_SIZE 64

#define OBJECT_MAX 4
#define BACKGROUND_MAX 2
#define GIMMICK_MAX 2

#include"Vertex.h"
#include "MapObject.h"
#include "MapGimmick.h"
#include "MapBackGround.h"


class Library;
class CollisionChecker;

enum MAP_ID
{
	MAP_OBJECT,
	MAP_GIMMICK,
	MAP_BACKGROUND,
	MAP_MAX
};


class Map
{
private:
	
	Library*		m_pLibrary;
	int				m_GimmickData[MAP_HEIGHT][MAP_WIDTH];
	int				m_ObjectData[MAP_HEIGHT][MAP_WIDTH];
	int				m_BackGroundData[MAP_HEIGHT][MAP_WIDTH];
	MapObject*		m_pMapObject[OBJECT_MAX];
	MapGimmick*		m_pMapGimmick[GIMMICK_MAX];
	MapBackGround*	m_pMapBackGround[BACKGROUND_MAX];
	
	Position		m_MapBackGround_Pos [MAP_HEIGHT][MAP_WIDTH];
	Position		m_MapObject_Pos[MAP_HEIGHT][MAP_WIDTH];
	
	CustomVertex	m_MapObject_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	CustomVertex	m_MapBackGround_Tex[MAP_HEIGHT][MAP_WIDTH][4];

	bool CsvRead(const char* filename,MAP_ID MapId);
	

	//ÉøÉvÉåÉ[ÉìópÅ@è¨íJ
	void MapTex_UV_Set(MAP_ID MapId);
	void MapTex_XY_Set();

public:
	Map(Library* pLibrary);
	~Map();
	int GimmickCheck(float x, float y);
	int ObjectCheck(float x, float y);
	int BackGroundCheck(float x, float y);
	void Control();
	void Draw();
	bool StageInit(const char* Objname, const char* Gimmickname, const char* Backname);


	int	m_DrawPositionX;
	int	m_DrawPositionY;
};

#endif