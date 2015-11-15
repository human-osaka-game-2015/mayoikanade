#ifndef _DSOUNDMANAGER_H_
#define _DSOUNDMANAGER_H_
#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#pragma comment(lib,"dsound.lib")



enum SOUND_OPERATION
{
	PLAY,
	STOP,
	LOOP,
	RESET,
	STOP_RESET
};

class DSoundManager
{
private:
	IDirectSound8*	m_pDS8;
	bool Open_Wave(TCHAR *filename, WAVEFORMATEX &wFmt, char** pWaveData, DWORD &waveSize);

public:
	DSoundManager(HWND hWnd);
	~DSoundManager();
	int Set_Sound(char* filename, LPDIRECTSOUNDBUFFER8* ppDSBuffer);
	void Sound_Operation(LPDIRECTSOUNDBUFFER8* pDSBuffer, SOUND_OPERATION operation);

};


#endif