#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:主人公
class CObjBullet :public CObj
{
public:
	CObjBullet(float x, float y);  //コンストラクタ
	~CObjBullet() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_bx;    //弾丸の X 方向の位置用変数
	float m_by;    //弾丸の Y 方向の位置用変数
	float m_vx;    //弾丸の X 方向の速度用変数
	float m_vy;    //弾丸の Y 方向の速度用変数

	float m_r;     //弾丸の描画角度用変数

	float bx;      //弾丸の X ベクトル値収納用変数 
	float by;      //弾丸の Y ベクトル値収納用変数

	float m_sx;   //サイズ用
	float m_sy;

	 bool m_hit_up;
	 bool m_hit_down;
	 bool m_hit_left;
	 bool m_hit_right;


	 //当たっているblockの種類を確認用
	 int m_block_type;

	bool flag;     //発射角度制御フラグ

	float m_mou_bx;//マウスの X 方向の位置用変数
	float m_mou_by;//マウスの Y 方向の位置用変数



	int m_ani;//着弾アニメーション用
	int m_ani_time;//着弾アニメーション間隔用タイム
	bool m_del;//消去チェック
	RECT_F m_eff;//着弾エフェクト描画用


};
