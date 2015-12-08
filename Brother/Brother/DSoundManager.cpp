/**
 * @file DSoundManager.cpp
 * @brief DSoundManagerクラス
 * @author 森本
 * @date 11月9日
 */

#include "DSoundManager.h"



//サウンドデバイスの生成
DSoundManager::DSoundManager(HWND hWnd)
{
	// サウンドデバイス作成
	if (FAILED(DirectSoundCreate8(NULL, &m_pDS8, NULL)))
	{
		MessageBox(0, "サウンドデバイスの生成に失敗しました", "", MB_OK);
	}
	
	if (FAILED(m_pDS8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		MessageBox(0, "協調レベルの設定に失敗しました", "", MB_OK);
	}
}

DSoundManager::~DSoundManager()
{
	m_pDS8->Release();
}


//waveファイルをバッファにロードする
int DSoundManager::Set_Sound(char* filename, LPDIRECTSOUNDBUFFER8* ppDSBuffer)
{
	// Waveファイルオープン
	WAVEFORMATEX wFmt;
	char *pWaveData = 0;
	DWORD waveSize = 0;

	if (!Open_Wave((filename), wFmt, &pWaveData, waveSize))
	{
		return 0;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = 0;
	DSBufferDesc.dwBufferBytes = waveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &wFmt;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer *ptmpBuf = 0;
	m_pDS8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)ppDSBuffer);

	ptmpBuf->Release();
	if (ppDSBuffer == NULL)
	{
		m_pDS8->Release();
		return 0;
	}


	// セカンダリバッファにWaveデータ書き込み
	//音声データ
	LPVOID lpvWrite = 0;
	//音声データの大きさ
	DWORD dwLength = 0;
	if (DS_OK == (*ppDSBuffer)->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		(*ppDSBuffer)->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	delete[] pWaveData; // 元音はもういらない

	return 0;
}


//サウンドバッファの操作
void DSoundManager::Sound_Operation(LPDIRECTSOUNDBUFFER8* pDSBuffer, SOUND_OPERATION operation)
{

	switch (operation)
	{
	case PLAY:
		(*pDSBuffer)->Play(0, 0, 0);
		break;
	case LOOP:
		(*pDSBuffer)->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case STOP:
		(*pDSBuffer)->Stop();
		break;
	case RESET:
		(*pDSBuffer)->SetCurrentPosition(0);
		break;
	case STOP_RESET:
		(*pDSBuffer)->Stop();
		(*pDSBuffer)->SetCurrentPosition(0);
		break;
	}
}


// Waveファイルオープン関数
bool DSoundManager::Open_Wave(TCHAR *filename, WAVEFORMATEX &wFmt, char** pWaveData, DWORD &waveSize)
{
	//filepathの位置になにもなければ失敗なのでfalseを返す
	if (filename == 0)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Waveファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));				//使わないので0をセット
	hMmio = mmioOpen(filename, &mmioInfo, MMIO_READ);
	if (!hMmio)
	{
		return false; // ファイルオープン失敗
	}


	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}


	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}


	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)&wFmt, fmsize);
	if (size != fmsize)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);


	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}


	*pWaveData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*pWaveData, dataChunk.cksize);
	if (size != dataChunk.cksize)
	{
		delete[] * pWaveData;
		return false;
	}

	waveSize = size;

	// ハンドルクローズ
	mmioClose(hMmio, 0);

	return true;
}