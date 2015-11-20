#ifndef PLAYER_H
#define PLAYER_H

class Library;

enum PLAYER_DIRECTION
{
	PLAYER_BACK,
	PLAYER_FRONT,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_MAX
};

class Player
{
private:

protected:
	Library* m_pLibrary;

public:
	Player(Library* pLibrary);
	virtual ~Player();
	virtual void Control() = 0;
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual void Init() = 0;
	PLAYER_DIRECTION m_Direction;

};

#endif