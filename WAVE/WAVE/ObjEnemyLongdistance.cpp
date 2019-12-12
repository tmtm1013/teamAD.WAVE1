#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemyLongdistance.h"
#include "GameL\HitBoxManager.h"




//�g�p����l�[���X�y�[�X
using namespace GameL;

void   CObjEnemyLongdistance::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void   CObjEnemyLongdistance::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float   CObjEnemyLongdistance::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float  CObjEnemyLongdistance::GetEY()
{


	return m_py;


}

//�C�j�V�����C�Y
void CObjEnemyLongdistance::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	
	m_sx=64;  //�摜�T�C�Y��BlockHit�ɓn���p
	m_sy=64;

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.3f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	//block�Ƃ̏Փˏ�ԗp�m�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_hp = 100;//ENEMY��HP


	m_time = 0;//�e�ۗp�^�C��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemyLongdistance::Action()
{
	
	//�ʏ푬�x
	m_speed_power = 0.1f;
	m_ani_max_time = 2;


	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	
	m_time++;//�e�۔��˗p�^�C���C���N�������g



	//�e�ۗp�v���O����
	if (m_time >100)
	{
		if (!(x + 150.0f > m_px +( block->GetScroll()) &&x - 200.0f < m_px +( block->GetScroll()))) {//��l�����G�̋߂��ɗ������������U�������Ȃ�����v���O����

			m_time = 0;

			//�e�ۃI�u�W�F�N�g
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py);//�I�u�W�F�쐬
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 1);

			m_ani_move = 1;

		}

	}

	

	//��������l���̌����Ɉړ���������������B
	if ((m_px + block->GetScroll()) < x)//�E
	{

		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx += m_speed_power;
		m_posture = 1.0;
		m_ani_time += 1;
		m_ani_move = 1;

		if (m_hit_left == true )//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
		{


			m_vy = -13;


		}

	}
	else//��
    {

		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx -= m_speed_power;
		m_posture = 0.0;
		m_ani_time += 1;
		m_ani_move = 1;

		//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
		if ( m_hit_right == true)
		{

			
			m_vy = -13;


		}


    }
	//�A�j���[�V����
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
		m_ani_move = 1;
	}
	//�A�j���[�V����
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
		m_ani_move = 1;
	}



	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);



	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	
	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;



	if (m_px < 0.0f)
	{
		m_px = 0.0f;
	}
	

    //HitBox�̈ʒu�̕ύX
    CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px+32+ block->GetScroll(), m_py);



	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		m_hp -= 15;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -= 10;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -= 40;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -= 50;


	}

	//���������G����������B
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�G�����������ꍇ�G����������B
	}

	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);

		//�G�����ł�����+100�_
		((UserData*)Save::GetData())->m_point += 100;

	}


}

//�h���[
void CObjEnemyLongdistance::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
    //�u���b�N���������Ă���
    CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����A�j���[�V��������o�^
	int AniData[2][6] =
	{
		0, 1, 2, 3, 4, 5, //�ړ����[�V����
		0, 1, 2, 3, //�U�����[�V����
	};

	if (m_ani_move = 0)
	{

		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_bottom = 132.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 132.0f + m_py;
		dst.m_left = (-132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;

		//�`��
		Draw::Draw(14, &src, &dst, c, 0.0f);

	}

	if (m_ani_move = 1)
	{
		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f + (132 - 132 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_bottom = 132.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = -66.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 66.0f + m_py;

		
		//�`��
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
}

