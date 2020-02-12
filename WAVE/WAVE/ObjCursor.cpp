//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "math.h"

#include "GameHead.h"
#include "ObjCursor.h"

#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjCursor::Init()
{
	
	//Cursor�̃O���t�B�b�N�ǂݍ���
	Draw::LoadImage(L"Cursor2.png", 16, TEX_SIZE_1024);


	x = 0;  //��l����X���ʒu���
	y = 0;  //��l����Y���ʒu���


	Cx = 0;//�~�̒��S�̍��W
	Cy = 0;
	Angle = 0;  //�~�̓����̊p�x
	R = 30;   //�~�̓����̔��a

	time=0;

	m_r = 0.0f;

	flag = true;

	button = false;

}

//�A�N�V����
void CObjCursor::Action()
{
	time++;

	m_mou_px = (float)Input::GetPosX();
	m_mou_py = (float)Input::GetPosY();
	if (time>=1)
	{
		m_r += 2.0f;

	}
	

	
	

}

//�h���[
void CObjCursor::Draw()
{
	           //   R    G    B    ����
	float c[4] = { 0.0f,0.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = -20.0f + m_mou_py ;
	dst.m_left   = -16.0f + m_mou_px ;
	dst.m_right  =  32.0f + m_mou_px ;
	dst.m_bottom =  28.0f + m_mou_py ;



	//�`��
	Draw::Draw(16, &src, &dst, c, m_r);

}