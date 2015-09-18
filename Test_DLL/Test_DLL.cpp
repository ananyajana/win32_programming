#include <iostream>
#include "Test_DLL.h"

#define DLL_EXPORT
using namespace std;

extern "C"
{
	__declspec(dllexport) int welcome_message(char* str)
	{
		cout << "Hi" << str << endl;
		return 0;
	}

	__declspec(dllexport) char* strrev1(const char* str)
	{
		int i = 0, len = 0;
		
		while(str[i++])
			++len;

		char* reverse_string = new char[len + 1];
		
		for(i = 0; i < len; ++i)
			reverse_string[len - 1 - i] = str[i];

		reverse_string[len] = '\0';

		//cout << "in strrev1:" << reverse_string << endl;

		return reverse_string;

	}

	__declspec(dllexport) int strrev2(char* str)
	{
		int i = 0, len = 0, mid;
		
		char* q = str;
		while(q && *q) ++q;
		for(--q; str < q; ++str, --q){
			*str = *str ^ *q,
			*q = *str ^ *q,
			*str = *str ^ *q;
		}


		//cout << "in strrev2:" << str << endl;
		return 0;
	}
}