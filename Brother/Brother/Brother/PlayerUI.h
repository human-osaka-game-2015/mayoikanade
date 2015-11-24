#ifndef PLAYERUI_H
#define PLAYERUI_H

class Library;

//
//TexKey�������œn���ׂ����A�����Ƃ��Ă͓n������X�e�[�W���Ƃ�UI�̐F�Ƃ����ς��Ƃ��Ȃ����ꍇ�֗����������A
//PlayerUI�͓n���ꂽ��񂾂��Ŕ��f���鑶�݂ɂȂ�C������B
//
//Player��Hp�̃A�h���X���������邩�A�l����������
//�l�����̏ꍇ�APlayer����hp���ϓ������ꍇ�ɂ�����Set�֐����Ăяo���ĕύX����`�ɂȂ�B
//
//
//���\�b�h�A�ϐ��A����
//
//�ؔ��Ƃ��̔��f���Ė{����CollisionChecker�����邱�ƂȂ́H
//�Ⴄ�Ȃ�N�����ׂ��H
//
//
//


class PlayerUI
{
private:
	Library*	m_pLibrary;
	int			m_PlayerHp;

public:
	PlayerUI(Library* pLibrary,int Hp);
	~PlayerUI();
	inline void PlayerHpSet(int Hp) { m_PlayerHp = Hp; }
	void Control();
	void Draw();

};



#endif