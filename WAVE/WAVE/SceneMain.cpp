#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBBUGGING (0)

#include "GameL\DrawTexture.h"

using namespace GameL;

#include "SceneMain.h"
#include "GameHead.h"

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//ゲームメインの初期化メソッド
void CSceneMain::InitScene()
{
	Draw::LoadImage(L"タイトル2.png", 0, TEX_SIZE_1024);
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}