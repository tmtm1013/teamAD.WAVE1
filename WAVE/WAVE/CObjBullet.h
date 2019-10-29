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
		float m_bx;    //弾丸の X 方向の位置用変数
		float m_by;    //弾丸の Y 方向の位置用変数
		float m_vx;    //弾丸の X 方向の速度用変数
		float m_vy;    //弾丸の Y 方向の速度用変数

		float bx;      //
		float by;      //

		bool flag;

		int speed;     //弾丸の速度
		float angle;   //マウスの中心点と角度返納

		float m_mou_bx;//弾丸の X 方向の位置用変数
		float m_mou_by;//弾丸の Y 方向の位置用変数
		
};
