#include <iostream>
#include <windows.h>
//#include <cstdlib>
using namespace std;

int main()
{
	/* Calling a program using system() call
	// calling a program from another using system() call
	//system("C:\\Users\\Ananya_Jana\\AppData\\Local\\Mozilla Firefox\\firefox.exe");
	//system("start C:\\Users\\Ananya_Jana\\AppData\\Local\\\"Mozilla Firefox\"\\firefox.exe");
	//system("start firefox.exe");

	// check out why it doesn't work
	//system("start \"C:\\Users\\Ananya_Jana\\Documents\\Visual Studio 2010\\Projects\\Assignment_1\\Debug\\Assignment_1.exe\"");

	// It's what I required
	//system("start C:\\Users\\Ananya_Jana\\Documents\\\"Visual Studio 2010\\Projects\"\\Assignment_1\\Debug\\Assignment_1.exe");
	
	// It works
	//system("start C:\\Users\\Ananya_Jana\\Documents\\Assignment_1.exe");
	
	//system("start Libraries\\Documents\\Assignment_1.exe");
	//system("start Dragnet 5");
	//system("start Network"); */
	

	// Calling a prgroam from another without using system() call
	cout << "Calling another executable" << endl;
	STARTUPINFO info={sizeof(info)};
	PROCESS_INFORMATION processInfo;

	if (!CreateProcess("C:\\Users\\Ananya_Jana\\Documents\\Visual Studio 2010\\Projects\\Assignment_1\\Debug\\Assignment_1.exe", 
		NULL, 
		NULL, 
		NULL, 
		TRUE, 
		0, 
		NULL, 
		NULL, 
		&info, 
		&processInfo))
	{
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
	
	//cout << "Exiting..." << endl;
	//cin.get();
}