#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�A�C�e��
class CObjDescriptionUi :public CObj
{
public:
	CObjDescriptionUi(float x, float y);
	~CObjDescriptionUi() {};
	void Init();	 //�C�j�V�����C�Y
	void Action();	 //�A�N�V����
	void Draw();	 //�h���[
private:
	float bx, by;

	float m_x, m_y;





};
