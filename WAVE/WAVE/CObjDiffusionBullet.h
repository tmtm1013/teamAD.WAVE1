/*#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト:拡散弾
class CObjDiffusionBullet :public CObj
{
public:
	CObjDiffusionBullet(float x, float y);  //コンストラクタ
	~CObjDiffusionBullet() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_bx;    //弾丸の X 方向の位置用変数
	float m_by;    //弾丸の Y 方向の位置用変数
	float m_vx;    //弾丸の X 方向の速度用変数
	float m_vy;    //弾丸の Y 方向の速度用変数

	float bx;      //弾丸の X ベクトル値収納用変数 
	float by;      //弾丸の Y ベクトル値収納用変数

	float m_time;  //弾丸の射程距離の制御

	bool flag;     //発射角度制御フラグ

	float m_mou_bx;//マウスの X 方向の位置用変数
	float m_mou_by;//マウスの Y 方向の位置用変数

};*/

#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjDiffusionBullet : public CObj
{
public:
	CObjDiffusionBullet(float x, float y, float r);
	~CObjDiffusionBullet() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	float m_bx;//オブジェクトの位置
	float m_by;
	float m_vx;//Xベクトル保存用変数
	float m_vy;//Yベクトル保存用変数
	float m_r; //角度保存用変数
	float m_s; //弾スピード用変数

	float m_sx, m_sy;

	int m_time;

	float x;
	float y;

	//ブロックとの当たり判定用フラグ
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//当たっているblockの種類を確認用
	int m_block_type;


	bool flag; //弾丸バウンド制御用フラグ

	float pl_x;//現在のプレイヤーXの位置を保存用変数
	float pl_y;//現在のプレイヤーYの位置を保存用変数

	float m_bxp;

	bool button;
};
