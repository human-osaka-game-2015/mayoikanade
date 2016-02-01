#include "StencilManager.h"


/**
 * StencilManager�N���X�̃R���X�g���N�^
 */
StencilManager::StencilManager(LPDIRECT3DDEVICE9 pDevice) :
m_pDevice(pDevice),
m_StencilRef(0x05)
{

}

/**
 * StencilManager�N���X�̃f�X�g���N�^
 */
StencilManager::~StencilManager()
{

}


/**
 * �X�e���V���̕`��O����
 */
void StencilManager::StencilDrawReady()
{
	//�X�e���V���o�b�t�@��̃f�[�^����
	m_pDevice->Clear(0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);


	//�X�e���V���e�X�g�̐ݒ�***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);		//�L��

	//�[�x�e�X�g�̐ݒ�******************************************
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);		//�K���s���i

	//�X�e���V���Q�ƒl�̐ݒ�************************************
	m_pDevice->SetRenderState(D3DRS_STENCILREF, m_StencilRef);			

	//�X�e���V���}�X�N�̐ݒ�************************************
	m_pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffff�ɂ���
	m_pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffff�ɂ���

	//�X�e���V���o�b�t�@�ɏ������ޏ����i��r�֐��j�̐ݒ�********
	m_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	//��΂ɏ������ށB

	//�������ޒl�̐ݒ�******************************************
	//�X�e���V���e�X�g�Ɏ��s�����ꍇ�͂Ȃɂ����Ȃ�
	m_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//�������Ȃ�
	//�X�e���V���e�X�g�ɐ������āAz�o�b�t�@�e�X�g�ɂɎ��s�����ꍇ
	m_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//�X�e���V���Q�ƒl���������ށB
	//�X�e���V���Az�A�������������ꍇ
	m_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//�������Ȃ�

}

/**
 * �X�e���V���̕`��㏈��
 */
void StencilManager::StencilDrawEnd()
{

	//�[�x�e�X�g�̐ݒ�*****************************************
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�X�e���V���Q�ƒl�̐ݒ�***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILREF, m_StencilRef);

	//�X�e���V���}�X�N�̐ݒ�***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffff�ɂ���
	m_pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffff�ɂ���


	m_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);


	//�������ޒl�̐ݒ�***********************************
	m_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//�������Ȃ�
	m_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	//�������Ȃ�
	m_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//�������Ȃ�

}

/**
 * �X�e���V���e�X�g�̏I������
 */
void StencilManager::StencilTestEnd()
{
	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
}

/**
 * �X�e���V���̎Q�ƒl�̃Z�b�g
 * @param[in] ref �ݒ肷��Q�ƒl
 */
void StencilManager::StencilRefSet(BYTE ref)
{
	m_StencilRef = ref;
}

/**
 * �X�e���V���`��
 * @param[in] vertex �`�悷�钸�_���
 */
void StencilManager::StencilDraw(CustomVertex* pvertex)
{

	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pvertex,
		sizeof(CustomVertex));
}

/**
 * ���e�X�g�̏���
 * @param[in] ref ���e�X�g���s���ۂ̊�l
 */
void StencilManager::AlphaTestReady(BYTE ref)
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, ref);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_EQUAL);
}

/**
 * ���e�X�g��؂�
 */
void StencilManager::AlphaTestEnd()
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

