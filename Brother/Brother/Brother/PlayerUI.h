#ifndef PLAYERUI_H
#define PLAYERUI_H

class Library;


//
//const�̎Q�Ƃ�n���āA�`�掞�͂������݂�
//
//���\�b�h�A�ϐ��A����
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