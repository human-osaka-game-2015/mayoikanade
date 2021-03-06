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