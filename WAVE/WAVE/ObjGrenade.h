#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：アイテム
class CObjGrenade :public CObj
{
public:
	CObjGrenade(float x,float y);
	~CObjGrenade() {};
	void Init();	 //イニシャライズ
	void Action();	 //アクション
	void Draw();	 //ドロー
private:
	float  m_x;       //弾丸のX方向の位置用変数
	float  m_y;       //弾丸のY方向の位置用変数
	float  m_vx;      //弾丸のx方向の速度用変数 
	float  m_vy;      //弾丸のY方向の速度用変数

	int	   m_ani;	  //着弾アニメーション用
	int    m_ani_time;//着弾アニメーション間隔タイム
	bool   m_del;	  //削除チェック
	//RECT_F m_eff;	  //着弾エフェクト描画用

	float bx;      //弾丸の X ベクトル値収納用変数 
	float by;      //弾丸の Y ベクトル値収納用変数

	float m_bx;    //弾丸の X 方向の位置用変数
	float m_by;    //弾丸の Y 方向の位置用変数

	bool flag;     //発射角度制御フラグ

	bool W;//幅
	bool H;//高さ

	float m_px;
	float m_py;

	float x, y;
	float vx, vy;

	float m_mou_bx;//マウスの X 方向の位置用変数
	float m_mou_by;//マウスの Y 方向の位置用変数

	float m_vv;
};
