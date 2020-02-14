#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:主人公
class CObjWeaponType :public CObj
{
public:
	CObjWeaponType(int type);
	~CObjWeaponType() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	short int weapontype;
	
};

