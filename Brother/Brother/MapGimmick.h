#ifndef _MAPGIMMICK_H_
#define _MAPGIMMICK_H_
class Library;

enum GIMMICK_ID
{
	SWITCH_01,
	SWITCH_02,
	GIMMICK_MAX
};

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