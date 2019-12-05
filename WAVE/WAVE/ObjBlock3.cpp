//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock3.h"

//使用するネームスペース
using namespace GameL;

//extern float m_hp;

CObjBlock3::CObjBlock3(int map3[10][100])
{
	//マップデータをコピー
	memcpy(m_map3, map3, sizeof(int)*(10 * 100));
}


//イニシャライズ
void CObjBlock3::Init()
{
	m_scroll = 0.0f;

}

//アクション
void CObjBlock3::Action()
{
	//主人公の位置を取得
	CObjHero*hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();



	//後方スクロールライン
	if (hx < 400)
	{
		hero->SetX(280);
		m_scroll -= hero->GetVX();
	}

	//前方スクロールライン
	if (hx > 400)
	{
		hero->SetX(360);
		m_scroll -= hero->GetVX();
	}

	/*//主人公の衝突確認用フラグの初期化
	hero->SetUp(false);
	hero->SetDown(false);
	hero->SetLeft(false);
	hero->SetRight(false);

	//踏んでいるblockの種類の初期化
	hero->SetBT(0);

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_map[i][j] > 0)
			{
				//要素番号を座標に変更
				float x = j * 64.0f;
				float y = i * 64.0f;

				//主人公とブロックの当たり判定
				if ((hx-(-m_scroll)+64.0f>x)&&(hx+(-m_scroll)<x+64.0f)&&(hy+64.0f>y)&&(hy<y+64.0f))
				{
					//上下左右判定

					//vectorの作成
					float vx = (hx+(-m_scroll)) - x;
					float vy = hy - y;
					//長さを求める
					float len = sqrt(vx*vx + vy * vy);
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
						if (r < 45 && r>0 || r > 135)
						{
							//右
							hero->SetRight(true);
							hero->SetX(x + 64.0f+(m_scroll));
							hero->SetVX(-hero->GetVX()*0.1f);
						}
						if (r > 45 && r > 135)
						{
							//上
							hero->SetDown(true);
							hero->SetY(y - 64.0f);
							//種類を渡すのスタートとゴールのみ変更する
							if(m_map[i][j]=2)
							hero->SetBT(m_map[i][j]);
							hero->SetVY(0.0f);
						}
						if (r > 135 && r < 225)
						{
							//左
							hero->SetLeft(true);
							hero->SetX(x - 64.0f+(m_scroll));
							hero->SetVY(-hero->GetVX()*0.1f);
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





					//当たってる場合
					hero->SetX(hx);
					hero->SetY(hy);
					hero->SetVY(0.0f);
				}

			}
		}
	}*/

	//敵出現ライン
	//主人公の位置+500を敵出現ラインにする
	float line = hx + (-m_scroll) + 500;

	//敵出現ラインを要素番号化
	int ex = ((int)line) / 64;
	int rx = ((int)line) / 64;

	//敵出現ラインの列を探索
	for (int i = 0; i < 10; i++)
	{

		//列の中から４を探す
		if (m_map3[i][ex] == 4)
		{

			//4があれば、敵を出現
			CObjEnemyLongdistance*obje = new CObjEnemyLongdistance(ex*64.0f, i*64.0f);
			Objs::InsertObj(obje, OBJ_ENEMYLONGDISTANCE, 10);

			//敵出現場所の値を0にする
			m_map3[i][ex] = 0;

		}

		//列の中から6を探す
		if (m_map3[i][rx] == 6)
		{
			CObjEnemyLongdistance*obje = new CObjEnemyLongdistance(rx*64.0f, i*64.0f);
			Objs::InsertObj(obje, OBJ_ENEMYLONGDISTANCE, 11);

			//敵出現場所の値を0にする
			m_map3[i][rx] = 0;

			
			//HPが0になったら破棄
			if (m_hp <= 0)
			{

				this->SetStatus(false);
				//Hits::DeleteHitBox(this);

				//敵消滅でシーンをゲームクリアに移行する
				Scene::SetScene(new CSceneGameOver());

			}
			
		}


	}

}

//ドロー
void CObjBlock3::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//背景表示
	src.m_top = 256.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//マップチップによるbloc設置

	//切り取り位置の設定
	/*src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = 64.0f;

	/*m_scroll -= 3.0f;//scroll実験用*/

	//マップチップによるblock設置
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map3[i][j] > 0)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f + m_scroll;
				dst.m_right = dst.m_left + 64.0f;
				dst.m_bottom = dst.m_top + 64.0f;
				/*
				if (m_map[i][j] == 2)
				{
					//スタートブロック
					BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);

				}
				else if (m_map[i][j] == 3)
				{
					//ゴールブロック
					BlockDraw(320.0f + 64.0f, 64.0f, &dst, c);
				}
				*/
				if (m_map3[i][j] == 4)
				{
					;//敵配置用の番号のため何もしない
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

//	BrockDrawMethod関数
//引数1 float x:リソース切り取り位置 x
//引数2 float y:リソース切り取り位置 y
//引数3 RECT_F*dst:描画位置
//引数4 float c[]:カラー情報
//ブロックを64*64限定描画用。リソース切り取りのみx・yで
//設定でできる
void CObjBlock3::BlockDraw(float x, float y, RECT_F*dst, float c[])
{

	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画
	Draw::Draw(2, &src, dst, c, 0.0f);

}

//BlockHit関数
void CObjBlock3::BlockHit(
	float *x, float *y, bool scroll_on,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//衝突確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map3[i][j] > 0 && m_map3[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;
					//長さを求める
					float len = sqrt(rvx*rvx + rvy * rvy);
					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//lenがある一定の長さのより短い場合判定に入る
					if (len < 88.0f)
					{
						//角度で上下左右を判定
						if (r < 45 && r>0 || r > 135)
						{
							//右
							*right = true;
							*x = bx + 64.0f + (scroll);
							*vx = -(*vx)*0.1f;
						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;
							*y = by - 64.0f;
							//種類を渡すのスタートとゴールのみ変更する
							if (m_map3[i][j] == 2)
								*bt = m_map3[i][j];
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;
							*x = bx - 64.0f + (scroll);
							*vx = -(*vx)*0.1f;
						}
						if (r > 225 && r < 315)
						{
							//下
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
//内積関数
float CObjBlock3::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * ay;

	return t;
}
//外積関数
float CObjBlock3::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//符号を求めるマクロ
#define SGN(x) 1-(x<=0)-(x<0)

//線と線と交差判定
bool CObjBlock3::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float*out_px, float*out_py
)

{
	//エラーコード
	*out_px = 99999.0f; *out_py = -99999.0f;

	//Ａベクトル作成（a2←a1）
	float ax = a2x - a1x; float ay = a2y - a1y;

	//Bベクトル作成（b2←b1）
	float bx = b2x - b1x; float by = b2y - b1y;

	//Cベクトル作成（b1←a1）
	float cx = b1x - a1x; float cy = b1y - a1y;

	//Dベクトル作成（b2←a1）
	float dx = b2x - a1x; float dy = b2y - a1y;

	//A*Cの射影とA*Bの射影を求める
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);

	//符号が同じ方向になっているかどうかをチェック
	if (SGN(t1) == SGN(t2))
		return false; //交点無し

	//射影を絶対値化
	t1 = abs(t1);  t2 = abs(t2);

	//交点を求める
	float px = bx * 1 + b1x;
	float py = by * t1 + b1y;

	//APベクトル(p←a1)
	float apx = px - a1x; float apy = py - a1y;

	//BPベクトル(p←a2)
	float bpx = px - a2x; float bpy = py - a2y;

	//A・APの射影とA・BPの射影を求める
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//符号チェック
	if (SGN(w1) == SGN(w2))
		return false; //交点が外

	//交点を返す
	*out_px = px; *out_py = py;

	return true;

}

//主人公と壁の交差判定
bool CObjBlock3::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float*out_len
)

{
	bool pb = false;
	float len = 99999.0f;

	float edge[4][4] =
	{
	{0,0,64,0},//→
	{64,0,64,64 },//↓
	{64,64,0,64},//←
	{0,64,0,0},//↑
	};

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map3[i][j] > 0 && m_map3[i][j] != 4)
			{
				//ブロックの4辺からこうてんを探す
				for (int k = 0; k < 4; k++)
				{
					//交点を探す
					float px, py;
					bool b;
					float l = 0.0f;
					b = LineCrossPoint(x, y, x + vx, y + vy,
						j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
						&px, &py);

					//交点チェック
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