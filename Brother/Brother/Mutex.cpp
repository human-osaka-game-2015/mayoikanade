#include "Mutex.h"

Mutex::Mutex(char* Object)
{
	m_ObjectName = Object;
}

Mutex::~Mutex()
{
	CloseHandle(m_MutexHandle);
}

void Mutex::GetMutexHwnd()
{
	CreateMutex(NULL, FALSE, m_ObjectName);
	m_MutexHandle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, m_ObjectName);
}

void Mutex::WaitMutex()
{
	WaitForSingleObject(m_MutexHandle, INFINITE);
}

void Mutex::MutexRelease()
{
	ReleaseMutex(m_MutexHandle);
}