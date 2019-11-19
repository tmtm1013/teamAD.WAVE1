//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//#include "GameL/WinInputs.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjBackground.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"

//�R���X�g���N�^
CSceneMain::CSceneMain()
{

}

//�f�X�g���N�^
CSceneMain::~CSceneMain()
{

}

//���������\�b�h
void CSceneMain::InitScene()
{
	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);

	//�u���b�N�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"ObjBlock.png", 2, TEX_SIZE_512);

	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"GameOver1.png", 3, TEX_SIZE_512);


	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Bullet3.png", 4, TEX_SIZE_256);



	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//�w�i�̃I�u�W�F�N�g�쐬
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);

	

	/*//�e�X�g�p:�e�ۃI�u�W�F�N�g�쐬
	CObjBullet* obj_b =new CObjBullet();//�e�ۃI�u�W�F�N�g
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
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

//���s�����\�b�h
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
	 //�ʏ�G�\���p�v���O�����i����ʏo���j
		 if (m_time > 100)//�G�̏o���Ԋu
		 {

			 if (Enemy <=2) {//�G�̏o����

				 //�G�I�u�W�F�N�g�쐬
				 CObjEnemy* obj_enemy = new CObjEnemy();
				 Objs::InsertObj(obj_enemy, OBJ_ENEMY, 10);
			 }

			 Enemy++;

			 m_time = 0;
		 }
		 //�ʏ�G�\���p�v���O�����i�E��ʏo���j
		 if (m_time2>250) {//�G�̏o���Ԋu

			 if (Enemyleft <= 2) {//�G�̏o����

				 CObjEnemyleft* obj_enemyleft = new CObjEnemyleft();
				 Objs::InsertObj(obj_enemyleft, OBJ_ENEMY, 10);
			 }

			 Enemyleft++;

			 m_time2 = 0;
		 }

		 
		 //�W�����v����G�o���p�v���O�����i����ʏo���j
		 if (m_time3>100) {//�G�̏o���Ԋu

			 if (EnemyJump <= 2) {//�G�̏o����

				 CObjEnemyJump* obj_enemyjump = new CObjEnemyJump();
				 Objs::InsertObj(obj_enemyjump, OBJ_ENEMY, 10);


			 }

			 EnemyJump++;

			 m_time3 = 0;

		 }
		 //�W�����v����G�o���p�v���O�����i�E��ʏo���j
		 if (m_time4 > 100) {//�G�̏o���Ԋu

			 if (EnemyJumpleft <= 2) {//�G�̏o����

				 CObjEnemyJumpleft* obj_enemyjumpleft = new CObjEnemyJumpleft();
				 Objs::InsertObj(obj_enemyjumpleft, OBJ_ENEMY, 10);
			 }

			 EnemyJumpleft++;

			 m_time4 = 0;

		 }


		 //�񕜃A�C�e�������G�o���p�v���O�����i����ʏo���j
		 if (m_time5 > 100) {//�G�̏o���Ԋu

			 if (EnemyRecovery <= 2) {//�G�̏o����

				 CObjEnemyRecovery* obj_enemyrecovery = new CObjEnemyRecovery();
				 Objs::InsertObj(obj_enemyrecovery, OBJ_ENEMY, 10);
			 }

			 EnemyRecovery++;

			 m_time5 = 0;

		 }
		 //�񕜃A�C�e�������G�o���p�v���O�����i�E��ʏo���j
		 if (m_time6 > 100) {//�G�̏o���Ԋu

			 if (EnemyRecoveryleft <= 2) {//�G�̏o����

				 ObjEnemyRecoveryleft* obj_enemyrecoveryleft = new ObjEnemyRecoveryleft();
				 Objs::InsertObj(obj_enemyrecoveryleft, OBJ_ENEMY, 10);
			 }

			 EnemyRecoveryleft++;

			 m_time6 = 0;

		 }


		 //�e��A�C�e�������G�o���p�v���O�����i����ʏo���j
		 if (m_time7 > 100) {//�G�̏o���Ԋu

			 if (EnemyAmmunition <= 2) {//�G�̏o����

				 CObjEnemyAmmunition* obj_enemyammunition = new CObjEnemyAmmunition();
				 Objs::InsertObj(obj_enemyammunition, OBJ_ENEMY, 10);
			 }

			 EnemyAmmunition++;

			 m_time7 = 0;

		 }
		 //�e��A�C�e�������G�o���p�v���O�����i�E��ʏo���j
		 if (m_time8 > 100) {//�G�̏o���Ԋu

			 if (EnemyAmmunitionleft <= 2) {//�G�̏o����

				 CObjEnemyAmmunitionleft* obj_enemyammunitionleft = new CObjEnemyAmmunitionleft();
				 Objs::InsertObj(obj_enemyammunitionleft, OBJ_ENEMY, 10);
			 }

			 EnemyAmmunitionleft++;

			 m_time8 = 0;

		 }
		 

		//�������U���G�o���v���O�����i�E��ʏo���j
		 if (m_time9 > 100) {//�G�̏o���Ԋu

			 if (EnemyLongdistance <= 1) {//�G�̏o����

				 CObjEnemyLongdistance* obj_enemylongdistance = new CObjEnemyLongdistance();
				 Objs::InsertObj(obj_enemylongdistance, OBJ_ENEMY, 10);
			 }

			 EnemyLongdistance++;

			 m_time9 = 0;

		 }
		 */
		 //�������U���G�o���v���O�����i�E��ʏo���j
		 if (m_time10 > 100) {//�G�̏o���Ԋu

			 if (EnemyLongdistanceleft <= 1) {//�G�̏o����

				 CObjEnemyLongdistanceleft* obj_enemylongdistanceleft = new CObjEnemyLongdistanceleft();
				 Objs::InsertObj(obj_enemylongdistanceleft, OBJ_ENEMY, 10);
			 }

			 EnemyLongdistanceleft++;

			 m_time10 = 0;

		 }







}