//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "CObjAngleBullet.h "

#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
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
	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time = 0;
	m_del = false;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	m_bxp = 0.0f;//主人公のベクトル値を格納するよう

	m_sx = 16.0f;
	m_sy = 16.0f;

	//blockとの衝突状態確認用
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

    //当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_ANGLE_BULLET, OBJ_ANGLE_BULLET, 1);
}

//アクション
void CObjAngleBullet::Action()
{
    //HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);



	//主人公期と誘導弾丸で角度をとる。
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_bxp = obj->GetVX();//主人公のベクトル値を持ってくる

	//移動
	m_x += m_vx * m_speed;
	m_y -= m_vy * m_speed;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_x, &m_y, true, &m_sx, &m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_del = true;
		hit->SetInvincibility(true);
	}
	if (m_del == true)
	{
		//着弾アニメーション
		//リソース着弾アニメーション位置
		RECT_F ani_src[4] =
		{
			{37, 13, 22,56},
			{37,45, 54,56},
			{37,77, 86,56},
			{37,109,118,56},
		};
		//アニメーションのコマ間隔
		if (m_ani_time > 2)
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{
			m_ani_time++;
		}
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);

		}

		return;

	}

	if (m_x < 0)
	{
		this->SetStatus(false);
	}
	if (  m_hit_up == true
		||m_hit_down == true
		||m_hit_left == true
		||m_hit_right == true)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		//Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
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
	//ブロックと当たると弾丸削除
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}

}

//ドロー
void CObjAngleBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;



	//弾丸の状態で描画を変更
	if (m_del == true)
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 32.0f + m_y;

		Draw::Draw(28, &m_eff, &dst, c, 0.0f);
		
	}
	else
	{


		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = -24.0f + m_y;
		dst.m_left = -20.0f + m_x;
		dst.m_right = 52.0f + m_x;
		dst.m_bottom = 48.0f + m_y;

		Draw::Draw(24, &src, &dst, c, 0.0f);
	}
}