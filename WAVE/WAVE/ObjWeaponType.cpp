#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "ObjWeaponType.h"
#include "GameHead.h"
#include "SceneMain.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWeaponType::CObjWeaponType(int type)
{
	weapontype =type;
}


//イニシャライズ
void CObjWeaponType::Init()
{
	
}

//アクション
void CObjWeaponType::Action()
{


}

//ドロー
void CObjWeaponType::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f * weapontype;//　+　weapontype * 切り取り位置
	src.m_right = 256.0f * weapontype;
	src.m_bottom = 256.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(39, &src, &dst, c, 0.0f);
}