//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "ObjMethod.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMethod::Init()
{

	flag = false; //他の処理に移行しないフラグ

}
//アクション
void CObjMethod::Action()
{

	if (flag == true)//他の処理に移行しない処理
		while (1) {//他の処理に移行しないための無限ループ
		
			
			if (Input::GetVKey('Q') == true) {//マウス左 が押されると真

				flag = false;//処理を止めるフラグを切り替える

			}
			if (Input::GetVKey('Q') == false && flag == false)
			{
				this->SetStatus(false);//操作説明削除

				break;//ループを抜ける
			}
		}

}
//ドロー
void CObjMethod::Draw()
{
	
	flag = true;//画像を表示した後、他の処理に移行しないフラグを真にする

	//得点を描画：右上
	float cc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"Qキーでゲームに戻る");
	Font::StrDraw(str, 450, 400, 20, cc);

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 470.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 500.0f;


	//描画
	Draw::Draw(38, &src, &dst, c, 0.0f);

	
}




