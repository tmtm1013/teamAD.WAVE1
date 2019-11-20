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
private:



	float m_x;	//オブジェクトの位置
	float m_y;
	float m_vx;	//オブジェクトの移動用ベクトル
	float m_vy;
	float leng;
	float x;
	float y;


	bool button;
};
