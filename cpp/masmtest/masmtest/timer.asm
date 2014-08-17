.586
.MODEL FLAT,STDCALL
OPTION CASEMAP:NONE

INCLUDE		windows.inc
INCLUDE		user32.inc
INCLUDELIB	user32.lib
INCLUDE		kernel32.inc
INCLUDELIB	kernel32.lib

;################################################################################
.CODE
;################################################################################


;================================================================================
; Timer
;================================================================================
Timer PROC x:DWORD
		ret
Timer ENDP

END