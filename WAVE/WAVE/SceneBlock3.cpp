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
	p = Save::ExternalDataOpen(L"stage333.csv", &size);//�O���f�[�^�ǂݍ���

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


		//�O���t�B�b�N�ǂݍ���
		//Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);

		//���y�ǂݍ���
	Audio::LoadAudio(25, L"maguma2.wav", BACK_MUSIC);//�}�O�}
	Audio::Start(25);//���y�X�^�[�g
	Audio::LoadAudio(23, L"back3.wav", BACK_MUSIC);
	Audio::Start(23);//���y�X�^�[�g
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  ��l�� (  �W�����v  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// ��l�� (  �ҋ@  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  ��l�� (�O�i) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//��l�� ( �K�[�h ) �O���t�B�b�N�ǂݍ���
	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SEgan/nomal.wav", SOUND_TYPE::EFFECT);// �ʏ�e ���ˉ��ǂݍ���----
	Audio::LoadAudio(3, L"SEgan/magic.wav", SOUND_TYPE::EFFECT);// ���e ���ˉ��ǂݍ���----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);// �����e ���ˉ��ǂݍ���----
	Audio::LoadAudio(5, L"SEgan/NomalM.wav", SOUND_TYPE::EFFECT);//    �Z�؂�ւ����̉�(�ʏ�e)----
	Audio::LoadAudio(6, L"SEgan/FullM.wav", SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(���e)----
	Audio::LoadAudio(7, L"SEgan/SpecialM.wav", SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(�点��e)----
	Audio::LoadAudio(8, L"SEgan/landing.wav", SOUND_TYPE::EFFECT);//-------�W�����v���̓ǂݍ���----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------���n���̓ǂݍ���----
	Audio::LoadAudio(10, L"SEgan/HitD.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"SEgan/HitMA.wav", SOUND_TYPE::EFFECT);//�G�̖��@�U���ɓ����������̉�
	Audio::LoadAudio(12, L"SEgan/sou.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(13, L"SEgan/tyu.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(14, L"SEgan/dai.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(15, L"SEgan/MAFlying.wav", SOUND_TYPE::EFFECT);//���@�U��
	Audio::LoadAudio(17, L"SEgan/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(18, L"SEgan/kakigoori.wav", SOUND_TYPE::EFFECT);//�����X
	Audio::LoadAudio(19, L"SEgan/kaihuku.wav", SOUND_TYPE::EFFECT);//��
	Audio::LoadAudio(26, L"SEgan/yakeruoto.wav", SOUND_TYPE::EFFECT);//�n��u���b�N�𓥂񂾎��̉�


    //�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512);

	//�G�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"M.png", 20, TEX_SIZE_256);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Gagebase2.png", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"block02.png", 10, TEX_SIZE_1024);

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

	//�n���
	Draw::LoadImageW(L"LavaAni1.png", 16, TEX_SIZE_512);

	//�_���[�W�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"dblock2.png", 17, TEX_SIZE_512);

	//�X���̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"icicle.png", 24, TEX_SIZE_512);

	Draw::LoadImageW(L"FhitEff5.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"HhitEff1.png", 23, TEX_SIZE_512);
	//HP�J�o�[�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"gagecaver.png", 25, TEX_SIZE_512);

	//�K�E�Z�Q�[�W�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"shoumetu.png", 21, TEX_SIZE_2048);
	
	//�v���C���[�K�E�Z�摜
	Draw::LoadImageW(L"hissatu.png", 34, TEX_SIZE_1024);

	//��l�����S�A�j���[�V�����摜�ǂݍ���
	Draw::LoadImageW(L"Animation/death.png", 35, TEX_SIZE_1024);//��l�� ( ���S ) �O���t�B�b�N�ǂݍ���

	//�K�E�Z�񕜃A�C�e���O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"kakigouri.png", 36, TEX_SIZE_512);//�����X�O���t�B�b�N�ǂݍ���

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);

	//�w�i�̃I�u�W�F�N�g�쐬
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);


	//block�I�u�W�F�N�g�쐬
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);


	//�n��ǃI�u�W�F�N�g�쐬
	CObjDangerWall* objdw = new CObjDangerWall();
	Objs::InsertObj(objdw, OBJ_DANGER_WALL, 5);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//�^�C���I�u�W�F�N�g�쐬
	CObjTime* objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 11);


	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

	//�X�R�A�\��
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);

	

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