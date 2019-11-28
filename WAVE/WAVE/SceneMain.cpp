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
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
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
	//�O���f�[�^�̓ǂݎ��i�X�e�[�W���j
	unique_ptr<wchar_t>p;//�X�e�[�W���|�C���^�[
	int size;//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"Book3.csv", &size);//�O���f�[�^�ǂݍ���

	int map[10][100];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
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
	/*
	//���y�ǂݍ���
	Audio::Loadaudio(0, L"wav".BACK_MUSIC);
	Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	*/
	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SEgan/gun2.wav", SOUND_TYPE::EFFECT);//-----------�n���h�K�����ˉ��ǂݍ���----
	Audio::LoadAudio(3, L"SEgan/submachinegun2.wav", SOUND_TYPE::EFFECT);//�T�u�}�V���K�����ˉ��ǂݍ���----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);//-------�V���b�g�K�����ˉ��ǂݍ���----
	Audio::LoadAudio(5, L"SEgan/gun-gird1.wav", SOUND_TYPE::EFFECT);//-----����؂�ւ����ǂݍ���----
	Audio::LoadAudio(6, L"SEgan/cartridge1.wav", SOUND_TYPE::EFFECT);//----�J�[�g���b�W������----
	Audio::LoadAudio(7, L"SEgan/cartridge2.wav", SOUND_TYPE::EFFECT);//----�T�u�}�V���K���̃J�[�g���b�W������----
	Audio::LoadAudio(8, L"SEgan/landing.wav", SOUND_TYPE::EFFECT);//-------�W�����v���̓ǂݍ���----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------���n���̓ǂݍ���----


	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	//��l��(�O�i)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE3.png", 1, TEX_SIZE_1024);

	//��l��(�ҋ@)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);

	//��l��(�W�����v)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE4.png", 3, TEX_SIZE_1024);

	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Bullet3.png", 4, TEX_SIZE_256);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Gauge.jpg", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//��֒e�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//�w�i�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"ObjBlock.png", 9, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Block2.png", 10, TEX_SIZE_512);

	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"GameOver1.png", 11, TEX_SIZE_512);

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);

	//block�I�u�W�F�N�g�쐬

	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


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



	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 1);



	m_time = 0;
	m_time2 = 0;
	m_time3 = 0;
	m_time4 = 0;
	m_time5 = 0;
	m_time6 = 0;
	m_time7 = 0;
	m_time8 = 0;
	m_time9 = 0;
	m_time10 = 0;
	m_time11 = 0;

	Enemy = 1;

	EnemyJump = 1;

	EnemyRecovery = 1;

	EnemyAmmunition = 1;

	EnemyLongdistance = 1;

	Boss = 1;

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
	m_time11++;

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



		//�W�����v����G�o���p�v���O�����i����ʏo���j
		if (m_time3>100) {//�G�̏o���Ԋu

			if (EnemyJump <= 2) {//�G�̏o����

				CObjEnemyJump* obj_enemyjump = new CObjEnemyJump();
				Objs::InsertObj(obj_enemyjump, OBJ_ENEMY, 10);


			}

			EnemyJump++;

			m_time3 = 0;

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

		*/

		/*	//�e��A�C�e�������G�o���p�v���O�����i����ʏo���j
		if (m_time7 > 100) {//�G�̏o���Ԋu

			if (EnemyAmmunition <= 1) {//�G�̏o����

				CObjEnemyAmmunition* obj_enemyammunition = new CObjEnemyAmmunition(100, 100);
				Objs::InsertObj(obj_enemyammunition, OBJ_ENEMY, 10);

				EnemyAmmunition++;

				m_time7 = 0;

			}
		}*/


		/*
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


		/*
		//BOSS�v���O�����i�E��ʏo���j
		if (m_time10 > 100) {//�G�̏o���Ԋu

			if (Boss <= 1) {//�G�̏o����

				CObjBoss* obj_boss = new CObjBoss(320.0,400.0);
				Objs::InsertObj(obj_boss, OBJ_ENEMY, 10);
			}

			Boss++;

			m_time11 = 0;

		}*/

		//�ʏ�G�\���p�v���O�����i����ʏo���j
	if (m_time > 100)//�G�̏o���Ԋu
	{

		if (Enemy <= 2) {//�G�̏o����

		//�G�I�u�W�F�N�g�쐬
			CObjEnemy* obj_enemy = new CObjEnemy(600, 100);
			Objs::InsertObj(obj_enemy, OBJ_ENEMY, 10);
		}

		Enemy++;

		m_time = 0;
	}




}