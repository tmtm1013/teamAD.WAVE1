#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "CObjBullet.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#define BULLET_SPEED (15.0f)


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBullet::CObjBullet(float x, float y)
{
	m_bx = x ;
	m_by = y ;
	
}

//イニシャライズ
void CObjBullet::Init()
{

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_bx, m_by, 16, 16, ELEMENT_WHITE, OBJ_BULLET, 1);


	m_vx = 1.0f;
	m_vy = -1.0f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	bx = 0.0f;
	by = 0.0f;
	m_bxp = 0.0f;
	
	m_sx = 16.0f;  //画像サイズBlockHit関数に渡す用
	m_sy = 16.0f;


	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	flag = true;


	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time = 0;
	m_del = false;



}

//アクション
void CObjBullet::Action()
{
	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);

	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		m_del = true;
		hit->SetInvincibility(true);
		m_vx = 0.0f;
		m_vy = 0.0f;
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

		if (m_ani == 9)
		{


			this->SetStatus(false);
			Hits::DeleteHitBox(this);


		}

		return;

	}

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_bx, &m_by, true,&m_sx,&m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	
	//マウスの位置を取得
	if (flag==true)
	{
		m_mou_bx = (float)Input::GetPosX();
		m_mou_by = (float)Input::GetPosY() ;

		bx = (m_mou_bx - m_bx)*m_vx;
		by = (m_by - m_mou_by)*m_vy;

		flag = false;
	}

	float r = 0.0f;
	r = bx * bx + by * by;
	r = sqrt(r);//r をルートを求める

	//長さが0かどうか調べる
	if (r==0.0f)
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

	//主人公期と誘導弾丸で角度をとる。
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_bxp = obj->GetVX();

	//移動ベクトルを座標に加算する
	m_bx += m_vx - m_bxp;
	m_by += m_vy;

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
	if (m_hit_up == true||m_hit_down == true|| m_hit_left == true||m_hit_right == true)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	
}

//ドロー
void CObjBullet::Draw()
{

	//描画カラー情報rgba
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

		//表示位置の設定
	dst.m_top = -16.0f + m_by;
	dst.m_left = -16.0f + m_bx;
	dst.m_right = 32.0f + m_bx;
	dst.m_bottom = 32.0f + m_by;




	//弾丸の状態で描画を変更
	if (m_del == true)
	{
		//着弾アニメーション
		Draw::Draw(23, &m_eff, &dst, c, 0.0f);
	
                                                               
	}
	else
	{

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

	
		//描画
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

	
}
