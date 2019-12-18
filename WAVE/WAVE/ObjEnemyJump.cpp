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

	m_speed_power = 0.1f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_hp = 100;//ENEMYのHP

	m_time = 0;//ジャンプ用タイム

	m_move = false;//true=右

	m_rnd = 0;//ジャンプ用ランダム変数

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

	//ここが主人公の向きに移動する条件を書く。
	if ((m_px + block->GetScroll()) < x)//右
	{
		//主人公が移動していない時のプログラム
		m_vx += m_speed_power;
		m_posture = 1.0;
		m_ani_time += 1;
		m_ani_move = 1;

		if (m_hit_left == true )//左右のブロックに触れたときジャンプしてブロックを乗り越えるようにした。
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

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 32 + block->GetScroll(), m_py);
		

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
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

			m_hp -= 1;


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

			//敵が消滅したら+100点
			((UserData*)Save::GetData())->m_point += 100;

		//敵消滅でシーンをゲームクリアに移行する
		Scene::SetScene(new CSceneBlock2());

	}

	
}

//ドロー
void CObjEnemyJump::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//歩くアニメーション情報を登録
	int AniData[2][6] =
	{
		0, 1, 2, 3, 4, 5, //移動モーション
		0, 1, 2, 3, 4, 5, //攻撃モーション
	};

	if (m_ani_move == 0)
	{

		//描画カラー情報
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//描画元切り取り位置
		RECT_F dst;//描画先表示位置

			//切り取り位置の設定
		src.m_top = 0.0f + (48 - 48 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_right = 48.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_bottom = 48.0f;
		//表示位置の設定
		dst.m_top = 132.0f + m_py;
		dst.m_left = (-132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;

		//描画
		Draw::Draw(12, &src, &dst, c, 0.0f);

	}

	if (m_ani_move == 1)
	{
	   //描画カラー     R     G    B    透過 
		float c[4] = { 1.0f,0.0f,.0f,1.0f };

		RECT_F src;//描画元切り取り位置
		RECT_F dst;//描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f + (48 - 48 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_right = 48.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_bottom = 48.0f;

		//表示位置の設定
		dst.m_top = -66.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 66.0f + m_py;


		//描画
		Draw::Draw(12, &src, &dst, c, 0.0f);
	}
}
int CObjEnemyJump::EnemyCount = 0;

