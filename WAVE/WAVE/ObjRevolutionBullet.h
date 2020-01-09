#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjRevolutionBullet : public CObj
{
public:
	CObjRevolutionBullet(float x, float y);
	~CObjRevolutionBullet() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	float m_x;	//オブジェクトの位置
	float m_y;
	float m_vx;	//オブジェクトの移動用ベクトル
	float m_vy;

	float Angle;
	float R;
	float Cx, Cy;

	int second;

	float x;
	float y;
	short int pos;

	bool flag; //弾丸バウンド制御用フラグ

	float pl_x;//現在のプレイヤーXの位置を保存用変数
	float pl_y;//現在のプレイヤーYの位置を保存用変数

	bool button;

	float m_r;  //移動する角度
	float m_speed;  //速度

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//当たっているblockの種類を確認用
	int m_block_type;

};


