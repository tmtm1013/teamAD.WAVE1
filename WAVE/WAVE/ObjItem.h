#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：アイテム
class CObjItem :public CObj
{
public:
	CObjItem(float x,float y) ;
	~CObjItem() {};
	void Init();	 //イニシャライズ
	void Action();	 //アクション
	void Draw();	 //ドロー
private:
	float bx,by;

	float m_x, m_y;
	float m_px, m_py;


	float  m_posture;

};
