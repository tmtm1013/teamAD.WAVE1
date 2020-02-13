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
	((UserData*)Save::GetData())->Scenecontinue = 0;
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
	p = Save::ExternalDataOpen(L"tutorial1.csv", &size);//�O���f�[�^�ǂݍ���

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
	Audio::LoadAudio(11, L"SEgan/MA.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(17, L"SEgan/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(27, L"SEgan/Ga-do.wav", SOUND_TYPE::EFFECT);//�K�[�h

	//���y�ǂݍ���
	//Audio::LoadAudio(0, L"Title.wav", BACK_MUSIC);
	Audio::LoadAudio(1, L"SEgan/k.wav", SOUND_TYPE::EFFECT);

	Audio::LoadAudio(0, L"tutorial.wav", BACK_MUSIC);
	Audio::Start(0);

	Draw::LoadImage(L"Title1.png", 15, TEX_SIZE_1024);//�^�C�g���O���t�B�b�N�ǂݍ���

	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512); //�e�ۃO���t�B�b�N�ǂݍ���

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	Draw::LoadImageW(L"Gagebase2.png", 6, TEX_SIZE_256);

	Draw::LoadImageW(L"ice1.png", 7, TEX_SIZE_512);//�񕜖�O���t�B�b�N�ǂݍ���

	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);//��֒e�O���t�B�b�N�ǂݍ���

	Draw::LoadImageW(L"Block2.png", 10, TEX_SIZE_512);//Block�̃O���t�B�b�N�ǂݍ���

	Draw::LoadImageW(L"GAMEOVER01.png", 11, TEX_SIZE_512);	//�Q�[���I�[�o�[�̃O���t�B�b�N�ǂݍ���

	//JumpEnemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //�W�����v����G

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //�{�X

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //�e�ۂ��΂��G


	//HP�J�o�[�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"gagecaver.png", 25, TEX_SIZE_512);

	//�K�E�Z�Q�[�W�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

	//�v���C���[�K�E�Z�摜
	Draw::LoadImageW(L"hissatu.png", 34, TEX_SIZE_1024);

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//block�I�u�W�F�N�g�쐬
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//��������I�u�W�F�N�g�쐬
	CObjDescription* obj_de = new CObjDescription(10,10);
	Objs::InsertObj(obj_de, OBJ_DESCRIPTION, 7);

	//�w�i�̃I�u�W�F�N�g�쐬
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

}

//���s�����\�b�h
void CSceneDescription::Scene()
{ 

	bool flag;//��l���̈攻��i�[�t���O

	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();

	flag = CheckWindow(x, y, 0 , 0, 800, 570);///�̈�O�Ȃ�false
	if (flag == false)
		Scene::SetScene(new CSceneMain());
}