#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：敵
class CObjBoss :public CObj
{
public:
	CObjBoss(float x, float y);
	   ~CObjBoss() {};
	   void Init();   //イニシャライズ
	   void Action(); //アクション
	   void Draw();   //ドロー

	   float GetEX();//位置情報ｘ取得用
	   float GetEY();//位置情報Y取得用
	   void SetXX(float x);//位置情報X変更用
	   void SetYY(float y);//位置情報Y変更用


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

	int Boss_hp_max;//ENEMYのHP
	int Boss_hp_now;

	//移動の向き制御用
	bool m_move;

	//ENEMYのHP
	int m_hp;

	//弾丸用プログラム
	int m_time;
	int m_time2;
	
	//マップ移動用数値
	int kazu;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_attack;//単発攻撃アニメーションフラグ
	bool m_attack2;//範囲攻撃アニメーションフラグ
	int m_ani_frame2;//攻撃アニメーション用タイム
	float m_ani_max_time2; //アニメーション動作間隔最大値
	float m_ani_max_time3; //アニメーション動作間隔最大値
};