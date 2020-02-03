//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "math.h"//計算用sin cos tan

#include "GameHead.h"
#include "CObjDiffusionBullet.h"

#include "UtilityModule.h"

#define M_PI 3.14f
#define B_S  6.0f

//使用するネームスペース
using namespace GameL;
//コンストラクタ
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y, float r)
{
	m_bx = x;  //敵のX軸を取得
	m_by = y;  //敵のY軸を取得
	m_r = r;  //角度を取得

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_bx, m_by, 32, 32, ELEMENT_WHITE, OBJ_DIFFUSION_BULLET, 1);

}

//イニシャライズ
void CObjDiffusionBullet::Init()
{
	//弾丸の角度を求める
	m_vx = cos(M_PI / 180.0*m_r);
	m_vy = sin(M_PI / 180.0*m_r);

	m_time = 0.0f;

	m_s = B_S;//弾丸のスピード
}

//アクション
void CObjDiffusionBullet::Action()
{

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_bx, &m_by, true, &m_bx, &m_by,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	m_time += 0.1f;

	m_bx += m_vx * m_s;//敵の位置から求めた角度にベクトル(スピード)を入れていく
	m_by += m_vy * m_s;

	//主人公期と誘導弾丸で角度をとる。
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公の座標を変数に保存する
	pl_x = obj->GetX();//主人公のX座標
	pl_y = obj->GetY();//主人公のY座標

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);

	//敵機オブジェクトと接触したら弾丸消去
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

	}
	if (m_time >= 1.0f)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
		m_time = 0.0f;
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
	

	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
}

//ドロー
void CObjDiffusionBullet::Draw()
{
	float c[4] = { 1.0f,0.0f,0.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り位置の設定
	src.m_top = 600.0f;
	src.m_left = 200.0f;
	src.m_right = 400.0f;
	src.m_bottom = 800.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_by;
	dst.m_left = -5.0f + m_bx;
	dst.m_right = 27.0f + m_bx;
	dst.m_bottom = 32.0f + m_by;
	//描画
	Draw::Draw(34, &src, &dst, c, m_r);



}
/*#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "CObjDiffusionBullet.h"
#include "GameL\HitBoxManager.h"


#define BULLET_SPEED (30.0f)

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDiffusionBullet::CObjDiffusionBullet(float x, float y)
{
	m_bx = x;
	m_by = y;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_bx, m_by, 32, 32, ELEMENT_WHITE, OBJ_DIFFUSION_BULLET, 1);

}

//イニシャライズ
void CObjDiffusionBullet::Init()
{
	m_vx = 0.1f;
	m_vy = -0.1f;

	m_time = 0.0f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	bx = 0.0f;
	by = 0.0f;

	flag = true;

}

//アクション
void CObjDiffusionBullet::Action()
{



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

	m_time += 0.1f;

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);

	//敵機オブジェクトと接触したら弾丸消去
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

	}
	if (m_time>=1.0f)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
		m_time = 0.0f;
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
}

//ドロー
void CObjDiffusionBullet::Draw()
{

	           //   R    G    B    透過
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_by;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = 32.0f + m_bx;
	dst.m_bottom = 32.0f + m_by;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);

}
*/

// m_bx += speed * cosf((90)*3.14 / 180.0f);
//m_by += speed * sinf((90)*3.14 / 180.0f);

//m_vx += speed * cos(angle / 180 * 3.14);
//m_vy += speed * sin(angle / 180 * 3.14);

//m_bx = m_vx;
//m_by = m_vy;
//if (flag == true)