#ifndef PLAYERUI_H
#define PLAYERUI_H

class Library;

//
//TexKeyを引数で渡すべきか、自分としては渡したらステージごとにUIの色とかが変わるとかなった場合便利そうだし、
//PlayerUIは渡された情報だけで判断する存在になる気がする。
//
//PlayerのHpのアドレスを持たせるか、値だけを持つか
//値だけの場合、Player側でhpが変動した場合にこいつのSet関数を呼び出して変更する形になる。
//
//
//メソッド、変数、順番
//
//木箱とかの判断って本当にCollisionCheckerがすることなの？
//違うなら誰がすべき？
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