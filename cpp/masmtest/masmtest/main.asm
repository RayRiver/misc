.586
.MODEL FLAT,STDCALL
OPTION CASEMAP:NONE

INCLUDE		windows.inc
INCLUDE		gdi32.inc
INCLUDELIB	gdi32.lib
INCLUDE		user32.inc
INCLUDELIB	user32.lib
INCLUDE		kernel32.inc
INCLUDELIB	kernel32.lib

INCLUDE		timer.inc

; 等值定义
IDR_MENU1		EQU		101
IDM_EXIT		EQU		40001
IDM_ABOUT		EQU		40002
IDM_HELP		EQU		40003

;################################################################################
.DATA?
;################################################################################
hInstance		DD	?
hWinMain		DD	?
hMenu			DD	?

;################################################################################
.CONST
;################################################################################
szCaption		DB	'测试', 0
szMsgAbout		DB	'这是关于对话框', 0
szMsgHelp		DB	'这是帮助对话框', 0
szClassName		DB	'my class', 0
szCaptionMain	DB	'my first window', 0
szTextMain		DB	'你好 win32 asm!', 0

;################################################################################
.CODE
;################################################################################

;================================================================================
; _Quit
;================================================================================
_Quit PROC
		invoke	DestroyWindow, hWinMain
		invoke	PostQuitMessage, NULL
		ret
_Quit ENDP

;================================================================================
; _ProcWinMain
;================================================================================
_ProcWinMain PROC USES ebx edi esi, hWnd, uMsg, wParam, lParam
		LOCAL	@stPs:PAINTSTRUCT
		LOCAL	@stRect:RECT
		LOCAL	@hDc

		mov		eax, uMsg
		.IF		eax == WM_PAINT
				invoke	BeginPaint, hWnd, ADDR @stPs
				mov		@hDc, eax

				invoke	GetClientRect, hWnd, ADDR @stRect
				invoke	DrawText, @hDc, ADDR szTextMain, -1, ADDR @stRect, DT_SINGLELINE or DT_CENTER or DT_VCENTER
				invoke	EndPaint, hWnd, ADDR @stPs
		.ELSEIF	eax == WM_CLOSE
				call	_Quit
		.ELSEIF eax == WM_COMMAND
				mov		eax, wParam
				.IF		eax == IDM_EXIT
						call	_Quit
				.ELSEIF	eax == IDM_ABOUT
						invoke	MessageBox, NULL, OFFSET szMsgAbout, OFFSET szCaption, MB_OK
				.ELSEIF	eax == IDM_HELP
						invoke	MessageBox, NULL, OFFSET szMsgHelp, OFFSET szCaption, MB_OK
				.ENDIF
		.ELSE
				invoke	DefWindowProc, hWnd, uMsg, wParam, lParam
				ret
		.ENDIF

		xor		eax, eax
		ret
_ProcWinMain ENDP

;================================================================================
; _WinMain
;================================================================================
_WinMain PROC
		LOCAL	@stWndClass:WNDCLASSEX
		LOCAL	@stMsg:MSG

		invoke	GetModuleHandle, NULL
		mov		hInstance, eax

		; 加载菜单
		invoke	LoadMenu, hInstance, IDR_MENU1
		mov		hMenu, eax

		; 注册窗口类
		invoke	RtlZeroMemory, ADDR @stWndClass, SIZEOF @stWndClass
		invoke	LoadCursor, 0, IDC_ARROW
		mov		@stWndClass.hCursor, eax
		push	hInstance
		pop		@stWndClass.hInstance
		mov		@stWndClass.cbSize, SIZEOF WNDCLASSEX
		mov		@stWndClass.style, CS_HREDRAW or CS_VREDRAW
		mov		@stWndClass.lpfnWndProc, OFFSET _ProcWinMain
		mov		@stWndClass.hbrBackground, COLOR_WINDOW+1
		mov		@stWndClass.lpszClassName, OFFSET szClassName
		invoke	RegisterClassEx, ADDR @stWndClass

		; 创建窗口
		invoke	CreateWindowEx, WS_EX_CLIENTEDGE, \
				OFFSET szClassName, OFFSET szCaptionMain, \
				WS_OVERLAPPEDWINDOW, \
				100, 100, 600, 400, \
				NULL, hMenu, hInstance, NULL
		mov		hWinMain, eax

		; 显示窗口
		invoke	ShowWindow, hWinMain, SW_SHOWNORMAL
		invoke	UpdateWindow, hWinMain

		; 消息循环
		.WHILE	TRUE
				invoke	GetMessage, ADDR @stMsg, NULL, 0, 0
				.BREAK	.IF eax == 0
				invoke	TranslateMessage, ADDR @stMsg
				invoke	DispatchMessage, ADDR @stMsg
		.ENDW

		ret
_WinMain ENDP

;================================================================================
; entry
;================================================================================
main:
		call	Timer
		call	_WinMain
		invoke	ExitProcess, NULL
		end	main