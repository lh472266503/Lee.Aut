#include "includes/Log.h"
#include "includes/String.h"
#include <cstdio>

int main()
{
	String str = "abcdDE18236FgH**&&%iJklMn";
	printf("String = %s, size = %d\n", str.CStr(), str.Size());
	str.ToLower();
	printf("String = %s, size = %d\n", str.CStr(), str.Size());
	str.ToUpper();
	printf("String = %s, size = %d\n", str.CStr(), str.Size());
}