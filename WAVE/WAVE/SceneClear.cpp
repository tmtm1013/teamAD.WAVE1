// STL�Ńo�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneClear.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneClear::CSceneClear()
{

}
//�f�X�g���N�^
CSceneClear::~CSceneClear()
{

}
//���������\�b�h
void CSceneClear::InitScene()
{
	
	//�N���A��ʃI�u�W�F�N�g�쐬
	CObjClear*objr = new CObjClear();
	Objs::InsertObj(objr, OBJ_CLEAR, 10);


	//���y�ǂݍ���
	/*Audio::LoadAudio(0, L"BGMClear.wav", BACK_MUSIC);

	//�{�����[����1.0�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);

	//���y�X�^�[�g
	Audio::Start(0);
	*/



}
//���s�����\�b�h
void CSceneClear::Scene()
{

}