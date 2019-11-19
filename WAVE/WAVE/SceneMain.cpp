//STLデバッグ機能をOFFにする
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
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
	//グラフィック読み込み
	Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);

	//ブロックのグラフィック読み込み
	Draw::LoadImageW(L"ObjBlock.png", 2, TEX_SIZE_512);

	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GameOver1.png", 3, TEX_SIZE_512);


	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"Bullet3.png", 4, TEX_SIZE_256);



	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);

	

	/*//テスト用:弾丸オブジェクト作成
	CObjBullet* obj_b =new CObjBullet();//弾丸オブジェクト
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
	*/

	

	CObjMain* p = new CObjMain();
	Objs::InsertObj(p, OBJ_MAIN, 1);
	
	
	
	m_time  = 0;
	m_time2 = 0;
	m_time3 = 0;
	m_time4 = 0;
	m_time5 = 0;
	m_time6 = 0;
	m_time7 = 0;
	m_time8 = 0;
	m_time9 = 0;
	m_time10  = 0;

	Enemy = 1;
	Enemyleft = 1;
	EnemyJump = 1;
	EnemyJumpleft = 1;
	EnemyRecovery = 1;
	EnemyRecoveryleft = 1;
	EnemyAmmunition = 1;
	EnemyAmmunitionleft = 1;
	EnemyLongdistance = 1;
	EnemyLongdistanceleft = 1;
	
}

//実行中メソッド
 void CSceneMain::Scene()
{
	 m_time++;
	 m_time2++;
	 m_time3++;
	 m_time4++;
	 m_time5++;
	 m_time6++;
	 m_time7++;
	 m_time8++;
	 m_time9++;
	 m_time10++;





	 /*
	 //通常敵表示用プログラム（左画面出現）
		 if (m_time > 100)//敵の出現間隔
		 {

			 if (Enemy <=2) {//敵の出現数

				 //敵オブジェクト作成
				 CObjEnemy* obj_enemy = new CObjEnemy();
				 Objs::InsertObj(obj_enemy, OBJ_ENEMY, 10);
			 }

			 Enemy++;

			 m_time = 0;
		 }
		 //通常敵表示用プログラム（右画面出現）
		 if (m_time2>250) {//敵の出現間隔

			 if (Enemyleft <= 2) {//敵の出現数

				 CObjEnemyleft* obj_enemyleft = new CObjEnemyleft();
				 Objs::InsertObj(obj_enemyleft, OBJ_ENEMY, 10);
			 }

			 Enemyleft++;

			 m_time2 = 0;
		 }

		 
		 //ジャンプする敵出現用プログラム（左画面出現）
		 if (m_time3>100) {//敵の出現間隔

			 if (EnemyJump <= 2) {//敵の出現数

				 CObjEnemyJump* obj_enemyjump = new CObjEnemyJump();
				 Objs::InsertObj(obj_enemyjump, OBJ_ENEMY, 10);


			 }

			 EnemyJump++;

			 m_time3 = 0;

		 }
		 //ジャンプする敵出現用プログラム（右画面出現）
		 if (m_time4 > 100) {//敵の出現間隔

			 if (EnemyJumpleft <= 2) {//敵の出現数

				 CObjEnemyJumpleft* obj_enemyjumpleft = new CObjEnemyJumpleft();
				 Objs::InsertObj(obj_enemyjumpleft, OBJ_ENEMY, 10);
			 }

			 EnemyJumpleft++;

			 m_time4 = 0;

		 }


		 //回復アイテム所持敵出現用プログラム（左画面出現）
		 if (m_time5 > 100) {//敵の出現間隔

			 if (EnemyRecovery <= 2) {//敵の出現数

				 CObjEnemyRecovery* obj_enemyrecovery = new CObjEnemyRecovery();
				 Objs::InsertObj(obj_enemyrecovery, OBJ_ENEMY, 10);
			 }

			 EnemyRecovery++;

			 m_time5 = 0;

		 }
		 //回復アイテム所持敵出現用プログラム（右画面出現）
		 if (m_time6 > 100) {//敵の出現間隔

			 if (EnemyRecoveryleft <= 2) {//敵の出現数

				 ObjEnemyRecoveryleft* obj_enemyrecoveryleft = new ObjEnemyRecoveryleft();
				 Objs::InsertObj(obj_enemyrecoveryleft, OBJ_ENEMY, 10);
			 }

			 EnemyRecoveryleft++;

			 m_time6 = 0;

		 }


		 //弾薬アイテム所持敵出現用プログラム（左画面出現）
		 if (m_time7 > 100) {//敵の出現間隔

			 if (EnemyAmmunition <= 2) {//敵の出現数

				 CObjEnemyAmmunition* obj_enemyammunition = new CObjEnemyAmmunition();
				 Objs::InsertObj(obj_enemyammunition, OBJ_ENEMY, 10);
			 }

			 EnemyAmmunition++;

			 m_time7 = 0;

		 }
		 //弾薬アイテム所持敵出現用プログラム（右画面出現）
		 if (m_time8 > 100) {//敵の出現間隔

			 if (EnemyAmmunitionleft <= 2) {//敵の出現数

				 CObjEnemyAmmunitionleft* obj_enemyammunitionleft = new CObjEnemyAmmunitionleft();
				 Objs::InsertObj(obj_enemyammunitionleft, OBJ_ENEMY, 10);
			 }

			 EnemyAmmunitionleft++;

			 m_time8 = 0;

		 }
		 

		//遠距離攻撃敵出現プログラム（右画面出現）
		 if (m_time9 > 100) {//敵の出現間隔

			 if (EnemyLongdistance <= 1) {//敵の出現数

				 CObjEnemyLongdistance* obj_enemylongdistance = new CObjEnemyLongdistance();
				 Objs::InsertObj(obj_enemylongdistance, OBJ_ENEMY, 10);
			 }

			 EnemyLongdistance++;

			 m_time9 = 0;

		 }
		 */
		 //遠距離攻撃敵出現プログラム（右画面出現）
		 if (m_time10 > 100) {//敵の出現間隔

			 if (EnemyLongdistanceleft <= 1) {//敵の出現数

				 CObjEnemyLongdistanceleft* obj_enemylongdistanceleft = new CObjEnemyLongdistanceleft();
				 Objs::InsertObj(obj_enemylongdistanceleft, OBJ_ENEMY, 10);
			 }

			 EnemyLongdistanceleft++;

			 m_time10 = 0;

		 }







}