//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "ObjTitle.h"
#include "GameHead.h"
#include "SceneMain.h"

//�g�p����w�b�_�[�t�@�C��         
using namespace GameL;

void CObjTitle::Init()
{


	//���y�X�^�[�g
	Audio::Start(0);

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	time = 0;
	flag = false;

	b = 1.0f;
	t = 1.0f;

	((UserData*)Save::GetData())->SceneNum=1; //�}�b�v�ړ��p
	((UserData*)Save::GetData())->Scenecontinue = 1; //�}�b�v�ړ��p
}

void CObjTitle::Action()
{




	if (flag == true)//���̏����Ɉڍs���Ȃ�����
		while (1) {
			//�}�E�X�̈ʒu���擾
			m_mou_x = (float)Input::GetPosX();
			m_mou_y = (float)Input::GetPosY();
			//�}�E�X�̃{�^���̏��
			m_mou_r = Input::GetMouButtonR();
			m_mou_l = Input::GetMouButtonL();
			//���̏����Ɉڍs���Ȃ����߂̖������[�v
			//�}�E�X�̈ʒu�ƃN���b�N����ꏊ�œ����蔻��
			if (m_mou_x > 440 && m_mou_x < 800 && m_mou_y > 440 && m_mou_y < 490)
			{
				//�}�E�X�̃{�^���������ꂽ�烁�C���Ɉڍs
				if (m_mou_r == true || m_mou_l == true)
				{
					Audio::Start(1);

					//�{�����[����1.0�ɖ߂�
					float v = Audio::VolumeMaster(0);
					v = Audio::VolumeMaster(0.5 - v);

					this->SetStatus(false);//�I�u�W�F�N�g�폜
					break;

				}
			}

		
		}
	
}

void CObjTitle::Draw()
{
	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	

	RECT_F src;
	RECT_F dst;


	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 570.0f;

	//�\���ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(15, &src, &dst, c, 0.0f);

	
	/*
	//���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x = %f, y = %f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, c);
	//���}�E�X�̃{�^���̏��
	if (m_mou_r == true)
		Font::StrDraw(L"R=�����Ă���", 20, 30, 12, c);
	else
		Font::StrDraw(L"R=�����Ă��Ȃ�", 20, 30, 12, c);
	if (m_mou_l == true)
		Font::StrDraw(L"L=�����Ă���", 20, 40, 12, c);
	else
		Font::StrDraw(L"L=�����Ă��Ȃ�", 20, 40, 12, c);
	  */       //   R    G    B    ����
	float d[4] = { 0, 0, b, t };
	
	Font::StrDraw(L">>�Q�[���X�^�[�g<<", 440, 440, 40, d);

	flag = true;
	
}

