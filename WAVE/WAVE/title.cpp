//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "title.h"
#include "GameHead.h"

//コンストラクタ
Ctitle::Ctitle()
{

}

//デストラクタ
Ctitle::~Ctitle()
{

}

//ゲーム初期化メソッド
void Ctitle::InitScene()
{
	CObjTitle* p = new CObjTitle();
	Objs::InsertObj(p, OBJ_TITLE, 1);
}

//ゲームタイトル実行メソッド
void Ctitle::Scene()
{

}