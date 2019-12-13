#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjHomingBullet : public CObj
{
public:
	CObjHomingBullet(float x, float y);
	~CObjHomingBullet() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetBX();//�ʒu��񂘎擾�p
	float GetBY();//�ʒu���Y�擾�p
	void SetXX(float x);//�ʒu���X�ύX�p
	void SetYY(float y);//�ʒu���Y�ύX�p


private:
	float m_px;    //�ʒu
	float m_py;
	
	float m_x;	//�I�u�W�F�N�g�̈ʒu
	float m_y;
	float m_vx;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��
	float m_vy;
	float leng;
	float x;
	float y;


	bool button;
};
