#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�^�C��
class CObjTime : public CObj
{
public :
	CObjTime() {};
	~CObjTime() {};
	void Init();
	void Action();
	void Draw();

	void SetTimeFlag(bool b) { m_flag_time = b; }
private :
	int m_time;
	int m_time_count;
	bool m_flag_time;
	
};
