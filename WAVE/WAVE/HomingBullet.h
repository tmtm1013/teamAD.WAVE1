#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�z�[�~���O�e��
class CObjHomingBullet : public CObj
{
public :
	CObjHomingBullet(float x, float y);
	~CObjHomingBullet() {};
	void Init();
	void Action();
	void Draw();
private :
	float m_x; //�z�[�~���O�e�ۂ�x�����̈ʒu
	float m_y; //�z�[�~���O�e�ۂ�y�����̈ʒu 
	float m_vx; //�z�[�~���O�e�ۈړ��x�N�g���ʒu
	float m_vy; //�z�[�~���O�e�ۈړ��x�N�g���ʒu
	
};
