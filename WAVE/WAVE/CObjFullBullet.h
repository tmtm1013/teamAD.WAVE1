#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:主人公
class CObjFullBullet :public CObj
{
public:
	CObjFullBullet(float x, float y);  //コンストラクタ
	~CObjFullBullet() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_bx;    //弾丸の X 方向の位置用変数
	float m_by;    //弾丸の Y 方向の位置用変数
	float m_vx;    //弾丸の X 方向の速度用変数
	float m_vy;    //弾丸の Y 方向の速度用変数

	float bx;      //弾丸の X ベクトル値収納用変数 
	float by;      //弾丸の Y ベクトル値収納用変数

	bool flag;     //発射角度制御フラグ
	float m_time;  //弾丸発射頻度制御用変数

	float m_mou_bx;//マウスの X 方向の位置用変数
	float m_mou_by;//マウスの Y 方向の位置用変数

	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	float m_sx;   //サイズ用
	float m_sy;

	//当たっているblockの種類を確認用
	int m_block_type;

};

