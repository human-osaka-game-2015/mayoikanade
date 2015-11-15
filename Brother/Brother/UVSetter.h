#ifndef _UVSETTER_H_
#define _UVSETTER_H_
#define DEFAULTCOLOR 0xffffffff
#define DEFAULTRHW 1
#define DEFAULTZ 0.5
#define INITFRAMECOUNT 0
#define INITAnimaNum 0
#define INITADDNUM 1
#define VERTEXNUM 4
#define AnimationTypeERROR -1
#define FILEOPENERROR -1

#define VERTEX_INFO 24
#define FILE_INFO 1
#define ANIMA_INFO 6

#include <d3dx9.h>
#include <d3dx9tex.h>
#include "Vertex.h"

enum REVERSAL_NUM
{
	UP_AND_DOWN,
	LEFT_AND_RIGHT
};

//
//enum VERTEXINFO_ID
//{
//	BROTHER_WAIT_FRONT_01,
//	BROTHER_WAIT_FRONT_02,
//
//	BROTHER_WAIT_SIDE_01,
//	BROTHER_WAIT_SIDE_02,
//
//	BROTHER_WAIT_BACK_01,
//	BROTHER_WAIT_BACK_02,
//
//	BROTHER_WALK_FRONT_01,
//	BROTHER_WALK_FRONT_02,
//	BROTHER_WALK_FRONT_03,
//	BROTHER_WALK_FRONT_04,
//
//	BROTHER_WALK_SIDE_01,
//	BROTHER_WALK_SIDE_02,
//	BROTHER_WALK_SIDE_03,
//	BROTHER_WALK_SIDE_04,
//
//	BROTHER_WALK_BACK_01,
//	BROTHER_WALK_BACK_02,
//	BROTHER_WALK_BACK_03,
//	BROTHER_WALK_BACK_04,
//
//	WOOD_01,
//	WOOD_02,
//	WOOD_03,
//	WOOD_04,
//
//	GRASS_01,
//	GROUND_01,
//
//};

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
	int FileInfo_Set(const char* name, int FileNum);
	int VertexInfo_Set(const char* name, int VertexNum);
	int AnimaInfo_Set(const char* name, int AnimaNum);

	void FileInfo_Release();
	void VertexInfo_Release();
	void AnimaInfo_Release();

	void MakeVertex(int VertexNum, CustomVertex* vertex);
	void MakePosition(int VertexNum, Position* pos);
	void InitAnima(int AnimaNum);
	int AnimaControl(int AnimaNum);

	void UVReversal(CustomVertex* pvertex, REVERSAL_NUM rev);

};


#endif