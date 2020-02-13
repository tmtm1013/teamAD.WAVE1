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
	((UserData*)Save::GetData())->Scenecontinue =1;
	((UserData*)Save::GetData())->attackpoint   =2;//�����K�E�Z�c�e��
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
	p= Save::ExternalDataOpen(L"stage01.csv", &size);//�O���f�[�^�ǂݍ���
	
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

	
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	
	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SEgan/nomal.wav", SOUND_TYPE::EFFECT);// �ʏ�e ���ˉ��ǂݍ���----
	Audio::LoadAudio(3, L"SEgan/magic.wav", SOUND_TYPE::EFFECT);// ���e ���ˉ��ǂݍ���----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);// �����e ���ˉ��ǂݍ���----
	Audio::LoadAudio(5, L"SEgan/NomalM.wav", SOUND_TYPE::EFFECT);//    �Z�؂�ւ����̉�(�ʏ�e)----
	Audio::LoadAudio(6, L"SEgan/FullM.wav", SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(���e)----
	Audio::LoadAudio(7, L"SEgan/SpecialM.wav", SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(�点��e)----
	Audio::LoadAudio(8, L"SEgan/landing.wav", SOUND_TYPE::EFFECT);//-------�W�����v���̓ǂݍ���----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------���n���̓ǂݍ���----
	Audio::LoadAudio(10, L"SEgan/HitD.wav", SOUND_TYPE::EFFECT);//�G�Ɏ�l���������������̉�
	Audio::LoadAudio(11, L"SEgan/HitMA.wav", SOUND_TYPE::EFFECT);//�G�̖��@�U���ɓ����������̉�
	Audio::LoadAudio(12, L"SEgan/sou.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(13, L"SEgan/tyu.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(14, L"SEgan/dai.wav", SOUND_TYPE::EFFECT);//�G����l���̍U���ɓ����������̉�
	Audio::LoadAudio(15, L"SEgan/MAFlying.wav", SOUND_TYPE::EFFECT);//���@�U��
	Audio::LoadAudio(17, L"SEgan/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(18, L"SEgan/kakigoori.wav", SOUND_TYPE::EFFECT);//�����X
	Audio::LoadAudio(19, L"SEgan/kaihuku.wav", SOUND_TYPE::EFFECT);//��
	Audio::LoadAudio(26, L"SEgan/yakeruoto.wav", SOUND_TYPE::EFFECT);//�n��u���b�N�𓥂񂾎��̉�
	Audio::LoadAudio(27, L"SEgan/Ga-do.wav", SOUND_TYPE::EFFECT);//�K�[�h
	Audio::LoadAudio(29, L"SEgan/opu.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(30, L"SEgan/tojiru.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(31, L"SEgan/turarahit.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(25, L"SEgan/syoumetu.wav", SOUND_TYPE::EFFECT);//


	//���y�ǂݍ���
	Audio::LoadAudio(21, L"back1.wav", BACK_MUSIC);


	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  ��l�� (  �W�����v  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// ��l�� (  �ҋ@  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  ��l�� (�O�i) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//��l�� ( �K�[�h ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//��l�� ( �K�[�h ) �O���t�B�b�N�ǂݍ���



	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_1024);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Gagebase2.png", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"ice1.png", 7, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"grass01.png", 10, TEX_SIZE_1024);

	//�S�[���u���b�N�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Blockg1.png", 11, TEX_SIZE_512);

	//�W�����v����G
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_512);

	//�{�X
	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); 

	//�G�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"M.png", 20, TEX_SIZE_256);

	//�y���̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"soil1.png", 30, TEX_SIZE_512);

	//�v���C���[�K�E�Z�摜
	Draw::LoadImageW(L"hissatu.png", 34, TEX_SIZE_1024);
	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"image1234.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"FhitEff5.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"HhitEff1.png", 23, TEX_SIZE_512);
	Draw::LoadImageW(L"EhitEff.png", 24, TEX_SIZE_512);

	//HP�J�o�[�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"gagecaver.png", 25, TEX_SIZE_512);

	//�K�E�Z�Q�[�W�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);
	Draw::LoadImageW(L"HPGauge02_bg_01.png", 28, TEX_SIZE_512);
	Draw::LoadImageW(L"HPGauge02_red.png", 29, TEX_SIZE_512);


	//�e�ۏ��ŃG�t�F�N�g
	Draw::LoadImageW(L"HhitEff1.png", 23, TEX_SIZE_512);

	//�e�ۏ��ŃG�t�F�N�g
	Draw::LoadImageW(L"FhitEff5.png", 22, TEX_SIZE_512);
	//�G���ŃA�j���[�V�����摜�Ǎ�
	Draw::LoadImageW(L"shoumetu.png", 21, TEX_SIZE_2048);

	//��l�����S�A�j���[�V�����摜�ǂݍ���
	Draw::LoadImageW(L"Animation/death.png", 35, TEX_SIZE_1024);//��l�� ( ���S ) �O���t�B�b�N�ǂݍ���

	//�K�E�Z�񕜃A�C�e���O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"kakigouri.png", 36, TEX_SIZE_512);//�����X�O���t�B�b�N�ǂݍ���

	//���[�h�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Title.png", 37, TEX_SIZE_512);//�����X�O���t�B�b�N�ǂݍ���

	//��������O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Method.png", 38, TEX_SIZE_1024);//�����X�O���t�B�b�N�ǂݍ���

	//�o�b�N�~���[�W�b�N�X�^�[�g
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(21);//���y�X�^�[�g

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);


	//block�I�u�W�F�N�g�쐬
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
	
	//�w�i�̃I�u�W�F�N�g�쐬
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);
	
	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);
}

//���s�����\�b�h
void CSceneMain::Scene()
{
	//Method_flag = false;

	
	
}