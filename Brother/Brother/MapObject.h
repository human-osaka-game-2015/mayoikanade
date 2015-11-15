#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_
class Library;

enum OBJECT_ID
{
	WOOD_01 = 19,
	WOOD_02,
	WOOD_03,
	WOOD_04,
	OBJECT_MAX
};

class MapObject
{
private:
	Library*	m_pLibrary;

public:
	MapObject(Library* pLibrary);
	~MapObject();
	void Control();
	void Draw();

};

#endif