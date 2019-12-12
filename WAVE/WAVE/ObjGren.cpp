// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "ObjGren.h"
#include "CObjBullet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGren::CObjGren(float x, float y)
{

	m_bx = x;
	m_by = y;

	//当たり判定HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 36, 36, ELEMENT_PLAYER, OBJ_GREN, 1);



}


//イニシャライズ
void CObjGren::Init()
{
	m_vx = 0;
	m_vy = -17;

	flag = true;

	
	

}


//アクション
void CObjGren::Action()
{
	//ブロックタイプ検知用の変数がないためのダミー
	int d;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_bx, &m_by, true, &m_bx, &m_by,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);



	m_mou_bx = (float)Input::GetPosX();

	if (m_mou_bx < m_bx)
	{
		m_vx -= 0.6f;
	}
	else
	{
		m_vx += 0.6f;
	}

	//弾丸に速度つける
	m_vy += 1.0f;

	//移動ベクトルを座標に加算する

	m_bx += m_vx;
	m_by += m_vy;


	
	//自由落下運動
	//m_by += 9.8 / (16.0f);

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
	/*if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

	}*/
	
	if (m_hit_up==true|| m_hit_down == true || m_hit_left == true || m_hit_right == true)
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

	//m_vx -= 0.1f;

	//m_x += m_vx;




}


//ドロー
void CObjGren::Draw()
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
	dst.m_right = 36.0f + m_bx;
	dst.m_bottom = 36.0f + m_by;


	//描画
	Draw::Draw(8, &src, &dst, c, 0.0f);


}



