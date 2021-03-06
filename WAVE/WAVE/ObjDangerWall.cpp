#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjDangerWall.h"
#include "GameL\HitBoxManager.h"


//使用するネームスペース
using namespace GameL;

//位置情報X変更用
void  CObjDangerWall::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjDangerWall::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjDangerWall::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjDangerWall::GetEY()
{


	return m_py;


}

//イニシャライズ
void CObjDangerWall::Init()
{

	m_px = 0.0f;
	m_py = 0.0f;

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	
	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅
	m_ani_move = 0;

	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;


	m_ani_frame = 0;
	m_ani_max_time = 4;    //アニメーション間隔幅

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 100, 600, ELEMENT_ENEMY, OBJ_DANGER_WALL, 2);
	

}
//アクション
void CObjDangerWall::Action()
{


	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//通常速度
	m_speed_power = 1.3;
	m_ani_max_time = 2;

	m_ani_move = 1;//歩くアニメーション条件

	//主人公が移動していない時のプログラム
	m_vx += m_speed_power;
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);


	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	m_vx = 0.0f;
	m_vy = 0.0f;

}

//ドロー
void CObjDangerWall::Draw()
{
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5, //モーション
	};

	//描画カラー情報 r g b a 
	float c[4] = { 1.0f,0.0f,0.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f/* + AniData[m_ani_frame] * 100*/;
	src.m_right  = 188.0f /*+ AniData[m_ani_frame] * 100*/;
	src.m_bottom = 268.0f;
	

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (-400.0f ) + m_px + block->GetScroll();
	dst.m_right =  100+ m_px + block->GetScroll();
	dst.m_bottom = 600.0f + m_py;

	
	/*
	//表示位置の設定
	dst.m_top = -66.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = (132 - 132.0f) + m_px+ block->GetScroll();
	dst.m_bottom = 66.0f + m_py;
	*/
	//描画
	Draw::Draw(15, &src, &dst, c, 0.0f);
	
}