#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"

#define GRAUND (546.0f)

//�g�p����l�[���X�y�[�X
using namespace GameL;

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

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��

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
	//m_vy = 0;
	//�ړ��x�N�g���̔j��
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	//��l���̒e�۔���
	if (Input::GetMouButtonL()==true)
	{
		if (m_f==true)
		{

			//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
			CObjBullet* obj_b = new CObjBullet(m_px+30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_b, OBJ_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			m_f = false;

		}

	}
	else
	{
		m_f = true;
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

	

	
	if (m_px > m_mou_px)
	{

			m_posture = 0.0f;

	}
	else
	{
			m_posture = 1.0f;

	}

		

	//�L�[�̓��͕���
	if (Input::GetVKey('D')==true)
	{
		m_vx += m_speed_power;
		//m_posture = 1.0f;
		m_ani_time += 1;
	}
	//�L�[�̓��͕���
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= m_speed_power;
		//m_posture = 0.0f;
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame = 1; //�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
		m_ani_time = 0;
	}

	if (m_ani_time>m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame==4)
	{
		m_ani_frame = 0;
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

	if (m_py + 64.0f > GRAUND)
	{
		//m_py = 0;
		m_py = GRAUND - 64.0f;
	
	}
	
	if (m_px < 0.0f)
	{
		m_px = 0.0f;
	}
	
}

//�h���[
void CObjHero::Draw()
{
	//�����A�j���[�V��������o�^
	int AniData[4] =
	{
		1 , 0 , 2 , 0,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 64.0f;
	src.m_left   = 256.0f + AniData[m_ani_frame] * 64;
	src.m_right  = 320.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 128.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f + m_py;
	dst.m_left   = (      64.0f * m_posture ) + m_px;
	dst.m_right  = ( 64 - 64.0f * m_posture ) + m_px;
	dst.m_bottom = 64.0f+ m_py;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

}