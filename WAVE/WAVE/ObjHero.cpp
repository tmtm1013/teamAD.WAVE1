#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "ObjItem.h"

#define GRAUND (546.0f)
#define ANIMAITON_FRAME (8)


//�g�p����l�[���X�y�[�X
using namespace GameL;

float idou;//�q�[���[�������Ă��邩�m�F����O���[�o���ϐ�



//�ʒu���X�ύX�p
void  CObjHero::SetXX(float x)
{

	m_px = x;



}
//�ʒu���Y�ύX�p
void  CObjHero::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjHero::GetXX()
{

	return m_px;


}
//�ʒu���Y�擾�p
float  CObjHero::GetYY()
{

	return m_py;

}

//�C�j�V�����C�Y
void CObjHero::Init()
{

	m_px = 300.0f;    //�ʒu
	m_py = 500.0f;

	m_sx = 64.0f;  //�摜�T�C�YBlockHit�֐��ɓn���p
	m_sy = 64.0f;

	m_mou_px = 0.0f;//����
	m_mou_py = 0.0f;

	m_mou_pr = 0.0f;
	m_mou_pl = 0.0f;

	m_f = true;   //�e�ې���
	m_time = 0.0f; //�e�۔��˕p�x����
	bullet_type = 1;//�e�ۂ̎��(�����n���h�K��)

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_timeJump = 0;
	m_ani_frame = 0;   //�Î~�t���[���������ɂ���
	m_ani_move = 1;    //�A�j���[�V�����I��
	//m_ret = 8;  //�A�j���[�V��������

	top = 0.0;
	left = 0.0;
	right = 80.0;
	bottom = 96.0;

	m_SEtime = 0;
	second = 0;
	SE_flag = true;//SE����p�t���O

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 10;    //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	flag = true;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = 10;//��l���̃q�b�g�|�C���g�p
	hp_max = 10;
	hp_now = hp_max;
	hp_time = 0.0f;//��l���̃q�b�g�|�C���g����p

	/*
	for (int i = 0; i < 28; i++)
	{



		srcAnim[i].top = top+;
		srcAnim[i].left = left+;
		srcAnim[i].right = right+;
		srcAnim[i].bottom = bottom+;

	}
	*/
}

//�A�N�V����
void CObjHero::Action()
{
	//SE����time


	if (second >= 600)
	{
		m_SEtime++;
		second = 0;
	}

	//m_SEtime = (second / 60) % 60; // 600 / 10 = 10�b

	//����؂�ւ�(1�`3)
	if (Input::GetVKey('1') == true)//�n���h�K��
	{
		if (m_SEtime >= 12)
			Audio::Start(5);//SE�Đ�(������)
		bullet_type = 1;//�e�ۂ̎�ނ��w��
		m_SEtime = 0;
	}
	if (Input::GetVKey('2') == true)//�T�u�}�V���K��
	{
		if (m_SEtime >= 12)
			Audio::Start(5);//SE�Đ�(������)
		bullet_type = 2;//�e�ۂ̎�ނ��w��
		m_SEtime = 0;

	}
	if (Input::GetVKey('3') == true)//�V���b�g�K��
	{
		if (m_SEtime >= 12)
			Audio::Start(5);//SE�Đ�(������)
		bullet_type = 3;//�e�ۂ̎�ނ��w��
		m_SEtime = 0;

	}

	//�����n���h�K���A�j���[�V����
	if (bullet_type == 1)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = 3;//�A�j���[�V�����f�[�^���w��
		}

	}
	//�����T�u�}�V���K���A�j���[�V����
	if (bullet_type == 2)
	{
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 4;//�A�j���[�V�����f�[�^���w��
	}
	//�����V���b�g�K���A�j���[�V����
	if (bullet_type == 3)
	{
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 5;//�A�j���[�V�����f�[�^���w��
	}


	//�e�۔��˕p�x����
	m_time += 0.1;


	//��l���̃n���h�K���e�۔���
	if (Input::GetMouButtonL() == true && m_time >= 2.0f&&bullet_type == 1)
	{
		if (m_f == true)
		{
			//���ˉ���炷
			//Audio::Start(2);

			//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
			CObjBullet* obj_b = new CObjBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_b, OBJ_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

				//Audio::Start(6);//��䰗�����

			m_f = false;
			m_time = 0.0f;
		}
	}
	else if (Input::GetMouButtonL() == false)
	{
		m_f = true;
	}

	//�T�u�}�V���K���e�۔���
	if (Input::GetMouButtonL() == true && m_time >= 0.8f&&bullet_type == 2)
	{
		//���ˉ���炷
		/*Audio::Start(2);//�T�u�}�V���K�����ˉ��Đ�
		m_SEtime++;*/

		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

		m_time = 0.0f;
		//Audio::Start(7);//��䰗�����
	}

	//�V���b�g�K���e�۔���
	if (Input::GetMouButtonL() == true && m_time >= 6.0f&&bullet_type == 3)
	{
		//���ˉ���炷
		//Audio::Start(4);//�V���b�g�K�����ˉ��Đ�


		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjDiffusionBullet* obj_db = new CObjDiffusionBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_db, OBJ_DIFFUSION_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

		m_time = 0.0f;

	}
	//��֒e����
	/*if (Input::GetVKey('Q') == true && m_time >= 10.0f)
	{
		if (m_f == true)
		{
			//���ˉ���炷
			//Audio::Start(2);

			//�e�ۃI�u�W�F�N�g�쐬
			CObjGrenade* obj_g = new CObjGrenade(m_px + 30.0f, m_py + 30.0f);//�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_g, OBJ_GRENADE, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			m_f = false;
			m_time = 0.0f;
		}
	}
	else
	{
		m_f = true;
	}
	*/

	if (Input::GetVKey('Y') == true && m_time >= 1.0f)
	{
		if (m_f == true)
		{
			//���ˉ���炷
			//Audio::Start(2);

			//�e�ۃI�u�W�F�N�g�쐬
			CObjGren* obj_g = new CObjGren(m_px, m_py );//�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_g, OBJ_GREN, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			m_f = false;
			m_time = 0.0f;
		}
	}
	else
	{
		m_f = true;
	}
	

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true, &m_sx, &m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);


	//SPACE�L�[���͂ŃW�����v
	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_hit_down == true)
		{
			Audio::Start(8);
			m_vy = -16;
		}
	}

	//Z�L�[���͂ő��x�A�b�v
	if (Input::GetVKey('Z') == true)
	{
		//�_�b�V�����̑��x
		m_speed_power = 1.1f;
		m_ani_max_time = 1;
	}

	else
	{
		//�ʏ푬�x
		m_speed_power = 0.5f;
		m_ani_max_time = 2;
	}

	//��l���̌����𐧌�
	//�}�E�X�̈ʒu���擾
	m_mou_px = (float)Input::GetPosX();
	m_mou_py = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_pr = Input::GetMouButtonR();
	m_mou_pl = Input::GetMouButtonL();

	//���Ɉړ����̏���
	if (Input::GetVKey('D') == true)
	{
		idou = 1;//��l���̓����Ă��邩�ǂ����̊m�F

		m_vx += m_speed_power;//�E�Ɉړ��x�N�g�����Z
		m_posture = 1.0f;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 1;//�����A�j���[�V�����f�[�^���w��
	
		if (second >= 2 && m_hit_down == true)
		{
			m_ani_time += 1;
		}
		if (second>=21&&m_hit_down==true)
		{
			Audio::Start(8);
			second = 0;
		}
		else 
		{
			second++;
		}
	}
	//���Ɉړ����̏���
	else if (Input::GetVKey('A') == true)
	{
		//���Ɉړ����̏���
		idou = 2;//��l���̓����Ă��邩�ǂ����̊m�F

		m_vx -= m_speed_power;//���Ɉړ��x�N�g�����Z
		m_posture = 0.0f;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 1;//�����A�j���[�V�����f�[�^���w��
		
		if (second >= 2 && m_hit_down == true)
		{
			m_ani_time += 1;
		}
		if (second >= 21 && m_hit_down == true)
		{
			Audio::Start(8);
			second = 0;
		}
		else
		{
			second++;
		}

	}
	else//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
	{
		idou = 3;//��l���̓����Ă��邩�ǂ����̊m�F

		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 0;//�Î~�A�j���[�V�����f�[�^���w��

	
		second = 100;
	

	}
	if (m_hit_down == false)//�W�����v�A�j���[�V����
	{

			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = 2;//�W�����v�A�j���[�V�����f�[�^���w��
			SE_flag = true;

	}
	if (m_hit_down == true && SE_flag == true)//������Block�ƐڐG���ɒ��n����炷
	{
		SE_flag = false;
	//	Audio::Start(9);
	}
	//�A�j���[�V�����Ԋu����
	if (m_ani_time  > m_ani_max_time)
	{
		m_ani_frame += 1;//�A�j���[�V�����t���[����+1���Z
		m_ani_time = 0; //�A�j���[�V�����^�C����������
	}

	//�A�j���[�V������������
	if (m_ani_frame == 10)
	{
		m_ani_frame = 0;//�A�j���[�V�����t���[����������
	}
	
	//HitBox�̈ʒu�̕ύXa
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);
	
	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	hp_time -= 0.1;

	//�񕜖�ɓ������hp��+����
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr)
	{

		m_hp += 10;

		hp += 50;

	}
	//OBJ_ENEMY�Ɠ�����Ǝ�l�����_���[�W�� 1 �󂯂�
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 1;

			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}

				HIT_DATA** hit_data;
				hit_data = hit->SearchObjNameHit(OBJ_ENEMY);


		/*float r = hit_data[0]->r;
		if ((r < 45 && r >= 0) || r > 315)
		{
			m_vx = -5.0f; //���Ɉړ�������B
		}
		if (r > 135 && r < 225)
		{
			m_vx = +5.0f; //�E�Ɉړ�������B
		}
	}

	//�������G�̍U���ڐG��Hero��HP������
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{

		

		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 1;
			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}

		//OBJ_BULLET�Ɠ�����Ǝ�l�����m�b�N�o�b�N����
		HIT_DATA** hit_data;
		hit_data = hit->SearchObjNameHit(OBJ_HOMING_BULLET);
		
		float r = hit_data[0]->r;
		if ((r < 45 && r >= 0) || r > 315)
		{
			m_vx = -5.0f; //���Ɉړ�������B
		}

		if (r > 135 && r < 225)
		{
			m_vx = +5.0f; //�E�Ɉړ�������B
		}
	}
	
	//��l����HP���[���ɂȂ�������l����������
	if (hp<=0) {

			this->SetStatus(false);
			Hits::DeleteHitBox(this);

		//��l����HP���[���ɂȂ������Q�[���I�[�o�[��ʂɈڍs����
		Scene::SetScene(new CSceneGameOver());
	}
	

			//�ʒu�̍X�V
			m_px += m_vx;
			m_py += m_vy;

	
}


//�h���[
void CObjHero::Draw()
{

	//�L�����N�^�[�̃A�j���[�V��������o�^
	int AniData[6][10] =
	{
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�Î~�A�j���[�V��������o�^-----(1���) m_ani_move = 0
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�n���h�K������(���s)-------------(2���) m_ani_move = 1
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�W�����v�A�j���[�V��������o�^-(3���) m_ani_move = 2
		{ 0 , 1 , 2 , 3 , 4 , 0 , 0 , 0 , 0 , 0 }, //�T�u�}�V���K������---------------(4���) m_ani_move = 3
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�V���b�g�K������-----------------(5���) m_ani_move = 4
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�_���[�W�A�j���[�V����-----------(6���) m_ani_move = 5

	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	if (m_ani_move == 1)//��l�����ړ����Ă��鎞�̕`��
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f + (80.0f - 80.0f*m_ani_move + 1);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 78;
		src.m_right = 78.0f + AniData[m_ani_move][m_ani_frame] * 78;
		src.m_bottom = 96.0 + (96.0f - 96.0f *m_ani_move + 1);

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f      * m_posture) + m_px;
		dst.m_right = (64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		m_posture = 0.0;

		//�`��
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	if (m_ani_move == 0)//��l�����Î~��Ԃ̎��̕`��
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_right = 80.0f + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_bottom = 96.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f      * m_posture) + m_px;
		dst.m_right = (64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		//�`��
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	if (m_ani_move == 2)//�W�����v�A�j���[�V����
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = top;
		src.m_left = left + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_right = right + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_bottom = bottom;
		//�\���ʒu�̐ݒ�s
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f        * m_posture) + m_px;
		dst.m_right = (64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		//�`��
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	/*if (m_ani_move == 3)//
	{
		//�؂���ʒu�̐ݒ�
		src.m_top    = top;
		src.m_left   = left  + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_right  = right + AniData[m_ani_move][m_ani_frame] * 80;
		src.m_bottom = bottom;
		//�\���ʒu�̐ݒ�s
		dst.m_top    = 0.0f  + m_py;
		dst.m_left   = ( 64.0f      * m_posture) + m_px;
		dst.m_right  = ( 64 - 64.0f * m_posture) + m_px;
		dst.m_bottom = 64.0f + m_py;

		//�`��
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}*/



	//HP
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 16.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 32.0f;
	dst.m_left = 32.0f;
	dst.m_right = dst.m_top + (128.0f*(hp / (float)hp_max));
	dst.m_bottom = 40.0f;

	Draw::Draw(6, &src, &dst, c, 0.0f);
}
