// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "ObjEnemy.h"

#include "GameHead.h"
#include "ObjDescription.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDescription::CObjDescription(float x, float y)
{
	

}

//イニシャライズ
void CObjDescription::Init()
{
	
	//当たり判定用のHitBoxを作成
	//Hits::SetHitBox(this, m_x, m_y, 36, 30, ELEMENT_ITEM, OBJ_ITEM, 1);
}

//アクション
void CObjDescription::Action()
{






}

//ドロー
void CObjDescription::Draw()
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

	
	Font::StrDraw(L"操作説明" ,330,50,30,c);

	Font::StrDraw(L"左移動　　　　Aキー             右移動　　　　Dキー", 130, 100, 20, c);

	Font::StrDraw(L"ジャンプ　　　Spaceキー", 125, 130, 20, c);

	//Font::StrDraw(L"ダッシュ　　　Zキー", 455, 130, 20, c);

	Font::StrDraw(L"攻撃　　　マウス左クリック", 129, 160, 20, c);

	Font::StrDraw(L"攻撃切り替え　1(ぬ）キー：単発　2(ふ)キー：連射　", 180, 200, 20, c);

	Font::StrDraw(L"穴に落ちたらゲームスタート", 215, 240, 30, c);

}
