/* 2018 ReVoL Primer Template */
/* drawing.h */
#pragma once
/* ���������� �������� 2 ��� ��������������� ���� */
#define MAX_PEN_TYPE 1
/* ������� ���������� */
TOOLS painting_tool = TOOL_MOUSE;
/* ������� ���� */
COLORREF fore_color = RGB(0, 0, 0);
/* ������� ��� */
COLORREF back_color = RGB(255, 255, 255);
/* ���� ��� ����� */
HPEN PenFore = 0;
/* ���� ��� ���� */
HPEN PenBack = 0;
/* ��� ���� */
int pen_type = PS_COSMETIC;
/* ��� ����� ������� �������������� ���� */
int line_style = PS_SOLID;
/* ������ ���� */
int pen_size = 1;
/* ����� ��������������� ���� */
LOGBRUSH PenBrush;
/* ��� �������� ����� */
int pen_endcap = PS_ENDCAP_FLAT;
/* ��� ���������� */
int pen_jointy = PS_JOIN_ROUND;
/* ��� ����� ���� */
int g_style = BS_SOLID;
/* ��� ��������� ���� */
int g_hatch = HS_CROSS;
/* ������� ��������� */
int poly_left = 0, poly_right = 0;

/* ��������� ����������� �������� ���� */
void ShiftMouse(short X1, short Y1, short & X2, short & Y2) {
}

/* ����� ���� */
void SetBackStyle(COLORREF color) {
    if (backstyle_mode == 1) {
        /* ����� ���� ���������� */
    } else {
        /* ����� ���� ������������ */
    }
}

/* ������� WM_LBUTTONDOWN */
int LeftButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// ������ ����� ������
	mouse_down = WM_LBUTTONDOWN;
	// ����������� ������� ����
	SetCapture(hWnd);
	// ���������� ����
	GetMouse(MX1, MX2, wParam, lParam);
	// ������� ����� ���������
	MoveToEx(CDC, MX1, MY1, 0);
	// �������� ���� �����
	SelectObject(CDC, PenFore);
	// �������� �����������
	ImageSave();
	
	// ���� ���������
	if (painting_tool == TOOL_POLY && poly_right == 0) poly_left = 1;
	poly_right = 0;

	// ������� ���������
    return 0;
}

/* ������� WM_RBUTTONDOWN */
int RightButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// ������� ������ ������
	mouse_down = WM_RBUTTONDOWN;
	// ������������ ������� ����
	SetCapture(hWnd);
	// ���������� ����
	GetMouse(MX1, MY1, wParam, lParam);
	// ������� ����� ���������
	MoveToEx(CDC, MX1, MY1, 0);
	// �������� ���� ����
	SelectObject(CDC, PenBack);
	// �������� �����������
	ImageSave();

	// ���� ���������
	if (painting_tool == TOOL_POLY && poly_left == 0) poly_right = 1;
	poly_left = 0;

	// ������� ����������
    return 0;
}

/* ������� WM_LBUTTONUP */
int LeftButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// ���� ��������� ����� ������
	if (poly_left) return 0;
	// ���� ��������
	mouse_down = 0;
	// ����������� ������ ����
	ReleaseCapture();
	// ������� ����������
    return 0;
}

/* ������� WM_RBUTTONUP */
int RightButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// ���� ��������� ����� ������
	if (poly_right) return 0;
	// ���� ��������
	mouse_down = 0;
	// ����������� ������ ����
	ReleaseCapture();
	// ������� ����������
    return 0;
}

/* ������� ����� ���� ����� ��� ���� */
void CreateNewPen(HPEN & Pen, COLORREF color) {
	DeleteObject(Pen);
    // ������� ����
    if (pen_type == PS_COSMETIC) {
        // ������������� ����
		Pen = CreatePen(line_style, pen_size, color);
    } else {
        // �������������� ����
		PenBrush.lbColor = color;
		PenBrush.lbStyle = g_style;
		PenBrush.lbHatch = g_hatch;
		int style = PS_GEOMETRIC | line_style | pen_endcap | pen_jointy;
		Pen = ExtCreatePen(style, pen_size, &PenBrush, 0, 0);
    }


}

/* ������ ����� */
void DrawMouse(short & X1, short & Y1, short X2, short Y2) {
	RECT rc;

	// ������������� ������� �����
	//MoveToEx(CDC, X1, Y1, 0);
	// ������ ������� ������
	LineTo(CDC, X2, Y2);
	// ����������� �����������
	InvalidateRect(hWndGDE, 0, 0);

}

/* ������ ������ */
void DrawLine(short X1, short Y1, short X2, short Y2) {
	// �������������� �����������
	ImageRestore();
	// ������������� ������� �����
	MoveToEx(CDC, X1, Y1, 0);
	// ������ ������� ������
	LineTo(CDC, X2, Y2);
	// ����������� �����������
	InvalidateRect(hWndGDE, 0, 0);
}

/* ������ ������������� */
void DrawRect(short X1, short Y1, short X2, short Y2) {
	ImageRestore();
	Rectangle(CDC, X1, Y1, X2, Y2);
	InvalidateRect(hWndGDE, 0, 0);
}

/* ������ ���� */
void DrawOval(short X1, short Y1, short X2, short Y2) {
	ImageRestore();
	Ellipse(CDC, X1, Y1, X2, Y2);
	InvalidateRect(hWndGDE, 0, 0);
}

/* ������ ������ �� ��������� ����������� */
void DrawBrez(short X1, short Y1, short X2, short Y2) {
}

/* ������ ������ �� ��������� �� */
void DrawBWoo(short X1, short Y1, short X2, short Y2) {
}
