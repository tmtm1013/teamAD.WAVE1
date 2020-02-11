#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "UtilityModule.h"

#include "GameL\UserData.h"
//#include "Graf.h"

#include "ObjLastBoss.h"

#include "stdio.h" //乱数用ヘッダー
#include "stdlib.h"//乱数用ヘッダー
#include "time.h"  //乱数用ヘッダー
#define GRAUND (546.0f)

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLastBoss::CObjLastBoss(float x, float y)
{
	m_px = x;    //位置
	m_py = y;

}
//イニシャライズ
void CObjLastBoss::Init()
{
	Audio::LoadAudio(0, L"SEgan/Honoo.wav", SOUND_TYPE::EFFECT);





	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする
	m_time_a = 0;

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 10;    //アニメーション間隔幅

	Boss_hp_max = 2000;//ENEMYのHP
	Boss_hp_now = Boss_hp_max;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_move = false;//true=右

	m_rnd = 0;

	m_ani_move = 0;

	m_time = 0;//拡散弾用変数
	m_time2 = 0;//普通遠距離攻撃用変数
	m_time3 = 0;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 500, 315, ELEMENT_GREEN, OBJ_ENEMY, 1);//当たり判定

}





//アクション
void CObjLastBoss::Action()
{
	int d;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	
	//通常速度
	m_speed_power = 0.14f;

	//乱数の種を初期化
	srand(time(NULL));
	//1～100のランダムな数値
	m_rnd = rand() % 10 + 1;



	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//ここに敵が主人公の向きに移動する条件を書く。
	if (x <= m_px)//右
	{
		m_move = true;
	}
	if (x >= m_px)//左
	{
		m_move = false;
	}




	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);

	//自由落下運動
	//m_vy += 9.8 / (16.0f);

	
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px - 150.0 + block->GetScroll(), m_py - 250);

	m_time3++;
	if (m_time3 > 200)
	{
		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム


			for (int i = 1; i < 360; i += 20)
			{

				m_time3 = 0;
				//弾丸オブジェクト
				CObjRevolutionBullet* obj_r = new CObjRevolutionBullet(m_px+100 + block->GetScroll(), m_py);//オブジェ作成
				Objs::InsertObj(obj_r, OBJ_HOMING_BULLET,24);

				Audio::Start(0);
			}
		}
	}

	//BOSSの周り20°間隔で発射
	m_time++;//弾丸発射間隔をあけるインクリメント
	if (m_time > 300)//50の間隔で拡散弾攻撃をする
	{

		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム

			//19発同時発射
			CObjAngleBullet*obj_b;
			for (int i = 01; i < 360; i += 20)
			{
				m_time = 0;
				//弾丸オブジェクト
				CObjAngleBullet* obj_a = new CObjAngleBullet(m_px + block->GetScroll(), m_py, i, 5.0f);//オブジェ作成
				Objs::InsertObj(obj_a, OBJ_HOMING_BULLET, 23);
				Audio::Start(0);

			}
		}
	}

	m_time2++;//通常遠距離攻撃に間隔をつけるためのインクリメント
	if (m_time2 > 100) {


		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム

			m_time2 = 0;
			//弾丸オブジェクト
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py, 20);//オブジェ作成
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 20);
			Audio::Start(0);


		}


	}

	//ここが主人公の向きに移動する条件を書く。
	if ((m_px + block->GetScroll()) < x)//右
	{
		//主人公が移動していない時のプログラム
		m_vx += m_speed_power;

		//アニメーション動作間隔
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			1, 2, 1.0f);
		
		m_ani_move = 1;

		//ランダムで決まる数値が1の時ジャンプする
		if (m_rnd == 1) {//m_rndがランダムの数値が入る変数

			if (m_hit_down == true)//敵が地面にいるときジャンプする
				m_vy = -16;
		}

	}
	else//左
	{

		//主人公が移動していない時のプログラム
		m_vx -= m_speed_power;

		//アニメーション動作間隔
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			1, 2, 0.0f);

		m_ani_move = 1;

		//ランダムで決まる数値が1の時ジャンプする
		if (m_rnd == 1) {//m_rndがランダムの数値が入る変数

			if (m_hit_down == true)//敵が地面にいるときジャンプする
			{
				m_vy = -16;
			}


		}

	}
	


	//位置の更新
	m_px += m_vx;
	m_py += m_vy;





	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		Boss_hp_now -= 30;

		Audio::Start(12);
	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		Boss_hp_now -= 10;

		Audio::Start(13);
	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		Boss_hp_now -= 40;

		Audio::Start(14);
	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		Boss_hp_now -= 10;


	}
	//HPが0になったら破棄
	if (Boss_hp_now <= 0)
	{

		//ボス消滅でシーンをクリア画面に移行する
		Scene::SetScene(new CSceneClear());

		//Audio::Stop(24);//音楽ストップ

	}



}

//ドロー
void CObjLastBoss::Draw()
{
	//スクロール情報取得
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//歩くアニメーション情報を登録
	int AniData[2] =
	{
		0, 1, 
	};
	

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 512;
	src.m_right = 512.0f + AniData[m_ani_frame] * 512;
	src.m_bottom = 512.0f;

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	dst.m_top = -290.0f + m_py;
	dst.m_left = (-200 + 600.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (400 - 600.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 70.0f + m_py;

	/*
	//表示位置の設定
	dst.m_top = -64.0f + m_py;
	dst.m_left = pb->GetScroll() + (m_px - 54.0f);
	dst.m_right = m_px + (132 + pb->GetScroll());
	dst.m_bottom = 68.0f + m_py;
	*/

	//描画
	Draw::Draw(31, &src, &dst, c, 0.0f);

	//-------------------------------------------------------------------------------------
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
	dst.m_right = 751.0f * (Boss_hp_now / (float)Boss_hp_max);
	dst.m_bottom = 593.0f;

	//描画
	Draw::Draw(29, &src, &dst, c, 0.0f);
	
}