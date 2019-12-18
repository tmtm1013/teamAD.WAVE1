//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "math.h"

#include "GameHead.h"
#include "ObjRevolutionBullet.h"

#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjRevolutionBullet::CObjRevolutionBullet(float x, float y)
{
	m_x = x;  //主人公のX軸を取得
	m_y = y;  //主人公のY軸を取得
}

//イニシャライズ
void CObjRevolutionBullet::Init()
{
	m_vx = 2.0f;//弾丸のX軸方向の速度
	//m_vy = 0.0f;//弾丸のY軸方向の速度
	x = 0;  //主人公のX軸位置情報
	y = 0;  //主人公のY軸位置情報


	Cx=0;//円の中心の座標
	Cy=0;
	Angle = 0;  //円の動きの角度
	R = 30;   //円の動きの半径

	pos = 0;

	flag = true;

	button = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 16, 16, ELEMENT_WHITE, OBJ_REVOLUTION_BULLET, 1);

}

//アクション
void CObjRevolutionBullet::Action()
{
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	// 位置の計算
	Angle += 20;
	x = Cx + (cos(Angle)*R );
	y = Cy + (sin(Angle)*R );
	
	if (button == false)
	{
		//主人公の位置情報をここで取得
		CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
		
		float ex = obj->GetXX();

		//ノックバックプログラム
		if (m_x + block->GetScroll() > ex + block->GetScroll())
		{
			pos = -1;
		}
		else //(m_px < ex)
		{
			pos = 1;
		}
		//float x = obj->GetXX();
		//float y = obj->GetYY();
        button = true;
		
	}
	m_x += m_vx * pos;

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + x, m_y + y);
	
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
void CObjRevolutionBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;


	//表示位置の設定
	dst.m_top = 0.0f +m_y+ y;
	dst.m_left = 0.0f +m_x+ x;
	dst.m_right = 32.0f +m_x+x;
	dst.m_bottom = 32.0f +m_y+ y;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);

}