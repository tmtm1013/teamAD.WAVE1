//STLデバッグ機能をOffにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUUGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneTitle.h"
#include "GameHead.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームタイトル初期化メソッド
void CSceneTitle::InitScene()
{



	CObjTitle* p = new CObjTitle();
	Objs::InsertObj(p, OBJ_TITLE, 10);
}

//ゲームタイトル実行メソッド
void CSceneTitle::Scene()
{

}