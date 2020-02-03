//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "COHomingBullet.h "

#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//位置情報X変更用
void  CObjHomingBullet::SetXX(float x)
{

	m_px = x;


}
//位置情報Y変更用
void  CObjHomingBullet::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjHomingBullet::GetBX()
{

	return m_px;


}
//位置情報Y取得用
float  CObjHomingBullet::GetBY()
{

	return m_py;

}
//コンストラクタ
CObjHomingBullet::CObjHomingBullet(float x, float y,int ani)
{

	m_x = x;
	m_y = y;

	m_aninum = ani;

}

//イニシャライズ
void CObjHomingBullet::Init()
{
	

	//距離
	leng = 0;
	m_vx = 8.0;
	m_vy = 8.0f;
	x = 0;
	y = 0;
	button = false;


	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time = 0;
	m_del = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_HOMING_BULLET, OBJ_HOMING_BULLET,  1);
}

//アクション
void CObjHomingBullet::Action()
{

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_x, &m_y, true, &m_x, &m_y,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	
	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);//作成したHitBox更新用の入り口を取り出す
	hit->SetPos(m_x, m_y);
	
	
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_del = true;
		hit->SetInvincibility(true);
	}
	if (m_del == true)
	{
		//着弾アニメーション
		//リソース着弾アニメーション位置
		RECT_F ani_src[9] =
		{
			//切り取り位置の設定
		//top left light bot
			{51,0, 50,0},
			{51,50,105,0},
			{51,105,155,0},
			{51,155,205,0},
		    {51,205,255,0},
		    {51,255,305,0},
		    {51,305,355,0},
		    {51,355,405,0},
		    {51,405,512,0},
			


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

	//主人公期と誘導弾丸で角度をとる。
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);



	//主人公機が存在する場合、誘導角度の計算をする
	if (button == false)
	{
		x = obj->GetX() - m_x;
		y = obj->GetY() - m_y;
	}

	leng = x * x + y * y;

	leng = sqrt(leng);

	m_x += (x / leng)*m_vx;
	m_y += (y / leng)*m_vy;
	button = true;



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
void CObjHomingBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;


	//表示位置の設定
	dst.m_top = -10.0f + m_y;
	dst.m_left = -8.0f + m_x;
	dst.m_right = 24.0f + m_x;
	dst.m_bottom = 22.0f + m_y;


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	Draw::Draw(m_aninum, &src, &dst, c, 0.0f);

	//弾丸の状態で描画を変更
	if (m_del == true)
	{
		float c[4] = { 1.0f,0.0f,0.0f,1.0f };
		//表示位置の設定
		dst.m_top = -12.0f + m_y;
		dst.m_left = -10.0f + m_x;
		dst.m_right = 26.0f + m_x;
		dst.m_bottom = 24.0f + m_y;

		Draw::Draw(22, &m_eff, &dst, c, 0.0f);
		//着弾アニメーション

	}


}