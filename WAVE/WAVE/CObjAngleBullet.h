#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：BOSS拡散弾
class CObjAngleBullet : public CObj
{
public:
	CObjAngleBullet(float x, float y,float r,float speed);
	~CObjAngleBullet() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:



	float m_x;	//オブジェクトの位置X
	float m_y;  //オブジェクトの位置Y
	float m_vx;	//オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY
	float m_r;  //移動する角度
	float m_speed;  //速度
	
};
