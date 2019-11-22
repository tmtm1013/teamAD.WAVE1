//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "CObjAngleBullet.h "

#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjAngleBullet::CObjAngleBullet(float x, float y,float r,float speed)
{
	m_x = x;
	m_y = y;
	m_r = r;
	m_speed = speed;
}

//イニシャライズ
void CObjAngleBullet::Init()
{
	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);

		//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_ANGLE_BULLET, OBJ_HOMING_BULLET, 1);
}

//アクション
void CObjAngleBullet::Action()
{
	//移動
	m_x += m_vx * m_speed;
	m_y -= m_vy * m_speed;



	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

	if (m_x < 0)
	{
		this->SetStatus(false);
	}

	

	//敵機オブジェクトと接触したら弾丸消去
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

	}
	//領域外に出たら弾丸を破棄する
	if (m_x > 800.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	if (m_x < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	if (m_y < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	if (m_y > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}

}

//ドロー
void CObjAngleBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 126.0f;
	src.m_right = 96.0f;
	src.m_bottom = 32.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = 16.0f + m_x;
	dst.m_bottom = 16.0f + m_y;

	Draw::Draw(4, &src, &dst, c, m_r);
}