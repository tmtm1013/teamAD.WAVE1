#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ホーミング弾丸
class CObjHomingBullet : public CObj
{
public :
	CObjHomingBullet(float x, float y);
	~CObjHomingBullet() {};
	void Init();
	void Action();
	void Draw();
private :
	float m_x; //ホーミング弾丸のx方向の位置
	float m_y; //ホーミング弾丸のy方向の位置 
	float m_vx; //ホーミング弾丸移動ベクトル位置
	float m_vy; //ホーミング弾丸移動ベクトル位置
	
};
