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
	



		 int Enemy;//通常敵の数用変数
		 int EnemyJump;//ジャンプ用の敵数用変数
		 int EnemyRecovery;//主人公回復用の敵の数用変
		 int EnemyAmmunition;//敵弾丸所持用敵変
		 int EnemyLongdistance;//遠距離攻撃型敵用変数
		 int Boss;
}; 
