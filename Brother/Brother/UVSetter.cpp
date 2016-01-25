/**
 * @file UVSetter.cpp
 * @brief UVSetterクラス
 * @author 森本
 * @date 11月9日
 */

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <mmsystem.h>
#include "UVSetter.h"


/**
 * UVSetterクラスのコンストラクタ
 */
UVSetter::UVSetter()
{
	
}

/**
 * UVSetterクラスのデストラクタ
 */
UVSetter::~UVSetter()
{
	
}

/**
 * ファイル情報の入ったcsvを読み込む関数
 * @param[in] name 読み込むファイルの名前
 * @param[in] fileNum 読み込む情報量
 * @return 成功したかどうか(成功したら0が返る)
 */
int UVSetter::FileInfoSet(const char* name, int FileNum)
{
	if (FileNum <= 0)
	{
		return -1;
	}

	m_pFileInfo = new InfoFile[FileNum];

	FILE* fp;
	fopen_s(&fp, name, "r");
	if (fp == NULL)
	{
		return FILEOPENERROR;
	}

	for (int i = 0; i < FileNum; i++)
	{
		fscanf_s(fp, "%d,%f,%f", &m_pFileInfo[i].FileNum, &m_pFileInfo[i].FileWidth, &m_pFileInfo[i].FileHight);
	}

	fclose(fp);
	return 0;
}

/**
 * 頂点情報の入ったcsvを読み込む関数
 * @param[in] name 読み込むファイルの名前
 * @param[in] vertexNum 読み込む情報量
 * @return 成功したかどうか(成功したら0が返る)
 */
int UVSetter::VertexInfoSet(const char* name, int VertexNum)
{
	if (VertexNum <= 0)
	{
		return -1;
	}

	m_pVertexInfo = new InfoVertex[VertexNum];

	FILE* fp;
	fopen_s(&fp, name, "r");
	if (fp == NULL)
	{
		return FILEOPENERROR;
	}

	for (int i = 0; i < VertexNum; i++)
	{
		fscanf_s(fp, "%d,%f,%f,%f,%f", &m_pVertexInfo[i].ThisFileNum, &m_pVertexInfo[i].TextureLeft, &m_pVertexInfo[i].TextureTop,
				 &m_pVertexInfo[i].TextureWidth, &m_pVertexInfo[i].TextureHight);
	}

	fclose(fp);
	return 0;
}


/**
 * アニメーション情報の入ったcsvを読み込む関数
 * @param[in] name 読み込むファイルの名前
 * @param[in] animaNum 読み込む情報量
 * @return 成功したかどうか(成功したら0が返る)
 */
int UVSetter::AnimaInfoSet(const char* name, int AnimaNum)
{
	if (AnimaNum <= 0)
	{
		return -1;
	}

	m_pAnimaInfo = new InfoAnime[AnimaNum];

	FILE* fp;
	fopen_s(&fp, name, "r");
	if (fp == NULL)
	{
		return FILEOPENERROR;
	}

	for (int i = 0; i < AnimaNum; i++)
	{
		fscanf_s(fp, "%d,%d,%d,%d", &m_pAnimaInfo[i].TopAnima, &m_pAnimaInfo[i].AnimaMax, &m_pAnimaInfo[i].AnimationType,
				 &m_pAnimaInfo[i].FrameMax);
	}

	fclose(fp);
	return 0;
}


/**
 * ファイルの情報の解放
 */
void UVSetter::FileInfoRelease()
{
	delete[] m_pFileInfo;
}

/**
 * 頂点情報の解放
 */
void UVSetter::VertexInfoRelease()
{
	delete[] m_pVertexInfo;
}

/**
 * アニメーション情報の解放
 */
void UVSetter::AnimaInfoRelease()
{
	delete[] m_pAnimaInfo;
}


/**
 * 頂点情報をCustomVertex構造体に出力する
 * @param[in] vertexNum 参照する頂点情報の番号
 * @param[out] pVertex 頂点情報が出力されるCustomVertex構造体
 */
void UVSetter::MakeVertex(int VertexNum, CustomVertex* vertex)
{
	//プログラム的に配列は0～なのに対して ファイル番号は1～なので 現状はー1してる
	int FileNum = m_pVertexInfo[VertexNum].ThisFileNum - 1;

	vertex[0].tu = m_pVertexInfo[VertexNum].TextureLeft / m_pFileInfo[FileNum].FileWidth;
	vertex[0].tv = m_pVertexInfo[VertexNum].TextureTop / m_pFileInfo[FileNum].FileHight;

	vertex[1].tu = (m_pVertexInfo[VertexNum].TextureLeft + m_pVertexInfo[VertexNum].TextureWidth) / m_pFileInfo[FileNum].FileWidth;
	vertex[1].tv = m_pVertexInfo[VertexNum].TextureTop / m_pFileInfo[FileNum].FileHight;

	vertex[2].tu = (m_pVertexInfo[VertexNum].TextureLeft + m_pVertexInfo[VertexNum].TextureWidth) / m_pFileInfo[FileNum].FileWidth;
	vertex[2].tv = (m_pVertexInfo[VertexNum].TextureTop + m_pVertexInfo[VertexNum].TextureHight) / m_pFileInfo[FileNum].FileHight;

	vertex[3].tu = m_pVertexInfo[VertexNum].TextureLeft / m_pFileInfo[FileNum].FileWidth;
	vertex[3].tv = (m_pVertexInfo[VertexNum].TextureTop + m_pVertexInfo[VertexNum].TextureHight) / m_pFileInfo[FileNum].FileHight;

	for (int i = 0; i < VERTEXNUM; i++)
	{
		vertex[i].color = DEFAULT_COLOR;
		vertex[i].rhw = DEFAULT_RHW;
		vertex[i].z = DEFAULT_Z;
	}
}


/**
 * 頂点情報をPosition構造体に出力する
 * @param[in] vertexNum 参照する頂点情報の番号
 * @param[out] pPos 頂点情報が出力されるPosition構造体
 */
void UVSetter::MakePosition(int VertexNum, Position* pos)
{
	pos->w = m_pVertexInfo[VertexNum].TextureWidth;
	pos->h = m_pVertexInfo[VertexNum].TextureHight;
}

/**
 * アニメーション情報の初期化
 * @param[in] animaNum 初期化するアニメーション
 */
void UVSetter::InitAnima(int AnimationNum)
{
	m_pAnimaInfo[AnimationNum].FrameCount = INITFRAMECOUNT;
	m_pAnimaInfo[AnimationNum].AnimaNum = INITAnimaNum;
	m_pAnimaInfo[AnimationNum].AddNum = INITADDNUM;
}

/**
 * 反転させる関数
 * @param[out] pVertex 反転するCustomVertex
 * @param[in] rev 横反転か縦反転か
 */
void UVSetter::UVReversal(CustomVertex* pvertex,REVERSAL_NUM rev)
{
	float temp;
	switch (rev)
	{
	case UP_AND_DOWN:
		temp = pvertex[0].tv;
		pvertex[0].tv = pvertex[3].tv;
		pvertex[3].tv = temp;
		temp = pvertex[1].tv;
		pvertex[1].tv = pvertex[2].tv;
		pvertex[2].tv = temp;
		break;

	case LEFT_AND_RIGHT:
		temp = pvertex[0].tu;
		pvertex[0].tu = pvertex[1].tu;
		pvertex[1].tu = temp;
		temp = pvertex[3].tu;
		pvertex[3].tu = pvertex[2].tu;
		pvertex[2].tu = temp;
		break;
	}
}


/**
 * 次の画像を教えてくれる関数
 * @param[in] AnimaNum アニメーション番号
 * @return 次に表示する画像の番号
 */
int UVSetter::AnimaControl(int AnimationNum)
{
	//フレームカウントを増分
	m_pAnimaInfo[AnimationNum].FrameCount++;

	//フレーム数を見て切り替えるかを判断
	if (m_pAnimaInfo[AnimationNum].FrameCount >= m_pAnimaInfo[AnimationNum].FrameMax)
	{
		//アニメーション
		m_pAnimaInfo[AnimationNum].AnimaNum += m_pAnimaInfo[AnimationNum].AddNum;
		
		//現在指しているアニメーションの番号が最大値を超えているか、0を下回っているか
		if (m_pAnimaInfo[AnimationNum].AnimaNum >= m_pAnimaInfo[AnimationNum].AnimaMax || m_pAnimaInfo[AnimationNum].AnimaNum < 0)
		{
			if (m_pAnimaInfo[AnimationNum].AnimationType == 0)//リバースなのか
			{
				//リバースならAddNumをマイナスにして Animeを最大値で初期化
				m_pAnimaInfo[AnimationNum].AddNum *= -1;
				m_pAnimaInfo[AnimationNum].AnimaNum -= 2;
			}
			else if (m_pAnimaInfo[AnimationNum].AnimationType == 1)//ループなのか
			{
				//ループなら0で初期化
				m_pAnimaInfo[AnimationNum].AnimaNum = INITAnimaNum;
			}
			else
			{
				return AnimationTypeERROR;
			}
		}
		m_pAnimaInfo[AnimationNum].FrameCount = 0;
	}
	return m_pAnimaInfo[AnimationNum].TopAnima + m_pAnimaInfo[AnimationNum].AnimaNum;
}

