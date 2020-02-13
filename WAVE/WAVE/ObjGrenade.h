#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjGrenade: public CObj
{
public:
	CObjGrenade(float x, float y);
	~CObjGrenade() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	float m_x;	//オブジェクトの位置
	float m_y;
	float m_vx;	//オブジェクトの移動用ベクトル
	float m_vy;
	float leng;

	float m_sx ;  //画像サイズBlockHit関数に渡す用
	float m_sy ;

	float x;
	float y;

	bool flag; //弾丸バウンド制御用フラグ

	float pl_x;//現在のプレイヤーXの位置を保存用変数
	float pl_y;//現在のプレイヤーYの位置を保存用変数


	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;


	//当たっているblockの種類を確認用
	int m_block_type;

	bool HitCheck;//判定結果保存用変数

	bool button;
};

