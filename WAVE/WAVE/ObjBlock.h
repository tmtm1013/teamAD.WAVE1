#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock :public CObj
{
public:
	CObjBlock(int map[30][30]) ;
	~CObjBlock() {};
	void Init();
	void Action();
	void Draw();

	//ブロックとの当たり判定
	void BlockHit(
		float *x, float *y,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);


private:
	int m_map[30][30];//マップ情報（仮）

	float len;
	int r;
	float bx;
	float by;

};