//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
//#include "GameL/WinInputs.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneDescription.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "UtilityModule.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"



//�R���X�g���N�^
CSceneDescription::CSceneDescription()
{

}

//�f�X�g���N�^
CSceneDescription::~CSceneDescription()
{

}

//���������\�b�h
void CSceneDescription::InitScene()
{
	//�O���f�[�^�̓ǂݎ��i�X�e�[�W���j
	unique_ptr<wchar_t>p;//�X�e�[�W���|�C���^�[
	int size;//�X�e�[�W���̑傫��
	p = Save::ExternalDataOpen(L"stage000003.csv", &size);//�O���f�[�^�ǂݍ���

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



	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"image1.png", 1, TEX_SIZE_512);

	//���y�ǂݍ���
	//Audio::LoadAudio(22, L"back2.wav", BACK_MUSIC);
	//Audio::Start(22);//���y�X�^�[�g
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	
	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	//��l��(�O�i)�O���t�B�b�N�ǂݍ���


	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Bullet3.png", 4, TEX_SIZE_256);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Gauge.jpg", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Item.png", 7, TEX_SIZE_512);

	//��֒e�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Grenade.png", 8, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Block2.png", 10, TEX_SIZE_512);

	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	//JumpEnemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Animation/slime.png", 12, TEX_SIZE_1024); //�W�����v����G

	Draw::LoadImage(L"Animation/motion1.png", 13, TEX_SIZE_2048); //�{�X

	Draw::LoadImage(L"Animation/motion3.png", 14, TEX_SIZE_2048); //�e�ۂ��΂��G

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//block�I�u�W�F�N�g�쐬
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);


	//��������I�u�W�F�N�g�쐬
	CObjDescription* obj_de = new CObjDescription(10,10);
	Objs::InsertObj(obj_de, OBJ_DESCRIPTION, 7);


	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
}

//���s�����\�b�h
void CSceneDescription::Scene()
{
	

	bool flag;

	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();

	flag=CheckWindow(x, y, 0 , 0, 800, 570);
	if (flag == false)
		Scene::SetScene(new CSceneMain());
}