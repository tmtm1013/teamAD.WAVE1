#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock :public CObj
{
public:
	CObjBlock() {};
	~CObjBlock() {};
	void Init();
	void Action();
	void Draw();
private:
	int m_map[30][30];//マップ情報（仮）

	float len;
	int r;
	float y;

};