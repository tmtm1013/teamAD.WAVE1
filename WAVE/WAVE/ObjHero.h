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
		   int GetBT() { return m_block_type; }
		   float GetVK_SPACE() { return m_vy; };

		   void SetX(float x) { m_px = x; }
		   void SetY(float y) { m_py = y; }
		   void SetVY(float vy) { m_vy = vy; }
		   void SetVX(float vx) { m_vx = vx; }
		   void SetBT(int t) { m_block_type = t; }

		   void SetUp(bool b) { m_hit_up = b; }
		   void SetDown(bool b) { m_hit_down = b; }
		   void SetLeft(bool b) { m_hit_left = b; }
		   void SetRight(bool b) { m_hit_right = b; }

		   float m_mou_px; //マウスの位置X
		   float m_mou_py; //マウスの位置Y


		   void SetXX(float x);//位置情報X変更用
		   void SetYY(float y);//位置情報Y変更用
		   float GetXX();//位置情報ｘ取得用
		   float GetYY();//位置情報Y取得用

	private:
		float m_px;    //位置
		float m_py;
		float m_sx;   //サイズ用
		float m_sy;

		bool m_mou_pr; //マウスの右ボタン
		bool m_mou_pl; //マウス左ボタン

		bool  m_f;     //弾丸発射制御用
		bool  m_gf;     //グレネード発射用フラグ
		float m_time;  //弾丸発射可能頻度制御
		int bullet_type;//弾丸の種類

		float m_vx;    //移動ベクトル
		float m_vy;
		float m_posture;  //姿勢

		int  m_ani_time;  //アニメーションフレーム動作間隔
		int  m_ani_timeJump;
		int  m_ani_frame; //描画フレーム

		float m_speed_power;  //スピードパワー
		float m_ani_max_time; //アニメーション動作間隔最大値
		int   m_ani_move;//アニメーション切り替え用
		
		bool SE_flag;

		short int movesecond; //秒間用変数	
		short int jumpsecond; //秒間用変数
		short int m_SEtime;//SEの再生頻度制御用変数

		//blockとの衝突状態確認用
		bool m_hit_up ;
		bool m_hit_down;
		bool m_hit_left ;
		bool m_hit_right ;
		bool flag;

		int hp;
		int hp_max;
		int hp_now;
		float hp_time;

		float top;//切り取り位置格納用変数
		float left;
		float right;
		float bottom;
		int   ani_num;//描画番号管理用

		int i = 0;
		
		float  m_x;       //弾丸のX方向の位置用変数
		float  m_y;       //弾丸のY方向の位置用変数

		//踏んでいるblockの種類を確認用
		int m_block_type;

};