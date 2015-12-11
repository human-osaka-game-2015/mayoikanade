#include "StencilManager.h"
#include "D3DManager.h"



StencilManager::StencilManager() :m_StencilRef(0x05)
{

}

StencilManager::~StencilManager()
{

}



void StencilManager::StencilDrawReady()
{
	//�X�e���V���o�b�t�@��̃f�[�^����
	D3DManager::pD3Device->Clear(0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);


	//�X�e���V���e�X�g�̐ݒ�***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILENABLE, TRUE);		//�L��

	//�[�x�e�X�g�̐ݒ�******************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);		//�K���s���i

	//�X�e���V���Q�ƒl�̐ݒ�************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILREF, m_StencilRef);			

	//�X�e���V���}�X�N�̐ݒ�************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffff�ɂ���
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffff�ɂ���

	//�X�e���V���o�b�t�@�ɏ������ޏ����i��r�֐��j�̐ݒ�********
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	//��΂ɏ������ށB

	//�������ޒl�̐ݒ�******************************************
	//�X�e���V���e�X�g�Ɏ��s�����ꍇ�͂Ȃɂ����Ȃ�
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//�������Ȃ�
	//�X�e���V���e�X�g�ɐ������āAz�o�b�t�@�e�X�g�ɂɎ��s�����ꍇ
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//�X�e���V���Q�ƒl���������ށB
	//�X�e���V���Az�A�������������ꍇ
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//�������Ȃ�

}

void StencilManager::StencilDrawEnd()
{

	//�[�x�e�X�g�̐ݒ�*****************************************
	D3DManager::pD3Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�X�e���V���Q�ƒl�̐ݒ�***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILREF, m_StencilRef);

	//�X�e���V���}�X�N�̐ݒ�***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//0xffffffff�ɂ���
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);		//0xffffffff�ɂ���


	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);


	//�������ޒl�̐ݒ�***********************************
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//�������Ȃ�
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	//�������Ȃ�
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//�������Ȃ�

}

void StencilManager::StencilTestEnd()
{
	D3DManager::pD3Device->SetRenderState(D3DRS_STENCILENABLE, false);
}

void StencilManager::StencilRefSet(BYTE ref)
{
	m_StencilRef = ref;
}



void StencilManager::StencilDraw(CustomVertex* pvertex)
{

	D3DManager::pD3Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pvertex,
		sizeof(CustomVertex));
}

void StencilManager::AlphaTestReady(BYTE ref)
{
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHAREF, ref);
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_EQUAL);
}

void StencilManager::AlphaTestEnd()
{
	D3DManager::pD3Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

