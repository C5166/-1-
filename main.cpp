// =============================
// App/main.cpp
// =============================
#include "DxPlus/DxPlus.h"
#include "SceneManager.h"
#include <crtdbg.h>

static LRESULT CALLBACK CustomWinProc(HWND, UINT msg, WPARAM wParam, LPARAM)
{
	if (msg == WM_KEYDOWN && wParam == VK_ESCAPE)
	{
		PostQuitMessage(0);
	}

	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
    srand((unsigned int)time(NULL));
	DxLib::SetHookWinProc(CustomWinProc);

	SM().Init();
	SM().Run();
	SM().Shutdown();

	return 0;
}
