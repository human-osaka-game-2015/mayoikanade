#ifndef MAPGIMMICK_H
#define MAPGIMMICK_H

class Library;

class MapGimmick
{
private:
	Library*	m_pLibrary;

public:
	MapGimmick(Library* pLibrary);
	~MapGimmick();
	void Control();
	void Draw();

};

#endif