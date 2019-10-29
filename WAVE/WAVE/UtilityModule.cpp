#include "GameHead.h"
#include <math.h>  //数学計算ヘッダー
#include "GameL\DrawTexture.h"
//使用するネームスペース
using namespace GameL;

//---UnitVec関数
//引数１　float* vx :ベクトルのX成分のポインタ
//引数２　float* vy :ベクトルのY成分のポインタ
//戻り値　bool      :trur=計算成功　flase=計算失敗
//内容
//引数のベクトルを正規化し、その値をvx,vyに変更します。
bool UnitVec(float* vx, float * vy)
{
	//ベクトルの長さを求める（三平方の定理）
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);

	r = sqrt(r);

	//長さが０かどうか調べる
	if (r == 0.0f)
	{
		;//０なら計算失敗
		return false;
	}
	else
	{
		//正規化を行う
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);
	}

	//計算成功
	return true;
}

//---CheckWindow関数
//引数1 float pos_x    :領域外かどうか調べるｘ位置
//引数2 float pos_y    :領域外かどうか調べるｙ位置
//引数3 float window_x :領域のtop位置
//引数4 float window_y :領域のleft位置
//引数5 float window_w :領域のright位置
//引数6 float window_h :領域のbottom位置
//戻り値 bool       :true=領域内  flase=領域外
//内容
//領域内かどうか調べる位置pos_(x,y)がwindow_(xywh)の内か外かを調べる

bool CheckWindow(float pos_x, float pos_y, float window_x, float window_y, float window_w, float window_h)
{
	//領域チェック
	if (pos_x < window_x)
	{
		return false;   //領域外
	}
	if (pos_x > window_w)
	{
		return false;   //領域外
	}
	if (pos_y < window_y)
	{
		return false;   //領域外
	}
	if (pos_y > window_h)
	{
		return false;   //領域外
	}
	return true;       //領域内
}

//---GetAtan2Angle関数
//引数１ float w        :幅
//引数２ float h        :高さ
//戻り値 float          :角度(0°～360°)
//内容
//高さと幅から直角三角形があると仮定しその角度を求める。
float GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w)*180.0f / 3.14;

	//-180°～-0°を180°～360°に変換
	if (r < 0)
	{
		r = 360 - abs(r);
	}

	return r;
}