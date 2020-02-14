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
		while (1) {//���̏����Ɉڍs���Ȃ����߂̖������[�v


			if (Input::GetVKey(VK_RETURN) == true) {//�}�E�X�� ���������Ɛ^

				flag = false;//�������~�߂�t���O��؂�ւ���

			}
			if (Input::GetVKey(VK_RETURN) == false && flag == false)
			{
				Audio::Start(30);
				this->SetStatus(false);//��������폜
				break;//���[�v�𔲂���
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
	
	Font::StrDraw(L">>Enter Push<<", 440, 460, 40, d);

	flag = true;
	
}

