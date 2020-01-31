#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "ObjItem.h"
#include "CheckHit.h"

#define GRAUND (546.0f)
#define ANIMAITON_FRAME (8)


//使用するネームスペース
using namespace GameL;



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
	
	Draw::LoadImageW(L"Animation/EDGE3.png",   1, TEX_SIZE_1024);//  主人公 (  前進  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png",  2, TEX_SIZE_1024);// 主人公 (  待機  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE4.png",   3, TEX_SIZE_1024);//  主人公 (ジャンプ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE3.png",  16, TEX_SIZE_1024);// 主人公 (  前進  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//主人公 ( ガード ) グラフィック読み込み
	
	//SE読み込み
	Audio::LoadAudio(2, L"SEgan/nomal.wav",        SOUND_TYPE::EFFECT);// 通常弾 発射音読み込み----
	Audio::LoadAudio(3, L"SEgan/FullSound.wav",    SOUND_TYPE::EFFECT);// れん弾 発射音読み込み----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav",      SOUND_TYPE::EFFECT);// 螺旋弾 発射音読み込み----
	Audio::LoadAudio(5, L"SEgan/NomalM.wav",       SOUND_TYPE::EFFECT);//    技切り替え時の音(通常弾)----
	Audio::LoadAudio(6, L"SEgan/FullM.wav",        SOUND_TYPE::EFFECT);//----技切り替え時の音(れん弾)----
	Audio::LoadAudio(7, L"SEgan/SpecialM.wav",     SOUND_TYPE::EFFECT);//----技切り替え時の音(らせん弾)----
	Audio::LoadAudio(8, L"SEgan/landing.wav",      SOUND_TYPE::EFFECT);//-------ジャンプ音の読み込み----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----
	Audio::LoadAudio(10, L"SEgan/HitD.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"SEgan/HitMA.wav", SOUND_TYPE::EFFECT);


	m_px = 300.0f; //主人公の X 位置
	m_py = 500.0f; //主人公の Y 位置

	m_sx = 64.0f;  //画像サイズBlockHit関数に渡す用
	m_sy = 64.0f;

	m_mou_px = 0.0f;//向き
	m_mou_py = 0.0f;

	m_mou_pr = 0.0f; //マウスのReftの状態
	m_mou_pl = 0.0f; //マウスのLightの状態

	m_f = true;   //弾丸制御
	m_gf = true;  //グレネード発射フラグ
	m_time = 0.0f; //弾丸発射頻度制限
	bullet_type = 1;//弾丸の種類(初期ハンドガン)

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;  //左右移動・静止アニメーションタイム制御
	m_ani_timeJump = 0; //ジャンプアニメーションタイム制御
	m_ani_frame = 0;   //静止フレームを初期にする
	m_ani_move = 1;    //アニメーション選択
	//m_ret = 8;  //アニメーション往復

	top = 0.0; //切り取り位置管理用
	left = 0.0;
	right = 80.0;
	bottom = 96.0;
	ani_num = 0; //描画番号管理用

	m_SEtime = 0;    //装着時のSE制御
	movesecond = 0;  //左右移動時のアニメーション/SE制御
	jumpsecond = 0;  //ジャンプ時のアニメーション/SE制御

	SE_flag = true;//SE制御用フラグ

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 10;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;

	flag = true;

	Guard_flag = false;//ガード用フラグ
	guard = 1;//ガード用変数

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = 100;//主人公のヒットポイント用
	hp_max = 100;
	hp_now = hp_max;
	hp_time = 0.0f;//主人公のヒットポイント制御用
	Remainingammo = 3;

	//必殺技回数
	attackpoint_max = 3;
	attackpoint_now = attackpoint_max;
}

//アクション
void CObjHero::Action()
{
	//SE・アニメーション制御time
	movesecond++;
	jumpsecond++;
	m_SEtime++;
	
	//武器切り替え(1～3)
	if (Input::GetVKey('1') == true)//通常弾
	{
		if (m_SEtime >= 12) {
			Audio::Start(5);//SE再生(装備音)
			m_SEtime = 0;
		}
		bullet_type = 1;//弾丸の種類を指定
	}
	if (Input::GetVKey('2') == true)//れん弾
	{
		if (m_SEtime >= 12) {
			Audio::Start(6);//SE再生(装備音)
			m_SEtime = 0;
		}
		bullet_type = 2;//弾丸の種類を指定
	}
	if (Input::GetVKey('3') == true)//螺旋弾
	{
		if (m_SEtime >= 12) {
			Audio::Start(7);//SE再生(装備音)
			m_SEtime = 0;
		}
		bullet_type = 3;//弾丸の種類を指定
	}

	//弾丸アニメーション
	if (bullet_type == 1)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += 1;//アニメーションタイムを+1加算
			m_ani_move = 3;//アニメーションデータを指定
		}

	}
	//連弾アニメーション
	if (bullet_type == 2)
	{
		if (Input::GetMouButtonL() == true) 
		{
			m_ani_time += 1;//アニメーションタイムを+1加算
			m_ani_move = 4;//アニメーションデータを指定
		}
		
	}
	//螺旋弾アニメーション
	if (bullet_type == 3)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += 1;//アニメーションタイムを+1加算
			m_ani_move = 5;//アニメーションデータを指定
		}
		
	}

	//弾丸発射頻度制御
	m_time += 0.1;
	
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 1)//通常弾発射--------
	{
		if (m_f == true)
		{
			//発射音を鳴らす
			Audio::Start(2);

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
	

	//必殺技
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 3 && 
		attackpoint_now <= 3 && attackpoint_now > 0)
	{
		if (m_f == true)
		{



			//発射音を鳴らす
			Audio::Start(2);
			for (int i = 360 / 64; i <= 360; i += 360 / 64)
			{
				//弾丸オブジェクト
				CObjDiffusionBullet* obj_ex = new CObjDiffusionBullet(m_px, m_py, i);//オブジェ作成
				Objs::InsertObj(obj_ex, OBJ_DIFFUSION_BULLET, 6);
			}
			//Audio::Start(6);//薬莢落下音
			m_f = false;
			m_time = 0.0f;


			attackpoint_now--;


		}
		
	}
	else if (Input::GetMouButtonL() == false)
	{
		m_f = true;
	}

	if (Input::GetMouButtonL() == true && m_time >= 2 &&bullet_type == 2)//連弾発射----------
	{
		m_ani_move = 4;//------弾丸アニメーションデータを指定--------
		Action_ani_flag = true;

		if (movesecond >= 21 && m_hit_down == true)//SE制御
		{
			Audio::Start(3);
			movesecond = 0;
		}

		//発射音を鳴らす
		Audio::Start(2);//連弾発射音再生
		//m_SEtime++;

		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

		m_time = 0.0f;
		//Audio::Start(7);//薬莢落下音
	}
	/*if (Input::GetMouButtonL() == true && m_time >= 6.0f&&bullet_type == 3)//特殊弾丸発射---------
	{
		//発射音を鳴らす
		//Audio::Start(4);//ショットガン発射音再生


		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjDiffusionBullet* obj_rb = new CObjDiffusionBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_rb, OBJ_DIFFUSION_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

		/*
		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjRevolutionBullet* obj_rb = new CObjRevolutionBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_rb, OBJ_REVOLUTION_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
		
		m_time = 0.0f;

	}*/
	/*
	//グレネード発射
	if (Input::GetVKey('Y') == true && m_time >= 10.0f)
	{
		if (m_gf == true)
		{
			//発射音を鳴らす
			//Audio::Start(2);

			//弾丸オブジェクト作成
			CObjGren* obj_g = new CObjGren(m_px, m_py );//弾丸オブジェクト作成
			Objs::InsertObj(obj_g, OBJ_GREN, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

			m_gf = false;
			m_time = 0.0f;
		}
	}
	else
	{
		m_gf = true;
	}
	*/
	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true,
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

	if (Input::GetVKey('C') == true/*&&Guard_flag==false*/)//ガード--------
		guard = 2;
	else
		guard = 1;
	
	//領域外に出たらゲームオーバー画面に移行
	if (m_py > 600.0f)
	{
		this->SetStatus(false);

		Scene::SetScene(new CSceneGameOver());
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
		//アイスブロック
		if (m_block_type == 2)
			m_vx += (m_vx*0.12);//摩擦の計算   (運動energy X 摩擦係数)

		m_vx += m_speed_power;//右に移動ベクトル加算
		m_posture = 1.0f;//アニメーションタイムを+1加算
		m_ani_move = 1;//歩くアニメーションデータを指定

		if (movesecond >= 4 && m_hit_down == true)
			m_ani_time += 1;

		if (movesecond >= 21 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}

		//ダメージブロック
		if (m_block_type == 5)
			hp -= 0.5;

		//ゴールブロック
		if (m_block_type == 3)
		{
			this->SetStatus(false);

			Scene::SetScene(new SceneBossStage());
		}

		/*else
		{
			second++;
		}*/


	}
	//左に移動時の処理
	else if (Input::GetVKey('A') == true)
	{
		//アイスブロック
		if (m_block_type == 2)
			m_vx += (m_vx*0.12);//摩擦の計算   -(運動energy X 摩擦係数)

		m_vx -= m_speed_power;//左に移動ベクトル減算
		m_posture = 0.0f;//アニメーションタイムを+1加算
		m_ani_move = 1;//歩くアニメーションデータを指定
		if (movesecond >= 4 && m_hit_down == true)
		{
			m_ani_time += 1;
		}
		if (movesecond >= 21 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}
		//ダメージブロック
		if (m_block_type == 5)
			hp -= 0.5;

		//ゴールブロック
		if (m_block_type == 3)
		{
			this->SetStatus(false);
			Scene::SetScene(new SceneBossStage());
		}
			/*else
			{
				second++;
			}*/

	}
	else//キー入力がない場合は静止フレームにする---
	{
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 0;//静止アニメーションデータを指定

		movesecond = 100;

	}
	if (m_hit_down == false)//ジャンプアニメーション---
	{
		m_ani_move = 2;//ジャンプアニメーションデータを指定
		if (jumpsecond >= 10)
		{

			m_ani_time += 1;//アニメーションタイムを+1加算

			SE_flag = true;
			jumpsecond = 0;
		}
		else
			jumpsecond = 100;
	}
	if (m_hit_down == true && SE_flag == true)//落下後Blockと接触時に着地音を鳴らす---
	{
		SE_flag = false;
		Audio::Start(9);
	}
	//---------アニメーション間隔制御-------------
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;//アニメーションフレームを+1加算
		m_ani_time = 0; //アニメーションタイムを初期化
	}
	//アニメーションを初期化---
	if (m_ani_frame == 10)
	{
		m_ani_frame = 0;//アニメーションフレームを初期化
	}

	//摩擦の計算   -(運動energy X 摩擦係数)
	m_vx += -(m_vx*0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	hp_time -= 0.1;

	//自身のヒットボックスを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//回復薬に当たるとhpを+する
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr && hp <= 90)
	{
		hp += 10;
	}

	//必殺技回数回復
	if (hit->CheckObjNameHit(OBJ_AITEM) != nullptr && attackpoint_now <= 2)
	{
		attackpoint_now += 1;
	}

	//遠距離敵の攻撃接触でHeroのHPが減る
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{
		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 30/guard;
			
			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}
		Audio::Start(11);
		//ブロック情報を持ってくる
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//HomingBulletの位置情報をここで取得
		CObjHomingBullet*obj = (CObjHomingBullet*)Objs::GetObj(OBJ_HOMING_BULLET);
		float x = obj->GetBX();
		if (obj != nullptr) {
			//ノックバックプログラム
			if (m_px > x + block->GetScroll())
			{
				m_vx = -5.0f;
			}
			else //(m_px < x)
			{
				m_vx = +5.0f;
			}
		}
	}

	//OBJ_ENEMYと当たると主人公がダメージを 1 受ける  OBJ_HOMING_BULLETと当たるとダメージを1受ける
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{

		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 10 / guard;
			Audio::Start(10);
			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}

		//ブロック情報を持ってくる
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		

		//通常敵機の位置情報をここで取得
		CObjEnemy*obj = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
		if (obj != nullptr) {

			float ex = obj->GetEX();

			//ノックバックプログラム
			if (m_px > ex + block->GetScroll())
			{
				m_vx = -5.0f;
			}
			else //(m_px < ex)
			{
				m_vx = 5.0f;
			}
		}

		//フライングエネミーの位置情報取得
		CObjFlyingenemy*obj1 = (CObjFlyingenemy*)Objs::GetObj(OBJ_ENEMY);
		if (obj1 != nullptr) {

			float ex = obj1->GetEX();

			//ノックバックプログラム
			if (m_px > ex + block->GetScroll())
			{
				m_vx = -5.0f;
			}
			else //(m_px < ex)
			{
				m_vx = 5.0f;
			}

		}


			//ジャンプエネミーの位置情報を取得
			CObjEnemyJump*obj3 = (CObjEnemyJump*)Objs::GetObj(OBJ_ENEMY);
			if (obj3 != nullptr) {

				float ex = obj3->GetEX();

				//ノックバックプログラム
				if (m_px > ex + block->GetScroll())
				{
					m_vx = +5.0f;
				}
				else //(m_px < ex)
				{
					m_vx = -5.0f;
				}

			}

			//遠距離敵の位置情報を取得
			CObjEnemyLongdistance*obj4 = (CObjEnemyLongdistance*)Objs::GetObj(OBJ_ENEMY);
			if (obj4 != nullptr) {

				float ex = obj4->GetEX();

				//ノックバックプログラム
				if (m_px > ex + block->GetScroll())
				{
					m_vx = +5.0f;
				}
				else //(m_px < ex)
				{
					m_vx = -5.0f;
				}

			}

			//BOSSの位置情報を取得
			CObjBoss*obj5 = (CObjBoss*)Objs::GetObj(OBJ_ENEMY);
			if (obj5 != nullptr) {

				float ex = obj5->GetEX();

				//ノックバックプログラム
				if (m_px > ex + block->GetScroll())
				{
					m_vx = +5.0f;
				}
				else //(m_px < ex)
				{
					m_vx = -5.0f;
				}

			}

		}
		
	 
	
	//主人公のHPがゼロになった時主人公が消える
	if (hp<=0) 
	{
		
		
		/*
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		
		//主人公のHPがゼロになった時ゲームオーバー画面に移行する
		Scene::SetScene(new CSceneGameOver());
		*/
	}
		




		//位置の更新
		m_px += m_vx;
		m_py += m_vy;

		//ヒットボックスの最新
		hit->SetPos(m_px+8, m_py+10);
	
}


//ドロー
void CObjHero::Draw()
{
	if (m_ani_move == 0) {//静止描画                            描画番号
		top = 0.0f; left = 0.0f; right = 80.0f; bottom = 96.0f; ani_num = 2;
	}
	if (m_ani_move == 1) {//移動描画                            描画番号
		top = 0.0f; left = 0.0f; right = 78.0f; bottom = 96.0f; ani_num = 1;
	}
	if (m_ani_move == 2) {//ジャンプ描画                        描画番号
		top = 0.0f; left = 0.0f; right = 80.0f; bottom = 96.0f; ani_num = 3;
	}
	if (m_ani_move == 3) {//攻撃通常弾丸                       描画番号
		top = 0.0f; left = 0.0f; right = 80.0f; bottom = 96.0f; ani_num = 18;
	}
	if (m_ani_move == 3) {//攻撃通常弾丸                       描画番号
		top = 96.0f; left = 0.0f; right = 80.0f; bottom = 192.0f; ani_num = 18;
	}

	//キャラクターのアニメーション情報を登録
	int AniData[7][10] =
	{
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //静止アニメーション情報を登録-----(1列目) m_ani_move = 0
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //-------------歩行----------------(2列目) m_ani_move = 1
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //ジャンプアニメーション情報を登録-(3列目) m_ani_move = 2
		{ 0 , 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 }, //通常弾発射-----------------------(4列目) m_ani_move = 3
		{ 0 , 0 , 0 , 1 , 1 , 1 , 2 , 2 , 2 , 2 }, //連弾発射-------------------------(5列目) m_ani_move = 4
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //螺旋弾---------------------------(6列目) m_ani_move = 5
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //ダメージアニメーション-----------(7列目) m_ani_move = 6

	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//主人公アニメーション
	//切り取り位置
	src.m_top = top;
	src.m_left = left + AniData[m_ani_move][m_ani_frame] * right;
	src.m_right = right + AniData[m_ani_move][m_ani_frame] * right;
	src.m_bottom = bottom;
	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f       *  m_posture) + m_px;
	dst.m_right = (64 - 64.0f  *  m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//描画　　　　　　　　　　　　　　 回転
	Draw::Draw(ani_num, &src, &dst, c, 0.0f);
	//--------------------------------------------------
	//HP
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 123.0f;

	//表示位置設定
	dst.m_top = 35.0f;
	dst.m_left = 29.0f;
	dst.m_right = dst.m_top + (210.0f*(hp / (float)hp_max));
	dst.m_bottom = 53.0f;

	Draw::Draw(6, &src, &dst, c, 0.0f);

	//HPカバー
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 163.0f;

	//表示位置の設定
	dst.m_top = 30.0f;
	dst.m_left = 30.0f;
	dst.m_right = 250.0f;
	dst.m_bottom = 55.0f;

	Draw::Draw(25, &src, &dst, c, 0.0f);

	//必殺技ゲージ
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 248.0f;
	src.m_bottom = 26.0f;

	//表示位置設定
	dst.m_top = 66.0f;
	dst.m_left = 40.0f;
	dst.m_right = (40.0f + (attackpoint_now * 50.0f));
	dst.m_bottom = 75.0f;

	Draw::Draw(26, &src, &dst, c, 0.0f);

	//必殺技カバー表示
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 30.0f;

	//表示位置設定
	dst.m_top = 65.0f;
	dst.m_left = 40.0f;
	dst.m_right = 192.0f;
	dst.m_bottom = 75.0f;

	Draw::Draw(27, &src, &dst, c, 0.0f);
}
