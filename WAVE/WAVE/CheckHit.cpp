#include "GameHead.h"
#include "CheckHit.h"

//CheckHit�֐��̒�`
//float m_x = �I�u�W�F�N�gA�� X ���W

//float e_x = �I�u�W�F�N�gB�� X ���W

bool CheckHit(float m_x,float e_x)
{
	if (
		//�I�u�W�F�N�g�ƃI�u�W�F�N�g��X���̓����蔻��
		 e_x <= m_x + 64.0)
	{
		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
	}
	else if(m_x <= e_x + 64.0)
	{
		
		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
		
	}
	
}