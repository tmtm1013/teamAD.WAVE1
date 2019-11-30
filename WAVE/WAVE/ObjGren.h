#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：アイテム
class CObjGren :public CObj
{
public:
	CObjGren(float x, float y);
	~CObjGren() {};
	void Init();	 //イニシャライズ
	void Action();	 //アクション
	void Draw();	 //ドロー
private:
	float  m_x;       //弾丸のX方向の位置用変数
	float  m_y;       //弾丸のY方向の位置用変数
	float  m_vx;      //弾丸のx方向の速度用変数 
	float  m_vy;      //弾丸のY方向の速度用変数

	float bx;      //弾丸の X ベクトル値収納用変数 
	float by;      //弾丸の Y ベクトル値収納用変数

	float m_bx;    //弾丸の X 方向の位置用変数
	float m_by;    //弾丸の Y 方向の位置用変数

	float flag;

	float m_mou_by;
	float m_mou_bx;

	float x, y;
	float vx, vy;

	
};
