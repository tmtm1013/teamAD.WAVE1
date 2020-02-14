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
	((UserData*)Save::GetData())->Scenecontinue = 4;
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
	p = Save::ExternalDataOpen(L"Stage/lBStage1.csv", &size);//�O���f�[�^�ǂݍ���

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

	Font::SetStrTex(L"0123456789���b");

	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  ��l�� (  �W�����v  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// ��l�� (  �ҋ@  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  ��l�� (�O�i) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//��l�� ( �K�[�h ) �O���t�B�b�N�ǂݍ���


	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SE/nomal.wav", SOUND_TYPE::EFFECT);// �ʏ�e ���ˉ��ǂݍ���----
	Audio::LoadAudio(3, L"SE/magic.wav", SOUND_TYPE::EFFECT);// ���e ���ˉ��ǂݍ���----
	Audio::LoadAudio(4, L"SE/cannon1.wav", SOUND_TYPE::EFFECT);// �����e ���ˉ��ǂݍ���----
	Audio::LoadAudio(5, L"SE/NomalM.wav", SOUND_TYPE::EFFECT);//    �Z�؂�ւ����̉�(�ʏ�e)----
	Audio::LoadAudio(6, L"SE/FullM.wav", SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(���e)----
	Audio::LoadAudio(7, L"SE/SpecialM.wav", SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(�点��e)----
	Audio::LoadAudio(8, L"SE/landing.wav", SOUND_TYPE::EFFECT);//-------�W�����v���̓ǂݍ���----
	Audio::LoadAudio(9, L"SE/landingpoint.wav", SOUND_TYPE::EFFECT);//-------���n���̓ǂݍ���----
	Audio::LoadAudio(10, L"SE/HitD.wav", SOUND_TYPE::EFFECT);//�G�Ɏ�l���������������̉�
	Audio::LoadAudio(11, L"SE/HitMA.wav", SOUND_TYPE::EFFECT);//�G�̖��@�U���ɓ����������̉�
	Audio::LoadAudio(12, L"SE/sou.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(13, L"SE/tyu.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(14, L"SE/dai.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(15, L"SE/MAFlying.wav", SOUND_TYPE::EFFECT);//���@�U��
	Audio::LoadAudio(17, L"SE/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(18, L"SE/kakigoori.wav", SOUND_TYPE::EFFECT);//�����X
	Audio::LoadAudio(19, L"SE/kaihuku.wav", SOUND_TYPE::EFFECT);//��
	Audio::LoadAudio(26, L"SE/yakeruoto.wav", SOUND_TYPE::EFFECT);//�n��u���b�N�𓥂񂾎��̉�
	Audio::LoadAudio(27, L"SE/Ga-do.wav", SOUND_TYPE::EFFECT);//�K�[�h
	Audio::LoadAudio(29, L"SE/opu.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(30, L"SE/tojiru.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(31, L"SE/turarahit.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(25, L"SE/syoumetu.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(0, L"SE/Honoo.wav", SOUND_TYPE::EFFECT);//�{�X�U��



	//Font�쐬
	Font::SetStrTex(L"0123456789���b");
	
	///�G�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Bullet/M.png", 20, TEX_SIZE_256);

	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Bullet/cool.png", 4, TEX_SIZE_512);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"UI/Gagebase2.png", 6, TEX_SIZE_256);


	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Block/block3.png", 10, TEX_SIZE_512);

	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"BackGround/GAMEOVER01.png", 11, TEX_SIZE_512);
	
	Draw::LoadImageW(L"Animation/�h���S����s.png", 31, TEX_SIZE_1024);

	//�h���S���U���G�t�F�N�g�摜
	Draw::LoadImageW(L"Eff/image1234.png", 23, TEX_SIZE_512);


	Draw::LoadImageW(L"Eff/FhitEff5.png", 22, TEX_SIZE_512);

	//HP�J�o�[�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"UI/gagecaver.png", 25, TEX_SIZE_512);

	//�h���S���U���G�t�F�N�g�摜
	Draw::LoadImageW(L"Bullet/kakyuu.png", 24, TEX_SIZE_256);

	//�K�E�Z�Q�[�W�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"UI/HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"UI/HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

	//�{�X��HP�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"UI/HPGauge02_bg_01.png", 28, TEX_SIZE_512);
	Draw::LoadImageW(L"UI/HPGauge02_purple.png", 29, TEX_SIZE_512);

	//�v���C���[�K�E�Z�摜
	Draw::LoadImageW(L"Bullet/hissatu.png", 34, TEX_SIZE_1024);

	//��l�����S�A�j���[�V�����摜�ǂݍ���
	Draw::LoadImageW(L"Animation/death.png", 35, TEX_SIZE_1024);//��l�� ( ���S ) �O���t�B�b�N�ǂݍ���


	//���X�g�{�X�O���l�[�h
	Draw::LoadImageW(L"Bullet/taiyou.png", 36, TEX_SIZE_512);

	//��������O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"UI/Method.png", 38, TEX_SIZE_1024);//�����X�O���t�B�b�N�ǂݍ���


	//���y���̓ǂݍ���
	Audio::LoadAudio(24, L"BackM/Boss3.wav", BACK_MUSIC);
	Audio::Start(24);//���y�X�^�[�g
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);

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
	
	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

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



	

}

//���s�����\�b�h
void SceneBossStage::Scene()
{

	//��l���̕K�E�Z�e�X�g�p
	((UserData*)Save::GetData())->attackpoint = 3;





}