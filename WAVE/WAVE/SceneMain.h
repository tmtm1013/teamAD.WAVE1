#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:メイン
class CSceneMain :public CScene
{
	public:CSceneMain();
		   ~CSceneMain();
		   void InitScene();//初期化メソッド
		   void Scene();    //実行中メソッド
	private:
         int m_time;//敵の表示用タイム
		 int m_time2;//敵の表示タイム
		 int m_time3;
		 int m_time4;
		 int m_time5;
		 int m_time6;
		 int m_time7;
		 int m_time8;
		 int m_time9;
		 int m_time10;
		 int m_time11;



		 int Enemy;//通常敵の数用変数
		 int Enemyleft;//通常右敵の数用変数
		 int EnemyJump;//ジャンプ用の敵数用変数
		 int EnemyJumpleft;//ジャンプ用の敵右の数用変数
		 int EnemyRecovery;//主人公回復用の敵の数用変数
		 int EnemyRecoveryleft;//主人公回復用の敵の数用変数
		 int EnemyAmmunition;//敵弾丸所持用敵変数
		 int EnemyAmmunitionleft;//敵弾丸所持右用敵変数
		 int EnemyLongdistance;//遠距離攻撃型敵用変数
		 int EnemyLongdistanceleft;//遠距離攻撃型敵用変数
		 int Boss;
}; 
