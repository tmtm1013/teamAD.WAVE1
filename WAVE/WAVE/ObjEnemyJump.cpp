#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjEnemyJump.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "stdio.h" //乱数用ヘッダー
#include "stdlib.h"//乱数用ヘッダー
#include "time.h"  //乱数用ヘッダー



//使用するネームスペース
using namespace GameL;
//位置情報X変更用
void  CObjEnemyJump::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjEnemyJump::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjEnemyJump::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjEnemyJump::GetEY()
{


	return m_py;


}

//コンストラクタ
CObjEnemyJump::CObjEnemyJump(float x,float y)
{
	m_px = x;    //位置
	m_py = y;

}

//イニシャライズ
void CObjEnemyJump::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_sx = 64.0f;
	m_sy = 64.0f;


	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_time = 0;//ジャンプ用タイム

	m_move = false;//true=右

	m_rnd = 0;//ジャンプ用ランダム変数

	//ボスHP
	b_hp_max = 200;
	b_hp_now = b_hp_max;

	//攻撃アニメーション
	m_attack = false;
	m_ani_frame2 = 0;
	m_ani_max_time2 = 4;

	//消滅エフェクト
	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;


	EnemyCount++;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}


//アクション
void CObjEnemyJump::Action()
{

	//ブロックタイプ検知用の変数がないためのダミー
	int d;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);


	//乱数の種を初期化
	srand(time(NULL));
	//1～100のランダムな数値
	m_rnd = rand() % 10 + 1;

	//通常速度
	m_speed_power = 0.1f;
	m_ani_max_time = 2;

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);	
	float x = obj->GetXX();
	float y = obj->GetYY();
	

	if (m_attack == false) {
		//ここが主人公の向きに移動する条件を書く。
		if ((m_px + block->GetScroll()) < x)//右
		{
			//主人公が移動していない時のプログラム
			m_vx += m_speed_power;
			
			//アニメーション関数の呼び出し
			Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
				1, 4, 1.0f);


			if (m_hit_left == true)//左右のブロックに触れたときジャンプしてブロックを乗り越えるようにした。
				m_vy = -13;

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

			//アニメーション関数の呼び出し
			Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
				1, 4, 0.0f);


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
		

	}


	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);
	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 32 + block->GetScroll(), m_py);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_attack = true;

		//敵を動かさないようにする。
		m_vx = 0;
		m_vy = 0;

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
		if (m_ani_frame2 == 5)
		{
			m_ani_frame2 = 0;
			m_attack = false;
		}



	}
	
		

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;



	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

			b_hp_now -= 30;

			Audio::Start(12);
	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

			b_hp_now -= 10;

			Audio::Start(13);
	}

	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

			b_hp_now -= 30;


			Audio::Start(14);
	}

	//落下した敵を消去する。
	if (m_py > 600.0f)
		{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//敵が落下した場合敵を消去する。
	}

	//HPが0になったら破棄
	if (b_hp_now <= 0)
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




			//ボス消滅でシーンをステージ2に移行する
			Scene::SetScene(new CSceneBlock2());

		}

		return;

	}

}

//ドロー
void CObjEnemyJump::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//歩くアニメーション情報を登録
	int AniData[5] =
	{
		0, 1, 2, 3, 4,  //移動モーション		
	};

	//歩くアニメーション情報を登録
	int AniDataack[6] =
	{
		0, 1, 2, 3, 4, 5, //移動モーション		
	};


	   //描画カラー     R     G    B    透過 
		float c[4] = { 1.0f,0.0f,0.0f,1.0f };

		RECT_F src;//描画元切り取り位置
		RECT_F dst;//描画先表示位置


		//表示位置の設定
		dst.m_top = -66.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 66.0f + m_py;


		if (m_attack == true) {
			//弾丸の状態で描画を変更if (m_del == true)
			if (m_del == true)
			{

				Draw::Draw(21, &m_eff, &dst, c, 0.0f);
				//着弾アニメーション

			}
			else
			{


				//切り取り位置の設定
				src.m_top = 49.0f;
				src.m_left = 1.0f + AniDataack[m_ani_frame2] * 49;
				src.m_right = 47.0f + AniDataack[m_ani_frame2] * 47;
				src.m_bottom = 95.0f;

				//描画
				Draw::Draw(12, &src, &dst, c, 0.0f);
			}
		}
		else
		{

			//弾丸の状態で描画を変更if (m_del == true)
			if (m_del == true)
			{

				Draw::Draw(21, &m_eff, &dst, c, 0.0f);
				//着弾アニメーション

			}
			else
			{


				// 切り取り位置の設定
				src.m_top = 1.0f;
				src.m_left = 1.0f + AniData[m_ani_frame] * 47;
				src.m_right = 47.0f + AniData[m_ani_frame] * 47;
				src.m_bottom = 47.0f;

				//描画
				Draw::Draw(12, &src, &dst, c, 0.0f);

			}
		}


	//---------------------------------------------------------------------
		
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
int CObjEnemyJump::EnemyCount = 0;

