//STLデバッグ機能OFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include"GameL\DrawTexture.h"


//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneGameOver.h"
#include "GameHead.h"

//コントラスタ
CSceneGameOver::CSceneGameOver()
{

}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{

}

//初期化メソッド
void CSceneGameOver::InitScene()
{
	
	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	//ゲームオーバーオブジェクト作成
	CObjGameOver*objf = new CObjGameOver();
    Objs::InsertObj(objf, OBJ_GAME_OVER, 3);

	
}

//実行中メソッド
void CSceneGameOver::Scene()
{

}

