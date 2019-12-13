#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
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

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
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
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	int m_point;    //GameMain�o���|�C���g
	int SceneNum;   //�X�e�[�W�؂�ւ�
	int Scenecontinue;//�X�e�[�W��蒼��
		
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
extern float m_hp;
extern float kazu;




//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------
#include "UtilityModule.h"

//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
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

//�Q�[���V�[���N���X�w�b�_------------------------
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

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START SceneBossStage
//-----------------------------------------------