// test_lemon.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <stdlib.h>
#include <Windows.h>
#include <setjmp.h>

//jmp_buf co;
int co;
int ret_to;

void *sbp, *sbx, *sdi, *ssp;

int test_accept() {
	printf("hello\n");
	
	while (true) {
		int n = 0;

		printf("N : ");
		scanf_s("%d", &n);

		if (n == -1) {
			__asm {
				mov eax, -1;
			}
			return;
		}

		void *vstack = malloc(1024);

		__asm {
			mov eax, hello;
			mov co, eax;
			mov eax, [ebp + 4];
			mov ret_to, eax;

			mov sbp, ebp;
			mov sbx, ebx;
			mov sdi, edi;
			mov ssp, esp;
			mov ebp, vstack;

			jmp ret_to;
		}
	hello:
		__asm {
			mov ebp, sbp;
			mov ebx, sbx;
			mov edi, sdi;
			mov esp, ssp;
		}
	}
	
	/*

	printf("world\n");

	vstack = malloc(1024);

	__asm {
		mov eax, hello2;
		mov co, eax;
		mov eax, [ebp + 4];
		mov ret_to, eax;

		mov sbp, ebp;
		mov sbx, ebx;
		mov sdi, edi;
		mov ssp, esp;
		mov ebp, vstack;

		jmp ret_to;
	}
hello2:
	__asm {
		mov ebp, sbp;
		mov ebx, sbx;
		mov edi, sdi;
		mov esp, ssp;
	}

	printf("end\n");
	*/

	__asm {
		mov eax, -1;
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	int a = 1234;

	int c;

	if (test_accept() != -1) {
		int test_local = 1234;

		printf("accepted : %d\n", test_local);

		test_local = 12345;

		__asm {
			jmp co;
		}
	}
	/*
	__asm {
	mov c, eax;
	}
	printf("ret\n");
	Sleep(10);
	if(c != -1){

	}
	*/
	//	printf("onret\n");

	/*
	hello:
	__asm {
	mov eax, hello;
	mov c, eax;
	}
	printf("qwer");
	__asm jmp c;
	//mov ebp, vstack;
	*/
	return 0;
}
