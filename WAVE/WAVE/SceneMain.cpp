//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
#include "GameL/WinInputs.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
#include "OBJBoss.h"
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
	p= Save::ExternalDataOpen(L"stage001.csv", &size);//�O���f�[�^�ǂݍ���
	
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
	Audio::LoadAudio(21, L"back1.wav",BACK_MUSIC);
	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(21);//���y�X�^�[�g



	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	

	//Font�쐬
	Font::SetStrTex(L"0123456789���b");


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

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"blockg111.png", 10, TEX_SIZE_1024);

	//�S�[���u���b�N�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Blockg1.png", 11, TEX_SIZE_512);

	//�W�����v����G
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_512);

	//�{�X
	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); 

	//�e�ۂ��΂��G
	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); 

	//�A�C�X�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"blocka1.png", 15, TEX_SIZE_512);

	//�_���[�W�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"dblock1.png", 17, TEX_SIZE_512);


	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);

	//block�I�u�W�F�N�g�쐬

	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);


	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
	/*
	//boss�I�u�W�F�N�g�쐬
	CObjEnemyJump2* objz = new CObjEnemyJump2(600,300);
	Objs::InsertObj(objz, OBJ_ENEMYJUMP2, 12);
	*/
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




	/*//�e�X�g�p:�e�ۃI�u�W�F�N�g�쐬
	CObjBullet* obj_b =new CObjBullet();//�e�ۃI�u�W�F�N�g
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	*/

	
	//�X�R�A�\��
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);
	

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



}

//���s�����\�b�h
void CSceneMain::Scene()
{
	
	 
	

}