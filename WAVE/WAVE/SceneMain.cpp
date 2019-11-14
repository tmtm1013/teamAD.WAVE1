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
	
	
	
	m_time = 0;
	m_time2 = 0;
	m_time3= 0;
	Enemy = 1;
	Enemyleft = 1;
	EnemyJump = 1;
}

//���s�����\�b�h
 void CSceneMain::Scene()
{
	 m_time++;
	 m_time2++;
	 m_time3++;
	 /*
		 if (m_time > 100)//�G���o�Ă���Ԋu
		 {

			 if (Enemy <=2) {//�G�̐������߂鐔��
				 //�G�I�u�W�F�N�g�쐬
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