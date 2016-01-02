#ifndef OPENINGSCENE_H
#define OPENINGSCENE_H


#include <dshow.h>
//COM使う上で必要な定義
#define _WIN32_DCOM


#include "Scene.h"
class Library;

class OpeningScene:public Scene
{
private:
	IGraphBuilder*			m_pGB;
	ICaptureGraphBuilder2*	m_pCGB2;
	IBaseFilter*			m_pVMR9;
	IMediaControl*			m_pMediaCont;
	HWND					m_hWnd;


public:
	OpeningScene(Library* pLibrary,HWND hWnd);
	~OpeningScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif