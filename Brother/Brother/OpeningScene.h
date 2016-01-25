#ifndef OPENINGSCENE_H
#define OPENINGSCENE_H


#include <dshow.h>

#define _WIN32_DCOM				//COM使うために必要
#define OPENING_TIME 60 * 43	//オープニングの時間(フレーム×時間)
#define ONE_FRAME 1000 / 60		//1フレーム(1秒×60)
#define ONE_MILLISECOND 1		//1000分の1秒
#define INIT_TIME 0				//タイムの初期値
#define MOVIE_TOP 0				//ムービーの頭
#define MOVIE_LEFT 0			//ムービーの左側

#include "Scene.h"
class Library;

class OpeningScene :public Scene
{
private:
	IGraphBuilder*			m_pGB;
	ICaptureGraphBuilder2*	m_pCGB2;
	IBaseFilter*			m_pVMR9;
	IMediaControl*			m_pMediaCont;
	HWND					m_hWnd;


public:
	OpeningScene(Library* pLibrary, HWND hWnd);
	~OpeningScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif