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
#include "SceneClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneClear::CSceneClear()
{

}
//デストラクタ
CSceneClear::~CSceneClear()
{

}
//初期化メソッド
void CSceneClear::InitScene()
{

	//クリアオブジェクト作成
	CObjClear* obj = new CObjClear();
	Objs::InsertObj(obj, OBJ_CLEAR, 10);

	//音楽読み込み
	/*Audio::LoadAudio(0, L"BGMClear.wav", BACK_MUSIC);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);

	//音楽スタート
	Audio::Start(0);
	*/



}
//実行中メソッド
void CSceneClear::Scene()
{

}