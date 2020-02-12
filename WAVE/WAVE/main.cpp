#include <Windows.h>

//削除されていないメモリを出力にダンプする
#include <crtdbg.h>
#ifdef _DEBUG
    #ifndef DBG_NEW
       #define DBG_NEW new ( _NORMAL_BLOCK,__FILE__,__LINE__)

       #define new DBG_NEW
    #endif
#endif  // _DEBUG

//グローバル変数
HWND g_hWnd;   //ウィンドウハンドル
int g_width;   //ウィンドウの横幅
int g_height;  //ウィンドウの縦幅

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Main関数
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, int nCmdShow)
{
	//メモリダンプ開始
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	wchar_t name[] = { L"GameEngine" };  //ウィンドウ＆タイトルネーム
	MSG  msg;                            //メッセージハンドル 

	//ウィンドウステータス
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),CS_HREDRAW | CS_VREDRAW,
		WndProc,0,0,hInstance,NULL,NULL,
		(HBRUSH)(COLOR_WINDOW + 1),NULL,name,NULL
	};

	//ウィンドウクラス作成
	RegisterClassEx( &wcex );

	//ウィンドウ作成
	g_width = 800;
	g_height = 600;

	int width = g_width + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height = g_height + GetSystemMetrics(SM_CXDLGFRAME) * 2+GetSystemMetrics(SM_CYCAPTION);

	//ウィンドウ作成
	if ( !( g_hWnd = CreateWindow(name, name,
		WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX),
		CW_USEDEFAULT, 0, width, height, 0, 0, hInstance, 0)))
	{
		return false;
	}
	ShowWindow(g_hWnd, SW_SHOW);

	//メッセージループ
	do
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	} while (msg.message!=WM_QUIT );

	//この時点で開放されていないメモリの情報の表示
	_CrtDumpMemoryLeaks();
	return true;
}

//コールバック関数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		break;
		case WM_CLOSE:
			PostQuitMessage(0);
		case WM_DESTROY:
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

