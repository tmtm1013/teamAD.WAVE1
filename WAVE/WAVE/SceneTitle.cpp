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
	//Draw::LoadImageW(L"title3.png", 1, TEX_SIZE_1024);
	CObjTitle* p = new CObjTitle();
	Objs::InsertObj(p, OBJ_TITLE, 10);
}

//�Q�[���^�C�g�����s���\�b�h
void CSceneTitle::Scene()
{

}