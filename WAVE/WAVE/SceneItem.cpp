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
#include "SceneItem.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneItem::CSceneItem()
{
	


}

//�f�X�g���N�^
CSceneItem::~CSceneItem()
{


}

//���������\�b�h
void CSceneItem::InitScene()
{
	CObjItem* obj = new CObjItem();
	Objs::InsertObj(obj, OBJ_ITEM, 10);

	

}

//���s�����\�b�h
void CSceneItem::Scene()
{

}
