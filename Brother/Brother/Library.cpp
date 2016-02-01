/**
* @file Library.cpp
* @brief Library�N���X
* @author �X�{
* @date 12��9��
*/
#include "D3DManager.h"
#include "Library.h"



/**
 * Library�N���X�̃R���X�g���N�^
 * @param[in] hWnd �E�B���h�E�n���h��
 * @param[in] isFullWindow �t���E�B���h�E�ɂ��邩�̃t���O
 * @param[in] isStencil �X�e���V�����g�����̃t���O
 */
Library::Library(HWND hWnd, bool isFullWindow,bool isStencil) :
m_pD3DManager(NULL), 
m_pDSoundManager(NULL), 
m_pXInput(NULL), 
m_pTexture(NULL), 
m_pVertex(NULL), 
m_pUVSetter(NULL)
{
	//���C�u�����N���X�̐���
	m_pD3DManager		= new D3DManager(hWnd, isFullWindow,isStencil);
	m_pDSoundManager	= new DSoundManager(hWnd);
	m_pXInput			= new XInput();
	m_pTexture			= new Texture(D3DManager::pD3Device);
	m_pVertex			= new Vertex();
	m_pUVSetter			= new UVSetter();
	m_pStencilManager	= new StencilManager(D3DManager::pD3Device);
	m_pInputDevice		= new InputDevice(hWnd);
}


Library::~Library()
{
	//���C�u�����N���X�̔j��
	delete m_pInputDevice;
	delete m_pStencilManager;
	delete m_pUVSetter;
	delete m_pVertex;
	delete m_pTexture;
	delete m_pXInput;
	delete m_pDSoundManager;
	delete m_pD3DManager;
}


/**
 * �f�o�C�X���擾����֐�
 * @return LPDIRECT3DDECVICE9���Ԃ�
 */
LPDIRECT3DDEVICE9 Library::GetDevice()
{
	return m_pD3DManager->pD3Device;
}


//--------------------------------------------------------------------------------------
//
//		D3DManager
//
//--------------------------------------------------------------------------------------

/**
 * �`�掞��SetRenderState�֐����܂Ƃ߂ēǂ�ł����
 */
void Library::RenderInit()
{
	m_pD3DManager->RenderInit();
}

/**
 * �`��O�̏������s���Ă����
 */
void Library::DrawReady()
{
	m_pD3DManager->DrawReady();
}

/**
 * �`���̏������s���Ă����
 */
void Library::DrawEnd()
{
	m_pD3DManager->DrawEnd();
}



//--------------------------------------------------------------------------------------
//
//		DSoundManager
//
//--------------------------------------------------------------------------------------

/**
 * �T�E���h�̃��[�h�֐�(wav�̂�)
 * @param[in] filename �ǂݍ��ރt�@�C���̖��O
 * @param[in] key �i�[��̃L�[
 * @return �����������̏�񂪕Ԃ��Ă���
 */
int Library::SoundLoad(char* filename, int Key)
{
	return m_pDSoundManager->SoundLoad(filename, Key);
}

/**
 * �T�E���h�̉���֐�
 * @param[in] Key ������鉹���̊i�[��̃L�[
 */
void Library::ReleaseSound(int Key)
{
	m_pDSoundManager->ReleaseSound(Key);
}

/**
 * �T�E���h�̉���֐�
 * @param[in] Key ���삷�鉹���̊i�[��̃L�[
 * @param[in] operation �����ɑ΂��鑀��
 */
void Library::SoundOperation(int Key, SOUND_OPERATION operation)
{
	m_pDSoundManager->SoundOperation(Key, operation);
}


//--------------------------------------------------------------------------------------
//
//		Texture
//
//--------------------------------------------------------------------------------------

/**
 * �e�N�X�`���̓ǂݍ���
 * @param[in] name �ǂݍ��ރt�@�C���̖��O
 * @param[in] key �i�[��̃L�[
 * @param[in] alpha ���߂���F�̎w��(��)
 * @param[in] red ���߂���F�̎w��(��)
 * @param[in] green ���߂���F�̎w��(��)
 * @param[in] blue ���߂���F�̎w��(��)
 * @return �����������ǂ����̏��
 */
int Library::LoadTextureEx(const char* name, int key, int alpha = 255, int red = 0, int green = 255, int blue = 0)
{
	return m_pTexture->LoadTextureEx(name, key, alpha, red, green, blue);
}

/**
 * �e�N�X�`���̉��
 * @param[in] key �������摜�̊i�[��̃L�[
 */
void Library::ReleaseTexture(int key)
{
	m_pTexture->ReleaseTexture(key);
}

/** 
 * �`��֐�
 * @param[in] key �`�悷��e�N�X�`���̊i�[��L�[
 * @param[in] pVertex �`�悷�钸�_���W
 */
void Library::DrawTexture(int key, CustomVertex* pVertex)
{
	m_pTexture->DrawTexture(key, pVertex);
}



//--------------------------------------------------------------------------------------
//
//		Vertex
//
//--------------------------------------------------------------------------------------

/**
 * Position�\���̂���xy�����擾����pVertex�ɏo�͂���
 * @param[in] pos xy�����擾����position�\����
 * @param[out] pVertex xy�����o�͂���CustomVertex
 */
void Library::xySet(Position pos, CustomVertex* pVertex)
{
	m_pVertex->xySet(pos, pVertex);
}

/**
 * ���_���W�̉�]�֐�
 * @param[out] pVertex ��]���钸�_
 * @param[in] pos ���̒��_�̈ʒu
 * @param[in] angle ��]����p�x
 */
void Library::Turn(CustomVertex* pVertex, Position* pos, double angle)
{
	m_pVertex->Turn(pVertex, pos, angle);
}


//--------------------------------------------------------------------------------------
//
//		UVSetter
//
//--------------------------------------------------------------------------------------

/**
 * �t�@�C�����̓�����csv��ǂݍ��ފ֐�
 * @param[in] name �ǂݍ��ރt�@�C���̖��O
 * @param[in] fileNum �ǂݍ��ޏ���
 * @return �����������ǂ���(����������0���Ԃ�)
 */
int Library::FileInfoSet(const char* name, int fileNum)
{
	return m_pUVSetter->FileInfoSet(name, fileNum);
}


/**
 * ���_���̓�����csv��ǂݍ��ފ֐�
 * @param[in] name �ǂݍ��ރt�@�C���̖��O
 * @param[in] vertexNum �ǂݍ��ޏ���
 * @return �����������ǂ���(����������0���Ԃ�)
 */
int Library::VertexInfoSet(const char* name, int vertexNum)
{
	return m_pUVSetter->VertexInfoSet(name, vertexNum);
}

/**
 * �A�j���[�V�������̓�����csv��ǂݍ��ފ֐�
 * @param[in] name �ǂݍ��ރt�@�C���̖��O
 * @param[in] animaNum �ǂݍ��ޏ���
 * @return �����������ǂ���(����������0���Ԃ�)
 */
int Library::AnimaInfoSet(const char* name, int animaNum)
{
	return m_pUVSetter->AnimaInfoSet(name, animaNum);
}

/**
 * �t�@�C���̏��̉��
 */
void Library::FileInfoRelease()
{
	m_pUVSetter->FileInfoRelease();
}

/**
 * ���_���̉��
 */
void Library::VertexInfoRelease()
{
	m_pUVSetter->VertexInfoRelease();
}

/**
 * �A�j���[�V�������̉��
 */
void Library::AnimaInfoRelease()
{
	m_pUVSetter->AnimaInfoRelease();
}

/**
 * ���_����Position�\���̂ɏo�͂���
 * @param[in] vertexNum �Q�Ƃ��钸�_���̔ԍ� 
 * @param[out] pPos ���_��񂪏o�͂����Position�\����
 */
void Library::MakePosition(int vertexNum, Position* pPos)
{
	m_pUVSetter->MakePosition(vertexNum, pPos);
}

/**
 * ���_����CustomVertex�\���̂ɏo�͂���
 * @param[in] vertexNum �Q�Ƃ��钸�_���̔ԍ�
 * @param[out] pVertex ���_��񂪏o�͂����CustomVertex�\����
 */
void Library::MakeVertex(int vertexNum, CustomVertex* pVertex)
{
	m_pUVSetter->MakeVertex(vertexNum, pVertex);
}

/**
 * �A�j���[�V�������̏�����
 * @param[in] animaNum ����������A�j���[�V����
 */
void Library::InitAnima(int animaNum)
{
	m_pUVSetter->InitAnima(animaNum);
}

/**
 * ���̉摜�������Ă����֐�
 * @param[in] animaNum �A�j���[�V�����ԍ�
 * @return ���ɕ\������摜�̔ԍ�
 */
int Library::AnimaControl(int animaNum)
{
	return m_pUVSetter->AnimaControl(animaNum);
}


/**
 * ���]������֐�
 * @param[out] pVertex ���]����CustomVertex
 * @param[in] rev �����]���c���]��
 */
void Library::UVReversal(CustomVertex* pVertex, REVERSAL_NUM rev)
{
	m_pUVSetter->UVReversal(pVertex, rev);
}


//--------------------------------------------------------------------------------------
//
//		XInput
//
//--------------------------------------------------------------------------------------

/**
 * �R���g���[���[�̏�ԃ`�F�b�N
 * @param[in] pad �`�F�b�N����GAMEPAD
 */
void Library::Check(XINPUTPAD pad)
{
	m_pXInput->Check(pad);
}

/**
 * �{�^���̏�Ԃ��擾����֐�
 * @param[in] id �擾����{�^��
 * @param[in] pad �`�F�b�N����GamePad
 * @return �`�F�b�N�����{�^���̏��
 */
PADSTATE Library::GetButtonState(XINPUT_ID id, XINPUTPAD pad)
{
	return m_pXInput->GetButtonState(id, pad);
}


/**
 * �X�e�B�b�N�̏�Ԃ��擾����֐�
 * @param[in] id �擾����X�e�B�b�N
 * @param[in] pad �`�F�b�N����GamePad
 * @return �`�F�b�N�����X�e�B�b�N�̏��
 */
bool Library::GetAnalogState(ANALOGPAD id, XINPUTPAD pad)
{
	return m_pXInput->GetAnalogState(id, pad);
}



//--------------------------------------------------------------------------------------
//
//		StencilManager
//
//--------------------------------------------------------------------------------------

/**
 * �X�e���V���̕`��O����
 */
void Library::StencilDrawReady()
{
	m_pStencilManager->StencilDrawReady();
}

/**
 * �X�e���V���̕`��㏈��
 */
void Library::StencilDrawEnd()
{
	m_pStencilManager->StencilDrawEnd();
}


/**
 * �X�e���V���̎Q�ƒl�̃Z�b�g
 * @param[in] ref �ݒ肷��Q�ƒl
 */
void Library::StencilRefSet(BYTE ref)
{
	m_pStencilManager->StencilRefSet(ref);
}

/**
 * �X�e���V���`��
 * @param[in] vertex �`�悷�钸�_���
 */
void Library::StencilDraw(CustomVertex* vertex)
{
	m_pStencilManager->StencilDraw(vertex);
}


/**
 * ���e�X�g�̏���
 * @param[in] ref ���e�X�g���s���ۂ̊�l
 */
void Library::AlphaTestReady(BYTE ref)
{
	m_pStencilManager->AlphaTestReady(ref);
}

/**
 * ���e�X�g��؂�
 */
void Library::AlphaTestEnd()
{
	m_pStencilManager->AlphaTestEnd();
}


/**
 * �X�e���V���e�X�g�̏I������
 */
void Library::StencilTestEnd()
{
	m_pStencilManager->StencilTestEnd();
}



//--------------------------------------------------------------------------------------
//
//		InputDevice
//
//--------------------------------------------------------------------------------------

/**
 * DirectInput�̃L�[�̏�����
 * @return �������������ĂȂ���(����������S_OK)
 */
HRESULT Library::InitDinputKey()
{
	return m_pInputDevice->InitDinputKey();
}

/**
 * DirectInput�̃}�E�X�̏�����
 * @return �������������ĂȂ���(����������S_OK)
 */
HRESULT Library::InitDinputMouse()
{
	return m_pInputDevice->InitDinputMouse();
}


/**
 * �L�[�̏�ԃ`�F�b�N�֐�
 * @param[out] Key �L�[�̏�Ԃ��i�[����z��
 * @param[in] DIK �`�F�b�N����L�[
 */
void Library::KeyCheck(KEYSTATE* Key, int DIK)
{
	m_pInputDevice->KeyCheck(Key, DIK);
}


/**
 * �}�E�X�̏�ԃ`�F�b�N�֐�
 * @param[out] Mouse �}�E�X�̏�Ԃ��o�͂���MOUSEKIND�\����
 */
void Library::MouseCheck(MOUSEKIND* Mouse)
{
	m_pInputDevice->MouseCheck(Mouse);
}

