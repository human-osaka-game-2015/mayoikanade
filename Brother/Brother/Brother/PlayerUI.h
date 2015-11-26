#ifndef PLAYERUI_H
#define PLAYERUI_H

class Library;


//
//constの参照を渡して、描画時はそこをみる
//
//メソッド、変数、順番
//


class PlayerUI
{
private:
	Library*	m_pLibrary;
	const int&	m_PlayerHp;

public:
	PlayerUI(Library* pLibrary,const int Hp);
	~PlayerUI();
	void Control();
	void Draw();

};



#endif