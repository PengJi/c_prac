#include <stdio.h>
#include <stdlib.h>

/**
 * 字符串转换为浮点型
 */

int main(){
	char *endptr;
	char a[] = "12345.6789";
	char b[] = "1234.567qwer";
	char c[] = "-232.23e4";

	//使用atof
	printf("a=%lf\n", atof(a));
	printf("b=%lf\n", atof(b));
	printf("c=%lf\n", atof(c));

	//使用strod
	printf("a=%lf\n", strtod(a,NULL));
	printf("b=%lf\n", strtod(b, &endptr));
	printf("endptr=%s\n", endptr);
	printf("c=%lf\n", strtod(c, NULL));

	return 0;
}
