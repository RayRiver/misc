.586
.MODEL FLAT,STDCALL
OPTION CASEMAP:NONE

INCLUDE		windows.inc
INCLUDE		kernel32.inc
INCLUDELIB	kernel32.lib

Test1_WinMain			PROTO 
Test2_WinMain			PROTO 

;################################################################################
.CODE
;################################################################################

;================================================================================
; entry
;================================================================================
main:
		call	Test2_WinMain
		invoke	ExitProcess, NULL
		end	main