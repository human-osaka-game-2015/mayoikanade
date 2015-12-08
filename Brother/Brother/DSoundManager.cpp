/**
 * @file DSoundManager.cpp
 * @brief DSoundManager�N���X
 * @author �X�{
 * @date 11��9��
 */

#include "DSoundManager.h"



//�T�E���h�f�o�C�X�̐���
DSoundManager::DSoundManager(HWND hWnd)
{
	// �T�E���h�f�o�C�X�쐬
	if (FAILED(DirectSoundCreate8(NULL, &m_pDS8, NULL)))
	{
		MessageBox(0, "�T�E���h�f�o�C�X�̐����Ɏ��s���܂���", "", MB_OK);
	}
	
	if (FAILED(m_pDS8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		MessageBox(0, "�������x���̐ݒ�Ɏ��s���܂���", "", MB_OK);
	}
}

DSoundManager::~DSoundManager()
{
	m_pDS8->Release();
}


//wave�t�@�C�����o�b�t�@�Ƀ��[�h����
int DSoundManager::Set_Sound(char* filename, LPDIRECTSOUNDBUFFER8* ppDSBuffer)
{
	// Wave�t�@�C���I�[�v��
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


	// �Z�J���_���o�b�t�@��Wave�f�[�^��������
	//�����f�[�^
	LPVOID lpvWrite = 0;
	//�����f�[�^�̑傫��
	DWORD dwLength = 0;
	if (DS_OK == (*ppDSBuffer)->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		(*ppDSBuffer)->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	delete[] pWaveData; // �����͂�������Ȃ�

	return 0;
}


//�T�E���h�o�b�t�@�̑���
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


// Wave�t�@�C���I�[�v���֐�
bool DSoundManager::Open_Wave(TCHAR *filename, WAVEFORMATEX &wFmt, char** pWaveData, DWORD &waveSize)
{
	//filepath�̈ʒu�ɂȂɂ��Ȃ���Ύ��s�Ȃ̂�false��Ԃ�
	if (filename == 0)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Wave�t�@�C���I�[�v��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));				//�g��Ȃ��̂�0���Z�b�g
	hMmio = mmioOpen(filename, &mmioInfo, MMIO_READ);
	if (!hMmio)
	{
		return false; // �t�@�C���I�[�v�����s
	}


	// RIFF�`�����N����
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}


	// �t�H�[�}�b�g�`�����N����
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


	// �f�[�^�`�����N����
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

	// �n���h���N���[�Y
	mmioClose(hMmio, 0);

	return true;
}