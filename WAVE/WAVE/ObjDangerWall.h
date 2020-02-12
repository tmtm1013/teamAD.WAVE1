
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;


//オブジェクト：敵
class CObjDangerWall :public CObj
{
public:CObjDangerWall() {};
	   ~CObjDangerWall() {};
	   void Init();   //イニシャライズ
	   void Action(); //アクション
	   void Draw();   //ドロー

	   float GetEX();//位置情報ｘ取得用
	   float GetEY();//位置情報Y取得用
	   void SetXX(float x);//位置情報X変更用
	   void SetYY(float y);//位置情報Y変更用


private:
	float m_px;    //オブジェクトの位置
	float m_py;

	float m_vx;    //移動ベクトル
	float m_vy;

	int m_ani_time;  //アニメーションフレーム動作間隔
	int m_ani_frame; //描画フレーム
	int m_ani_move;

	float m_speed_power;  //スピードパワー
	float m_ani_max_time; //アニメーション動作間隔最大値

	//移動の向き制御用
	bool m_move;

	float m_f;

	int m_ani;//着弾アニメーション用
	int m_ani_time2;//エフェクトアニメーション用間隔用タイム
	bool m_del;//消去チェック
	RECT_F m_eff;//着弾エフェクト描画用

	
};
