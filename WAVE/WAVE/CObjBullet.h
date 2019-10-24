#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:主人公
class CObjBullet :public CObj
{
	public:
		CObjBullet(float x,float y);  //コンストラクタ
		   ~CObjBullet() {};
		   void Init();   //イニシャライズ
		   void Action(); //アクション
		   void Draw();   //ドロー
	private:
		float m_px;    //弾丸の X 方向の位置用変数
		float m_py;    //弾丸の Y 方向の位置用変数
		float m_vx;    //弾丸の X 方向の速度用変数
		
};
