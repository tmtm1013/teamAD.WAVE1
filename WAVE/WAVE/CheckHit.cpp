#include "GameHead.h"
#include "CheckHit.h"

//CheckHit関数の定義
//float m_x = オブジェクトAの X 座標
//float m_y = オブジェクトAの Y 座標

//float e_x = オブジェクトBの X 座標
//float e_y = オブジェクトBの Y 座標

bool CheckHit(float m_x, float m_y, float e_x, float e_y)
{
	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	if (
		//オブジェクトとオブジェクトのX軸の当たり判定
		e_x - block->GetScroll() <= m_x + 100.0 && m_x <= e_x - block->GetScroll() + 100.0

		&&
		
		//オブジェクトとオブジェクトのY軸の当たり判定
		m_y <= e_y + 500.0&& e_y <= m_y + 100.0)
	{
		return true;//判定結果当たっている( 真 )を返す
	}
	else
	{
		return false;//判定結果当たっていない( 偽 )を返す
	}
}