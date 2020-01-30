//STL�f�o�b�O�@�\��Off�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUUGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneTitle.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneTitle::InitScene()
{

	//�J�[�\���쐬
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);


	CObjTitle* p = new CObjTitle();
	Objs::InsertObj(p, OBJ_TITLE, 10);


	//���y�ǂݍ���
	Audio::LoadAudio(0, L"Title.wav", BACK_MUSIC);

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);

	//���y�X�^�[�g
	Audio::Start(0);
	





}

//�Q�[���^�C�g�����s���\�b�h
void CSceneTitle::Scene()
{

}