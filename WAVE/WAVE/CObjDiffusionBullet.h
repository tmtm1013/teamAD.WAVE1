#pragma once
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

};

