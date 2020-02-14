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

	//Audio::Start(60);




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

	Font::StrDraw(L"左移動: A　Key 右移動: D Key", 170, 150, 35, c);

	Font::StrDraw(L"ジャンプ: Space Key:", 80, 200, 30, c);

	Font::StrDraw(L"ダッシュ: 移動 + Shift:", 430, 200 , 30, c);

	Font::StrDraw(L"攻撃切り替え　1(ぬ）Key：単発　2(ふ)Key：連射:", 80, 300, 35, c);

	Font::StrDraw(L"必殺技：3（あ）Key:", 80, 350, 33, c);

	Font::StrDraw(L"操作説明表示: Qキー", 430, 350, 33, c);


	Font::StrDraw(L"ゲームスタート→", 250, 400, 45, c);


	Font::StrDraw(L"攻撃: マウス左クリック(マウスカーソル攻撃照準)", 80, 250, 30, c);
	
}
