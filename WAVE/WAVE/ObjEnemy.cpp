#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"

#define GRAUND (546.0f)

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;
}

extern float idou;

//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	m_hp = 100;//ENEMY��HP

	flag = true;


	m_move = false;//true=�E

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 131, 132, ELEMENT_ENEMY, OBJ_ENEMY, 1);



}

//�A�N�V����
void CObjEnemy::Action()
{


	//�ʏ푬�x
	m_speed_power = 0.1f;
	m_ani_max_time = 2;



	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//�����ɓG����l���̌����Ɉړ���������������B
	if (x <= m_px)//�E
	{

		m_move = true;



	}
	if (x >= m_px)//��
	{


		m_move = false;



	}

	if (m_move == false)
	{
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}

	else if (m_move == true)
	{
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}


	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}



	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	if (m_vy > 26 && m_py <= GRAUND)
	{
		m_vy = 0;
	}

	//������
















	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;


	//�G�̈ʒuX(x_px)+��l���̕�����+X�������ɗ̈�O��F��
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

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);



	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GRENADE) != nullptr)
	{

		m_hp -= 50;


	}

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

	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{


		this->SetStatus(false);
		Hits::DeleteHitBox(this);



		if (flag == true)
		{
			//�A�C�e���I�u�W�F�N�g�쐬	
			CObjItem*obju = new CObjItem(m_px, m_py);
			Objs::InsertObj(obju, OBJ_ITEM, 7);
			flag = false;
		}



		//�G�����ł�����+100�_
		((UserData*)Save::GetData())->m_point += 100;




		//�G���łŃV�[�����Q�[���N���A�Ɉڍs����
		//Scene::SetScene(new CSceneClear());

	}

}

//�h���[
void CObjEnemy::Draw()
{
	//�����A�j���[�V��������o�^
	int AniData[1][6] =
	{
		0, 1, 2, 3, 4, 5,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 131;
	src.m_right = 131.0f + AniData[m_ani_move][m_ani_frame] * 132;
	src.m_bottom = 132.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (131.0f * m_posture) + m_px;
	dst.m_right = (131 - 131.0f * m_posture) + m_px;
	dst.m_bottom = 132.0f + m_py;

	//�`��
	Draw::Draw(5, &src, &dst, c, 0.0f);

}