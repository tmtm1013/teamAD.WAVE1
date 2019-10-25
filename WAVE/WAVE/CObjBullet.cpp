#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "CObjBullet.h"]
#include "GameL\HitBoxManager.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBullet::CObjBullet(float x, float y)
{
	m_px = x;
	m_py = y;
	

	//当たり判定用のHitBoxを作成
Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_WHITE,  OBJ_BULLET, 1);


}


//イニシャライズ
void CObjBullet::Init()
{
	m_vx = 0.0f;
}

//アクション
void CObjBullet::Action()
{
	m_vx += 1.0f;

	m_px += m_vx;

	//領域外に出たら弾丸を破棄する
	if (m_px>800.0f)
	{
		this->SetStatus(false);
	}

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

	//敵機オブジェクトと接触したら弾丸消去
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//自身に消去命令を出す。
		Hits::DeleteHitBox(this);//弾丸が所有するHitBoxに消去する。


	}

}

//ドロー
void CObjBullet::Draw()
{
	/*//歩くアニメーション情報を登録
	int AniData[4] =
	{
		1 , 0 , 2 , 0,
	};w
	*/

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top    = 64.0f;
	src.m_left   = 256.0f;
	src.m_right  = 320.0f;
	src.m_bottom = 128.0f;

	//表示位置の設定
	dst.m_top    = 0.0f  + m_py;
	dst.m_left   = 0.0f  + m_px;
	dst.m_right  = 16.0f + m_px;
	dst.m_bottom = 16.0f + m_py;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
	
}