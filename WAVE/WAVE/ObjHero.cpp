#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"

#define GRAUND (546.0f)

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

	m_px = 0.0f;    //位置
	m_py = 0.0f;

	m_mou_px = 0.0f;//向き
	m_mou_py = 0.0f;

	m_mou_pr = 0.0f;
	m_mou_pl = 0.0f;

	m_f = true;   //弾丸制御
	m_time = 0.0f; //弾丸発射頻度制限
	bullet_type = 1;

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする
	m_ani_move = 1;

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 4;    //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	m_hp = 3;//主人公HP


	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO,  1);








	
}

//アクション
void CObjHero::Action()
{
	if (Input::GetVKey('1') == true)
		bullet_type = 1;
	if (Input::GetVKey('2') == true)
		bullet_type = 2;
	if (Input::GetVKey('3') == true)
		bullet_type = 3;
	/*
	//初期ハンドガンアニメーション
	if (bullet_type==1)
	{
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 2;//アニメーションデータを指定
	}
	//初期サブマシンガンアニメーション
	if (bullet_type == 2)
	{

	}
	//初期ショットガンアニメーション
	if (bullet_type == 3)
	{

	}
	*/


	





	m_time += 0.1;
	

	//主人公のハンドガン弾丸発射
	if (Input::GetMouButtonL() == true && m_time >= 2.0f&&bullet_type == 1)
	{
		
	
		if (m_f==true)
		{
			//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
			CObjBullet* obj_b = new CObjBullet(m_px+30.0f, m_py + 30.0f); //弾丸オブジェクト作成
			Objs::InsertObj(obj_b, OBJ_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

			m_f = false;
			m_time = 0.0f;
			
		}

	}
	else if(Input::GetMouButtonL() == false)
	{
		m_f = true;
	}
	
	
	//サブマシンガン弾丸発射
	if (Input::GetMouButtonL() == true && m_time >= 0.8f&&bullet_type == 2)
	{
	
			//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
			CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
			Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録

			m_time = 0.0f;

	}

	//ショットガン弾丸発射
	if (Input::GetMouButtonL() == true && m_time >= 2.8f&&bullet_type == 3)
	{
		

		//弾丸オブジェクト作成             //発射位置を主人公の位置+offset値
		CObjDiffusionBullet* obj_db = new CObjDiffusionBullet(m_px + 30.0f, m_py + 30.0f); //弾丸オブジェクト作成
		Objs::InsertObj(obj_db, OBJ_DIFFUSION_BULLET, 6);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
		 
		m_time = 0.0f;

	}
	

	

	//Xキー入力でジャンプ
	if (Input::GetVKey(VK_SPACE)==true)
	{
		if (m_py + 64.0f == GRAUND)
		{
			m_vy = -16;
		}
	}

	//Zキー入力で速度アップ
	if (Input::GetVKey('Z')==true)
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
	if (Input::GetVKey('D')==true)
	{
		m_vx += m_speed_power;//右に移動ベクトル加算
		//m_posture = 1.0f;
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 0;//歩くアニメーションデータを指定
	}
	//右に移動時の処理
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= m_speed_power;//左に移動ベクトル減算
		//m_posture = 0.0f;
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 0;//歩くアニメーションデータを指定
	}
	else
	{
		 //キー入力がない場合は静止フレームにする
		m_ani_time += 1;//アニメーションタイムを+1加算
		m_ani_move = 1;//静止アニメーションデータを指定
	}
	//アニメーション間隔制御
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;//アニメーションフレームを+1加算
		m_ani_time = 0; //アニメーションタイムを初期化
	}
	//アニメーションを初期化
	if (m_ani_frame==4)
	{
		m_ani_frame = 0;//アニメーションフレームを初期化
	}

	//主人公を軸にマウスの方向に向く処理
	if (m_px > m_mou_px)
	{
		//左に向く
		m_posture = 0.0f;
	}
	else
	{
		//右に向く
		m_posture = 1.0f;
	}


	//HitBoxの位置の変更a
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

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


	


	//主人公が敵と接触したとき主人公のHｐが減る
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{

		m_hp -= 1;


	}
	//HPが0になったら破棄
	if (m_hp <= 0)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);

		//主人公消滅でシーンをゲームオーバーに移行する
		Scene::SetScene(new CSceneGameOver());

	}





	//主人公の位置X(x_px)+主人公の幅分が+X軸方向に領域外を認識
	if (m_px + 64.0f > 800.0f)
	{
		m_px = 800.0f - 64.0f;//はみ出ない位置に移動させる

	}
	if (m_px < 0.0f)
	{
		m_px = 0.0f;//はみ出ない位置に移動させる
	}


	//テスト用落下制限
	if (m_py + 64.0f > GRAUND)
	{
		//m_py = 0;
		m_py = GRAUND - 64.0f;
	
	}
}

//ドロー
void CObjHero::Draw()
{

	

	//キャラクターのアニメーション情報を登録
	int AniData[4][4] =
	{
		1 , 0 , 2 , 0, //1ハンドガン
		1 , 2 , 2 , 1, //2サブマシンガン
		1 , 1 , 1 , 1, //3ショットガン
		1 , 1 , 1 , 1, //0静止アニメーション情報を登録
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//主人公が移動している時の描画
	if (Input::GetVKey('D') == true || Input::GetVKey('A') == true)
	{
		//切り取り位置の設定
		src.m_top = 64.0f;
		src.m_left = 256.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_right = 320.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_bottom = 128.0f;
	}
	else//主人公が静止状態の時の描画
	{
		src.m_top = 320.0f;
		src.m_left = 256.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_right = 320.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_bottom = 386.0f;
	}
	//表示位置の設定
	dst.m_top    = 0.0f + m_py;
	dst.m_left   = (      64.0f * m_posture ) + m_px;
	dst.m_right  = ( 64 - 64.0f * m_posture ) + m_px;
	dst.m_bottom = 64.0f+ m_py;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

}