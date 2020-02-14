#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "ObjWeaponType.h"
#include "GameHead.h"
#include "SceneMain.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWeaponType::CObjWeaponType(int type)
{
	weapontype =type;
}


//�C�j�V�����C�Y
void CObjWeaponType::Init()
{
	
}

//�A�N�V����
void CObjWeaponType::Action()
{


}

//�h���[
void CObjWeaponType::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f * weapontype;//�@+�@weapontype * �؂���ʒu
	src.m_right = 256.0f * weapontype;
	src.m_bottom = 256.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(39, &src, &dst, c, 0.0f);
}