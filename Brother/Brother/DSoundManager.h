#ifndef DSOUNDMANAGER_H
#define DSOUNDMANAGER_H



#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#include <map>


enum SOUND_OPERATION
{
	SOUND_PLAY,
	SOUND_STOP,
	SOUND_LOOP,
	SOUND_RESET,
	SOUND_STOP_RESET
};

class DSoundManager
{
private:
	IDirectSound8*						m_pDS8;
	std::map<int, LPDIRECTSOUNDBUFFER8> m_SoundMap;

	bool OpenWave(TCHAR *filename, WAVEFORMATEX &wFmt, char** pWaveData, DWORD &waveSize);

public:
	DSoundManager(HWND hWnd);
	~DSoundManager();
	int SoundLoad(char* filename, int Key);
	void ReleaseSound(int Key);
	void SoundOperation(int Key, SOUND_OPERATION operation);
	

};


#endif