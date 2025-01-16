#include "TypingFrame.h"

static int m_time_count = 0;
static TypingFrame* main_frame;

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	//MessageBox(NULL, L"test", L"Timer is running!", MB_OK);
	m_time_count += 1;
	main_frame->InvalidateRect(&main_frame->m_timeRect, FALSE);

	return;
}


TypingFrame::TypingFrame()
{
	this->initFrame();

	this->m_content_box.loadText(this->m_contents);
	this->m_pulley.setPulley(1 * (TEXTBOX_HEIGHT + 10) + /*����հײ���*/(TEXTBOX_HEIGHT + 10) * 4, -1);
	
	this->m_count_num = this->m_contents.GetLength();

	return;
}

TypingFrame::TypingFrame(CString content)
{
	this->initFrame();

	this->m_contents = content;
	this->m_content_box.loadText(content);

	this->m_pulley.setPulley(this->m_content_box.getContentLineNum() * (TEXTBOX_HEIGHT + 10) + /*����հײ���*/(TEXTBOX_HEIGHT + 10) * 4, -1);

	this->m_count_num = this->m_contents.GetLength();

	return;
}

TypingFrame::TypingFrame(LPCTSTR path)
{
	this->initFrame();

	std::ifstream ifs(path, std::ios::in);
	if (!ifs)
	{
		MessageBox(L"�޷����ı��ļ�", L"����");
		this->m_is_errorInit = -1;
		return;
	}

	this->m_content_box.textName(getFileName(path));

	ifs.seekg(0, std::ios::end);
	std::streampos file_size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::string file_contents;
	file_contents.resize(static_cast<std::size_t>(file_size));
	ifs.read(&file_contents[0], file_size);
	ifs.close();

	CString contents(file_contents.c_str());
	this->m_contents = contents;
	this->m_content_box.loadText(contents);
	this->m_pulley.setPulley(this->m_content_box.getContentLineNum() * (TEXTBOX_HEIGHT + 10) + /*����հײ���*/(TEXTBOX_HEIGHT + 10) * 4, -1);

	this->m_count_num = this->m_contents.GetLength();

	return;
}

TypingFrame::~TypingFrame()
{
	if (this->m_is_start == true)
	{
		KillTimer(TIMER);
	}

	return;
}

void TypingFrame::initFrame()
{
	this->m_is_errorInit = 0;

	//���ô��� ��600 ��800
	RECT rect;
	rect.left = 0, rect.top = 0, rect.right = GetSystemMetrics(SM_CXSCREEN), rect.bottom = GetSystemMetrics(SM_CYSCREEN);

	//��������
	Create(NULL, TEXT("TypingGame"), FWS_ADDTOTITLE, rect, NULL, NULL, 0, NULL);

	//ȥ����߿�
	LONG nStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	LONG newStyle = nStyle & (~(WS_CAPTION | WS_BORDER | WS_THICKFRAME));
	SetWindowLong(m_hWnd, GWL_STYLE, newStyle);
	::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	//ȥ���ڱ߿�
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	//���ڶ���
	//SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);

	main_frame = this;

	return;
}

void TypingFrame::setting(int is_can_back)
{
	this->m_is_canBack = is_can_back;

	return;
}

void TypingFrame::OnTimer()
{
	InvalidateRect(&m_timeRect, FALSE);
	return;
}

int TypingFrame::getCorrentCount()
{
	return this->m_content_box.m_corrent_count;
}

int TypingFrame::getErrorCount()
{
	return this->m_content_box.m_error_count;
}

BEGIN_MESSAGE_MAP(TypingFrame, CFrameWnd)

	ON_WM_LBUTTONDOWN()

	ON_WM_CHAR()

	ON_WM_PAINT()

	ON_WM_MOUSEWHEEL()

	ON_WM_ERASEBKGND()
	
END_MESSAGE_MAP()

void TypingFrame::OnLButtonDown(UINT, CPoint)
{

	return;
}

void TypingFrame::OnChar(UINT key, UINT, UINT)
{
	switch (key)
	{
	case VK_ESCAPE://ESC�˳�
	{
		if (this->m_is_errorInit)
		{
			//��ʼ����������ֱ���˳�
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
		}

		CString tips;
		tips.Format(_T("��ǰ��ʱ��%s����ȷ��%d������%d��ȷ���Ƿ��˳���"), intDateToCStringDate(m_time_count), this->m_content_box.getCorrent(), this->m_content_box.getError());
		int res = MessageBox(tips, _T("ȷ���˳�"), MB_OKCANCEL);
		if (res == IDOK)
		{
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
		}
		
		return;
	}
		break;
	case VK_BACK://�˸�
	{
		if (this->m_is_canBack)
		{
			this->m_content_box.delWord();
		}
	}
		break;
	case VK_RETURN://�س�
	{
		CString str;
		str.Format(_T("\n"));
		this->m_content_box.input(str);
	}
		break;
	default://�ַ�
	{
		if (this->m_is_start == false)
		{
			this->m_is_start = true;
			SetTimer(TIMER, 1000, (TIMERPROC)TimerProc);
		}
		CString str;
		str.Format(_T("%c"), key);
		if (this->m_content_box.input(str) == 1)
		{
			KillTimer(TIMER);
		}
	}
		break;
	}

	Invalidate();

	return;
}

void TypingFrame::OnPaint()
{
	CPaintDC dc(this); // �豸������
	CDC memDC; // �ڴ��豸������
	CBitmap memBitmap; // �ڴ�λͼ

	// ��ȡ���ڴ�С
	CRect rect;
	GetClientRect(&rect);

	// ��������DC��λͼ
	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	// ���ڴ�DC�л��Ʊ���
	memDC.FillSolidRect(rect, this->m_backgroundColor);
	memDC.SetBkMode(TRANSPARENT);

	if (this->m_is_errorInit)
	{
		memDC.TextOut(10, TEXTBOX_HEIGHT / 3, _T("�����������󣬰���ESC�˳�"));

		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		memBitmap.DeleteObject();
		return;
	}
	//�ı���
	this->m_content_box.draw(memDC, -PULLEY_WIDTH, 10 - this->m_pulley.getCameraY() + TEXTBOX_HEIGHT, 1);

	//״̬��
	CRect statusRect(0, 0, rect.Width(), TEXTBOX_HEIGHT);
	memDC.FillSolidRect(statusRect, RGB(255, 255, 255));

	CPen borderpen(PS_SOLID, 1, RGB(0, 0, 0));
	memDC.SelectObject(&borderpen);
	memDC.Rectangle(0, 0, rect.Width(), TEXTBOX_HEIGHT);

	memDC.TextOut(10, TEXTBOX_HEIGHT / 3, intDateToCStringDate(m_time_count));

	if (dc.GetClipBox(&m_timeRect) == SIMPLEREGION)
	{
		memDC.TextOut(10, TEXTBOX_HEIGHT / 3, intDateToCStringDate(m_time_count));
	}
	memDC.TextOut(10 + rect.Width() * 1 / 5, TEXTBOX_HEIGHT / 3, _T("����: " + this->m_content_box.getFileName()));
	memDC.TextOut(10 + rect.Width() * 2 / 5, TEXTBOX_HEIGHT / 3, _T("����: " + this->m_content_box.getLanguage()));
	CString str;
	str.Format(_T("����: %d ��ȷ: %d ����: %d"), this->m_content_box.getLength(), this->m_content_box.getCorrent(), this->m_content_box.getError());
	memDC.TextOut(10 + rect.Width() * 3 / 5, TEXTBOX_HEIGHT / 3, str);

	//������
	this->m_pulley.draw(memDC);

	// ���ڴ�λͼ���Ƶ���ĻDC
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// �ͷ���Դ
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	memBitmap.DeleteObject();

	//״̬��:��ʱ���ο�λ������
	m_timeRect.SetRect(10, TEXTBOX_HEIGHT / 3, 10 + rect.Width() * 1 / 5, TEXTBOX_HEIGHT / 3 + TEXTBOX_HEIGHT);
}

BOOL TypingFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	if (this->m_is_errorInit)
	{
		return 0;
	}

	if (zDelta > 0)
	{
		this->m_pulley.movePulley(-1);
	}
	if (zDelta < 0)
	{
		this->m_pulley.movePulley(1);
	}

	Invalidate();

	return 0;
}

BOOL TypingFrame::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; //���ñ�������
}
