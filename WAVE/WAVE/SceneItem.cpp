// STLでバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneItem.h"
#include "GameHead.h"

//コンストラクタ
CSceneItem::CSceneItem()
{
	


}

//デストラクタ
CSceneItem::~CSceneItem()
{


}

//初期化メソッド
void CSceneItem::InitScene()
{
	CObjItem* obj = new CObjItem();
	Objs::InsertObj(obj, OBJ_ITEM, 10);

	

}

//実行中メソッド
void CSceneItem::Scene()
{

}
