#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"

#define GRAUND (546.0f)

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;    //位置
	m_py = y;
}

extern float idou;

//イニシャライズ
void CObjEnemy::Init()
{

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f;  //右向き0.0f 左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //静止フレームを初期にする

	m_speed_power = 0.5f;  //通常速度
	m_ani_max_time = 2;    //アニメーション間隔幅
	m_ani_move = 0;

	m_hp = 100;//ENEMYのHP

	flag = true;


	m_move = false;//true=右

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 131, 132, ELEMENT_ENEMY, OBJ_ENEMY, 1);



}

//アクション
void CObjEnemy::Action()
{


	//通常速度
	m_speed_power = 0.1f;
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

	if (m_move == false)
	{
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}

	else if (m_move == true)
	{
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}


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

	//試しに
















	//位置の更新
	m_px += m_vx;
	m_py += m_vy;


	//敵の位置X(x_px)+主人公の幅分が+X軸方向に領域外を認識
	if (m_px + 64.0f > 800.0f)
	{
		m_px = 800.0f - 64.0f;//はみ出ない位置に移動させる

	}

	if (m_py + 64.0f > GRAUND)
	{
		//m_py = 0;
		m_py = GRAUND - 64.0f;

	}

	if (m_px < 0.0f)
	{
		m_px = 0.0f;
	}

	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);



	//敵と弾丸が接触したらHPが減る
	if (hit->CheckObjNameHit(OBJ_GRENADE) != nullptr)
	{

		m_hp -= 50;


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


		this->SetStatus(false);
		Hits::DeleteHitBox(this);



		if (flag == true)
		{
			//アイテムオブジェクト作成	
			CObjItem*obju = new CObjItem(m_px, m_py);
			Objs::InsertObj(obju, OBJ_ITEM, 7);
			flag = false;
		}



		//敵が消滅したら+100点
		((UserData*)Save::GetData())->m_point += 100;




		//敵消滅でシーンをゲームクリアに移行する
		//Scene::SetScene(new CSceneClear());

	}

}

//ドロー
void CObjEnemy::Draw()
{
	//歩くアニメーション情報を登録
	int AniData[1][6] =
	{
		0, 1, 2, 3, 4, 5,
	};


	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 131;
	src.m_right = 131.0f + AniData[m_ani_move][m_ani_frame] * 132;
	src.m_bottom = 132.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (131.0f * m_posture) + m_px;
	dst.m_right = (131 - 131.0f * m_posture) + m_px;
	dst.m_bottom = 132.0f + m_py;

	//描画
	Draw::Draw(5, &src, &dst, c, 0.0f);

}