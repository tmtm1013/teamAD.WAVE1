//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "SceneMain.h"
#include "ObjTitle.h"
#include "GameHead.h"
#include "ObjGameOver.h"
#include "GameL\DrawFont.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameOver::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
}

//アクション
void CObjGameOver::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonL();

	//マウスの位置とクリックする場所で当たり判定
	if (m_mou_x > 205 && m_mou_x < 325 && m_mou_y>490 && m_mou_y < 525)
	{
		//マウスのボタンが押されたらリスタート
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneMain());

		}
	}

	//マウスの位置とクリックする場所で当たり判定
	if (m_mou_x > 505 && m_mou_x < 590 && m_mou_y>490 && m_mou_y < 525)
	{

		//マウスのボタンが押されたらタイトル画面
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneTitle());

		}
	}






	/*
	if (Input::GetMouButtonL() == true)
	{
		Scene::SetScene()
	}*/
}



//ドロー
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

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