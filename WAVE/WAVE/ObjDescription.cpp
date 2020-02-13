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
	((UserData*)Save::GetData())->Scenecontinue = 0;

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

	float c[4] = { 0,0,0,1 };


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

	
	Font::StrDraw(L"操作説明" ,330,50,40,c);

	Font::StrDraw(L"左移動: A　Key 右移動: D Key", 130, 100, 25, c);

	Font::StrDraw(L"ジャンプ: Space Key", 125, 130, 25, c);

	Font::StrDraw(L"ダッシュ: 移動 + Shift", 455, 130, 25, c);

	Font::StrDraw(L"攻撃: マウス左クリック", 130, 160, 25, c);

	Font::StrDraw(L"攻撃切り替え　1(ぬ）キー：単発　2(ふ)キー：連射　", 180, 200, 25, c);
	Font::StrDraw(L"操作説明表示: Qキー", 215, 240, 25, c);


	Font::StrDraw(L"ゲームスタート→", 250, 300, 40, c);

	
}
