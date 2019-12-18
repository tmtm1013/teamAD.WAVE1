#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjCursor : public CObj
{
public:
	CObjCursor() {};
	~CObjCursor() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	float m_mou_px;	//オブジェクトの位置
	float m_mou_py;
	float m_vx;	//オブジェクトの移動用ベクトル
	float m_vy;

	float Angle;
	float R;
	float Cx, Cy;

	int second;

	float x;
	float y;

	bool flag; //弾丸バウンド制御用フラグ

	float pl_x;//現在のプレイヤーXの位置を保存用変数
	float pl_y;//現在のプレイヤーYの位置を保存用変数
	int time;
	float m_r;

	bool button;
};



