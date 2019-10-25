//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "ObjTitle.h"
#include "GameHead.h"
#include "SceneMain.h"

//使用するヘッダーファイル
using namespace GameL;

void CObjTitle::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
}

void CObjTitle::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//マウスの位置とクリックする場所で当たり判定
	if (m_mou_x > 240 && m_mou_x < 450 && m_mou_y > 350 && m_mou_y < 400)
	{
		//マウスのボタンが押されたらメインに移行
		if (m_mou_r == true || m_mou_l == true)
		{
			Scene::SetScene(new CSceneMain());
		}
	}
}

void CObjTitle::Draw()
{
	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	

	RECT_F src;
	RECT_F dst;


	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 972.0f;
	src.m_bottom = 483.0f;

	//表示位置
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x = %f, y = %f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, c);
	//仮マウスのボタンの状態
	if (m_mou_r == true)
		Font::StrDraw(L"R=押している", 20, 30, 12, c);
	else
		Font::StrDraw(L"R=押していない", 20, 30, 12, c);
	if (m_mou_l == true)
		Font::StrDraw(L"L=押している", 20, 40, 12, c);
	else
		Font::StrDraw(L"L=押していない", 20, 40, 12, c);

}

