
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
#include "Graf.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGraf::CSceneGraf()
{
	
}

//�f�X�g���N�^
CSceneGraf::~CSceneGraf()
{

}

//���������\�b�h
void CSceneGraf::InitScene()
{


	//�e�ۃO���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_1024);

	//Enemy�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //�G�O���t�B�b�N

	//�̗̓O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Gauge.jpg", 6, TEX_SIZE_256);

	//�񕜖�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//��֒e�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//Block�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"blockg111.png", 10, TEX_SIZE_1024);

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

	//�_���[�W�u���b�N�̃O���t�B�b�N�̓ǂݍ���
	Draw::LoadImageW(L"dblock1.png", 17, TEX_SIZE_512);

	//�O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"image1234.png", 20, TEX_SIZE_512);



}

//���s�����\�b�h
void CSceneGraf::Scene()
{




}