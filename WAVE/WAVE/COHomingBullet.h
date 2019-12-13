#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjHomingBullet : public CObj
{
public:
	CObjHomingBullet(float x, float y);
	~CObjHomingBullet() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetBX();//位置情報ｘ取得用
	float GetBY();//位置情報Y取得用
	void SetXX(float x);//位置情報X変更用
	void SetYY(float y);//位置情報Y変更用


private:
	float m_px;    //位置
	float m_py;
	
	float m_x;	//オブジェクトの位置
	float m_y;
	float m_vx;	//オブジェクトの移動用ベクトル
	float m_vy;
	float leng;
	float x;
	float y;


	bool button;
};
