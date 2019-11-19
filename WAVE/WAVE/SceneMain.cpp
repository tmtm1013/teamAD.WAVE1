//STLデバッグ機能をOFFにする
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
//#include "GameL/WinInputs.h"
//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjBackground.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//初期化メソッド
void CSceneMain::InitScene()
{
	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//グラフィック読み込み
	Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);

	//ブロックのグラフィック読み込み
	Draw::LoadImageW(L"ObjBlock.png", 2, TEX_SIZE_512);

	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GameOver1.png", 3, TEX_SIZE_512);


	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"Bullet3.png", 4, TEX_SIZE_256);

	//体力グラフィック読み込み
	Draw::LoadImageW(L"Gauge.jpg", 5, TEX_SIZE_256);



	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);

	//タイムオブジェクト作成
	CObjTime* objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 11);

	

	/*//テスト用:弾丸オブジェクト作成
	CObjBullet* obj_b =new CObjBullet();//弾丸オブジェクト
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
	*/

	

	CObjMain* p = new CObjMain();
	Objs::InsertObj(p, OBJ_MAIN, 1);
	
	
	
	m_time = 0;
	m_time2 = 0;
	m_time3= 0;
	Enemy = 1;
	Enemyleft = 1;
	EnemyJump = 1;
}

//実行中メソッド
 void CSceneMain::Scene()
{
	 m_time++;
	 m_time2++;
	 m_time3++;
	 /*
		 if (m_time > 100)//敵が出てくる間隔
		 {

			 if (Enemy <=2) {//敵の数を決める数字
				 //敵オブジェクト作成
				 CObjEnemy* obj_enemy = new CObjEnemy();
				 Objs::InsertObj(obj_enemy, OBJ_ENEMY, 10);
				 
			 }

			 Enemy++;
			 
			
			 m_time = 0;
		 }
		 if (m_time2>250) {

			 if (Enemyleft <= 2) {

				 CObjEnemyleft* obj_enemyleft = new CObjEnemyleft();
				 Objs::InsertObj(obj_enemyleft, OBJ_ENEMY, 10);


			 }

			 Enemyleft++;

			 m_time2 = 0;

		 }
		 */
		 if (m_time3>100) {

			 if (EnemyJump <= 2) {

				 CObjEnemyJump* obj_enemyjump = new CObjEnemyJump();
				 Objs::InsertObj(obj_enemyjump, OBJ_ENEMY, 10);


			 }

			 EnemyJump++;

			 m_time3 = 0;





		 }



		
}