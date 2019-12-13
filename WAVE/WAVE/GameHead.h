#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_HERO,
	OBJ_CURSOR,

	OBJ_BLOCK,
	OBJ_BLOCL2,
	OBJ_BLOCK3,
	OBJ_BOSS_STAGE,
	OBJ_ENEMY,
	OBJ_TITLE,
	OBJ_MAIN,
	OBJ_TIME,

	OBJ_BULLET,
	OBJ_FULL_BULLET,
	OBJ_DIFFUSION_BULLET,
	OBJ_HOMING_BULLET,
	OBJ_ANGLE_BULLET,
	OBJ_REVOLUTION_BULLET,

	OBJ_BACKGROUND,

	OBJ_FLYINGENEMY,
	OBJ_FLYINGENEMY2,
	OBJ_ENEMYJUMP,
	OBJ_ENEMYJUMP2,
	OBJ_ENEMYLONGDISTANCE,
	OBJ_BOSS,
	



	OBJ_CLEAR,
	OBJ_GAME_OVER,
	OBJ_ITEM,
	OBJ_GREN,
	OBJ_DESCRIPTION,
	OBJ_LASTBOSS,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	int m_point;    //GameMain出たポイント
	int SceneNum;   //ステージ切り替え
	int Scenecontinue;//ステージやり直し
		
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
extern float m_hp;
extern float kazu;




//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------
#include "UtilityModule.h"

//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjHero.h"
#include "ObjCursor.h"

#include "ObjBlock.h"
#include "ObjBlock2.h"
#include "ObjBlock3.h"
#include "ObjBossStage.h"
#include "ObjEnemy.h"


#include "ObjEnemy.h"
#include "ObjEnemyJump.h"
#include "ObjEnemyJump2.h"
#include "ObjEnemyLongdistance.h"
#include "ObjFlyingenemy.h"
#include "ObjFlyingEnemy2.h"
#include "ObjBoss.h"
#include "ObjBossSL.h"


#include "CObjBullet.h"
#include "CObjFullBullet.h"
#include "CObjDiffusionBullet.h"
#include "COHomingBullet.h "
#include "CObjAngleBullet.h"
#include "ObjRevolutionBullet.h"


#include "ObjTitle.h"
#include "ObjMain.h"
#include "ObjClear.h"
#include "ObjBackground.h"
//#include "CObjHomingBullet.h"
#include "ObjGameOver.h"
#include "ObjItem.h"
#include "ObjTime.h"
#include "ObjGren.h"
#include "ObjDescription.h"
#include "ObjLastBoss.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneBlock2.h"
#include "SceneBlock3.h"
#include "SceneBossStage.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "SceneItem.h"
#include "SceneDescription.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START SceneBossStage
//-----------------------------------------------