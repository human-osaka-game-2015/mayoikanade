#ifndef UVSETTER_H
#define UVSETTER_H

#define DEFAULT_COLOR 0xffffffff
#define DEFAULT_RHW 1
#define DEFAULT_Z 0
#define DEFAULT_TU 0
#define DEFAULT_TV 0
#define INITFRAMECOUNT 0
#define INITAnimaNum 0
#define INITADDNUM 1
#define VERTEXNUM 4
#define AnimationTypeERROR -1
#define FILEOPENERROR -1



#include <d3dx9.h>
#include <d3dx9tex.h>
#include "Vertex.h"



enum REVERSAL_NUM
{
	UP_AND_DOWN,
	LEFT_AND_RIGHT
};

typedef struct _InfoFile_
{
	int   FileNum;		//�����t�@�C���ԍ�
	float FileHight;	//�����t�@�C���̏c��
	float FileWidth;	//�����t�@�C���̉���
} InfoFile, *PInfoFile;

typedef struct _InfoVertex_
{
	int	  ThisFileNum;	//���̃e�N�X�`�����ǂ̓����t�@�C���ɑ����Ă��邩
	float TextureTop;	//���̃e�N�X�`���̓���y���W
	float TextureLeft;	//���̃e�N�X�`���̍�����x���W
	float TextureHight;	//���̃e�N�X�`���̏c��
	float TextureWidth;	//���̃e�N�X�`���̉���
} InfoVertex, *PInfoVertex;

typedef struct _InfoAnime_
{
	int TopAnima;		//�A�j���[�V�����̐擪��TextureNumber
	int AnimaMax;		//�A�j���[�V�����̑�����
	int FrameCount;		//���݂̃t���[�����̃J�E���g
	int FrameMax;		//�A�j���[�V��������t���[����
	int AnimaNum;		//�A�j���[�V�����̐擪���牽�Ԗڂ�
	int AnimationType;	//�A�j���[�V�����̃p�^�[��
	int AddNum;			//�A�j���[�V��������Ƃ��ɉ��Z���鐔�l
} InfoAnime, *PInfoAnime;



class UVSetter
{
private:
	PInfoFile		m_pFileInfo;	//InfoFile�̃A�h���X
	PInfoVertex		m_pVertexInfo;	//InfoVertex�̃A�h���X
	PInfoAnime		m_pAnimaInfo;	//InfoAnime�̃A�h���X

public:
	UVSetter();
	~UVSetter();

	//�ǂݍ���csv�t�@�C���̃p�X�Ƃ��̃t�@�C�����̏��ʂ�n��
	int FileInfoSet(const char* name, int fileNum);
	int VertexInfoSet(const char* name, int vertexNum);
	int AnimaInfoSet(const char* name, int animaNum);

	void FileInfoRelease();
	void VertexInfoRelease();
	void AnimaInfoRelease();

	void MakeVertex(int vertexNum, CustomVertex* pVertex);
	void MakePosition(int vertexNum, Position* pPos);
	void InitAnima(int animaNum);
	int AnimaControl(int animaNum);

	void UVReversal(CustomVertex* pVertex, REVERSAL_NUM rev);

};


#endif