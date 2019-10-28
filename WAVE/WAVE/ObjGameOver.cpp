//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "SceneMain.h"
#include "ObjTitle.h"
#include "GameHead.h"
#include "ObjGameOver.h"

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
	if (m_mou_x > 300 && m_mou_x < 460 && m_mou_y>260 && m_mou_y < 310)
	{
		//マウスのボタンが押されたらリスタート
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneMain());

		}
	}

	//マウスの位置とクリックする場所で当たり判定
	if (m_mou_x > 230 && m_mou_x < 450 && m_mou_y>330 && m_mou_y < 350)
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


}