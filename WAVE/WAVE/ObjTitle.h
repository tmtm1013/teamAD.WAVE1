#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクトタイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();
	void Action();
	void Draw();
private :
	float m_mou_x; //マウスの位置X
	float m_mou_y; //マウスの位置Y
	bool m_mou_r; //マウスの右ボタン
	bool m_mou_l; //マウス左ボタン

	float b;//青用
	float t;//透過用

};
