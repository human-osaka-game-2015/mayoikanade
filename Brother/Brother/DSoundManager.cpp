/**
 * @file DSoundManager.cpp
 * @brief DSoundManagerクラス
 * @author 森本
 * @date 11月9日
 */

#include "DSoundManager.h"



/**
 * DSoundManagerクラスのコンストラクタ
 * @param[in] hWnd ウィンドウハンドル
 */
DSoundManager::DSoundManager(HWND hWnd)
{
	// サウンドデバイス作成
	if (FAILED(DirectSoundCreate8(NULL, &m_pDS8, NULL)))
	{
		MessageBox(0, "サウンドデバイスの生成に失敗しました", "DSoundManager.cpp", MB_OK);
	}
	
	if (FAILED(m_pDS8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		MessageBox(0, "協調レベルの設定に失敗しました", "DSoundManager.cpp", MB_OK);
	}
}

/**
 * DSoundManagerクラスのデストラクタ
 */
DSoundManager::~DSoundManager()
{
	m_pDS8->Release();
}


/**
 * Wavファイルのを開いて情報を取得する関数
 * @param[in] filename 読み込むファイル名
 * @param[in] wFmt フォーマット
 * @param[in] pWaveData 音声データ
 * @param[in] waveSize 音声のサイズ
 * @return wavファイルのオープンに成功したか(成功したらtrue)
 */
bool DSoundManager::OpenWave(TCHAR *filename, WAVEFORMATEX &wFmt, char** pWaveData, DWORD &waveSize)
{
	//filepathの位置になにもなければ失敗なのでfalseを返す
	if (filename == NULL)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Waveファイルオープン
	ZeroMemory(&mmioInfo, sizeof(MMIOINFO));
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



/**
 * 音声の読み込み
 * @param[in] filename 読み込むファイルの名前
 * @param[in] Key 格納先のキー
 */
int DSoundManager::SoundLoad(char* filename, int Key)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	// Waveファイルオープン
	WAVEFORMATEX wFmt;
	char *pWaveData = 0;
	DWORD waveSize = 0;

	if (!OpenWave((filename), wFmt, &pWaveData, waveSize))
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
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);

	ptmpBuf->Release();
	if (pDSBuffer == NULL)
	{
		m_pDS8->Release();
		return 0;
	}


	// セカンダリバッファにWaveデータ書き込み
	//音声データ
	LPVOID lpvWrite = 0;
	//音声データの大きさ
	DWORD dwLength = 0;
	if (DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	delete[] pWaveData; // 元音はもういらない


	m_SoundMap[Key] = pDSBuffer;

	return 0;
}

/**
 * 音声の解放関数
 */
void DSoundManager::ReleaseSound(int Key)
{
	m_SoundMap[Key]->Release();
}


/**
 * サウンドの操作関数 
 * @param[in] Key 操作するサウンドの格納先のキー
 * @param[in] operation どのような操作をするか
 */
void DSoundManager::SoundOperation(int Key, SOUND_OPERATION operation)
{

	switch (operation)
	{
	case SOUND_PLAY:
		m_SoundMap[Key]->Play(0, 0, 0);
		break;
	case SOUND_LOOP:
		m_SoundMap[Key]->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case SOUND_STOP:
		m_SoundMap[Key]->Stop();
		break;
	case SOUND_RESET:
		m_SoundMap[Key]->SetCurrentPosition(0);
		break;
	case SOUND_STOP_RESET:
		m_SoundMap[Key]->Stop();
		m_SoundMap[Key]->SetCurrentPosition(0);
		break;
	}
}

