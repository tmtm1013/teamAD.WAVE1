
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：敵
class CObjEnemy :public CObj
{
public:CObjEnemy(float x,float y) ;
	   ~CObjEnemy() {};
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
	int m_ani_move;

	float m_speed_power;  //スピードパワー
	float m_ani_max_time; //アニメーション動作間隔最大値

	//移動の向き制御用
	bool m_move;

	//アイテムフラグ
	bool flag;


	//ENEMYのHP
	int m_hp;


	float m_f;

};