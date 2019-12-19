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
#include "SceneBlock2.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"



//�R���X�g���N�^
CSceneBlock2::CSceneBlock2()
{
	((UserData*)Save::GetData())->Scenecontinue=2;
}

//�f�X�g���N�^
CSceneBlock2::~CSceneBlock2()
{

}

//���������\�b�h
void CSceneBlock2::InitScene()
{
	//�O���f�[�^�̓ǂݎ��i�X�e�[�W���j
	unique_ptr<wchar_t>p;//�X�e�[�W���|�C���^�[
	int size;//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"stage0222.csv", &size);//�O���f�[�^�ǂݍ���

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

	//���y�ǂݍ���
	Audio::LoadAudio(22, L"back2.wav",BACK_MUSIC);
	Audio::Start(22);//���y�X�^�[�g
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	
	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SEgan/gun2.wav", SOUND_TYPE::EFFECT);//�n���h�K�����ˉ��ǂݍ���
	Audio::LoadAudio(3, L"SEgan/submachinegun2.wav", SOUND_TYPE::EFFECT);//�T�u�}�V���K�����ˉ��ǂݍ���
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);//�V���b�g�K�����ˉ��ǂݍ���
	Audio::LoadAudio(5, L"SEgan/gun-gird1.wav", SOUND_TYPE::EFFECT);//����؂�ւ����ǂݍ���
	Audio::LoadAudio(6, L"SEgan/cartridge1.wav", SOUND_TYPE::EFFECT);//�J�[�g���b�W������
	Audio::LoadAudio(7, L"SEgan/cartridge2.wav", SOUND_TYPE::EFFECT);//�T�u�}�V���K���̃J�[�g���b�W������
	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512);

	//�G�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"M.png", 21, TEX_SIZE_256);


	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Gauge.jpg", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//��֒e�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"blocka2.png", 10, TEX_SIZE_512);

	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	//JumpEnemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //�W�����v����G

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //�{�X

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //�e�ۂ��΂��G

	//�A�C�X�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"blocka1.png", 15, TEX_SIZE_512);

	//�_���[�W�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"dblock1.png", 16, TEX_SIZE_512);

	//�O���O���t�B�b�N�t�@�C���̓ǂݍ��݂O�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"image1234.png", 50, TEX_SIZE_512);


	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//block�I�u�W�F�N�g�쐬

	CObjBlock*objb2 = new CObjBlock(map);
	Objs::InsertObj(objb2, OBJ_BLOCK, 4);


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




}

//���s�����\�b�h
void CSceneBlock2::Scene()
{


}