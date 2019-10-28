#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "ObjHero.h"
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

	
}

//イニシャライズ
void CObjBullet::Init()
{
	m_vx = 0.2f;
	m_vy = -0.2f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;


	flag = true;
	speed = 5;

}



//イニシャライズ
void CObjBullet::Action()
{
	//マウスの位置を取得
	if (flag==true)
	{
		m_mou_bx = (float)Input::GetPosX();
		m_mou_by = (float)Input::GetPosY();
		flag = false;
	}
	

	
	//m_bx += speed * cosf((90)*3.14 / 180.0f);
	//m_by += speed * sinf((90)*3.14 / 180.0f);

	//m_vx += speed * cos(angle / 180 * 3.14);
	//m_vy += speed * sin(angle / 180 * 3.14);

	//m_bx = m_vx;
	//m_by = m_vy;
	//if (flag == true)

	
		m_bx += (m_mou_bx - m_bx)*m_vx;
		m_by += (m_by - m_mou_by)*m_vy;

		
	
	

	
	


		//領域外に出たら弾丸を破棄する
		if (m_bx > 800.0f)
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
	dst.m_top    = 0.0f  + m_by;
	dst.m_left   = 0.0f  + m_bx;
	dst.m_right  = 16.0f + m_bx;
	dst.m_bottom = 16.0f + m_by;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
	
}