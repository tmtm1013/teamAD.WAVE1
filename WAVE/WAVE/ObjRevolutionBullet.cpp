//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "math.h"

#include "GameHead.h"
#include "ObjRevolutionBullet.h"

#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjRevolutionBullet::CObjRevolutionBullet(float x, float y)
{
	m_x = x;  //��l����X�����擾
	m_y = y;  //��l����Y�����擾
}

//�C�j�V�����C�Y
void CObjRevolutionBullet::Init()
{
	m_vx = 2.0f;//�e�ۂ�X�������̑��x
	//m_vy = 0.0f;//�e�ۂ�Y�������̑��x
	x = 0;  //��l����X���ʒu���
	y = 0;  //��l����Y���ʒu���


	Cx=0;//�~�̒��S�̍��W
	Cy=0;
	Angle = 0;  //�~�̓����̊p�x
	R = 30;   //�~�̓����̔��a

	pos = 0;

	flag = true;

	button = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 16, 16, ELEMENT_WHITE, OBJ_REVOLUTION_BULLET, 1);

}

//�A�N�V����
void CObjRevolutionBullet::Action()
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	// �ʒu�̌v�Z
	Angle += 20;
	x = Cx + (cos(Angle)*R );
	y = Cy + (sin(Angle)*R );
	
	if (button == false)
	{
		//��l���̈ʒu���������Ŏ擾
		CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
		
		float ex = obj->GetXX();

		//�m�b�N�o�b�N�v���O����
		if (m_x + block->GetScroll() > ex + block->GetScroll())
		{
			pos = -1;
		}
		else //(m_px < ex)
		{
			pos = 1;
		}
		//float x = obj->GetXX();
		//float y = obj->GetYY();
        button = true;
		
	}
	m_x += m_vx * pos;

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + x, m_y + y);
	
	//�G�@�I�u�W�F�N�g�ƐڐG������e�ۏ���
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	//�̈�O�ɏo����e�ۂ�j������
	if (m_x > 800.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_x < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_y < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_y > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	//�u���b�N�Ɠ�����ƒe�ۍ폜
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}

}

//�h���[
void CObjRevolutionBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f +m_y+ y;
	dst.m_left = 0.0f +m_x+ x;
	dst.m_right = 32.0f +m_x+x;
	dst.m_bottom = 32.0f +m_y+ y;

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);

}