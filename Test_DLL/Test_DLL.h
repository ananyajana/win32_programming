
extern "C"
{
	__declspec(dllexport) int welcome_message(char* str);
	__declspec(dllexport) char* strrev1(const char* str);
	__declspec(dllexport) int strrev2(char* str);
}