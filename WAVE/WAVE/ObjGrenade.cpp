// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "ObjGrenade.h"
#include "CObjBullet.h"

#define GRAND (546.0f)

#define BULLET_SPEED (7.0f)

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGrenade::CObjGrenade(float x, float y)
{

	m_bx = x;
	m_by = y;
	
	//当たり判定HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 30, 30, ELEMENT_PLAYER, OBJ_GRENADE, 1);



}


//イニシャライズ
void CObjGrenade::Init()
{
	m_vx = 0.1f;
	m_vy = -0.1f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	bx = 0.0f;
	by = 0.0f;

	flag = true;


	x = 0;
	y = 0;
	
	vx = 4;
	vy = 4;

	m_vv = 0.0;

	
}


//アクション
void CObjGrenade::Action()
{
	/*
	x += m_vx;
	y += m_vy;

	vy += 1.0f;
	*/

	//マウスの位置を取得
	if (flag == true)
	{

		m_mou_bx = (float)Input::GetPosX();
		m_mou_by = (float)Input::GetPosY();

		bx = (m_mou_bx - m_bx)*m_vx;
		by = (m_by - m_mou_by)*m_vy;

		flag = false;

	}

	float r = 0.0f;
	r = bx * bx + by * by;
	r = sqrt(r);//r をルートを求める

	//長さが0かどうか調べる
	if (r == 0.0f)
	{
		;//0なら何もしない
	}
	else
	{
		//正規化を行う
		m_vx = 1.0f / r * bx;
		m_vy = 1.0f / r * by;
	}
	

	//弾丸に速度つける
	m_vx *= BULLET_SPEED;
	m_vy *= BULLET_SPEED;
	
	//移動ベクトルを座標に加算する

	m_bx += m_vx;
	m_by += m_vy;


	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);


	//敵機オブジェクトと接触したら弾丸消去
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

	}
	//領域外に出たら弾丸を破棄する
	if (m_bx > 800.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	if (m_bx < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	if (m_by < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	if (m_by > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}

	//摩擦の計算   -(運動energy X 摩擦係数)
	vx += -(vx*0.09);

	/*

	//自由落下運動
	vy += 9.8 / (16.0f);
	if (vy > 26 && m_by <= GRAND)
	{
		vy += 1.0f;
	}
	*/

	//弾丸消滅処理　-----
	if (m_del == true)
	{
		//アニメーションRECT情報
		RECT_F ani_src[4] =
		{
			{32, 0, 32,64},
			{32,32, 64,64},
			{32,64, 96,64},
			{32,96,128,64},
		};

		

		//弾丸消滅処理　-----
		if (m_ani_time > 2)
		{
			m_ani++;          //アニメーションのコマを1つ進める
			m_ani_time = 0;

			//m_eff = ani_src[m_ani];//アニメーションRECT配列からm_ani番目のRECT情報取得
		}
		else
		{
			m_ani_time++;
		}

		//着弾アニメーション終了で本当にオブジェクトの破棄
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}


		return;//消滅処理は、ここでアクションメソッドを終了させる
	}


	//弾丸実行処理　-----
	/*m_vx += -1.0f;

	m_x += m_vx;

	*/
	

	//当たり判定を行うオブジェクト情報部
	int data_base[2] =
	{
		OBJ_BLOCK,
		OBJ_ENEMY,
	};

	//オブジェクト情報部と当たり判定行い。当たっていれば削除する。
	for (int i = 0; i < 6; i++)
	{
		if (hit->CheckObjNameHit(data_base[i]) != nullptr)
		{
			//着弾音を鳴らす
			//Audio::Start(3);

			m_del = true;				//消滅実行
			hit->SetInvincibility(true);//当たり判定無効

		}
	}



}


//ドロー
void CObjGrenade::Draw()
{

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;




	dst.m_top = 0.0f + m_by;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = 30.0f + m_bx;
	dst.m_bottom = 30.0f + m_by;


	//描画
	Draw::Draw(10, &src, &dst, c, 0.0f);


}



