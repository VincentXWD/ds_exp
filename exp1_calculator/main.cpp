//main.cpp
#include <iostream>
#include "calculator.h"
using namespace std;
 
int main() {
	char tmp[1024];
	memset(tmp, 0, sizeof(tmp));
	freopen("cases", "r", stdin);
	cin >> tmp;
	while (strcmp(tmp, "@") != 0) {
		kirai::calculator cal;
		cal.convert(tmp);
		memset(tmp, 0, sizeof(tmp));
		cin >> tmp;
	}
	//strcpy_s(tmp, "89.5*749+25)#");
	//strcpy_s(tmp, "()(5dsa6 sad-asd dd23)d d/d d8d asdd-asd asd4");
	//strcpy_s(tmp, "(8*(7-4)#");
	//char* tmp = "(2ewqoeopqw`.5*hasdao(asdsda3+5.13.).+.w.q./asd,adskahdlae.joiqe(2..-...3...3./6.sdaoihdaoisdq)*4asadsd.1)";
}
