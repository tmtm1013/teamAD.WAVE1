// 使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "ObjEnemy.h"

#include "GameHead.h"
#include "ObjItem.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjItem::CObjItem(float x,float y)
{
	m_x = x;
	m_y = y;

}



//イニシャライズ
void CObjItem::Init()
{
	
	
	//当たり判定HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 36,30, ELEMENT_ITEM, OBJ_ITEM, 1);


}


//アクション
void CObjItem::Action()
{
	//HitBoxの位置の変更
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x+16.0, m_y +20.0);


	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		
		this->SetStatus(false);	
		Hits::DeleteHitBox(this);//が所有するHitBoxに消去する。

	}

	

	


	//当たり判定を行うオブジェクト情報部
	int data_base[2] =
	{
		OBJ_BLOCK,
		OBJ_HERO,
	};
	
}


//ドロー
void CObjItem::Draw()
{

	float c[4] = { 1,1,1,1 };


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;


	//表示位置の設定
	dst.m_top = 0.0f+m_y;
	dst.m_left = 0.0f+m_x;
	dst.m_right = 64.0f + m_x;
	dst.m_bottom = 64.0f + m_y;


	//描画
	Draw::Draw(7, &src, &dst, c, 0.0f);


	
}