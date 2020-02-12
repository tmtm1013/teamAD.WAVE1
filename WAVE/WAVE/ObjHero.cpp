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
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;  //左右移動・静止アニメーションタイム制御

	m_ani = 0;//死亡アニメーションフレーム管理用
	m_ani_time2 = 0;//死亡アニメーションフレーム動作間隔
	m_del = false;//死亡アニメーション動作フラグ

	top = 0.0; //切り取り位置管理用
	left = 0.0;
	right = 80.0;
	bottom = 96.0;
	ani_num = 0; //描画番号管理用

	m_SEtime = 0;    //装着時のSE制御
	movesecond = 0;  //左右移動時のアニメーション/SE制御
	jumpsecond = 0;  //ジャンプ時のアニメーション/SE制御
	jump_time = 0.0f;//ジャンプ時間管理用変数

	SE_flag = true;//SE制御用フラグ

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 4;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;

	flag = true;

	Method_flag=false;

	guard_flag = false;//ガード用フラグ
	guard = 1;//ガード用変数

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = 300;//主人公のヒットポイント用
	hp_max = 300;
	hp_now = hp_max;
	hp_time = 0.0f;//主人公のヒットポイント制御用
	Remainingammo = 3;

	//必殺技回数
	attackpoint_max = 3;
	attackpoint_now = attackpoint_max;


	
	m_ani_frame = 0;
	m_ani_frame_Waiting = 0;
	m_ani_frame_Jump = 0;


	Action_Waiting = false;
	Action_Walk = false;
	Action_direction = false;
	Action_Jump = false;
	Action_guard = false;
	
	m_ani_max_time_Jump = 4;
	m_ani_time_Jump = 0;
}

//アクション
void CObjHero::Action()
{
	//SE・アニメーション制御time
	movesecond++;
	jumpsecond++;
	m_SEtime++;

	//アニメーションフラグ初期化
	Action_Waiting = false;
	Action_Walk = false;
	Action_Jump = false;
	Action_guard = false;

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

	/*
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
	*/

	//弾丸発射頻度制御
	m_time += 0.1;

	//通常弾発射-----------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 1 )
	{
		if (m_f == true)
		{
			//発射音を鳴らす
			Audio::Start(2);

			//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
			CObjBullet* obj_b = new CObjBullet(m_px + 30.0f, m_py + 25.0f); //弾丸オブジェクト作成
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
	//連弾発射--------------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 1 && bullet_type == 2 )
	{
		m_ani_move = 4;//------弾丸アニメーションデータを指定--------
		Action_ani_flag = true;

		if (movesecond >= 21 && m_hit_down == true)//SE制御
		{
			//Audio::Start(3);
			movesecond = 0;
		}

		//発射音を鳴らす
		Audio::Start(2);//連弾発射音再生
		//m_SEtime++;
		
		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 25.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

		m_time = 0.0f;
		//Audio::Start(7);//薬莢落下音
	}
	//必殺技-----------------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 3 &&
		attackpoint_now <= 3 && attackpoint_now > 0)
	{
		if (m_f == true)
		{
			//発射音を鳴らす
			Audio::Start(3);
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

	//ブロックとの当たり判定
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//ガード管理用変数を初期化
	guard = 1;
	guard_flag = false;

	if (Input::GetVKey('D') == true && Action_guard == false && m_del == false)	//左に移動時の処理-----------
	{

		//主人公移動
		m_vx += 0.5;
		//アニメーション関数の呼び出し
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			1, 12, 0.0f);

		movesecond++;
		if (movesecond >= 63 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}

		Action_Walk = true;

		Action_direction = false;
	}
	else if (Input::GetVKey('A') == true && Action_guard == false && m_del == false)//左に移動時の処理------------
	{
		//主人公移動
		m_vx -= 0.5f;
		//アニメーション関数の呼び出し
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			  1, 12, 1.0f);

		movesecond++;
		if (movesecond >= 63 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}

		Action_Walk = true;

		Action_direction = true;
	}
	else if (Input::GetMouButtonR() == true && m_hit_down == true && Input::GetMouButtonL() == false && m_del == false)//ガードアクション-----------
	{
		Action_guard = true;
		guard_flag = true;
		
		guard = 0;//ダメージを無効化
	}
	else if(m_del==false)//キー入力がない場合は静止フレームにする---
	{
		//アニメーション関数の呼び出し
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame_Waiting, &m_posture,
			1, 9, NULL);
		movesecond = 100;

		//待機モーション向き
		if (Action_direction == false)
			m_posture = 0.0f;//アニメーション向き変更
		else
			m_posture = 1.0f;	//アニメーション向き変更

		Action_Waiting = true;
	}
	if (Input::GetVKey(VK_SHIFT) == true && Action_Walk == true)	//Zキー入力で速度アップ---------
	{
		//SE間隔(仮)
		movesecond+=2;

		//主人公移動
		if (Action_direction == true) {
			m_vx -= 0.6;
		}
		else {
			m_vx += 0.6;
		}
		//アニメーション関数の呼び出し
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			  2, 12, m_posture);
	}
	//SPACEキー入力でジャンプ
	if (Input::GetVKey(VK_SPACE) == true && m_del == false)
	{
		
		if (m_hit_down == true && m_py > 100)
			m_vy =-16.0f;
		/*
		else if (jump_time < 100 && m_hit_down == false && m_py > 100)
		{
			jump_time++;
			
			m_vy -= 0.7f;
	
            
		}
		if (m_hit_up==true)
			m_vy =+ 8.0f;

		if (m_py < 100)
		{
			m_vy += 1.0f;
		}*/
	}
	else if (m_hit_down == true)
	{
		jump_time = 0.0f;
	}




	if (Input::GetVKey('P') == true && m_del == false)
	{

		//弾丸オブジェクト
		CObjGrenade* obj_gre = new CObjGrenade(m_px, m_py);//オブジェ作成
		Objs::InsertObj(obj_gre, OBJ_GRENADE, 1);
	}
	



	if (Input::GetVKey('Q') == true)// Q 操作説明表示処理
	{
		Method_flag = true;//処理を止めるフラグを切り替える


	}
	if (Input::GetVKey('Q') == false && Method_flag == true)
	{
		//操作説明表示
		CObjMethod* md = new CObjMethod();
		Objs::InsertObj(md, OBJ_METHOD, 18);
		Method_flag = false;
	}

	
	//ジャンプアニメーション用
	if (m_hit_down == false) {
		//アニメーション関数の呼び出し
		Anime(&m_ani_time_Jump, &m_ani_max_time_Jump, &m_ani_frame_Jump, &m_posture,
			1, 10, NULL);
		
		Action_Jump = true;
	}

	//flag = false;//フラグを初期化

	//主人公の向きを制御
	//マウスの位置を取得
	m_mou_px = (float)Input::GetPosX();
	m_mou_py = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_pr = Input::GetMouButtonR();
	m_mou_pl = Input::GetMouButtonL();

	//摩擦の計算   -(運動energy X 摩擦係数)
	if(m_block_type == 2)
	    m_vx += -(m_vx*0.008);
	else
	{
		m_vx += -(m_vx*0.098);
	}
	
	//自由落下運動
	m_vy += 9.8 / (16.0f);

	hp_time -= 0.1;

	//自身のヒットボックスを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 8, m_py + 10);//ヒットボックスの最新

	//回復薬に当たるとhpを+する
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr && hp <= 300)
	{
		hp += 60;
		Audio::Start(19);
		if (hp >= 300)//hpが300以上になる場合300ぴったりに上書き！！たいあり！
		{
			hp = 300;
		}
	}
		

	//必殺技回数回復
	if (hit->CheckObjNameHit(OBJ_AITEM) != nullptr && attackpoint_now <= 2) {
		attackpoint_now += 1;
		Audio::Start(18);
	}
	//遠距離敵の攻撃接触でHeroのHPが減る
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{
		
		if (flag == true && hp_time <= 0.0f) {

			if (guard_flag == true)
			{
				Audio::Start(27);
				hp -= guard;//ダメージ量×ガード値
				//Audio::Start(27);
			}
			else {
				hp -= 30;//ダメージ量×ガード値
				Audio::Start(11);
			}

			flag = false;//主人公HP減算量管理フラグ 
			hp_time = 1.6f;//主人公HP減算量管理タイム
		}
		if (hp_time >= 0.0f) {
			flag = true;
		}
		
		//ブロック情報を持ってくる
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//HomingBulletの位置情報をここで取得
		CObjHomingBullet*obj = (CObjHomingBullet*)Objs::GetObj(OBJ_HOMING_BULLET);
		float x = obj->GetBX();
		if (obj != nullptr) {
			m_vx = KnockBack(m_px, x);//ノックバック関数
		}
	}
	if (hit->CheckObjNameHit(OBJ_ANGLE_BULLET) != nullptr)
	{

		if (flag == true && hp_time <= 0.0f) {

			if (guard_flag == true)
			{
				Audio::Start(27);
				hp -= guard;//ダメージ量×ガード値
				//Audio::Start(27);
			}
			else {
				hp -= 30;//ダメージ量×ガード値
				Audio::Start(26);
			}

			flag = false;//主人公HP減算量管理フラグ 
			hp_time = 1.6f;//主人公HP減算量管理タイム
		}
		if (hp_time >= 0.0f) {
			flag = true;
		}
		
		
	}
	//OBJ_ENEMYと当たると主人公がダメージを 1 受ける  OBJ_HOMING_BULLETと当たるとダメージを1受ける
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		if (flag == true && hp_time <= 0.0f){   

			if (guard_flag==true)
			{
				Audio::Start(27);
				hp -= guard;//ダメージ量×ガード値
				//Audio::Start(27);
			}
			else {
				hp -= 10;//ダメージ量×ガード値
				Audio::Start(10);
			}
		
			
			flag = false;//主人公HP減算量管理フラグ 
			hp_time = 1.6f;//主人公HP減算量管理タイム
		}
		if (hp_time >= 0.0f){
			flag = true;
		}
		//ブロック情報を持ってくる
		//CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		CObjEnemy*obj = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);//通常敵機の位置情報をここで取得
		if (obj != nullptr) {

			float ex = obj->GetEX();

			m_vx=KnockBack(m_px, ex);//ノックバック関数

		}
		CObjFlyingenemy*obj1 = (CObjFlyingenemy*)Objs::GetObj(OBJ_ENEMY);//フライングエネミーの位置情報取得
		if (obj1 != nullptr) {

			float ex = obj1->GetEX();

			m_vx = KnockBack(m_px, ex);
		}
		CObjEnemyJump*obj3 = (CObjEnemyJump*)Objs::GetObj(OBJ_ENEMY);//ジャンプエネミーの位置情報を取得
		if (obj3 != nullptr) {

			float ex = obj3->GetEX();

			m_vx = KnockBack(m_px, ex);
		}
		CObjEnemyLongdistance*obj4 = (CObjEnemyLongdistance*)Objs::GetObj(OBJ_ENEMY);//遠距離敵の位置情報を取得
		if (obj4 != nullptr) {

			float ex = obj4->GetEX();

			m_vx = KnockBack( m_px, ex);
		}
		CObjBoss*obj5 = (CObjBoss*)Objs::GetObj(OBJ_ENEMY);	//BOSSの位置情報を取得
		if (obj5 != nullptr) {

			float ex = obj5->GetEX();

			m_vx = KnockBack(m_px, ex);
		}
	}
	if (hit->CheckObjNameHit(OBJ_DANGER_WALL) != nullptr)//主人公がOBJ_DANGER_WALLに当たっているかどうかの判定
	{
		Audio::Start(26);
		m_vx += 6.0f;//主人公ノックバック
		hp -= 30;//主人公のHP減算
	}
	if (hit->CheckObjNameHit(OBJ_ICICLE) != nullptr|| m_block_type == 5)//主人公がOBU_ICICLE(つらら)と溶岩床に当たっているかどうかの判定
	{
		hp_time--;//ダメージ加算制限処理

		if (m_block_type == 5)//ダメージ音再生
			Audio::Start(26);
		
		if (hp_time <= 0.0f)//主人公のダメージ制御
		{
			m_vx += 3.0f;//主人公ノックバック
			hp -= 20;//主人公のHP減算
			hp_time=10.6f;//ダメージ加算までの時間
		}
	}
	if (m_block_type == 3)//主人公がBossブロックを踏むとステージ移行
	{
		this->SetStatus(false);//主人公オブジェクト削除
		Hits::DeleteHitBox(this);//ヒットボックス削除

		//bossステージに移行
		Scene::SetScene(new SceneBossStage());
	}

	//主人公移動速度Max制限
	if (m_vx >= 10)
		m_vx = 10;
	if (m_vx <= -10)
		m_vx = -10;

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	
	

	//主人公が画面下に落ちたらゲームオーバーに移行
	if ( m_py > 600.0f)
	{
		
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		
		//主人公のHPがゼロになった時ゲームオーバー画面に移行する
		Scene::SetScene(new CSceneGameOver());
		
	}

	//HPが0以下になると死亡アニメーション作動
	if (hp <= 0)
	{
		hp = 0;
		
		if(m_del==false)
		Audio::Start(17);
		m_del = true;
	}
		

	if (m_del == true)
	{
		//着弾アニメーション
		//リソース着弾アニメーション位置
		RECT_F ani_src[6] =
		{    
			//top left right bottom
			{ 96,  0,  80, 192},
			{ 96, 80, 160, 192},
			{ 96,160, 240, 192},
			{192,  0,  80, 288},
			{192, 80, 160, 288},
			{192,160, 240, 288},
			

		};
		//アニメーションのコマ間隔
		if (m_ani_time2 > 6)
		{
			m_ani++;		//アニメーションのコマを1つ進める
			m_ani_time2 = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{

			m_ani_time2++;

		}
		if (m_ani == 6)//アニメーションが終わるとオブジェクト削除
		{
			this->SetStatus(false);//オブジェクト削除
			Hits::DeleteHitBox(this);//ヒットボックス削除

			//主人公のHPがゼロになった時ゲームオーバー画面に移行する
			Scene::SetScene(new CSceneGameOver());

		}

		return;

	}
}

//ドロー
void CObjHero::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	int AniData_walk[13] =
	{
		0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12 //主人公が歩くモーション
	};

	int AniData_Waiting[9] =
	{
		0, 1, 2, 3, 4, 5, 7, 8, 9 //主人公の待機モーション
	};

	int AniData_Jump[12]=
	{
		0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11//主人公のジャンプモーション
	};

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f       *  m_posture) + m_px;
	dst.m_right = (64 - 64.0f  *  m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	if (m_del==false)//主人公が死亡していなければ真
	{
		//歩きモーション--------------------------------
		if (Action_Walk == true && Action_Jump == false) {
			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = -5.0f + AniData_walk[m_ani_frame] * 80;
			src.m_right = 70.0 + AniData_walk[m_ani_frame] * 80;
			src.m_bottom = 96.0f;
			//描画　　　　　　　　　　　　　　 回転
			Draw::Draw(3, &src, &dst, c, 0.0f);
		}

		//待機モーション--------------------------------
		if (Action_Waiting == true && Action_Jump == false) {
			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData_Waiting[m_ani_frame_Waiting] * 80;
			src.m_right = 80.0 + AniData_Waiting[m_ani_frame_Waiting] * 80;
			src.m_bottom = 96.0f;
			//描画　　　　　　　　　　　　　　 回転
			Draw::Draw(2, &src, &dst, c, 0.0f);
		}


		//ジャンプモーション--------------------------------
		if (Action_Jump == true) {
			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData_Jump[m_ani_frame_Jump] * 80;
			src.m_right = 80.0 + AniData_Jump[m_ani_frame_Jump] * 80;
			src.m_bottom = 96.0f;
			//描画　　　　　　　　　　　　　　 回転
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}

		//ガードモーション----------------------------------
		if (Action_guard == true) {

			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = 480.0f ;
			src.m_right = 560.0 ;
			src.m_bottom = 96.0f;
			//描画　　　　　　　　　　　    回転
			Draw::Draw(18, &src, &dst, c, 0.0f);

		}
	}
	else
	{   //描画
		Draw::Draw(35, &m_eff, &dst, c, 0.0f);
	}
	

	//--------------------------------------------------
	//HP
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f * (hp/(float)hp_max);
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
	//dst.m_right = 190.0f - (pow * 50) ;
	//190 140 95 40
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

/*

/*
if (movesecond >= 21 && m_hit_down == true)
{
	Audio::Start(8);
	movesecond = 0;
}

//ダメージブロック
if (m_block_type == 5)
hp -= 0.5;


	}
	else if (Action_ani_flag != true)//キー入力がない場合は静止フレームにする
	{
	m_ani_time += 1;//アニメーションタイムを+1加算
	m_ani_move = 0;//静止アニメーションデータを指定

	

	}
	if (m_hit_down == false)//ジャンプアニメーション
	{
		m_ani_move = 2;//ジャンプアニメーションデータを指定

		if (jumpsecond >= 10)
		{
			m_ani_time += 1;//アニメーションタイムを+1加算
			if (SE_flag == false)
				Audio::Start(10);//SE再生(降下)

			SE_flag = true;
			jumpsecond = 0;
		}
		else
			jumpsecond = 100;
	}
	if (m_hit_down == true && SE_flag == true)//落下後Blockと接触時に着地音を鳴らす
	{
		Audio::Stop(10);
		SE_flag = false;
		Audio::Start(9);
*/









/*

//Anime(m_ani_time,m_ani_max_time,m_ani_frame,m_posture)


Anime(&m_ani_time, &m_ani_max_time,&m_ani_frame, &m_posture,
		ani_time,ani_frame,posture)



*m_ani_time += 2;

if (*m_ani_time > *m_ani_max_time)
{
	*m_ani_frame += 1;
	*m_ani_time = 0;
}


//アニメーション
if (*m_ani_frame == 12)
{

	*m_ani_frame = 0;


}

//アニメーション向き変更
*m_posture = 0.0f;
*/