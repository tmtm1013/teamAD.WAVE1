//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "ObjAttackPoint.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjAttackPoint::Init()
{
	//得点の初期化
	((UserData*)Save::GetData())->m_point = 0;
}

//アクション
void CObjAttackPoint::Action()
{




}

//ドロー
void CObjAttackPoint::Draw()
{
	//得点を描画：右上 r g b a
	float cc[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"必 %d", ((UserData*)Save::GetData())->attackpoint);
	Font::StrDraw(str, 50, 500, 40, cc);
}