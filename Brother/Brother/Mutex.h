
#ifndef MUTEX_H
#define MUTEX_H
#include <windows.h>
class Mutex
{
public:
	Mutex(char* Object);
	~Mutex();
	void WaitMutex();
	void MutexRelease();
	void GetMutexHwnd();
private:
	char* m_ObjectName;
	HANDLE m_MutexHandle;
};
#endif

