#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void printRed(const char* fmt, ...) 
{
	va_list args;
	va_start(args, fmt);

	int x = strlen(fmt) + 14;
	
	char wholeString[x];
	wholeString[0] = '\0';

	strcat(wholeString, "\x1B[31m");
	strcat(wholeString, fmt);
	strcat(wholeString, "\033[0m");

	vprintf(wholeString, args);
	va_end(args);
}

void printGrn(const char* fmt, ...) 
{
	va_list args;
	va_start(args, fmt);

	int x = strlen(fmt) + 14;
	
	char wholeString[x];
	wholeString[0] = '\0';

	strcat(wholeString, "\x1B[32m");
	strcat(wholeString, fmt);
	strcat(wholeString, "\033[0m");

	vprintf(wholeString, args);
	va_end(args);
}

void printBlu(const char* fmt, ...) 
{
	va_list args;
	va_start(args, fmt);

	int x = strlen(fmt) + 14;
	
	char wholeString[x];
	wholeString[0] = '\0';

	strcat(wholeString, "\x1B[34m");
	strcat(wholeString, fmt);
	strcat(wholeString, "\033[0m");

	vprintf(wholeString, args);
	va_end(args);
}
