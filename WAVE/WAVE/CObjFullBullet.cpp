#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameL\Audio.h"

#include "GameHead.h"
#include "CObjFullBullet.h"
#include "GameL\HitBoxManager.h"


#define FULL_BULLET_SPEED (30.0f)


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFullBullet::CObjFullBullet(float x, float y)
{
	m_bx = x;
	m_by = y;


	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_bx, m_by, 16, 16, ELEMENT_WHITE, OBJ_FULL_BULLET, 1);

	Audio::LoadAudio(11, L"SEgan/FullSoundHit.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----
}

//イニシャライズ
void CObjFullBullet ::Init()
{
	m_vx = 0.1f;
	m_vy = -0.1f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	bx = 0.0f;
	by = 0.0f;

	m_sx = 16;   //サイズ用
	m_sy = 16;

	m_time = 0.0f;

	flag = true;

	//float Volume = Audio::VolumeMaster(-0.2f);

}

//アクション
void CObjFullBullet::Action()
{
	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_bx, &m_by, true, &m_sx, &m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);




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
		m_vx *= FULL_BULLET_SPEED;
		m_vy *= FULL_BULLET_SPEED;

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
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。

		//float Volume = Audio::VolumeMaster(-0.2f);
		Audio::Start(11);//SE再生(装備音)
	}
}

//ドロー
void CObjFullBullet::Draw()
{

	//描画カラー情報
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
	dst.m_right = 16.0f + m_bx;
	dst.m_bottom = 16.0f + m_by;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);

}


// m_bx += speed * cosf((90)*3.14 / 180.0f);
//m_by += speed * sinf((90)*3.14 / 180.0f);

//m_vx += speed * cos(angle / 180 * 3.14);
//m_vy += speed * sin(angle / 180 * 3.14);

//m_bx = m_vx;
//m_by = m_vy;
//if (flag == true)