#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：グレネード
class CObjGre : public CObj
{
public :
	CObjGre(float x, float y);
	~CObjGre() {};
	void Init();
	void Action();
	void Draw();
	
private :
	float m_vx; //速度変数
	float m_vy;

	int m_bx; //位置変数
	int m_by;

	float m_x; //弾丸のX方向の位置用変数
	float m_y; //弾丸のY方向の位置用変数

	float vx; //ベクトル数X方向
	float vy; //ベクトル数Y方向

	float x;
	float y;

	bool flag;


	int	   m_ani;	  //着弾アニメーション用
	int    m_ani_time;//着弾アニメーション間隔タイム
	bool   m_del;	  //削除チェック
};