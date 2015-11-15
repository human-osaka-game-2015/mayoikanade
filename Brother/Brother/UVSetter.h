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
	int   FileNum;		//統合ファイル番号
	float FileHight;	//統合ファイルの縦幅
	float FileWidth;	//統合ファイルの横幅
} InfoFile, *PInfoFile;

typedef struct _InfoVertex_
{
	int	  ThisFileNum;	//このテクスチャがどの統合ファイルに属しているか
	float TextureTop;	//このテクスチャの頭のy座標
	float TextureLeft;	//このテクスチャの左側のx座標
	float TextureHight;	//このテクスチャの縦幅
	float TextureWidth;	//このテクスチャの横幅
} InfoVertex, *PInfoVertex;

typedef struct _InfoAnime_
{
	int TopAnima;		//アニメーションの先頭のTextureNumber
	int AnimaMax;		//アニメーションの総枚数
	int FrameCount;		//現在のフレーム数のカウント
	int FrameMax;		//アニメーションするフレーム数
	int AnimaNum;		//アニメーションの先頭から何番目か
	int AnimationType;	//アニメーションのパターン
	int AddNum;			//アニメーションするときに加算する数値
} InfoAnime, *PInfoAnime;


class UVSetter
{
private:
	PInfoFile		m_pFileInfo;	//InfoFileのアドレス
	PInfoVertex		m_pVertexInfo;	//InfoVertexのアドレス
	PInfoAnime		m_pAnimaInfo;	//InfoAnimeのアドレス

public:
	UVSetter();
	~UVSetter();

	//読み込むcsvファイルのパスとそのファイル内の情報量を渡す
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