/* 2018 ReVoL Primer Template */
/* drawing.h */
#pragma once
/* установить значение 2 для геометрического пера */
#define MAX_PEN_TYPE 1
/* текущий инструмент */
TOOLS painting_tool = TOOL_MOUSE;
/* текущий цвет */
COLORREF fore_color = RGB(0, 0, 0);
/* текущий фон */
COLORREF back_color = RGB(255, 255, 255);
/* перо для плана */
HPEN PenFore = 0;
/* перо для фона */
HPEN PenBack = 0;
/* тип пера */
int pen_type = PS_COSMETIC;
/* тип линии тонкого косметического пера */
int line_style = PS_SOLID;
/* размер пера */
int pen_size = 1;
/* кисть геометрического пера */
LOGBRUSH PenBrush;
/* тип концевой точки */
int pen_endcap = PS_ENDCAP_FLAT;
/* тип соединения */
int pen_jointy = PS_JOIN_ROUND;
/* тип кисти пера */
int g_style = BS_SOLID;
/* тип штриховки пера */
int g_hatch = HS_CROSS;
/* признак полилинии */
int poly_left = 0, poly_right = 0;

/* вычисляет направление движения мыши */
void ShiftMouse(short X1, short Y1, short & X2, short & Y2) {
}

/* режим фона */
void SetBackStyle(COLORREF color) {
    if (backstyle_mode == 1) {
        /* режим фона прозрачный */
    } else {
        /* режим фона непрозрачный */
    }
}

/* событие WM_LBUTTONDOWN */
int LeftButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// нажата леавя кнопка
	mouse_down = WM_LBUTTONDOWN;
	// захватываем событие мыши
	SetCapture(hWnd);
	// координаты мыши
	GetMouse(MX1, MX2, wParam, lParam);
	// текущая точка рисования
	MoveToEx(CDC, MX1, MY1, 0);
	// выбираем перо плана
	SelectObject(CDC, PenFore);
	// созаняем изображение
	ImageSave();
	
	// если полилиния
	if (painting_tool == TOOL_POLY && poly_right == 0) poly_left = 1;
	poly_right = 0;

	// событие обработки
    return 0;
}

/* событие WM_RBUTTONDOWN */
int RightButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// нажатая правая кнопка
	mouse_down = WM_RBUTTONDOWN;
	// закхватываем событие мыши
	SetCapture(hWnd);
	// координаты мыши
	GetMouse(MX1, MY1, wParam, lParam);
	// текущая точка рисования
	MoveToEx(CDC, MX1, MY1, 0);
	// выбираем перо фона
	SelectObject(CDC, PenBack);
	// созаняем изображение
	ImageSave();

	// если полилиния
	if (painting_tool == TOOL_POLY && poly_left == 0) poly_right = 1;
	poly_left = 0;

	// событие обработано
    return 0;
}

/* событие WM_LBUTTONUP */
int LeftButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// если полилиния дерит захват
	if (poly_left) return 0;
	// мышь отпущена
	mouse_down = 0;
	// освобождаем захват мыши
	ReleaseCapture();
	// событие обработано
    return 0;
}

/* событие WM_RBUTTONUP */
int RightButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// если полилиния дерит захват
	if (poly_right) return 0;
	// мышь отпущена
	mouse_down = 0;
	// освобождаем захват мыши
	ReleaseCapture();
	// событие обработано
    return 0;
}

/* создает новое перо плана или фона */
void CreateNewPen(HPEN & Pen, COLORREF color) {
	DeleteObject(Pen);
    // создаем перо
    if (pen_type == PS_COSMETIC) {
        // косметическое перо
		Pen = CreatePen(line_style, pen_size, color);
    } else {
        // геометрическое перо
		PenBrush.lbColor = color;
		PenBrush.lbStyle = g_style;
		PenBrush.lbHatch = g_hatch;
		int style = PS_GEOMETRIC | line_style | pen_endcap | pen_jointy;
		Pen = ExtCreatePen(style, pen_size, &PenBrush, 0, 0);
    }


}

/* рисует линию */
void DrawMouse(short & X1, short & Y1, short X2, short Y2) {
	RECT rc;

	// Устанавливаем текущую точку
	//MoveToEx(CDC, X1, Y1, 0);
	// рисует отрезок прямой
	LineTo(CDC, X2, Y2);
	// обсновление изображения
	InvalidateRect(hWndGDE, 0, 0);

}

/* рисует прямую */
void DrawLine(short X1, short Y1, short X2, short Y2) {
	// восстановление изображения
	ImageRestore();
	// Устанавливаем текущую точку
	MoveToEx(CDC, X1, Y1, 0);
	// рисует отрезок прямой
	LineTo(CDC, X2, Y2);
	// обсновление изображения
	InvalidateRect(hWndGDE, 0, 0);
}

/* рисует прямоугольник */
void DrawRect(short X1, short Y1, short X2, short Y2) {
	ImageRestore();
	Rectangle(CDC, X1, Y1, X2, Y2);
	InvalidateRect(hWndGDE, 0, 0);
}

/* рисует овал */
void DrawOval(short X1, short Y1, short X2, short Y2) {
	ImageRestore();
	Ellipse(CDC, X1, Y1, X2, Y2);
	InvalidateRect(hWndGDE, 0, 0);
}

/* рисует прямую по алгоритму Брезенхейма */
void DrawBrez(short X1, short Y1, short X2, short Y2) {
}

/* рисует прямую по алгоритму Ву */
void DrawBWoo(short X1, short Y1, short X2, short Y2) {
}
