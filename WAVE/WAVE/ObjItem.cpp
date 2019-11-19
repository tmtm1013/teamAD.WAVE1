// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjItem.h"

//使用するネームスペース
using namespace GameL;



//イニシャライズ
void CObjItem::Init()
{
	
	
	

}


//アクション
void CObjItem::Action()
{
	

	

	
}


//ドロー
void CObjItem::Draw()
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
	dst.m_right = 64.0f;
	dst.m_bottom = 64.0f;


	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);


	//Draw::LoadImage(L"Item.png", 0, TEX_SIZE_512);

	//Draw::LoadImage(L"dannyaku.png", 0, TEX_SIZE_512);

	CObjItem*obju = new CObjItem();
	Objs::InsertObj(obju, OBJ_ITEM, 4);

}