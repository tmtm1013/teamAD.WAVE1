#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjSlime.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "stdio.h" //乱数用ヘッダー
#include "stdlib.h"//乱数用ヘッダー
#include "time.h"  //乱数用ヘッダー



//使用するネームスペース
using namespace GameL;
//位置情報X変更用
void  CObjSlime::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjSlime::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjSlime::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjSlime::GetEY()
{


	return m_py;


}

//コンストラクタ
CObjSlime::CObjSlime(float x, float y)
{
	m_px = x;    //位置
	m_py = y;

}

//イニシャライズ
void CObjSlime::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_sx = 64.0f;
	m_sy = 64.0f;


	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.1f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_time = 0;//ジャンプ用タイム

	m_move = false;//true=右

	m_rnd = 0;//ジャンプ用ランダム変数

	//HP
	m_hp = 100;

	//攻撃アニメーション
	m_attack = false;
	m_ani_frame2 = 0;
	m_ani_max_time2 = 4;


	//消滅エフェクト
	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;



	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 48, 48, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}


//アクション
void CObjSlime::Action()
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
			m_posture = 1.0;
			m_ani_time += 1;


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
			m_posture = 0.0;
			m_ani_time += 1;


			//左右のブロックに触れたときジャンプしてブロックを乗り越えるようにした。
			if (m_hit_right == true)
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


	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);
	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px  + block->GetScroll(), m_py + 12);

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

		m_hp -= 30;


		Audio::Start(14);
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


		}

		return;

	}

}

//ドロー
void CObjSlime::Draw()
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
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (50.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (50 - 50.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 73.0f + m_py;


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
			src.m_top = 48.0f;
			src.m_left = 0.0f + AniDataack[m_ani_frame2] * 48;
			src.m_right = 48.0f + AniDataack[m_ani_frame2] * 48;
			src.m_bottom = 96.0f;

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
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData[m_ani_frame] * 48;
			src.m_right = 48.0f + AniData[m_ani_frame] * 48;
			src.m_bottom = 48.0f;

			//描画
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
	}
}