// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjDescriptionUi.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDescriptionUi::CObjDescriptionUi(float x, float y)
{

}

//イニシャライズ
void CObjDescriptionUi::Init()
{

}

//アクション
void CObjDescriptionUi::Action()
{

}

//ドロー
void CObjDescriptionUi::Draw()
{

	float c[4] = { 1,1,1,1 };


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 0.0f;
	src.m_bottom = 0.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 0.0f;
	dst.m_bottom = 0.0f;

	//描画
	//Draw::Draw(0, &src, &dst, c, 0.0f);


	Font::StrDraw(L"操作説明", 330, 50, 30, c);

	Font::StrDraw(L"左移動　　　　Aキー             右移動　　　　Dキー", 130, 100, 20, c);

	Font::StrDraw(L"ジャンプ　　　Spaceキー", 125, 130, 20, c);

	//Font::StrDraw(L"ダッシュ　　　Zキー", 455, 130, 20, c);

	Font::StrDraw(L"攻撃　　　マウス左クリック", 129, 160, 20, c);

	Font::StrDraw(L"攻撃切り替え　2(ふ)キー", 455, 160, 20, c);

	Font::StrDraw(L"穴に落ちたらゲームスタート", 215, 200, 30, c);

}
