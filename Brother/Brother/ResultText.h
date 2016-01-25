#ifndef RESULTTEXT_H
#define RESULTTEXT_H

#include "Vertex.h"

#define RESULTTEXT_FADE_TIME 255
#define RESULTTEXT_INIT_FADE_TIME 0
#define RESULTTITLE_ALPHA_MIN 100
#define RESULTTITLE_ALPHA_MAX 255
#define RESULTTITLE_POS_X 300
#define RESULTTITLE_POS_Y 725
#define RESULTCLEAR_POS_X 440
#define RESULTCLEAR_POS_Y 350
#define RESULTOVER_POS_X 640
#define RESULTOVER_POS_Y 270
#define RESULT_TEXT_FADESPEAD 5

class Library;

//‚»‚Ì‚¤‚¿3‚Â‚É•ª‚¯‚é
class ResultText
{
private:
	Library*	m_pLibrary;
	bool		m_isTextFadeIn;
	bool		m_isTitleFadeIn;
	bool		m_isGameClear;
	int			m_ClearAlpha;
	int			m_OverAlpha;
	int			m_TitleAlpha;
	int			m_FadeTime;
	Position	m_TitlePos;
	Position	m_ClearPos;
	Position	m_OverPos;

public:
	ResultText(Library* pLibrary, bool isGameClear);
	~ResultText();
	void Control();
	void Draw();
	void ClearControl();
	void OverControl();
	void ClearDraw();
	void OverDraw();

};




#endif