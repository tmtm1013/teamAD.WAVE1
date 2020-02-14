#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//主人公関係初期化
#define HERO_X (300.0f)
#define HERO_Y (500.0f)
#define HERO_SPEED (0.5f)
#define HERO_GUARD (1)
#define RISET_HERO_HP (0)
#define HERO_HP (300)
#define HERO_HP_MAX (300)
#define HERO_HP_TIME (0.0f)
#define HERO_HP_TIME_INT (0.1)
#define HERO_HP_TIME_INT_G (1.6)
#define HERO_HP_SUB (30)
#define HERO_HP_SUB_ICE (20)
#define HERO_ATP_MAX (3)
#define HERO_MOVE (0.5f)
#define HERO_MOVE_SPEED_MAX (10)
#define HERO_MOVE_SPEED_MIN (-10)
#define HERO_MOVE_DUSH (0.6f)
#define HERO_MOVE_JUMP (-16.0f)
#define HERO_GUARD_DMAGE (30)
#define RISET_HERO_GUARD (1)
#define HERO_NOCK_BUCK (6.0f)
#define HERO_NOCK_BUCK_ICE (3.0f)
#define HERO_NOCK_BUCK_TIME (10.6f)
#define HERO_SET_HIT_BOX_X (8)
#define HERO_SET_HIT_BOX_Y (10)

#define SIZE_X (64.0f)
#define SIZE_Y (64.0f)

//マウス位置の初期化
#define RISET_MOU_X (0.0f)
#define RISET_MOU_Y (0.0f)
#define RISET_MOU_R (0.0f)
#define RISET_MOU_L (0.0f)

//移動ベクトル初期化
#define RISET_BEC_X (0.0f)
#define RISET_BEC_Y (0.0f)
#define RISET_POS (0.0f)

//切り取り位置初期化
#define RISET_TOP (0.0f)
#define RISET_LEFT (0.0f)
#define RISET_RIGHT (80.0f)
#define RISET_BOTTOM (96.0f)

//ジャンプ間隔管理用
#define RISET_JUMP_TIME (0.0f)

//当たり判定用
#define HIT_BOX_X (50)
#define HIT_BOX_Y (50)

//描画番号管理、SE制御、アニメーション制御
#define RISET_ANI_TIME (0)
#define RISET_ANI_TIME_MAX (4)
#define RISET_ANI_NUM (0)
#define RISET_ANI_POS (0.0f)
#define RISET_MOVE_S (0)
#define RISET_JUMP_S (0)
#define RISET_SE_TIME (0)
#define WEP_CHA_SE_TIME (12)
#define RISET_ANI_FRAME (0)
#define RISET_ANI_FRAME_WAIT (0)
#define RISET_ANI_FRAME_JUMP (0)
#define ANI_FRAME_MAX (12)
#define ANI_FRAME_JUMP (10)
#define ANI_FRAME_WAIT (9)
#define ANI_POS (1.0f)
#define ANI_MAX_TIME_JUMP (4)
#define ANI_TIME_JUMP (0)
#define ANI_TIME (1)
#define ANI_TIME_SHIFT (2)
#define ANI_MOVE_1 (3)
#define ANI_MOVE_2 (4)
#define ANI_MOVE_3 (5)

//弾丸関係
#define BULLET_ADD_X (30.0f)
#define BULLET_ADD_Y (30.0f)
#define BULLET_TIME (0.1f)
#define BULLET_INTERVAL (4.0f)
//弾丸発射間隔初期化
#define RISET_TIME (0.0f)

//ウィンドウ設定
#define WINDOW_BOTTOM (600.0f)

//音楽関係
#define RESET_AUD_TIME (0.0f) //音楽の時間初期化

//ブロックタイプ管理
#define BROCK_TYPE (0)




//シーン:主人公
class CObjHero :public CObj
{
public:CObjHero() {}
	   ~CObjHero() {};
	   void Init();   //イニシャライズ
	   void Action(); //アクション
	   void Draw();   //ドロー

	   float GetX() { return m_px; }
	   float GetY() { return m_py; }
	   float GetVY() { return m_vy; }
	   float GetVX() { return m_vx; }
	   int GetBT() { return m_block_type; }
	   float GetVK_SPACE() { return m_vy; }

	   int Get_bullet_type() { return bullet_type; }

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

	  bool guard_flag;//ガード用フラグ
	  int  guard;     //ガード用変数

	  float m_vx;    //移動ベクトル
	  float m_vy;
	  float m_posture;  //姿勢

	
	  int m_ani;//着弾アニメーション用
	  int m_ani_time2;//エフェクトアニメーション用間隔用タイム
	  bool m_del;//消去チェック
	  RECT_F m_eff;//着弾エフェクト描画用


	

	  int  m_ani_time;  //アニメーションフレーム動作間隔
	  int  m_ani_timeJump;


	  float m_speed_power;  //スピードパワー
	  float m_ani_max_time; //アニメーション動作間隔最大値
	  float m_ani_max_time_Jump;
	  int   m_ani_time_Jump;
	  int   m_ani_move;//アニメーション切り替え用

	  bool SE_flag;

	  short int movesecond; //秒間用変数	
	  short int jumpsecond; //秒間用変数
	  short int jump_time;//ジャンプ時間管理用
	  short int m_SEtime;//SEの再生頻度制御用変数
	  short int Action_ani_time;//攻撃アニメーション切り替え頻度制御
	  bool Action_ani_flag;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	bool flag;

	bool Method_flag;

	//ステータス関係
	int hp;
	int hp_max;
	int hp_now;
	float hp_time;
	int attackpoint;
	int attackpoint_max;
	float attackpoint_now;

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

	int time;
	int atari;

	int Remainingammo;

	//アニメーション用フラグ
	bool Action_Waiting;
	bool Action_Walk;
	bool Action_direction;
	bool Action_Jump;
	bool Action_guard;

	//アニメーションフレーム変数
	int  m_ani_frame;       //描画フレーム
	int m_ani_frame_Waiting;//描画フレーム
	int m_ani_frame_Jump;

};