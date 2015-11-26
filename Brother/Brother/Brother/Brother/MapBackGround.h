#ifndef MAPBACKGROUND_H
#define MAPBACKGROUND_H

class Library;



class MapBackGround
{
private:
	Library*	m_pLibrary;

public:
	MapBackGround(Library* pLibrary);
	~MapBackGround();
	void Draw();

};


#endif