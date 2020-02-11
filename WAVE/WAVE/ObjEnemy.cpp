#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;
//�ʒu���X�ύX�p
void  CObjEnemy::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjEnemy::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjEnemy::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjEnemy::GetEY()
{


	return m_py;


}


//�R���X�g���N�^
CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_sx = 132;
	m_sy = 132;



	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.4f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	m_hp =60;//ENEMY��HP

	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;

	m_attack = false;

	m_ani_frame2 = 0;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);
	m_ani_max_time2 = 4;    //�A�j���[�V�����Ԋu��
	
}
//�A�N�V����
void CObjEnemy::Action()
{


	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�ʏ푬�x
	m_ani_max_time = 2;


	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();



	if (m_attack == false) {
		//��������l���̌����Ɉړ���������������B
		if ((m_px + block->GetScroll()) < x)//�E
		{
			m_ani_move = 1;//�����A�j���[�V��������

			//��l�����ړ����Ă��Ȃ����̃v���O����
			m_vx += m_speed_power;

			//�A�j���[�V�����֐��̌Ăяo��
			Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
				1, 4, 1.0f);

			//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
			if (m_hit_left == true)
			{
				m_vy = -13;
			}
		}
		else//��
		{

			m_ani_move = 1;//�����A�j���[�V��������

			//��l�����ړ����Ă��Ȃ����̃v���O����
			m_vx -= m_speed_power;

			//�A�j���[�V�����֐��̌Ăяo��
			Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
				1, 4, 0.0f);
			
			//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
			if (m_hit_right == true)
			{
				m_vy = -13;
			}
		}
	
	}


	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 32 + block->GetScroll(), m_py);



	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_attack = true;

		//�G�𓮂����Ȃ��悤�ɂ���B
		m_vx = 0;
		m_vy = 0;

	}
	if (m_attack==true) {



		m_ani_time += 1;


		if (m_ani_time > m_ani_max_time2)
		{
			m_ani_frame2 += 1;
			m_ani_time = 0;
		}


		//�A�j���[�V����
		if (m_ani_frame2 == 3)
		{
			m_ani_frame2 = 0;

			m_attack = false;
		}



	}
	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	if (m_hit_down == false)
	{
		m_vy += 9.8 / (16.0f);
	}


	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;


	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -= 50;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		
		m_hp -= 60;

		Audio::Start(12);
	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -= 10;

		Audio::Start(13);
	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -= 40;

		Audio::Start(14);
	}



	//�u���b�N�����蔻��
	int d = 0;
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
		, &d
	);


   

	// ���������G����������B
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�G�����������ꍇ�G����������B
	}

	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{
		//�G�𓮂����Ȃ��悤�ɂ���B
		m_vx = 0;
		m_vy = 0;

		m_del = true;//���e�G�t�F�N�g�ڍs�p�t���O
		hit->SetInvincibility(true);//���薳��

		


	}
	if (m_del == true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[5] =
		{


			{0,  0,  204 ,200},
			{0, 204, 408 ,200},
			{0, 408, 612,200},
			{0, 612,816, 200},
		    {0, 816,1020,200},
		
		};
		//�A�j���[�V�����̃R�}�Ԋu
		if (m_ani_time2 > 2)
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time2 = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{

			m_ani_time2++;

		}

		if (m_ani == 5)
		{


			this->SetStatus(false);
			Hits::DeleteHitBox(this);


			//�G�����ł�����+100�_
			((UserData*)Save::GetData())->m_point += 10;


			//�A�C�e���I�u�W�F�N�g�쐬	
			CObjAitem*obju = new CObjAitem(m_px, m_py);
			Objs::InsertObj(obju, OBJ_AITEM, 7);

		}

		return;

	}
	
}

//�h���[
void CObjEnemy::Draw()
{ 
//�u���b�N���������Ă���
	
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�����A�j���[�V��������o�^
	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5, //�G���������[�V����
		
	};

	int AniDatatack[4] =
	{
		0, 1, 2, 3, //�U�����[�V����
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu
	
	


	//�\���ʒu�̐ݒ�
	dst.m_top = -66.0f + m_py;
	dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 66.0f + m_py;


	
		


		if (m_attack== true) {
			//�e�ۂ̏�Ԃŕ`���ύXif (m_del == true)
			if (m_del == true)
			{

				Draw::Draw(21, &m_eff, &dst, c, 0.0f);
				//���e�A�j���[�V����

			}
			else
			{


				//�؂���ʒu�̐ݒ�
				src.m_top = 133.0f;
				src.m_left = 3.0f + AniDatatack[m_ani_frame2] * 132;
				src.m_right = 132.0f + AniDatatack[m_ani_frame2] * 132;
				src.m_bottom = 264.0f;

				//�`��
				Draw::Draw(5, &src, &dst, c, 0.0f);

			}
		}
		else
		{


			//�e�ۂ̏�Ԃŕ`���ύX
			if (m_del == true)
			{

				Draw::Draw(21, &m_eff, &dst, c, 0.0f);
				//���e�A�j���[�V����

			}
			else
			{


				//�؂���ʒu�̐ݒ�
				src.m_top = 1.0f;
				src.m_left = 3.0f + AniData[m_ani_frame] * 132;
				src.m_right = 132.0f + AniData[m_ani_frame] * 132;
				src.m_bottom = 132.0f;

				//�`��
				Draw::Draw(5, &src, &dst, c, 0.0f);

			}


		}
}