#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_HERO,
	OBJ_BLOCK,
	OBJ_ENEMY,
	OBJ_TITLE,
	OBJ_MAIN,

	OBJ_BULLET,
	OBJ_FULL_BULLET,
	OBJ_DIFFUSION_BULLET,
	OBJ_HOMING_BULLET,
	OBJ_ANGLE_BULLET,

	OBJ_BACKGROUND,
	OBJ_ENEMYLEFT,
	OBJ_ENEMYJUMP,
	OBJ_ENEMYJUMPLEFT,
	OBJ_ENEMYRECOVERY,
	OBJ_ENEMYRECOVERYLEFT,
	OBJ_ENEMYAMMUNITION,
	OBJ_ENEMYAMMUNITIONLIFT,
	OBJ_ENEMYLONGDISTANCE,
	OBJ_ENEMYLONGDISTANCELEFT,
	OBJ_BOSS,
	



	
	OBJ_CLEAR,
	OBJ_GAME_OVER,
	OBJ_ITEM,

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
	int m_point;
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--



//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjHero.h"
#include "ObjBlock.h"
#include "ObjEnemy.h"
#include "ObjEnemyleft.h"
#include "ObjEnemyJump.h"
#include "ObjEnemyJumpleft.h"
#include "ObjEnemyRecovery.h"
#include "ObjEnemyRecoveryleft.h"
#include "ObjEnemyAmmunition.h"
#include "ObjEnemyAmmunitionleft.h"
#include "ObjEnemyLongdistance.h"
#include "ObjEnemyLongdistanceleft.h"
#include "ObjBoss.h"

#include "CObjBullet.h"
#include "CObjFullBullet.h"
#include "CObjDiffusionBullet.h"
#include "COHomingBullet.h "
#include "CObjAngleBullet.h"


#include "ObjTitle.h"
#include "ObjMain.h"
#include "ObjClear.h"
#include "ObjBackground.h"
//#include "CObjHomingBullet.h"
#include "ObjGameOver.h"
#include "ObjItem.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "SceneItem.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneTitle
//-----------------------------------------------