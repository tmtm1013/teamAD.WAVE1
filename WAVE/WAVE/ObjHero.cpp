#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"

#define GRAUND (546.0f)

//�g�p����l�[���X�y�[�X
using namespace GameL;

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

	m_px = 0.0f;    //�ʒu
	m_py = 0.0f;

	m_mou_px = 0.0f;//����
	m_mou_py = 0.0f;

	m_mou_pr = 0.0f;
	m_mou_pl = 0.0f;

	m_f = true;   //�e�ې���
	m_time = 0.0f; //�e�۔��˕p�x����
	bullet_type = 1;

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���
	m_ani_move = 1;

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 4;    //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

	m_hp = 3;//��l��HP


	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO,  1);








	
}

//�A�N�V����
void CObjHero::Action()
{
	if (Input::GetVKey('1') == true)
		bullet_type = 1;
	if (Input::GetVKey('2') == true)
		bullet_type = 2;
	if (Input::GetVKey('3') == true)
		bullet_type = 3;
	/*
	//�����n���h�K���A�j���[�V����
	if (bullet_type==1)
	{
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 2;//�A�j���[�V�����f�[�^���w��
	}
	//�����T�u�}�V���K���A�j���[�V����
	if (bullet_type == 2)
	{

	}
	//�����V���b�g�K���A�j���[�V����
	if (bullet_type == 3)
	{

	}
	*/


	





	m_time += 0.1;
	

	//��l���̃n���h�K���e�۔���
	if (Input::GetMouButtonL() == true && m_time >= 2.0f&&bullet_type == 1)
	{
		
	
		if (m_f==true)
		{
			//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
			CObjBullet* obj_b = new CObjBullet(m_px+30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_b, OBJ_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			m_f = false;
			m_time = 0.0f;
			
		}

	}
	else if(Input::GetMouButtonL() == false)
	{
		m_f = true;
	}
	
	
	//�T�u�}�V���K���e�۔���
	if (Input::GetMouButtonL() == true && m_time >= 0.8f&&bullet_type == 2)
	{
	
			//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
			CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			m_time = 0.0f;

	}

	//�V���b�g�K���e�۔���
	if (Input::GetMouButtonL() == true && m_time >= 2.8f&&bullet_type == 3)
	{
		

		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjDiffusionBullet* obj_db = new CObjDiffusionBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_db, OBJ_DIFFUSION_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
		 
		m_time = 0.0f;

	}
	

	

	//X�L�[���͂ŃW�����v
	if (Input::GetVKey(VK_SPACE)==true)
	{
		if (m_py + 64.0f == GRAUND)
		{
			m_vy = -16;
		}
	}

	//Z�L�[���͂ő��x�A�b�v
	if (Input::GetVKey('Z')==true)
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
	if (Input::GetVKey('D')==true)
	{
		m_vx += m_speed_power;//�E�Ɉړ��x�N�g�����Z
		//m_posture = 1.0f;
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 0;//�����A�j���[�V�����f�[�^���w��
	}
	//�E�Ɉړ����̏���
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= m_speed_power;//���Ɉړ��x�N�g�����Z
		//m_posture = 0.0f;
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 0;//�����A�j���[�V�����f�[�^���w��
	}
	else
	{
		 //�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 1;//�Î~�A�j���[�V�����f�[�^���w��
	}
	//�A�j���[�V�����Ԋu����
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;//�A�j���[�V�����t���[����+1���Z
		m_ani_time = 0; //�A�j���[�V�����^�C����������
	}
	//�A�j���[�V������������
	if (m_ani_frame==4)
	{
		m_ani_frame = 0;//�A�j���[�V�����t���[����������
	}

	//��l�������Ƀ}�E�X�̕����Ɍ�������
	if (m_px > m_mou_px)
	{
		//���Ɍ���
		m_posture = 0.0f;
	}
	else
	{
		//�E�Ɍ���
		m_posture = 1.0f;
	}


	//HitBox�̈ʒu�̕ύXa
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	if (m_vy > 26 && m_py <= GRAUND)
	{
		m_vy = 0;
	}

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;


	


	//��l�����G�ƐڐG�����Ƃ���l����H��������
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{

		m_hp -= 1;


	}
	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);

		//��l�����łŃV�[�����Q�[���I�[�o�[�Ɉڍs����
		Scene::SetScene(new CSceneGameOver());

	}





	//��l���̈ʒuX(x_px)+��l���̕�����+X�������ɗ̈�O��F��
	if (m_px + 64.0f > 800.0f)
	{
		m_px = 800.0f - 64.0f;//�͂ݏo�Ȃ��ʒu�Ɉړ�������

	}
	if (m_px < 0.0f)
	{
		m_px = 0.0f;//�͂ݏo�Ȃ��ʒu�Ɉړ�������
	}


	//�e�X�g�p��������
	if (m_py + 64.0f > GRAUND)
	{
		//m_py = 0;
		m_py = GRAUND - 64.0f;
	
	}
}

//�h���[
void CObjHero::Draw()
{

	

	//�L�����N�^�[�̃A�j���[�V��������o�^
	int AniData[4][4] =
	{
		1 , 0 , 2 , 0, //1�n���h�K��
		1 , 2 , 2 , 1, //2�T�u�}�V���K��
		1 , 1 , 1 , 1, //3�V���b�g�K��
		1 , 1 , 1 , 1, //0�Î~�A�j���[�V��������o�^
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//��l�����ړ����Ă��鎞�̕`��
	if (Input::GetVKey('D') == true || Input::GetVKey('A') == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 64.0f;
		src.m_left = 256.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_right = 320.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_bottom = 128.0f;
	}
	else//��l�����Î~��Ԃ̎��̕`��
	{
		src.m_top = 320.0f;
		src.m_left = 256.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_right = 320.0f + AniData[m_ani_frame][m_ani_move] * 64;
		src.m_bottom = 386.0f;
	}
	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py;
	dst.m_left   = (      64.0f * m_posture ) + m_px;
	dst.m_right  = ( 64 - 64.0f * m_posture ) + m_px;
	dst.m_bottom = 64.0f+ m_py;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

}