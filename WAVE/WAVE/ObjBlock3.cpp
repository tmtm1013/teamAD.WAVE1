//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock3.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//extern float m_hp;

CObjBlock3::CObjBlock3(int map3[10][100])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map3, map3, sizeof(int)*(10 * 100));
}


//�C�j�V�����C�Y
void CObjBlock3::Init()
{
	m_scroll = 0.0f;

}

//�A�N�V����
void CObjBlock3::Action()
{
	//��l���̈ʒu���擾
	CObjHero*hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();



	//����X�N���[�����C��
	if (hx < 400)
	{
		hero->SetX(280);
		m_scroll -= hero->GetVX();
	}

	//�O���X�N���[�����C��
	if (hx > 400)
	{
		hero->SetX(360);
		m_scroll -= hero->GetVX();
	}

	/*//��l���̏Փˊm�F�p�t���O�̏�����
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//����ł���block�̎�ނ̏�����
	hero->SetBT(0);

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_map[i][j] > 0)
			{
				//�v�f�ԍ������W�ɕύX
				float x = j * 64.0f;
				float y = i * 64.0f;

				//��l���ƃu���b�N�̓����蔻��
				if ((hx-(-m_scroll)+64.0f>x)&&(hx+(-m_scroll)<x+64.0f)&&(hy+64.0f>y)&&(hy<y+64.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float vx = (hx+(-m_scroll)) - x;
					float vy = hy - y;
					//���������߂�
					float len = sqrt(vx*vx + vy * vy);
					//�p�x�����߂�
					float r = atan2(vy, vx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if (r < 45 && r>0 || r > 135)
						{
							//�E
							hero->SetRight(true);
							hero->SetX(x + 64.0f+(m_scroll));
							hero->SetVX(-hero->GetVX()*0.1f);
						}
						if (r > 45 && r > 135)
						{
							//��
							hero->SetDown(true);
							hero->SetY(y - 64.0f);
							//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
							if(m_map[i][j]=2)
							hero->SetBT(m_map[i][j]);
							hero->SetVY(0.0f);
						}
						if (r > 135 && r < 225)
						{
							//��
							hero->SetLeft(true);
							hero->SetX(x - 64.0f+(m_scroll));
							hero->SetVY(-hero->GetVX()*0.1f);
						}
						if (r > 225 && r < 315)
						{
							//��
							hero->SetUp(true);
							hero->SetY(y + 64.0f);
							if (hero->GetVY() < 0)
							{
								hero->SetVY(0.0f);
							}
						}
					}





					//�������Ă�ꍇ
					hero->SetX(hx);
					hero->SetY(hy);
					hero->SetVY(0.0f);
				}

			}
		}
	}*/

	//�G�o�����C��
	//��l���̈ʒu+500��G�o�����C���ɂ���
	float line = hx + (-m_scroll) + 500;

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / 64;
	int rx = ((int)line) / 64;

	//�G�o�����C���̗��T��
	for (int i = 0; i < 10; i++)
	{

		//��̒�����S��T��
		if (m_map3[i][ex] == 4)
		{

			//4������΁A�G���o��
			CObjEnemyLongdistance*obje = new CObjEnemyLongdistance(ex*64.0f, i*64.0f);
			Objs::InsertObj(obje, OBJ_ENEMYLONGDISTANCE, 10);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map3[i][ex] = 0;

		}

		//��̒�����6��T��
		if (m_map3[i][rx] == 6)
		{
			CObjEnemyLongdistance*obje = new CObjEnemyLongdistance(rx*64.0f, i*64.0f);
			Objs::InsertObj(obje, OBJ_ENEMYLONGDISTANCE, 11);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map3[i][rx] = 0;

			
			//HP��0�ɂȂ�����j��
			if (m_hp <= 0)
			{

				this->SetStatus(false);
				//Hits::DeleteHitBox(this);

				//�G���łŃV�[�����Q�[���N���A�Ɉڍs����
				Scene::SetScene(new CSceneGameOver());

			}
			
		}


	}

}

//�h���[
void CObjBlock3::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�w�i�\��
	src.m_top = 256.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�}�b�v�`�b�v�ɂ��bloc�ݒu

	//�؂���ʒu�̐ݒ�
	/*src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = 64.0f;

	/*m_scroll -= 3.0f;//scroll�����p*/

	//�}�b�v�`�b�v�ɂ��block�ݒu
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map3[i][j] > 0)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f + m_scroll;
				dst.m_right = dst.m_left + 64.0f;
				dst.m_bottom = dst.m_top + 64.0f;
				/*
				if (m_map[i][j] == 2)
				{
					//�X�^�[�g�u���b�N
					BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);

				}
				else if (m_map[i][j] == 3)
				{
					//�S�[���u���b�N
					BlockDraw(320.0f + 64.0f, 64.0f, &dst, c);
				}
				*/
				if (m_map3[i][j] == 4)
				{
					;//�G�z�u�p�̔ԍ��̂��߉������Ȃ�
				}

				if (m_map3[i][j] == 6)
				{

				}




				else
				{
					BlockDraw(320.0f, 0.0f, &dst, c);
				}
			}
		}
	}


}

//	BrockDrawMethod�֐�
//����1 float x:���\�[�X�؂���ʒu x
//����2 float y:���\�[�X�؂���ʒu y
//����3 RECT_F*dst:�`��ʒu
//����4 float c[]:�J���[���
//�u���b�N��64*64����`��p�B���\�[�X�؂���̂�x�Ey��
//�ݒ�łł���
void CObjBlock3::BlockDraw(float x, float y, RECT_F*dst, float c[])
{

	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//�`��
	Draw::Draw(2, &src, dst, c, 0.0f);

}

//BlockHit�֐�
void CObjBlock3::BlockHit(
	float *x, float *y, bool scroll_on,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//�Փˊm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map3[i][j] > 0 && m_map3[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;
					//���������߂�
					float len = sqrt(rvx*rvx + rvy * rvy);
					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if (r < 45 && r>0 || r > 135)
						{
							//�E
							*right = true;
							*x = bx + 64.0f + (scroll);
							*vx = -(*vx)*0.1f;
						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;
							*y = by - 64.0f;
							//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
							if (m_map3[i][j] == 2)
								*bt = m_map3[i][j];
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;
							*x = bx - 64.0f + (scroll);
							*vx = -(*vx)*0.1f;
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;
							*y = by + 64.0f;
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}






				}

			}
		}
	}
}
//���ϊ֐�
float CObjBlock3::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * ay;

	return t;
}
//�O�ϊ֐�
float CObjBlock3::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//���������߂�}�N��
#define SGN(x) 1-(x<=0)-(x<0)

//���Ɛ��ƌ�������
bool CObjBlock3::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float*out_px, float*out_py
)

{
	//�G���[�R�[�h
	*out_px = 99999.0f; *out_py = -99999.0f;

	//�`�x�N�g���쐬�ia2��a1�j
	float ax = a2x - a1x; float ay = a2y - a1y;

	//B�x�N�g���쐬�ib2��b1�j
	float bx = b2x - b1x; float by = b2y - b1y;

	//C�x�N�g���쐬�ib1��a1�j
	float cx = b1x - a1x; float cy = b1y - a1y;

	//D�x�N�g���쐬�ib2��a1�j
	float dx = b2x - a1x; float dy = b2y - a1y;

	//A*C�̎ˉe��A*B�̎ˉe�����߂�
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);

	//���������������ɂȂ��Ă��邩�ǂ������`�F�b�N
	if (SGN(t1) == SGN(t2))
		return false; //��_����

	//�ˉe���Βl��
	t1 = abs(t1);  t2 = abs(t2);

	//��_�����߂�
	float px = bx * 1 + b1x;
	float py = by * t1 + b1y;

	//AP�x�N�g��(p��a1)
	float apx = px - a1x; float apy = py - a1y;

	//BP�x�N�g��(p��a2)
	float bpx = px - a2x; float bpy = py - a2y;

	//A�EAP�̎ˉe��A�EBP�̎ˉe�����߂�
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//�����`�F�b�N
	if (SGN(w1) == SGN(w2))
		return false; //��_���O

	//��_��Ԃ�
	*out_px = px; *out_py = py;

	return true;

}

//��l���ƕǂ̌�������
bool CObjBlock3::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float*out_len
)

{
	bool pb = false;
	float len = 99999.0f;

	float edge[4][4] =
	{
	{0,0,64,0},//��
	{64,0,64,64 },//��
	{64,64,0,64},//��
	{0,64,0,0},//��
	};

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map3[i][j] > 0 && m_map3[i][j] != 4)
			{
				//�u���b�N��4�ӂ��炱���Ă��T��
				for (int k = 0; k < 4; k++)
				{
					//��_��T��
					float px, py;
					bool b;
					float l = 0.0f;
					b = LineCrossPoint(x, y, x + vx, y + vy,
						j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
						&px, &py);

					//��_�`�F�b�N
					if (b == true)
					{
						l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

						if (len > l)
						{
							len = l;
							*out_px = px;
							*out_py = py;
							pb = true;
						}
					}
				}
			}
		}
	}
	*out_len = len;
	return pb;
}