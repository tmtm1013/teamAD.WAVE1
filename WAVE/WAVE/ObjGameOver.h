#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲームオーバー
class CObjGameOver :public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();
	void Action();
	void Draw();
private:
	//左クリック

	float m_mou_x;
	float m_mou_y;
	float m_mou_r;
};