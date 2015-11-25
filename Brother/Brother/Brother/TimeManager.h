#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H


class TimeManager
{
private:
	unsigned int GameTime;

public:
	TimeManager();
	~TimeManager();
	void Control();
	inline int GetGameTime(){ return GameTime; }
};


#endif