
#include <iostream>
#pragma inline
using namespace std;

int main() {
	int countNumbers = 5;
	float ten = 10;
	int* array = new int[countNumbers];
	float buffer;
	int* answer = new int[countNumbers];
	int result = 0;

	for (int i = 0; i < countNumbers; i++) {
		do {
			answer[i] = 0;
			cout << "Enter float number(array[" << i << "]) : ";
			cin >> buffer;
			if (cin.good()) {
				array[i] = buffer;
				break;
			}
			else {
				rewind(stdin);
				cin.clear();
			}
		} while (true);
	}

	_asm {
		xor ecx, ecx
		mov cx, 5
		
		mov edx, array

		//fld ten

		maxEl:
			mov esi, edx
			mov cx, 5
			xor ebx, ebx // в bh - максимум

			noe:
				lodsb
				cmp al, bh
				jg maxi
			jmp noe
			maxi:
				mov bh, al
			mol:
			loop noe

		fld [ebx]
		fld result

		start:

			fadd[edx]	// st[0] = st(0)(result) + [eax]
			//fdiv st(0), st(1);
			//fst[eax]

			//add eax, 4
			add edx, 4	// next number

			cmp ecx, 0	// if cx = 0  - exit and print answer
			dec cx
			jne start	// else - loop start

			fdiv st(0), st(1) 
			fst result

			fwait
	}


	cout << result << endl << endl;

	for (int i = 0; i < countNumbers; i++)
		cout << answer[i] << " ";

	return 0;
}

