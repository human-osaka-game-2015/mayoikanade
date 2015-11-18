#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_
class Library;



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