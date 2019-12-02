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

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGrenade::CObjGrenade(float x, float y)
{

	m_bx = x;
	m_by = y;

	m_x = x;
	m_y = 2.0f;
	
	//当たり判定HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 60, 60, ELEMENT_PLAYER, OBJ_GRENADE, 1);


	
}


//イニシャライズ
void CObjGrenade::Init()
{
	m_vx = 0.1f;
	m_vy = -0.1f;

	m_sx = 60;
	m_sy = 60;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	//bx = 0.0f;
	//by = 0.0f;

	flag = true;
	i = 0;
}


//アクション
void CObjGrenade::Action()
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
	m_vx *= 7.0f;
	m_vy *= 7.0f;


	
	
	//移動ベクトルを座標に加算する

	m_bx += m_vx;
	m_by += m_vy;

	//自由落下運動
	m_y += 9.8 / (16.0f);

	/*
	i++;
	//自由落下運動
	m_vy += 9.8 *i;
	*/
	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);


	//敵機オブジェクトと接触したら弾丸消去
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

	}
	//ブロックに接触したら弾丸削除
	if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
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

	//弾丸実行処理　-----
	/*m_vx += -1.0f;

	m_x += m_vx;

	*/
	
	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_x, &m_y, true, &m_sx, &m_sy, 
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	



	//当たり判定を行うオブジェクト情報部
	/*int data_base[2] =
	{
		OBJ_BLOCK,
		OBJ_ENEMY,
	};
	*/
	



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
	dst.m_right = 60.0f + m_bx;
	dst.m_bottom = 60.0f + m_by;


	//描画
	Draw::Draw(8, &src, &dst, c, 0.0f);


}



