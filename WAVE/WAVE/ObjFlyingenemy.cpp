#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjFlyingenemy.h"
#include "GameL\HitBoxManager.h"



//使用するネームスペース
using namespace GameL;



//位置情報X変更用
void  CObjFlyingenemy::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjFlyingenemy::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjFlyingenemy::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjFlyingenemy::GetEY()
{


	return m_py;



}



//コンストラクタ
CObjFlyingenemy::CObjFlyingenemy(float x, float y)
{
	m_px = x;    //位置
	m_py = y;

}

//イニシャライズ
void CObjFlyingenemy::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f


	m_sx = 64;  //画像サイズをBlockHitに渡す用
	m_sy = 64;

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.3f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅
	m_ani_move = 0;

	//blockとの衝突状態用確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_hp = 30;//ENEMYのHP

	elevator_flag = true;

	m_time = 0;//弾丸用タイム

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, OBJ_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjFlyingenemy::Action()
{

	//通常速度
	m_speed_power = 0.1f;
	m_ani_max_time = 2;


	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();



	m_time++;//弾丸発射用タイムインクリメント



	//弾丸用プログラム
	if (m_time > 100)
	{
		//if (!(x + 150.0f > m_px + (block->GetScroll()) && x - 200.0f < m_px + (block->GetScroll()))) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム
		{
			m_time = 0;

			//弾丸オブジェクト
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py);//オブジェ作成
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 10);

			m_ani_move = 1;



		}

	}

	

	//ここが主人公の向きに移動する条件を書く。
	if ((m_px + block->GetScroll()) < x)//右
	{

		//主人公が移動していない時のプログラム
		m_vx += m_speed_power;
		m_posture = 1.0;
		m_ani_time += 1;
		m_ani_move = 1;


	}
	else//左
	{

		//主人公が移動していない時のプログラム
		m_vx -= m_speed_power;
		m_posture = 0.0;
		m_ani_time += 1;
		m_ani_move = 1;


	}
	
	//アニメーション
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
		m_ani_move = 1;
	}
	//アニメーション
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
		m_ani_move = 1;
	}



	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);



	//自由落下運動
	
	if (m_py<300) {
	    m_vy += 0.1 / (2.0f);
	}
	if (m_py > 300)
	{
		m_vy -= 0.1 / (2.0f);
	}
	


	//ブロックタイプ検知用の変数がないためのダミー
	int d;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);
	

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;



	if (m_px < 0.0f)
	{
		m_px = 0.0f;
	}


	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 32 + block->GetScroll(), m_py);



	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		m_hp -= 15;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -= 10;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -= 40;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -= 50;


	}
	
	//落下した敵を消去する。
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//敵が落下した場合敵を消去する。
	}
	
	//HPが0になったら破棄
	if (m_hp <= 0)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);


		
		
			//アイテムオブジェクト作成	
			CObjItem*obju = new CObjItem(m_px, m_py);
			Objs::InsertObj(obju, OBJ_ITEM, 7);
			
		



		//敵が消滅したら+100点
		((UserData*)Save::GetData())->m_point += 100;

	}


}

//ドロー
void CObjFlyingenemy::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//歩くアニメーション情報を登録
	int AniData[2][6] =
	{
		0, 1, 2, 3, 4, 5, //移動モーション
		0, 1, 2, 3, //攻撃モーション
	};

	if (m_ani_move = 0)
	{

		//描画カラー情報
		float c[4] = { 0.0f,0.0f,5.0f,1.0f };

		RECT_F src;//描画元切り取り位置
		RECT_F dst;//描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_bottom = 132.0f;

		//表示位置の設定
		dst.m_top = 132.0f + m_py;
		dst.m_left = (-132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;

		//描画
		Draw::Draw(14, &src, &dst, c, 0.0f);

	}

	if (m_ani_move = 1)
	{
		//描画カラー情報
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//描画元切り取り位置
		RECT_F dst;//描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f + (132 - 132 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_bottom = 132.0f;

		//表示位置の設定
		dst.m_top = -66.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 66.0f + m_py;


		//描画
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
}

