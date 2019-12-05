#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_HERO,
	OBJ_BLOCK,
	OBJ_BLOCL2,
	OBJ_BLOCK3,
	OBJ_ENEMY,
	OBJ_TITLE,
	OBJ_MAIN,
	OBJ_TIME,

	OBJ_BULLET,
	OBJ_FULL_BULLET,
	OBJ_DIFFUSION_BULLET,
	OBJ_HOMING_BULLET,
	OBJ_ANGLE_BULLET,

	OBJ_BACKGROUND,

	OBJ_ENEMYJUMP,
	OBJ_ENEMYLONGDISTANCE,
	OBJ_BOSS,
	



	OBJ_CLEAR,
	OBJ_GAME_OVER,
	OBJ_ITEM,
	OBJ_GREN,

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

	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
extern float m_hp;
extern float kazu;
extern float idou;


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjHero.h"
#include "ObjBlock.h"
#include "ObjBlock2.h"
#include "ObjBlock3.h"


#include "ObjEnemy.h"
#include "ObjEnemyJump.h"
#include "ObjEnemyLongdistance.h"
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
#include "ObjTime.h"
#include "ObjGren.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"
#include "SceneBlock2.h"
#include "SceneBlock3.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "SceneItem.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneTitle