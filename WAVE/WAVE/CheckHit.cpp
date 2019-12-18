#include "GameHead.h"
#include "CheckHit.h"

//CheckHit関数の定義
//float m_x = オブジェクトAの X 座標

//float e_x = オブジェクトBの X 座標

bool CheckHit(float m_x,float e_x)
{
	if (
		//オブジェクトとオブジェクトのX軸の当たり判定
		 e_x <= m_x + 64.0)
	{
		return true;//判定結果当たっている( 真 )を返す
	}
	else if(m_x <= e_x + 64.0)
	{
		
		return false;//判定結果当たっていない( 偽 )を返す
		
	}
	
}