//STL�f�o�b�O�@�\OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include"GameL\DrawTexture.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���g���X�^
CSceneGameOver::CSceneGameOver()
{

}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{

}

//���������\�b�h
void CSceneGameOver::InitScene()
{
	
	Draw::LoadImage(L"GameOver1.png", 11, TEX_SIZE_512);


	//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	CObjGameOver*objf = new CObjGameOver();
    Objs::InsertObj(objf, OBJ_GAME_OVER, 3);

	
}

//���s�����\�b�h
void CSceneGameOver::Scene()
{

}

