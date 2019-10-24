#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjHero.h"

#define GRAUND (536.0f)

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHero::Init()
{
	m_px = 0.0f;    //位置
	m_py = 0.0f;
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅

}

//アクション
void CObjHero::Action()
{
	//m_vy = 0;
	//移動ベクトルの破棄
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	//Xキー入力でジャンプ
	if (Input::GetVKey('W')==true)
	{
		if (m_py + 64.0f == GRAUND)
		{
			m_vy = -16;
		}
	}

	//Zキー入力で速度アップ
	if (Input::GetVKey('Z')==true)
	{
		//ダッシュ時の速度
		m_speed_power = 1.1f;
		m_ani_max_time = 1;
	}
	else
	{
		//通常速度
		m_speed_power = 0.5f;
		m_ani_max_time = 2;
	}


	//キーの入力方向
	if (Input::GetVKey('D')==true)
	{
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	//キーの入力方向
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame = 1; //キー入力がない場合は静止フレームにする
		m_ani_time = 0;
	}

	if (m_ani_time>m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame==4)
	{
		m_ani_frame = 0;
	}



	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	if (m_vy > 26 && m_py <= GRAUND)
	{
		m_vy = 0;
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;


	//主人公の位置X(x_px)+主人公の幅分が+X軸方向に領域外を認識
	if (m_px + 64.0f > 800.0f)
	{
		m_px = 800.0f - 64.0f;//はみ出ない位置に移動させる

	}

	if (m_py + 64.0f > GRAUND)
	{
		//m_py = 0;
		m_py = GRAUND - 64.0f;
	
	}
	
	if (m_px < 0.0f)
	{
		m_px = 0.0f;
	}
	
}

//ドロー
void CObjHero::Draw()
{
	//歩くアニメーション情報を登録
	int AniData[4] =
	{
		1 , 0 , 2 , 0,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 64.0f;
	src.m_left   = 256.0f + AniData[m_ani_frame] * 64;
	src.m_right  = 320.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 128.0f;

	//表示位置の設定
	dst.m_top    = 0.0f + m_py;
	dst.m_left   = (      64.0f * m_posture ) + m_px;
	dst.m_right  = ( 64 - 64.0f * m_posture ) + m_px;
	dst.m_bottom = 64.0f+ m_py;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

}