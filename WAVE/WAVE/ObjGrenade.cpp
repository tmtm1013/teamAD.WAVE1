//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjGrenade.h"

#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjGrenade::CObjGrenade(float x, float y)
{
	m_x = x;  //主人公のX軸を取得
	m_y = y;  //主人公のY軸を取得
}

//イニシャライズ
void CObjGrenade::Init()
{
	m_vx = 10.0;//弾丸のX軸方向の速度
	m_vy = -6.0f;//弾丸のY軸方向の速度
	x = 0;  //のX軸位置情報
	y = 0;  //のY軸位置情報

	m_sx = 16.0f;  //画像サイズBlockHit関数に渡す用
	m_sy = 16.0f;

	m_hit_up=false;
    m_hit_down=false;
	m_hit_left=false;
	m_hit_right=false;


	flag = true;

	HitCheck = false;

	button = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 64, 64, OBJ_GRENADE, OBJ_GRENADE, 1);

}

//アクション
void CObjGrenade::Action()
{
	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);


	/*
		if (m_x < 0)
		{
			this->SetStatus(false);
		}
		*/
	

	

	
	
	
	//弾丸が画面端に到達すると弾丸が跳ねかえる処理
	
	if (m_hit_up == true || m_hit_down == true  && button == false)
	{

		m_vy += -10;//弾丸のベクトルY値を反転
		button = true;

		m_hit_up = false;
		m_hit_down = false;
		m_hit_left = false;
		m_hit_right = false;
	}
	if (m_hit_left == true || m_hit_right == true && button == false)
	{

		m_vx+= -10;//弾丸のベクトルX値を反転
		button = true;

		m_hit_up = false;
		m_hit_down = false;
		m_hit_left = false;
		m_hit_right = false;
	}
	
	if (m_y < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}

	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true && button == true) {

		for (int i = 360 / 24; i <= 360; i += 360 / 24)
		{
			//弾丸オブジェクト
			CObjAngleBullet* obj_a = new CObjAngleBullet(m_x, m_y, i,5.0f);//オブジェ作成
			Objs::InsertObj(obj_a, OBJ_ANGLE_BULLET, 23);
		
		}
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	/*
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。
	}
	*/

	/*
	//CheckHit関数を呼び出して弾丸と主人公で判定を取る
	bool CheckHit(float m_x, float m_y, float pl_x, float pl_y);

	//判定結果をHitCheckに保存する
	HitCheck = CheckHit(m_x, m_y, pl_x, pl_y);

	//判定結果が真なら弾丸を削除する
	if (HitCheck == true)
	{
		this->SetStatus(false);//オブジェクトを破棄する
	}
	*/	//ブロックとの当たり判定
	CObjBlock* pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_x, &m_y, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	
		//弾の移動ベクトルm_vx,m_vy
	m_x += m_vx;
	m_y += m_vy;

	//自由落下運動
	m_vy += 9.8 / (16.0f);
}

//ドロー
void CObjGrenade::Draw()
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
	dst.m_right = 32.0f + m_x;
	dst.m_bottom = 32.0f + m_y;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
}