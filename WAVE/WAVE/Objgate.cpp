#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemy.h"
//#include "GameL\HitBoxManager.h"


//使用するネームスペース
using namespace GameL;
//位置情報X変更用
void  CObjgate::SetXX(float x)
{

	m_px = x;

}
//位置情報Y変更用
void  CObjgate::SetYY(float y)
{

	m_py = y;

}
//位置情報X取得用
float  CObjgate::GetEX()
{


	return m_px;


}
//位置情報Y取得用
float CObjgate::GetEY()
{


	return m_py;


}


//コンストラクタ
CObjgate::CObjgate(float x, float y)
{
	m_px = x;    //位置
	m_py = y;



}

//イニシャライズ
void CObjgate::Init()
{

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.0f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅
	m_ani_move = 0;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	//主人公との当たり判定
	HitCheck = false;


	m_hp = 10;



	/*
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_GATE, 2);
	*/
}
//アクション
void CObjgate::Action()
{
	/*
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//通常速度
	m_ani_max_time = 0;


	
	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();
	*/


	//摩擦の計算   -(運動energy X 摩擦係数)
	//m_vx += -(m_vx*0.098);

	/*
	//主人公とiCICLEの距離判定
	if ((m_px - 100.0 + block->GetScroll()) < x)
		HitCheck = true;

	//判定が真ならばICICLEを落下させる
	if (m_hit_down == false && HitCheck == true)
		m_vy += 9.8 / (16.0f);//自由落下運動

	if (m_hit_down == true)
		m_hp = -1;
	*/

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;



	/*
	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 5.0 + block->GetScroll(), m_py);
	

	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -=0;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		m_hp -= 0;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -= 0;


	}
	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -=0;


	}

	
	//ブロック当たり判定
	int d = 0;
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
		, &d
	);
	*/

	/*
	// 落下した敵を消去する。
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//敵が落下した場合敵を消去する。
	}


	//HPが0になったら破棄
	if (m_hp <= 0)
	{
		flag = true;




		//Scene::SetScene(new CSceneBlock2());//テスト



		this->SetStatus(false);
		Hits::DeleteHitBox(this);


	}

	*/
}

//ドロー
void CObjgate::Draw()
{
	


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;


	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 200.0f;
	dst.m_right =80.0f;
	dst.m_bottom = 70.0f;


	//描画
	Draw::Draw(37, &src, &dst, c, 0.0f);

}