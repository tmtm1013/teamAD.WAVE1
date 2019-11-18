//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
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
	/*
	//���y�ǂݍ���
	Audio::Loadaudio(0, L"wav".BACK_MUSIC);
	Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	*/
	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SEgan/gun2.wav",SOUND_TYPE::EFFECT);//�n���h�K�����ˉ��ǂݍ���
	Audio::LoadAudio(3, L"SEgan/submachinegun2.wav", SOUND_TYPE::EFFECT);//�T�u�}�V���K�����ˉ��ǂݍ���
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);//�V���b�g�K�����ˉ��ǂݍ���
	Audio::LoadAudio(5, L"SEgan/gun-gird1.wav", SOUND_TYPE::EFFECT);//����؂�ւ����ǂݍ���
	Audio::LoadAudio(6, L"SEgan/cartridge1.wav", SOUND_TYPE::EFFECT);//�J�[�g���b�W������
	Audio::LoadAudio(7, L"SEgan/cartridge2.wav", SOUND_TYPE::EFFECT);//�T�u�}�V���K���̃J�[�g���b�W������

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);
	
	//��l��(�ҋ@)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait2.png",5,TEX_SIZE_1024);

	//��l��(�O�i)�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/forward.png", 6, TEX_SIZE_1024);

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


	//Test�p�@�@�@�G�I�u�W�F�N�g�쐬
	CObjEnemy* obje = new CObjEnemy();
	Objs::InsertObj(obje, OBJ_ENEMY, 10);

	/*//�e�X�g�p:�e�ۃI�u�W�F�N�g�쐬
	CObjBullet* obj_b =new CObjBullet();//�e�ۃI�u�W�F�N�g
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	*/


	CObjMain* p = new CObjMain();
	Objs::InsertObj(p, OBJ_MAIN, 1);

	
}

//���s�����\�b�h
 void CSceneMain::Scene()
{

}


