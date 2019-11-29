#pragma once

#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：敵
class CObjEnemyAmmunition :public CObj
{
public:CObjEnemyAmmunition(float x,float y) ;
	   ~CObjEnemyAmmunition() {};
	   void Init();   //イニシャライズ
	   void Action(); //アクション
	   void Draw();   //ドロー

private:
	float m_px;    //位置
	float m_py;
	float m_vx;    //移動ベクトル
	float m_vy;

	float m_sx ;  //画像サイズ用
	float m_sy ;
	

	float m_posture;  //姿勢

	int m_ani_time;  //アニメーションフレーム動作間隔
	int m_ani_frame; //描画フレーム

	float m_speed_power;  //スピードパワー
	float m_ani_max_time; //アニメーション動作間隔最大値

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//移動の向き制御用
	bool m_move;

	//ENEMYのHP
	int m_hp;



};