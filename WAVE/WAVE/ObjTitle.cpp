//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "ObjTitle.h"
#include "GameHead.h"
#include "SceneMain.h"

//使用するヘッダーファイル         
using namespace GameL;

void CObjTitle::Init()
{


	//音楽スタート
	Audio::Start(0);

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	time = 0;
	flag = false;

	b = 1.0f;
	t = 1.0f;

	((UserData*)Save::GetData())->SceneNum=1; //マップ移動用
	((UserData*)Save::GetData())->Scenecontinue = 1; //マップ移動用
}

void CObjTitle::Action()
{




	if (flag == true)//他の処理に移行しない処理
		while (1) {
			//マウスの位置を取得
			m_mou_x = (float)Input::GetPosX();
			m_mou_y = (float)Input::GetPosY();
			//マウスのボタンの状態
			m_mou_r = Input::GetMouButtonR();
			m_mou_l = Input::GetMouButtonL();
			//他の処理に移行しないための無限ループ
			//マウスの位置とクリックする場所で当たり判定
			if (m_mou_x > 440 && m_mou_x < 800 && m_mou_y > 440 && m_mou_y < 490)
			{
				//マウスのボタンが押されたらメインに移行
				if (m_mou_r == true || m_mou_l == true)
				{
					Audio::Start(1);

					//ボリュームを1.0に戻す
					float v = Audio::VolumeMaster(0);
					v = Audio::VolumeMaster(0.5 - v);

					this->SetStatus(false);//オブジェクト削除
					break;

				}
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
	src.m_right = 1024.0f;
	src.m_bottom = 570.0f;

	//表示位置
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(15, &src, &dst, c, 0.0f);

	
	/*
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
	  */       //   R    G    B    透過
	float d[4] = { 0, 0, b, t };
	
	Font::StrDraw(L">>ゲームスタート<<", 440, 440, 40, d);

	flag = true;
	
}

