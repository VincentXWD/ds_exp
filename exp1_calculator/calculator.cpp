//calculator.cpp
#include "calculator.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <string>
namespace kirai {
	bool isoperator(char ch) {
		//判断是否为操作符的函数
		if ((ch == '+') || (ch == '-') ||
			(ch == '*') || (ch == '/') ||
			(ch == '(') || (ch == ')')) {
			return true;
		}
		return false;
	}

	bool caloperator(char ch) {
		//判断是否为四则运算符号的函数
		if ((ch == '+') || (ch == '-') ||
			(ch == '*') || (ch == '/')) {
			return true;
		}
		return false;
	}

	int leftpriority(char cur) {	
		//定义左端操作符优先级并比较栈顶元素和当前元素的优先级。
		if (cur == '+')	return 3;
		if (cur == '-')	return 3;
		if (cur == '*')	return 5;
		if (cur == '/')	return 5;
		if (cur == '(')	return 1;
		if (cur == ')')	return 6;
		if (cur == '#')	return 0;
		return -1;
	}

	int rightpriority(char cur) {
		//定义右端操作符优先级并比较栈顶元素和当前元素的优先级。
		if (cur == '+')	return 2;
		if (cur == '-')	return 2;
		if (cur == '*')	return 4;
		if (cur == '/')	return 4;
		if (cur == '(')	return 6;
		if (cur == ')')	return 1;
		if (cur == '#')	return 0;
		return -1;
	}

	void calculator::clear() {
		//清空栈
		opt.clear();
		num.clear();
	}

	double calculator::calculate(char opt, double x, double y) {
		//进行计算
		if (opt == '+')		 return x + y;
		else if (opt == '-') return x - y;
		else if (opt == '*') return x * y;
		else if (opt == '/') return x / y;
		else				 return 0;
	}

	void calculator::convert(char* tmp) {   //用栈转换中缀表达式为后缀表达式
		using namespace std;
		int cnt = 0;
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		bool pointflag = false;	//用于确定是否有重复的小数点存在
		stack<char> bracket;	//判断括号是否匹配
		bool matched = false;	//表示括号是否匹配的状态
		for (int i = 0; tmp[i]; i++) {	//首先处理一遍，删掉无关的字符并且删除多余的'.'an 
			//判断括号是否匹配
			if (tmp[i] == '(') {
				bracket.push(tmp[i]);
			}
			if (tmp[i] == ')') {
				if (bracket.empty()) {
					cout << "Error!" << endl;
					return;
				}
				else {
					bracket.pop();
				}
			}
			//筛选出有效字符
			if (isoperator(tmp[i]) || isdigit(tmp[i])) {	//符合条件的放入缓冲区
				if (pointflag && tmp[i+1]) {
					pointflag = false;
				}	
				buffer[cnt++] = tmp[i];
			}
			else if (tmp[i] == '.' && !pointflag) {
				pointflag = true;
				buffer[cnt++] = tmp[i];
			}
			else if (tmp[i] == '.' && !isdigit(tmp[i-1]) && !isdigit(tmp[i +1])) {
				continue;
			}
		}
		strcpy(tmp, buffer);
		cnt = 0;
		int rem = -1;	//记下上一个数字or运算符
		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; tmp[i]; i++) {
			if (tmp[i] == ')' && tmp[i+1] == '(' && tmp[i]) {
				cout << "Error!" << endl;	//有两个括号相邻却无运算符链接的情况
				return;
			}
			if (rem != -1) {
				if (caloperator(tmp[i]) && caloperator(rem)) {	//如果当前是运算符并且上一个也是运算符，说明冲突。重复运算符出现。
					cout << "Error!" << endl;
					return;
				}
			}
			if (isdigit(tmp[i]) || caloperator(tmp[i])) {
				//记录上一个数字or运算符
				rem = i;
			}
			buffer[cnt++] = tmp[i];
		}

		buffer[cnt] = '#';			//把字符串的'\0'去掉，符合正常输入的逻辑，用stringstream模拟cin输入
		stringstream ss(buffer);	//将处理过的tmp(buffer)装填到streingstream中待使用
		char ch, op, theta;
		double val, a, b;
		ss >> ch;
		op = '#';
		while (ch != '#' || (op != '#')) {
			if (isdigit(ch)) {  //获取数字
				ss.putback(ch);
				ss >> val;
				num.push(val);
				ss >> ch;
			}
			else if (leftpriority(op) < rightpriority(ch)) {
				opt.push(ch);
				ss >> ch;
			}
			else if (leftpriority(op) == rightpriority(ch)) {
				opt.pop();
				ss >> ch;
			}
			else {
				if (num.size() < 2) {
					cout << "Error!" << endl;	//不够两个操作数来计算
					return;
				}
				theta = opt.pop();
				b = num.pop();
				a = num.pop();
				num.push(calculate(theta, a, b));
			}
			op = opt.top();
		}

		if (num.empty()) {
			cout << "Error!" << endl;
		}
		else {
			cout << buffer;	//输出处理后的字符串
			cout << '\b' << " = " << num.top() << endl;
		}
		clear();
	}
}
