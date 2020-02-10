#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：アイテム
class CObjAitem :public CObj
{
public:
	CObjAitem(float x, float y);
	~CObjAitem() {};
	void Init();	 //イニシャライズ
	void Action();	 //アクション
	void Draw();	 //ドロー
private:
	

	float m_vx;
	float m_vy;

	float m_sx;  //画像サイズ用
	float m_sy;


	float m_ix;
	float m_iy;

	float  m_posture;


	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	bool flag;

	float top;
	float left;
	float right;
	float bottom;

	int m_block_type;

};
