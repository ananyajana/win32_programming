#include <iostream>
#include <windows.h>
#define MAXLEN	100								
#define ENTER_KEY	10

typedef char* (*StringReverse1)(const char*);	// pointer to the function which reverses the string without manipulating the string itself
typedef int (*StringReverse2)(char*);			// pointer to the function which reverses the string itself

using namespace std;

extern "C"

int main()
{
	int ret_val;
	int printable_str_len = 0;					// Variable to store the the the total number of printable characters given as input.
	char current_char = 0;
	char* input_string = new char[MAXLEN];
	char* rev_str = '\0';						// pointer to the reverse string of input string.

	StringReverse1 string_reverse1;
	StringReverse2 string_reverse2;

	// Loading the instance of the dll into this process's address space
	
	HINSTANCE hInstLibrary = LoadLibrary("C:\\Users\\Ananya_Jana\\Documents\\Visual Studio 2010\\Projects\\Test_DLL\\Debug\\Test_DLL.dll");
	// don't forget to insert necessary backslashes in path


	if(hInstLibrary){

		//Taking user i/p
		cout << "Enter the string to be reversed:" << endl;

		current_char = cin.get();
		while((printable_str_len < MAXLEN - 1) && (current_char != '\n')){
			if( ((current_char >= 32) && (current_char <= 126)) || (current_char == '\t') ) // check whether the character is printable or not
				input_string[printable_str_len++] = current_char;
			current_char = cin.get();
		}

		
		input_string[printable_str_len] = '\0';
		if(input_string[0] == '\0'){
			cout << "Null string!!" << endl;
			cin.get();
			return 0;
		}
		//cout << input_string << endl;

		// Using the dll function
		string_reverse1 = (StringReverse1)GetProcAddress(hInstLibrary, "strrev1");
		string_reverse2 = (StringReverse2)GetProcAddress(hInstLibrary, "strrev2");

		
		if( string_reverse1 && string_reverse2){
			rev_str = string_reverse1(input_string);
			ret_val = string_reverse2(input_string);
		}

		else{
			DWORD errCode = GetLastError();
			char* err;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				errCode,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
				(LPTSTR) &err,
				0,
				NULL);
			cout << err << endl;
		}

		// displaying the o/p ----
		cout << "The reversed string(strrev1) is:" << endl << rev_str << endl;
		
		if(ret_val == 0)
			cout << "The reversed string(strrev2) is:" << endl << input_string << endl;
		else
			cout << "In place string manipulation failed.\n" << endl; 

		// freeing memory
		delete[] input_string;
		free(rev_str);
		FreeLibrary(hInstLibrary);
	}


	//error message
	else{
		cout << "Cause of failure:" << endl;
		DWORD errCode = GetLastError();
		char* err;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           errCode,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
                           (LPTSTR) &err,
                           0,
                           NULL);
		cout << err << endl;
	}
	
	cin.get();

	return 0;

}