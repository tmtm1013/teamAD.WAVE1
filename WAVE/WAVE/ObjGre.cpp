#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#include "GameHead.h"

using namespace GameL;

//コンストラクタ
CObjGre::CObjGre(float x, float y)
{
	m_x = x;
	m_y = y;

	Hits::SetHitBox(this, m_x, m_y, 30, 30, ELEMENT_PLAYER, OBJ_GRE, 1);
}

//イニシャライズ
void CObjGre::Init()
{
	x = 0;
	y = 0;

	m_vx = 2.0f;
	m_vy = 0.2;

}

//アクション
void CObjGre::Action()
{
	if (m_x < 0)
	{
		this->SetStatus(false);
	}
	
	m_x += m_vx;
	m_y += m_vy;

	m_vy += 0.1f;

	m_vx += -1.0f;

	m_x += m_vx;


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
		}
		else
		{
			m_ani_time++;
		}

		/*
		//着弾アニメーション終了で本当にオブジェクトの破棄
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}*/

	}



	


}

//ドロー
void CObjGre::Draw()
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
	Draw::Draw(6, &src, &dst, c, 0.0f);
}