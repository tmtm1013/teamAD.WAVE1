#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"

#include "ObjBoss.h"
#define GRAUND (546.0f)

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBoss::CObjBoss(float x, float y)
{
	m_px = x;    //位置
	m_py = y;

}

//イニシャライズ
void CObjBoss::Init()
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

	m_time = 0;//拡散弾用変数
	m_time2 = 0;//普通遠距離攻撃用変数


	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_ENEMY, 1);//当たり判定



}





//アクション
void CObjBoss::Action()
{


	//通常速度
	m_speed_power = 0.01f;
	m_ani_max_time = 2;

	

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
	
	/*
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	*/

		m_vx -= m_speed_power;//右から左にゆっくり進んでいく
		m_posture = 0.0f;
		m_ani_time += 1;
	


	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}



	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	if (m_vy > 26 && m_py <= GRAUND)
	{
		m_vy = 0;
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px+block->GetScroll(), m_py);



	//BOSSの周り20°間隔で発射
	m_time++;//弾丸発射間隔をあけるインクリメント
	if (m_time>300)//50の間隔で拡散弾攻撃をする
	{
		
		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム

			//19発同時発射
			CObjAngleBullet*obj_b;
			for (int i = 01; i < 360; i += 20)
			{
				m_time = 0;
				//弾丸オブジェクト
				CObjAngleBullet* obj_b = new CObjAngleBullet(m_px + block->GetScroll(), m_py, i, 5.0f);//オブジェ作成
				Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 1);


			}
		}
	}
	
	m_time2++;//通常遠距離攻撃に間隔をつけるためのインクリメント
	if (m_time2>100) {


		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//主人公が敵の近くに来た時遠距離攻撃をしなくするプログラム

			m_time2 = 0;
			//弾丸オブジェクト
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py);//オブジェ作成
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 1);
		}

	}
	
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
	//HPが0になったら破棄
	if (m_hp <= 0)
	{

		if (((UserData*)Save::GetData())->SceneNum == 1)//マップ移動用 
		{
			((UserData*)Save::GetData())->SceneNum++; //マップ移動用
			//敵消滅でシーンをゲームクリアに移行する
			Scene::SetScene(new CSceneBlock2());
		}
		else if (((UserData*)Save::GetData())->SceneNum == 2) 
		{
			((UserData*)Save::GetData())->SceneNum++;
			//敵消滅でシーンをゲームクリアに移行する
	    	Scene::SetScene(new CSceneBlock3());



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
void CObjBoss::Draw()
{
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

	
	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f * m_posture) + m_px + pb->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_px + pb->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);

}