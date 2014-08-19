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
INCLUDE		comdlg32.inc
INCLUDELIB	comdlg32.lib

; 等值定义
IDD_DIALOG1		EQU		102

;################################################################################
.DATA?
;################################################################################
hInstance		DD	?

;################################################################################
.CODE
;################################################################################

;================================================================================
; _ProcDlgMain
;================================================================================
_ProcDlgMain PROC USES ebx edi esi hWnd, wMsg, wParam, lParam
		mov		eax, wMsg
		.IF		eax == WM_CLOSE
				invoke	EndDialog, hWnd, NULL
		.ELSE
				mov		eax, FALSE
				ret
		.ENDIF

		mov		eax, TRUE
		ret
_ProcDlgMain ENDP

;================================================================================
; _WinMain
;================================================================================
Test2_WinMain PROC
		invoke	GetModuleHandle, NULL
		mov		hInstance, eax
		invoke	DialogBoxParam,	hInstance, IDD_DIALOG1, NULL, OFFSET _ProcDlgMain, NULL
		ret
Test2_WinMain ENDP

END
