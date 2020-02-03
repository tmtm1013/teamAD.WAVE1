#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemyLongdistance.h"
#include "GameL\HitBoxManager.h"



//使用するネームスペース
using namespace GameL;



//位置情報X変更用
void  CObjEnemyLongdistance::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjEnemyLongdistance::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjEnemyLongdistance::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjEnemyLongdistance::GetEY()
{


	return m_py;



}



//コンストラクタ
CObjEnemyLongdistance::CObjEnemyLongdistance(float x, float y)
{
	m_px = x;    //位置
	m_py = y;

}

//イニシャライズ
void CObjEnemyLongdistance::Init()
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


	//blockとの衝突状態用確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_hp = 30;//ENEMYのHP

	elevator_flag = true;

	m_time = 0;//弾丸用タイム


	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;



	//攻撃アニメーション
	m_attack = false;
	m_ani_frame2 = 0;
	m_ani_max_time2 = 4;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, OBJ_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjEnemyLongdistance::Action()
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
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py, 35);//オブジェ作成
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 21);


			m_attack = true;

			//敵を動かさないようにする。
			m_vx = 0;
			m_vy = 0;
		}

	}


	//攻撃アニメーションの時歩くモーションに入らない
	if (m_attack == false) {

		//ここが主人公の向きに移動する条件を書く。
		if ((m_px + block->GetScroll()) < x)//右
		{

			//主人公が移動していない時のプログラム
			m_vx += m_speed_power;
			m_posture = 1.0;
			m_ani_time += 1;



		}
		else//左
		{

			//主人公が移動していない時のプログラム
			m_vx -= m_speed_power;
			m_posture = 0.0;
			m_ani_time += 1;



		}

		//アニメーション
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;

		}
		//アニメーション
		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;

		}
	}

	//攻撃アニメーション
	if (m_attack == true) {



		m_ani_time += 1;


		if (m_ani_time > m_ani_max_time2)
		{
			m_ani_frame2 += 1;
			m_ani_time = 0;
		}


		//アニメーション
		if (m_ani_frame2 == 3)
		{
			m_ani_frame2 = 0;

			m_attack = false;
		}



	}

	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);



	//自由落下運動

	if (m_py < 300) {
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

		Audio::Start(12);
	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -= 10;

		Audio::Start(13);
	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -= 40;

		Audio::Start(14);
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
	
	
		
		//敵を動かさないようにする。
		m_vx = 0;
		m_vy = 0;

		m_del = true;//着弾エフェクト移行用フラグ

		hit->SetInvincibility(true);//判定無効




	}
	if (m_del == true)
	{
		//着弾アニメーション
		//リソース着弾アニメーション位置
		RECT_F ani_src[5] =
		{


			{0,  0,  204 ,200},
			{0, 204, 408 ,200},
			{0, 408, 612,200},
			{0, 612,816, 200},
			{0, 816,1020,200},

		};
		//アニメーションのコマ間隔
		if (m_ani_time2 > 2)
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time2 = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{

			m_ani_time2++;

		}

		if (m_ani == 5)
		{


			this->SetStatus(false);
			Hits::DeleteHitBox(this);


			//敵が消滅したら+100点
			((UserData*)Save::GetData())->m_point += 10;

			//アイテムオブジェクト作成	
			CObjItem*obju = new CObjItem(m_px, m_py);
			Objs::InsertObj(obju, OBJ_ITEM, 7);

		}




		return;

	}

}

//ドロー
void CObjEnemyLongdistance::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//歩くアニメーション情報を登録
	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5, //移動モーション

	};
	int AniDatatack[4]
	{

		0, 1, 2, 3, //攻撃モーション

	};



	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//表示位置の設定
	dst.m_top = -66.0f + m_py;
	dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 66.0f + m_py;

	if (m_attack == true) {

		if (m_del == true)
		{
			//消滅エフェクト
			Draw::Draw(21, &m_eff, &dst, c, 0.0f);
			

		}
		else
		{

			//切り取り位置の設定
			src.m_top = 133.0f;
			src.m_left = 3.0f + AniDatatack[m_ani_frame2] * 132;
			src.m_right = 132.0f + AniDatatack[m_ani_frame2] * 132;
			src.m_bottom = 264.0f;


			//描画
			Draw::Draw(14, &src, &dst, c, 0.0f);
		}
	}
	else
	{

		if (m_del == true)
		{
			//消滅エフェクト
			Draw::Draw(21, &m_eff, &dst, c, 0.0f);
			

		}
		else 
		{


			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData[m_ani_frame] * 132;
			src.m_right = 132.0f + AniData[m_ani_frame] * 132;
			src.m_bottom = 132.0f;


			//描画
			Draw::Draw(14, &src, &dst, c, 0.0f);

		}
	}
}

