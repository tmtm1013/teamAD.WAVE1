#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "ObjLoading.h"
#include "GameHead.h"
#include "SceneMain.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjLoading::Init()
{/*
	if (((UserData*)Save::GetData())->Scenecontinue == 0) {
		Draw::LoadImageW(L"village1.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 1) {
		Draw::LoadImageW(L"Background.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 2) {
		Draw::LoadImageW(L"stage2.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 3) {
		Draw::LoadImageW(L"hstage1.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 4) {
		Draw::LoadImageW(L"hstage2.png", 37, TEX_SIZE_1024);
	}*/
}

//アクション
void CObjLoading::Action()
{


}

//ドロー
void CObjLoading::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 739.0f;
	src.m_bottom = 415.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(37, &src, &dst, c, 0.0f);
}