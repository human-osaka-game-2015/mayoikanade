#ifndef MAPOBJECT_H
#define MAPOBJECT_H

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