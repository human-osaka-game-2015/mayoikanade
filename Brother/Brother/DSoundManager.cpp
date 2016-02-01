/**
 * @file DSoundManager.cpp
 * @brief DSoundManager�N���X
 * @author �X�{
 * @date 11��9��
 */

#include "DSoundManager.h"



/**
 * DSoundManager�N���X�̃R���X�g���N�^
 * @param[in] hWnd �E�B���h�E�n���h��
 */
DSoundManager::DSoundManager(HWND hWnd)
{
	// �T�E���h�f�o�C�X�쐬
	if (FAILED(DirectSoundCreate8(NULL, &m_pDS8, NULL)))
	{
		MessageBox(0, "�T�E���h�f�o�C�X�̐����Ɏ��s���܂���", "DSoundManager.cpp", MB_OK);
	}
	
	if (FAILED(m_pDS8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		MessageBox(0, "�������x���̐ݒ�Ɏ��s���܂���", "DSoundManager.cpp", MB_OK);
	}
}

/**
 * DSoundManager�N���X�̃f�X�g���N�^
 */
DSoundManager::~DSoundManager()
{
	m_pDS8->Release();
}


/**
 * Wav�t�@�C���̂��J���ď����擾����֐�
 * @param[in] filename �ǂݍ��ރt�@�C����
 * @param[in] wFmt �t�H�[�}�b�g
 * @param[in] pWaveData �����f�[�^
 * @param[in] waveSize �����̃T�C�Y
 * @return wav�t�@�C���̃I�[�v���ɐ���������(����������true)
 */
bool DSoundManager::OpenWave(TCHAR *filename, WAVEFORMATEX &wFmt, char** pWaveData, DWORD &waveSize)
{
	//filepath�̈ʒu�ɂȂɂ��Ȃ���Ύ��s�Ȃ̂�false��Ԃ�
	if (filename == NULL)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Wave�t�@�C���I�[�v��
	ZeroMemory(&mmioInfo, sizeof(MMIOINFO));
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



/**
 * �����̓ǂݍ���
 * @param[in] filename �ǂݍ��ރt�@�C���̖��O
 * @param[in] Key �i�[��̃L�[
 */
int DSoundManager::SoundLoad(char* filename, int Key)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	// Wave�t�@�C���I�[�v��
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


	// �Z�J���_���o�b�t�@��Wave�f�[�^��������
	//�����f�[�^
	LPVOID lpvWrite = 0;
	//�����f�[�^�̑傫��
	DWORD dwLength = 0;
	if (DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	delete[] pWaveData; // �����͂�������Ȃ�


	m_SoundMap[Key] = pDSBuffer;

	return 0;
}

/**
 * �����̉���֐�
 */
void DSoundManager::ReleaseSound(int Key)
{
	m_SoundMap[Key]->Release();
}


/**
 * �T�E���h�̑���֐� 
 * @param[in] Key ���삷��T�E���h�̊i�[��̃L�[
 * @param[in] operation �ǂ̂悤�ȑ�������邩
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

