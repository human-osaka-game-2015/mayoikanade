#ifndef MAP_H
#define MAP_H
#include "Tex.h"
#define MAP_TOP	0						//マップの頭
#define MAP_LEFT 0						//マップの左端
#define MAP_HEIGHT 48					//マップの高さ
#define MAP_WIDTH 60					//マップの横幅
#define SCREEN_SIZEX 1280				//スクリーンの大きさX
#define SCREEN_SIZEY 1024				//スクリーンの大きさY

#define ARRAY_DEFAULT_INIT 0			//配列の要素数の初期値
//#define MAPVIEW

#define GIMMICK_DATA 10000				//ギミックの情報を抜き出すための値
#ifdef MAPVIEW
#define MAPCHIP_DEFAULT_POSX 8 			//
#define MAPCHIP_DEFAULT_POSY 8			//
#define MAPCHIP_SIZE 16				//

#else
#define MAPCHIP_DEFAULT_POSX 32			//
#define MAPCHIP_DEFAULT_POSY 32			//
#define MAPCHIP_SIZE 64				//

#endif

#include"Vertex.h"



class Library;
class CollisionChecker;
class MapObject;
class MapGimmick;
class MapBackGround;

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
	MapObject*		m_pMapObject;
	MapGimmick*		m_pMapGimmick;
	MapBackGround*	m_pMapBackGround;
	

public:
	Map(Library* pLibrary);
	~Map();
	int GimmickCheck(float x, float y);
	void SwitchOn(float x, float y);
	void SwitchOnYoung(float x, float y);
	void SwitchOff(float x, float y);

	int ObjectCheck(float x, float y);
	int BackGroundCheck(float x, float y);
	bool WoodBoxCheck(float x, float y);
	bool WoodBoxSet(float x, float y);
	bool ClearCheck(float x, float y);

	void Control();
	void Draw();
	bool StageInit(const char* Objname, const char* Gimmickname, const char* Backname);

	bool GrassPortRaitCheck(float x, float y);
	bool GrassCheck(float x, float y);

	bool AppleCheck(float x, float y);

	float	m_DrawPositionX;
	float	m_DrawPositionY;

	int m_mapstage;
	void MapChange(float* x, float* y);
	void MapStartPos(float* x, float* y);

};

#endif