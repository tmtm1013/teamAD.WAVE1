#include "GameHead.h"
#include "CheckHit.h"

//CheckHit�֐��̒�`
//float m_x = �I�u�W�F�N�gA�� X ���W
//float m_y = �I�u�W�F�N�gA�� Y ���W

//float e_x = �I�u�W�F�N�gB�� X ���W
//float e_y = �I�u�W�F�N�gB�� Y ���W

bool CheckHit(float m_x, float m_y, float e_x, float e_y)
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	if (
		//�I�u�W�F�N�g�ƃI�u�W�F�N�g��X���̓����蔻��
		e_x - block->GetScroll() <= m_x + 100.0 && m_x <= e_x - block->GetScroll() + 100.0

		&&
		
		//�I�u�W�F�N�g�ƃI�u�W�F�N�g��Y���̓����蔻��
		m_y <= e_y + 500.0&& e_y <= m_y + 100.0)
	{
		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
	}
	else
	{
		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
	}
}