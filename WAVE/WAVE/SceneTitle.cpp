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

	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);


	CObjTitle* p = new CObjTitle();
	Objs::InsertObj(p, OBJ_TITLE, 10);


	//音楽読み込み
	Audio::LoadAudio(0, L"Title.wav", BACK_MUSIC);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);

	//音楽スタート
	Audio::Start(0);
	





}

//ゲームタイトル実行メソッド
void CSceneTitle::Scene()
{

}