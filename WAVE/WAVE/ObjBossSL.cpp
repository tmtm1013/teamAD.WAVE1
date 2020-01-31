#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjBossSL.h"


#include "stdio.h" //乱数用ヘッダー
#include "stdlib.h"//乱数用ヘッダー
#include "time.h"  //乱数用ヘッダー


//使用するネームスペース
using namespace GameL;

void  CObjBossSL::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjBossSL::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjBossSL::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjBossSL::GetEY()
{


	return m_py;


}


//コンストラクタ
CObjBossSL::CObjBossSL(float x, float y)
{
	m_px = x;    //位置
	m_py = y;

}

//イニシャライズ
void CObjBossSL::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅

	m_hp = 100;//ENEMYのHP

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_move = false;//true=右


	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_ENEMY, 1);//当たり判定



}





//アクション
void CObjBossSL::Action()
{

	//乱数の種を初期化
	srand(time(NULL));
	//1〜100のランダムな数値
	m_rnd = rand() % 10 + 1;


	int d;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);



	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//通常速度
	m_speed_power = 0.01f;
	m_ani_max_time = 2;



	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//ここが主人公の向きに移動する条件を書く。
	if ((m_px + block->GetScroll()) < x)//右
	{

		//主人公が移動していない時のプログラム
		m_vx += m_speed_power;
		m_posture = 1.0;
		m_ani_time += 1;
		m_ani_move = 1;


		//左右のブロックに触れたときジャンプしてブロックを乗り越えるようにした。
		if (m_hit_left == true)
		{


			m_vy = -13;


		}



		//ランダムで決まる数値が1の時ジャンプする
		if (m_rnd == 1) {//m_rndがランダムの数値が入る変数

			if (m_hit_down == true)//敵が地面にいるときジャンプする
			{
				m_vy = -16;
			}

		}
	}
	else//左
	{

		//主人公が移動していない時のプログラム
		m_vx -= m_speed_power;
		m_posture = 0.0;
		m_ani_time += 1;
		m_ani_move = 1;

		//左右のブロックに触れたときジャンプしてブロックを乗り越えるようにした。
		if (m_hit_left == true)
		{


			m_vy = -13;


		}

		//ランダムで決まる数値が1の時ジャンプする
		if (m_rnd == 1) {//m_rndがランダムの数値が入る変数

			if (m_hit_down == true)//敵が地面にいるときジャンプする
			{
				m_vy = -16;
			}


		}

	}
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




	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);


	m_time2++;//通常遠距離攻撃に間隔をつけるためのインクリメント
	if (m_time2 > 100) {


		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム

			m_time2 = 0;
			//弾丸オブジェクト
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py,20);//オブジェ作成
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 1);
		}

	}

	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

	    b_hp_now -= 15;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		b_hp_now -= 10;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		b_hp_now -= 40;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		b_hp_now -= 50;


	}
	//HPが0になったら破棄
	if (b_hp_now <= 0)
	{

		if (((UserData*)Save::GetData())->SceneNum == 1)//マップ移動用 
		{
			((UserData*)Save::GetData())->SceneNum++; //マップ移動用
			Audio::Stop(21); //BGMストップ
			//敵消滅でシーンをゲームクリアに移行する
			Scene::SetScene(new CSceneBlock2());

		}
		else if (((UserData*)Save::GetData())->SceneNum == 2)
		{
			((UserData*)Save::GetData())->SceneNum++;
			//ボス消滅でシーンをステージ３に移行する
			Scene::SetScene(new CSceneBlock3());



		}
		else if (((UserData*)Save::GetData())->SceneNum == 3)
		{
			((UserData*)Save::GetData())->SceneNum++;
			//ボス消滅でクリア画面に移行する
			Scene::SetScene(new CSceneClear());
		}



		/*else if (kazu == 3) {
			this->SetStatus(false);
			Hits::DeleteHitBox(this);

			//敵消滅でシーンをゲームクリアに移行する
			Scene::SetScene(new CSceneClear());
		}*/


	}



}

//ドロー
void CObjBossSL::Draw()
{
	//スクロール情報取得
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//歩くアニメーション情報を登録
	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 230;
	src.m_right = 230.0f + AniData[m_ani_frame] * 230;
	src.m_bottom = 150.0f;

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	///表示位置の設定
	dst.m_top = -64.0f + m_py;
	dst.m_left = pb->GetScroll() + (m_px - 54.0f);
	dst.m_right = m_px + (132 + pb->GetScroll());
	dst.m_bottom = 68.0f + m_py;


	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);

	//------------------------------------------------------------
	//HPカバー
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0;
	src.m_bottom = 20.0f;

	//表示位置設定
	dst.m_top = 580.0f;
	dst.m_left = 40.0f;
	dst.m_right = 760.0f;
	dst.m_bottom = 595.0f;

	//描画
	Draw::Draw(28, &src, &dst, c, 0.0f);

	//ボスHPグラフィック表示
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 248.0;
	src.m_bottom = 12.0f;

	//表示位置設定
	dst.m_top = 582.0f;
	dst.m_left = 46.0f;
	dst.m_right = 751.0f * (b_hp_now / (float)b_hp_max);
	dst.m_bottom = 593.0f;

	//描画
	Draw::Draw(29, &src, &dst, c, 0.0f);

}