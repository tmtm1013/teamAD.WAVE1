#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "ObjItem.h"

#define GRAUND (546.0f)
#define ANIMAITON_FRAME (8)


//使用するネームスペース
using namespace GameL;

float idou;//ヒーローが動いているか確認するグローバル変数



//位置情報X変更用
void  CObjHero::SetXX(float x)
{

	m_px = x;



}
//位置情報Y変更用
void  CObjHero::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjHero::GetXX()
{

	return m_px;


}
//位置情報Y取得用
float  CObjHero::GetYY()
{

	return m_py;

}

//イニシャライズ
void CObjHero::Init()
{

	m_px = 300.0f;    //位置
	m_py = 500.0f;

	m_sx = 64.0f;  //画像サイズBlockHit関数に渡す用
	m_sy = 64.0f;

	m_mou_px = 0.0f;//向き
	m_mou_py = 0.0f;

	m_mou_pr = 0.0f;
	m_mou_pl = 0.0f;

	m_f = true;   //弾丸制御
	m_time = 0.0f; //弾丸発射頻度制限
	bullet_type = 1;//弾丸の種類(初期ハンドガン)

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_timeJump = 0;
	m_ani_frame = 0;   //静止フレームを初期にする
	m_ani_move = 1;    //アニメーション選択
	//m_ret = 8;  //アニメーション往復

	top = 0.0;
	left = 0.0;
	right = 80.0;
	bottom = 96.0;

	m_SEtime = 0;
	second = 0;
	SE_flag = true;//SE制御用フラグ

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 10;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	flag = true;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = 10;//主人公のヒットポイント用
	hp_max = 10;
	hp_now = hp_max;
	hp_time = 0.0f;//主人公のヒットポイント制御用

	/*
	for (int i = 0; i < 28; i++)
	{



		srcAnim[i].top = top+;
		srcAnim[i].left = left+;
		srcAnim[i].right = right+;
		srcAnim[i].bottom = bottom+;

	}
	*/
}

//アクション
void CObjHero::Action()
{
	//SE制御time


	if (second >= 600)
	{
		m_SEtime++;
		second = 0;
	}

	//m_SEtime = (second / 60) % 60; // 600 / 10 = 10秒

	//武器切り替え(1～3)
	if (Input::GetVKey('1') == true)//ハンドガン
	{
		if (m_SEtime >= 12)
			Audio::Start(5);//SE再生(装備音)
		bullet_type = 1;//弾丸の種類を指定
		m_SEtime = 0;
	}
	if (Input::GetVKey('2') == true)//サブマシンガン
	{
		if (m_SEtime >= 12)
			Audio::Start(5);//SE再生(装備音)
		bullet_type = 2;//弾丸の種類を指定
		m_SEtime = 0;

	}
	if (Input::GetVKey('3') == true)//ショットガン
	{
		if (m_SEtime >= 12)
			Audio::Start(5);//SE再生(装備音)
		bullet_type = 3;//弾丸の種類を指定
		m_SEtime = 0;

	}

	//初期ハンドガンアニメーション
	if (bullet_type == 1)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += 1;//アニメーションタイムを+1加算
			m_ani_move = 3;//アニメーションデータを指定
		}

	}
	//初期サブマシンガンアニメーション
	if (bullet_type == 2)
	{
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 4;//アニメーションデータを指定
	}
	//初期ショットガンアニメーション
	if (bullet_type == 3)
	{
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 5;//アニメーションデータを指定
	}


	//弾丸発射頻度制御
	m_time += 0.1;


	//主人公のハンドガン弾丸発射
	if (Input::GetMouButtonL() == true && m_time >= 2.0f&&bullet_type == 1)
	{
		if (m_f == true)
		{
			//発射音を鳴らす
			//Audio::Start(2);

			//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
			CObjBullet* obj_b = new CObjBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
			Objs::InsertObj(obj_b, OBJ_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

				//Audio::Start(6);//薬莢落下音

			m_f = false;
			m_time = 0.0f;
		}
	}
	else if (Input::GetMouButtonL() == false)
	{
		m_f = true;
	}

	//サブマシンガン弾丸発射
	if (Input::GetMouButtonL() == true && m_time >= 0.8f&&bullet_type == 2)
	{
		//発射音を鳴らす
		/*Audio::Start(2);//サブマシンガン発射音再生
		m_SEtime++;*/

		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

		m_time = 0.0f;
		//Audio::Start(7);//薬莢落下音
	}

	//ショットガン弾丸発射
	if (Input::GetMouButtonL() == true && m_time >= 6.0f&&bullet_type == 3)
	{
		//発射音を鳴らす
		//Audio::Start(4);//ショットガン発射音再生


		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjDiffusionBullet* obj_db = new CObjDiffusionBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_db, OBJ_DIFFUSION_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

		m_time = 0.0f;

	}
	//手榴弾発射
	/*if (Input::GetVKey('Q') == true && m_time >= 10.0f)
	{
		if (m_f == true)
		{
			//発射音を鳴らす
			//Audio::Start(2);

			//弾丸オブジェクト作成
			CObjGrenade* obj_g = new CObjGrenade(m_px + 30.0f, m_py + 30.0f);//弾丸オブジェクト作成
			Objs::InsertObj(obj_g, OBJ_GRENADE, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

			m_f = false;
			m_time = 0.0f;
		}
	}
	else
	{
		m_f = true;
	}
	*/

	if (Input::GetVKey('Y') == true && m_time >= 1.0f)
	{
		if (m_f == true)
		{
			//発射音を鳴らす
			//Audio::Start(2);

			//弾丸オブジェクト作成
			CObjGren* obj_g = new CObjGren(m_px, m_py );//弾丸オブジェクト作成
			Objs::InsertObj(obj_g, OBJ_GREN, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

			m_f = false;
			m_time = 0.0f;
		}
	}
	else
	{
		m_f = true;
	}
	

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true, &m_sx, &m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);


	//SPACEキー入力でジャンプ
	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_hit_down == true)
		{
			Audio::Start(8);
			m_vy = -16;
		}
	}

	//Zキー入力で速度アップ
	if (Input::GetVKey('Z') == true)
	{
		//ダッシュ時の速度
		m_speed_power = 1.1f;
		m_ani_max_time = 1;
	}

	else
	{
		//通常速度
		m_speed_power = 0.5f;
		m_ani_max_time = 2;
	}

	//主人公の向きを制御
	//マウスの位置を取得
	m_mou_px = (float)Input::GetPosX();
	m_mou_py = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_pr = Input::GetMouButtonR();
	m_mou_pl = Input::GetMouButtonL();

	//左に移動時の処理
	if (Input::GetVKey('D') == true)
	{
		idou = 1;//主人公の動いているかどうかの確認

		m_vx += m_speed_power;//右に移動ベクトル加算
		m_posture = 1.0f;//アニメーションタイムを+1加算
		m_ani_move = 1;//歩くアニメーションデータを指定
	
		if (second >= 2 && m_hit_down == true)
		{
			m_ani_time += 1;
		}
		if (second>=21&&m_hit_down==true)
		{
			Audio::Start(8);
			second = 0;
		}
		else 
		{
			second++;
		}
	}
	//左に移動時の処理
	else if (Input::GetVKey('A') == true)
	{
		//左に移動時の処理
		idou = 2;//主人公の動いているかどうかの確認

		m_vx -= m_speed_power;//左に移動ベクトル減算
		m_posture = 0.0f;//アニメーションタイムを+1加算
		m_ani_move = 1;//歩くアニメーションデータを指定
		
		if (second >= 2 && m_hit_down == true)
		{
			m_ani_time += 1;
		}
		if (second >= 21 && m_hit_down == true)
		{
			Audio::Start(8);
			second = 0;
		}
		else
		{
			second++;
		}

	}
	else//キー入力がない場合は静止フレームにする
	{
		idou = 3;//主人公の動いているかどうかの確認

		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 0;//静止アニメーションデータを指定

	
		second = 100;
	

	}
	if (m_hit_down == false)//ジャンプアニメーション
	{

			m_ani_time += 1;//アニメーションタイムを+1加算
			m_ani_move = 2;//ジャンプアニメーションデータを指定
			SE_flag = true;

	}
	if (m_hit_down == true && SE_flag == true)//落下後Blockと接触時に着地音を鳴らす
	{
		SE_flag = false;
	//	Audio::Start(9);
	}
	//アニメーション間隔制御
	if (m_ani_time  > m_ani_max_time)
	{
		m_ani_frame += 1;//アニメーションフレームを+1加算
		m_ani_time = 0; //アニメーションタイムを初期化
	}

	//アニメーションを初期化
	if (m_ani_frame == 10)
	{
		m_ani_frame = 0;//アニメーションフレームを初期化
	}
	
	//HitBoxの位置の変更a
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);
	
	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	hp_time -= 0.1;

	//回復薬に当たるとhpを+する
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr)
	{

		m_hp += 10;

		hp += 50;

	}
	//OBJ_ENEMYと当たると主人公がダメージを 1 受ける
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 1;

			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}

				HIT_DATA** hit_data;
				hit_data = hit->SearchObjNameHit(OBJ_ENEMY);


		/*float r = hit_data[0]->r;
		if ((r < 45 && r >= 0) || r > 315)
		{
			m_vx = -5.0f; //左に移動させる。
		}
		if (r > 135 && r < 225)
		{
			m_vx = +5.0f; //右に移動させる。
		}
	}

	//遠距離敵の攻撃接触でHeroのHPが減る
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{

		

		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 1;
			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}

		//OBJ_BULLETと当たると主人公がノックバックする
		HIT_DATA** hit_data;
		hit_data = hit->SearchObjNameHit(OBJ_HOMING_BULLET);
		
		float r = hit_data[0]->r;
		if ((r < 45 && r >= 0) || r > 315)
		{
			m_vx = -5.0f; //左に移動させる。
		}

		if (r > 135 && r < 225)
		{
			m_vx = +5.0f; //右に移動させる。
		}
	}
	
	//主人公のHPがゼロになった時主人公が消える
	if (hp<=0) {

			this->SetStatus(false);
			Hits::DeleteHitBox(this);

		//主人公のHPがゼロになった時ゲームオーバー画面に移行する
		Scene::SetScene(new CSceneGameOver());
	}
	

			//位置の更新
			m_px += m_vx;
			m_py += m_vy;

	
}


//ドロー
void CObjHero::Draw()
{

	//キャラクターのアニメーション情報を登録
	int AniData[6][10] =
	{
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //静止アニメーション情報を登録-----(1列目) m_ani_move = 0
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //ハンドガン所持(歩行)-------------(2列目) m_ani_move = 1
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //ジャンプアニメーション情報を登録-(3列目) m_ani_move = 2
		{ 0 , 1 , 2 , 3 , 4 , 0 , 0 , 0 , 0 , 0 }, //サブマシンガン所持---------------(4列目) m_ani_move = 3
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //ショットガン所持-----------------(5列目) m_ani_move = 4
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //ダメージアニメーション-----------(6列目) m_ani_move = 5

	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	if (m_ani_move == 1)//主人公が移動している時の描画
	{
		//切り取り位置の設定
		src.m_top = 0.0f + (80.0f - 80.0f*m_ani_move + 1);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 78;
		src.m_right = 78.0f + AniData[m_ani_move][m_ani_frame] * 78;
		src.m_bottom = 96.0 + (96.0f - 96.0f *m_ani_move + 1);

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f      * m_posture) + m_px;
		dst.m_right = (64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		m_posture = 0.0;

		//描画
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	if (m_ani_move == 0)//主人公が静止状態の時の描画
	{
		//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_right = 80.0f + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_bottom = 96.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f      * m_posture) + m_px;
		dst.m_right = (64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		//描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	if (m_ani_move == 2)//ジャンプアニメーション
	{
		//切り取り位置の設定
		src.m_top = top;
		src.m_left = left + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_right = right + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_bottom = bottom;
		//表示位置の設定s
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f        * m_posture) + m_px;
		dst.m_right = (64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		//描画
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	/*if (m_ani_move == 3)//
	{
		//切り取り位置の設定
		src.m_top    = top;
		src.m_left   = left  + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_right  = right + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_bottom = bottom;
		//表示位置の設定s
		dst.m_top    = 0.0f  + m_py;
		dst.m_left   = ( 64.0f      * m_posture) + m_px;
		dst.m_right  = ( 64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		//描画
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}*/



	//HP
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 16.0f;

	//表示位置設定
	dst.m_top = 32.0f;
	dst.m_left = 32.0f;
	dst.m_right = dst.m_top + (128.0f*(hp / (float)hp_max));
	dst.m_bottom = 40.0f;

	Draw::Draw(6, &src, &dst, c, 0.0f);
}
