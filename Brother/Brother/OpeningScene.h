#ifndef OPENINGSCENE_H
#define OPENINGSCENE_H


#include <dshow.h>

#define _WIN32_DCOM				//COM�g�����߂ɕK�v
#define OPENING_TIME 60 * 43	//�I�[�v�j���O�̎���(�t���[���~����)
#define ONE_FRAME 1000 / 60		//1�t���[��(1�b�~60)
#define ONE_MILLISECOND 1		//1000����1�b
#define INIT_TIME 0				//�^�C���̏����l
#define MOVIE_TOP 0				//���[�r�[�̓�
#define MOVIE_LEFT 0			//���[�r�[�̍���

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