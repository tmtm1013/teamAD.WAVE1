#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：アイテム
class CObjDescription :public CObj
{
public:
	CObjDescription(float x, float y);
	~CObjDescription() {};
	void Init();	 //イニシャライズ
	void Action();	 //アクション
	void Draw();	 //ドロー
private:
	float bx, by;

	float m_x, m_y;

	



};
