#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:主人公
class CObjHero :public CObj
{
	public:CObjHero(){}
	       ~CObjHero() {};
		   void Init();   //イニシャライズ
		   void Action(); //アクション
		   void Draw();   //ドロー

		   float GetX() { return m_px; }
		   float GetY() { return m_py; }
		   float GetVY() { return m_vy; }
		   float GetVX() { return m_vx; }
		   float GetVK_SPACE() { return m_vy; };

		   void SetX(float x) { m_px = x; }
		   void SetY(float y) { m_py = y; }
		   void SetVY(float vy) { m_vy = vy; }
		   void SetVX(float vx) { m_vx = vx; }
		   
		   void SetUp(bool b) { m_hit_up = b; }
		   void SetDown(bool b) { m_hit_down = b; }
		   void SetLeft(bool b) { m_hit_left = b; }
		   void SetRight(bool b) { m_hit_right = b; }

		  
		   

		  


		   float m_mou_px; //マウスの位置X
		   float m_mou_py; //マウスの位置Y

	private:
		float m_px;    //位置
		float m_py;

		bool m_mou_pr; //マウスの右ボタン
		bool m_mou_pl; //マウス左ボタン

		bool  m_f;     //弾丸発射制御用

		float m_vx;    //移動ベクトル
		float m_vy;
		float m_posture;  //姿勢

		int m_ani_time;  //アニメーションフレーム動作間隔
		int m_ani_frame; //描画フレーム

		float m_speed_power;  //スピードパワー
		float m_ani_max_time; //アニメーション動作間隔最大値

		int m_hp;//主人公のHP

		//blockとの衝突状態確認用
		bool m_hit_up ;
		bool m_hit_down;
		bool m_hit_left ;
		bool m_hit_right ;

		int hp;
		int hp_max;
		int hp_now;

		

};