#pragma once
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：スライム
class CObjSlime :public CObj
{
public:CObjSlime(float x, float y);
	   ~CObjSlime() {};
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
	int m_ani_move; //モーション番号

	float m_speed_power;  //スピードパワー
	float m_ani_max_time; //アニメーション動作間隔最大値

	float m_hp;

	//移動の向き制御用
	bool m_move;

	int m_time;//ジャンプ用タイム

	int m_rnd;//ジャンプ用ランダム変数

		//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;


	float m_sx;  //画像サイズ保管用変数
	float m_sy;

	bool m_attack;//攻撃アニメーションフラグ
	int m_ani_frame2;//攻撃アニメーション用タイム
	float m_ani_max_time2; //アニメーション動作間隔最大値


	int m_ani;//着弾アニメーション用
	int m_ani_time2;//エフェクトアニメーション用間隔用タイム
	bool m_del;//消去チェック
	RECT_F m_eff;//着弾エフェクト描画用

};