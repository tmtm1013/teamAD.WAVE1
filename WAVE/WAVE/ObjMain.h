#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクトメイン
class CObjMain : public CObj
{
public :
	CObjMain() {};
	~CObjMain() {};
	void Init();
	void Action();
	void Draw();
private :
};
