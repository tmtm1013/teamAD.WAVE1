//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "ObjMain.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMain::Init()
{
	//得点の初期化
	((UserData*)Save::GetData())->m_point = 0;
}

//アクション
void CObjMain::Action()
{




}

//ドロー
void CObjMain::Draw()
{
	//得点を描画：右上
	float cc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"得点 : %d点", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 650, 10, 20, cc);
}