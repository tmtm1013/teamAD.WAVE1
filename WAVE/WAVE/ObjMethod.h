#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクトメイン
class CObjMethod : public CObj
{
public:
	CObjMethod(){};
	~CObjMethod(){};
	void Init();
	void Action();
	void Draw();
private:

	bool flag; //他の処理に移行しないフラグ


};

