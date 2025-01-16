#include "main.h"

Main app;

BOOL Main::InitInstance()
{
	TypingFrame* frame = new TypingFrame(L"./Snow-white.txt");

	//CString str = "123456,,,\n123 aaa.";
	//TypingFrame* frame = new TypingFrame(str);

	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();

	m_pMainWnd = frame;

	return TRUE;
}
