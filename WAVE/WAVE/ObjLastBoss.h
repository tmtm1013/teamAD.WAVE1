#pragma once
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：敵
class CObjLastBoss :public CObj
{
public:
	CObjLastBoss(float x, float y);
	~CObjLastBoss() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー

private:
	float m_px;    //位置
	float m_py;
	float m_vx;    //移動ベクトル
	float m_vy;
	float m_posture;  //姿勢

	int m_ani_time;  //アニメーションフレーム動作間隔
	int m_ani_frame; //描画フレーム
	int m_time_a;

	float m_speed_power;  //スピードパワー
	float m_ani_max_time; //アニメーション動作間隔最大値

	//移動の向き制御用
	bool m_move;

	//ENEMYのHP
	int Boss_hp_max;
	int Boss_hp_now;

	//弾丸用プログラム
	int m_time;
	int m_time2;
	int m_time3;

	//マップ移動用数値
	int kazu;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//敵移動用フラグ
	bool mover;

	int m_ani_move;

	float m_rnd;


};