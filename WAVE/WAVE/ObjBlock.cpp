//STLヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

CObjBlock::CObjBlock(int map[30][30])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(30 * 30));
}

//イニシャライズ
void CObjBlock::Init()
{
	//マップ情報
	int block_data[30][30] =
	{



		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},

	};

	//マップデータをコピー
	memcpy(m_map, block_data, sizeof(int)*(30 * 30));


}

//アクション
void CObjBlock::Action()
{
	//主人公の位置を取得
	CObjHero*hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//主人公の衝突状態確認用フラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);



	if ((hx + 64.0f > x) && (hx < x + 64.0f) && (hy + 64.0f > y) && (hy < y + 64.0f))
	{
		//vectorの作成
		float vx = hx - x;
		float vy = hy - y;

		//長さを求める
		float len= sqrt(vx*vx + vy * vy);

		//角度を求める
		float r = atan2(vy, vx);
		r = r * 180.0f / 3.14f;

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//lenがある一定の長さのより短い場合判定に入る
		if (len < 88.0f)
		{

			//角度で上下左右を判定
			if ((r < 45 && r>0) || r > 315)
			{
				//右
				hero->SetRight(true);
				hero->SetX(x + 64.0f);
				hero->SetVX(-hero->GetVX()*0.1f);

			}

			if (r > 45 && r < 135)
			{
				//上
				hero->SetDown(true);
				hero->SetY(y - 64.0f);
				hero->SetVY(0.0f);
			}

			//角度で上下左右を判定
			if (r < 135 && r>225)
			{
				//左
				hero->SetLeft(true);
				hero->SetX(x - 64.0f);
				hero->SetVX(-hero->GetVX()*0.1f);

			}

			if (r > 225 && r < 315)
			{
				//下
				hero->SetUp(true);
				hero->SetY(y + 64.0f);
				if (hero->GetVY() < 0)
				{
					hero->SetVY(0.0f);
				}
			}
		}



		//m_mapの全要素にアクセス
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				if (m_map[i][j] > 0)
				{
					//要素番号を座標に変更
					float x = j * 64.0f;
					float y = i * 64.0f;

					//主人公とブロックの当たり判定
					if ((hx + 64.0f > x) && (hx < x + 64.0f) && (hy + 64.0f > y) && (hy < y + 64.0f))
					{
						//当たってる場合
						hero->SetX(hx);
						hero->SetY(0.0f);
						hero->SetVY(0.0f);

					}
				}
			}
		}
	}
}

//ドロー
void CObjBlock::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	

	//マップチップによるblock設置
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = 64.0f;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (m_map[i][j] > 0)
			{
				//表示位置の設定
				dst.m_top = i * 20.0f;
				dst.m_left = j *27.0f;
				dst.m_right = dst.m_left + 27.0f;
				dst.m_bottom = dst.m_top + 20.0f;

				//描画
				Draw::Draw(4, &src, &dst, c, 0.0f);






				//背景表示
				src.m_top = 256.0f;
				src.m_left = 0.0f;
				src.m_right = 512.0f;
				src.m_bottom = 512.0f;
				dst.m_top = 0.0f;
				dst.m_left = 0.0f;
				dst.m_right = 800.0f;
				dst.m_bottom = 600.0f;
				Draw::Draw(0, &src, &dst, c, 0.0f);

			}
		}
	}

}

/*//BlockDrawMethod関数
//引数１ float x:リソース切り取り位置X
//引数２ float y:リソース切り取り位置Y
//引数３ RECT_F*dst:描画位置
//引数４ float c[]:カラー情報
//ブロックを64×64限定描画用。リソース切り取り位置のみx.yで設定
void CObjBlock::BlockDraw(float x, float y, RECT_F*dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//描画
	Draw::Draw(0, &src, dst, c, 0.0f);
}*/



//BlockHit関数
//引数１　float x
//引数２  float y
//引数３　bool* up
//引数４　bool*down
//引数５　bool*left
//引数６　bool*right
//引数７  float*vx
//引数８　float*vy
//引数９  int* bt

void CObjBlock::BlockHit(
	float*x, float*y, bool*up, bool*down, bool*left, bool*right,
	float*vx, float*vy, int*bt
)
{
	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (m_map[i][j] > 0)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				

				//オブジェクトとブロックの当たり判定
				if ((*x +64.0f > bx) && (*x< bx+64.0f)&&(*y+64.0f>by)&&(*y<by+64.0f))
				{
					/*//上下左右判定
					float rvx = (*x + (-scroll)) - bx;
					//長さを求める*/
					float len = sqrt(rvx*rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

				}
			}
		}
	}

}