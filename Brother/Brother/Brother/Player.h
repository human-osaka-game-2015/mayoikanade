#ifndef PLAYER_H
#define PLAYER_H

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

public:
	Player();
	virtual ~Player();
	virtual void Control() = 0;
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual void Init() = 0;
	PLAYER_DIRECTION m_Direction;

};

#endif