#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g���C��
class CObjMethod : public CObj
{
public:
	CObjMethod(){};
	~CObjMethod(){};
	void Init();
	void Action();
	void Draw();
private:

	bool flag; //���̏����Ɉڍs���Ȃ��t���O


};

