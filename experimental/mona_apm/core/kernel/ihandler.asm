;;;
;      \file  ihandler.asm
;      \brief interrupt handlers

;      definition for IDT
;      Copyright (c) 2002,2003 Higepon
;      All rights reserved.
;      License=MIT/X License

;      \author  HigePon
;      \version $Revision$
;      \date   create:2003/02/24 update:$Date$
;;;
BITS 32

%include "macro.asm"

cglobal arch_fault0dhandler
cglobal arch_dummyhandler
cglobal arch_syscall_handler
cglobal arch_cpufaulthandler_e
cglobal arch_cpufaulthandler_c
cextern g_currentThread
cextern arch_switch_process
cextern cpufaultHandler_c
cextern cpufaultHandler_e
cextern arch_set_stack_view
cextern fault0dHandler
cextern syscall_entrance
cextern dummyHandler
cextern arch_save_thread_registers
cextern arch_save_thread_registers2
cextern arch_set_dokodemo_view

%define KERNEL_DS 0x10

%macro pushAll 0
        pushad
        push ds
        push es
%endmacro

%macro popAll 0
        pop es
        pop ds
        popad
%endmacro

%macro changeData 0
        push dword KERNEL_DS
        pop  es
        push dword KERNEL_DS
        pop  ds
%endmacro

;;; IRQ handlers
%macro irqhandler 1
cglobal arch_irqhandler_%1
cextern irqHandler_%1
arch_irqhandler_%1:
        pushAll
        changeData
        call arch_save_thread_registers
;         call arch_set_dokodemo_view
;         call arch_set_stack_view
        call irqHandler_%1
        popAll
        iretd
%endmacro

section .text

irqhandler 0
irqhandler 1
irqhandler 2
irqhandler 3
irqhandler 4
irqhandler 5
irqhandler 6
irqhandler 7
irqhandler 8
irqhandler 9
irqhandler 10
irqhandler 11
irqhandler 12
irqhandler 13
irqhandler 14
irqhandler 15

;;; dummy handler
arch_dummyhandler:
        pushAll
        changeData
        call dummyHandler
        popAll
        iretd

;;; fault0dHandler
arch_fault0dhandler:
        call arch_set_dokodemo_view
        pushAll
        changeData
        call arch_save_thread_registers
        push dword[esp + 40]
        call arch_set_stack_view
        call fault0dHandler
        add  esp, 0x04          ; remove error_cd
        popAll
        iretd

%macro cpufaulthandler 1
cglobal arch_cpufaulthandler_%1
cextern cpufaultHandler_%1
arch_cpufaulthandler_%1:
        call arch_set_dokodemo_view
        pushAll
        changeData
        call arch_save_thread_registers
        call arch_set_stack_view
        call cpufaultHandler_%1
        popAll
        iretd
%endmacro

        cpufaulthandler 0
        cpufaulthandler 1
        cpufaulthandler 5
        cpufaulthandler 6
        cpufaulthandler 7
        cpufaulthandler 8
        cpufaulthandler a
        cpufaulthandler b
;          cpufaulthandler c;;;; removed by higepon
;          cpufaulthandler e;;;; removed by higepon
        cpufaulthandler 10
        cpufaulthandler 11

arch_cpufaulthandler_c:
        pushAll
        changeData
        call arch_save_thread_registers
        push dword[esp + 40]
        call cpufaultHandler_c
        add  esp, 0x04          ; remove error_cd
        popAll
        iretd

arch_cpufaulthandler_e:
        pushAll
        changeData
        call arch_save_thread_registers2
        push ebp
        mov  ebp, esp
        sub  esp, 8
        mov  eax, dword[esp + 52] ; error cd
        mov  dword[esp + 4], eax
        mov  eax, cr2             ; page fault address
        mov  dword[esp + 0], eax
        call cpufaultHandler_e
        leave
        popAll
        add esp, 0x04             ; remove error_cd
        iretd

;;; entrance of syscall
arch_syscall_handler:
        pushAll
        changeData
        call arch_save_thread_registers
        call syscall_entrance
        mov eax, dword[g_currentThread]
        mov ebx, dword[eax + 0 ]           ; ArchThreadInfo
        mov eax, dword [ebx + 12]          ; at g_current_thread->eax
        mov dword[esp + 36], eax           ; so set this to stack
        popAll
        iretd