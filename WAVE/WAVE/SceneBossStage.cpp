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
#include "SceneBossStage.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"



//�R���X�g���N�^
SceneBossStage::SceneBossStage()
{

}

//�f�X�g���N�^
SceneBossStage::~SceneBossStage()
{

}

//���������\�b�h
void SceneBossStage::InitScene()
{
	//�O���f�[�^�̓ǂݎ��i�X�e�[�W���j
	unique_ptr<wchar_t>p;//�X�e�[�W���|�C���^�[
	int size;//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"lBStage1.csv", &size);//�O���f�[�^�ǂݍ���

	int map[10][200];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			
			if (w >= 10)
			{
				count += 3;
			}
			else
			{
				count += 2;
			}


		}
	}


	//Font�쐬
	//Font::SetStrTex(L"0123456789���b");

	//���y���̓ǂݍ���
	Audio::LoadAudio(24, L"Boss3.wav", BACK_MUSIC);
	Audio::Start(24);//���y�X�^�[�g
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	//��l��(�O�i)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE3.png", 1, TEX_SIZE_1024);

	//��l��(�ҋ@)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);

	//��l��(�W�����v)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE4.png", 3, TEX_SIZE_1024);

	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512);

	Draw::LoadImageW(L"kakyuu.png", 18, TEX_SIZE_256);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Gagebase2.png", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//��֒e�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Block2.png", 10, TEX_SIZE_512);

	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"GAMEOVER01.png", 11, TEX_SIZE_512);
	
	Draw::LoadImageW(L"�h���S����s.png", 27, TEX_SIZE_1024);

	//JumpEnemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //�W�����v����G

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //�{�X

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //�e�ۂ��΂��G

	Draw::LoadImage(L"image1234.png", 24, TEX_SIZE_512);
	Draw::LoadImageW(L"FhitEff5.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"HhitEff1.png", 23, TEX_SIZE_512);

	//HP�J�o�[�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"gagecaver.png", 25, TEX_SIZE_512);

	//�K�E�Z�Q�[�W�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

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

	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

	//�X�R�A�\��
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);


	/*//�e�X�g�p:�e�ۃI�u�W�F�N�g�쐬
	CObjBullet* obj_b =new CObjBullet();//�e�ۃI�u�W�F�N�g
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	*/
	/*
	//�X�R�A�\��
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);
	*/

	/*//�e�X�g�p:�e�ۃI�u�W�F�N�g�쐬
	CObjBullet* obj_b =new CObjBullet();//�e�ۃI�u�W�F�N�g
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	*/

	/*
	//�O���f�[�^�̓ǂݎ��i�X�e�[�W���j
	unique_ptr<wchar_t>p2;//�X�e�[�W���|�C���^�[
	int size2;//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"stage02.csv", &size);//�O���f�[�^�ǂݍ���

	int map2[10][100];
	int count2 = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count2], L"%d", &w);

			map[i][j] = w;
			count += 2;


		}
	}

	*/



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
void SceneBossStage::Scene()
{

	//��l���̕K�E�Z�e�X�g�p
	((UserData*)Save::GetData())->attackpoint = 3;





}