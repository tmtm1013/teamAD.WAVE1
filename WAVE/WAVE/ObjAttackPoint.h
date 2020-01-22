#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクトメイン
class CObjAttackPoint : public CObj
{
public:
	CObjAttackPoint() {};
	~CObjAttackPoint() {};
	void Init();
	void Action();
	void Draw();
private:

};

