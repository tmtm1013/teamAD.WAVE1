// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"

#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjClear.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjClear::Init()
{
	
}
//アクション
void CObjClear::Action()
{
	//エンターキーを押してシーン：ゲームTitleに移行する
	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}

//ドロー
void CObjClear::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


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

	//得点を描画：右上
	float cc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"得点 : %d点", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 650, 10, 20, cc);



	/*//スコア
	Font::StrDraw(L"score", 200, 250, 30, c);
	for (int i = 0; i < 15; i++)
	{

	}*/
	Draw::LoadImage(L"Clear1.png", 0, TEX_SIZE_512);

	/*CObjClear*objr = new CObjClear();
	Objs::InsertObj(objr, OBJ_CLEAR, 2);
	*/

	/*Font::StrDraw(L"GameClear", 250, 100, 70, c);

	//タイトルに戻るキー
	Font::StrDraw(L"Enter to title",220,500,50, c);
	*/

}