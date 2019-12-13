//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
//#include "GameL/WinInputs.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjBlock3.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"

//�R���X�g���N�^
CSceneBlock3::CSceneBlock3()
{
	((UserData*)Save::GetData())->Scenecontinue=3;
}

//�f�X�g���N�^
CSceneBlock3::~CSceneBlock3()
{

}

//���������\�b�h
void CSceneBlock3::InitScene()
{
	//�O���f�[�^�̓ǂݎ��i�X�e�[�W���j
	unique_ptr<wchar_t>p;//�X�e�[�W���|�C���^�[
	int size;//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"stage0333.csv", &size);//�O���f�[�^�ǂݍ���

	int map[10][200];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}


	//Font�쐬
		//Font::SetStrTex(L"0123456789���b");


		//�O���t�B�b�N�ǂݍ���
		//Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);

		//���y�ǂݍ���
	Audio::LoadAudio(22, L"back3.wav", BACK_MUSIC);
	Audio::Start(22);//���y�X�^�[�g
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	//Font�쐬
	Font::SetStrTex(L"0123456789���b");


	//�e�ۃO���t�B�b�N�ǂݍ���
	//Draw::LoadImage(L"Bullet3.png", 4, TEX_SIZE_256);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Gauge.jpg", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Item.png", 7, TEX_SIZE_512);

	//��֒e�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Grenade.png", 8, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Block2.png", 4, TEX_SIZE_512);



	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	//JumpEnemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Animation/slime.png", 12, TEX_SIZE_1024); //�W�����v����G

	Draw::LoadImage(L"Animation/motion1.png", 13, TEX_SIZE_2048); //�{�X

	Draw::LoadImage(L"Animation/motion3.png", 14, TEX_SIZE_2048); //�e�ۂ��΂��G

	//�A�C�X�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"blocka1.png", 15, TEX_SIZE_512);

	//�_���[�W�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"dblock2.png", 17, TEX_SIZE_512);

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//block�I�u�W�F�N�g�쐬
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);


	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	/*
	//BOSS�I�u�W�F�N�g�쐬
	CObjBoss* objboss = new CObjBoss(600,300);
	Objs::InsertObj(objboss, OBJ_BOSS, 10);
	*/

	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);


	//�w�i�̃I�u�W�F�N�g�쐬
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);
	/*
	//Test�p�@�@�@�G�I�u�W�F�N�g�쐬
	CObjEnemy* obje = new CObjEnemy();
	Objs::InsertObj(obje, OBJ_ENEMY, 10);
	*/

	//�^�C���I�u�W�F�N�g�쐬
	CObjTime* objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 11);



	/*//�e�X�g�p:�e�ۃI�u�W�F�N�g�쐬
	CObjBullet* obj_b =new CObjBullet();//�e�ۃI�u�W�F�N�g
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	*/

	/*
	//�X�R�A�\��
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);
	*/



}

//���s�����\�b�h
void CSceneBlock3::Scene()
{





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
		////�������U���G�o���v���O�����i�E��ʏo���j
		//if (m_time10 > 100) {//�G�̏o���Ԋu

		   // if (EnemyLongdistanceleft <= 1) {//�G�̏o����

		   //	 CObjEnemyLongdistanceleft* obj_enemylongdistanceleft = new CObjEnemyLongdistanceleft(750,0);
		   //	 Objs::InsertObj(obj_enemylongdistanceleft, OBJ_ENEMY, 10);
		   // }

		   // EnemyLongdistanceleft++;

		   // m_time10 = 0;

		//}







}