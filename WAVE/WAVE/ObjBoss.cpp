#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//#include "Graf.h"

#include "ObjBoss.h"


//使用するネームスペース
using namespace GameL;


void  CObjBoss::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjBoss::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjBoss::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjBoss::GetEY()
{


	return m_py;


}

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
	m_time_a = 0;

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 4;    //アニメーション間隔幅

	m_hp = 300;//ENEMYのHP

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_move = false;//true=右

	m_time = 0;//拡散弾用変数
	m_time2 = 0;//普通遠距離攻撃用変数


	//攻撃アニメーション
	m_attack = false;
	m_ani_frame2 = 0;
	m_ani_max_time2 = 4;
	m_ani_max_time3 = 6;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 380, 200, ELEMENT_GREEN, OBJ_ENEMY, 1);//当たり判定



}





//アクション
void CObjBoss::Action()
{
	//アニメーション動作タイム
	m_time_a++;

	int d;

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);


	//通常速度
	m_speed_power = 0.04f;
	m_ani_max_time = 2;

	//敵を動かさないようにする。
	m_vx = 0;
	m_vy = 0;

	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();
	
	/*
	//ここに敵が主人公の向きに移動する条件を書く。
	if (x <= m_px)//右
	{

		m_move = true;



	}
	if (x >= m_px)//左
	{


		m_move = false;



	}
	*/
	/*
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	*/

	m_vx -= m_speed_power;//右から左にゆっくり進んでいく
	m_posture = 0.0f;


	//攻撃アニメーションの時歩くモーションに入らない
	if (m_attack == false&& m_attack2 == false) {
		//----アニメーション動作間隔----

		
		if (m_time_a >= 4)
		{
			//アニメーション関数の呼び出し
			Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
				1, 4, NULL);
			m_time_a = 0;
		}
		

	}
	//攻撃アニメーション単発
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
	//範囲攻撃アニメーション
	if (m_attack2 == true) {



		m_ani_time += 1;


		if (m_ani_time > m_ani_max_time3)
		{
			m_ani_frame2 += 1;
			m_ani_time = 0;
		}


		//アニメーション
		if (m_ani_frame2 == 3)
		{
			m_ani_frame2 = 0;

			m_attack2 = false;
		}


	}

		//摩擦の計算   -(運動energy X 摩擦係数)
		m_vx += -(m_vx*0.098);

		//自由落下運動
		m_vy += 9.8 / (16.0f);



		//位置の更新
		m_px += m_vx;
		m_py += m_vy;



		//ブロック情報を持ってくる
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


		//HitBoxの位置の変更
		CHitBox*hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 54.0 + block->GetScroll(), m_py - 140);



		//BOSSの周り20°間隔で発射
		m_time++;//弾丸発射間隔をあけるインクリメント
		if (m_time > 350)//50の間隔で拡散弾攻撃をする
		{
			
				//19発同時発射
				CObjAngleBullet*obj_b;
				for (int i = 01; i < 360; i += 20)
				{


					m_time = 0;
					//弾丸オブジェクト
					CObjAngleBullet* obj_b = new CObjAngleBullet(m_px + block->GetScroll()+50, m_py-100, i, 5.0f);//オブジェ作成
					Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 20);

				
				}
				//敵を動かさないようにする。
				m_vx = 0;
				m_vy = 0;

				m_attack2 = true;//攻撃アニメーション移行用フラグ
		}

		m_time2++;//通常遠距離攻撃に間隔をつけるためのインクリメント
		if (m_time2 > 100) {

			
				m_time2 = 0;
				//弾丸オブジェクト
				CObjHomingBullet* obj_bo = new CObjHomingBullet(m_px + block->GetScroll()+50, m_py-50, 20);//オブジェ作成
				Objs::InsertObj(obj_bo, OBJ_HOMING_BULLET, 20);
				m_attack = true;//攻撃アニメーション移行用フラグ
			//敵を動かさないようにする。
				m_vx = 0;
				m_vy = 0;
		}

		//敵と弾丸が接触したらHPが減る
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{

			m_hp -= 30;

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
		//HPが0になったら破棄
		if (m_hp <= 0)
		{

			//ボス消滅でシーンをステージ３に移行する
			Scene::SetScene(new CSceneBlock3());

			/*
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
			*/


			/*
			else if (((UserData*)Save::GetData())->SceneNum == 3)
			{
				((UserData*)Save::GetData())->SceneNum++;
				//ボス消滅でクリア画面に移行する
				Scene::SetScene(new CSceneClear());
			}
			*/





		}
	



}

//ドロー
void CObjBoss::Draw()
{
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//スクロール情報取得
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//歩くアニメーション情報を登録
	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5, 
	};
	//歩くアニメーション情報を登録
	int AniDataack[6] =
	{
		0, 1, 2, 3, 4, 5,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//表示位置の設定
	dst.m_top = -180.0f + m_py;
	dst.m_left = (460.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (460 - 460.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 70.0f + m_py;



	if (m_attack == true|| m_attack2 == true) {
		//切り取り位置の設定
		src.m_top = 150.0f;
		src.m_left = 0.0f + AniDataack[m_ani_frame2] * 230;
		src.m_right = 230.0f + AniDataack[m_ani_frame2] * 230;
		src.m_bottom = 300.0f;

		//描画
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	else
	{


		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 230;
		src.m_right = 230.0f + AniData[m_ani_frame] * 230;
		src.m_bottom = 150.0f;

		//描画
		Draw::Draw(13, &src, &dst, c, 0.0f);





	}
	





	

}