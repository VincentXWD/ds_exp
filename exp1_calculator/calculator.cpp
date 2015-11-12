//calculator.cpp
#include "calculator.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <string>
namespace kirai {
	bool isoperator(char ch) {
		//�ж��Ƿ�Ϊ�������ĺ���
		if ((ch == '+') || (ch == '-') ||
			(ch == '*') || (ch == '/') ||
			(ch == '(') || (ch == ')')) {
			return true;
		}
		return false;
	}

	bool caloperator(char ch) {
		//�ж��Ƿ�Ϊ����������ŵĺ���
		if ((ch == '+') || (ch == '-') ||
			(ch == '*') || (ch == '/')) {
			return true;
		}
		return false;
	}

	int leftpriority(char cur) {	
		//������˲��������ȼ����Ƚ�ջ��Ԫ�غ͵�ǰԪ�ص����ȼ���
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
		//�����Ҷ˲��������ȼ����Ƚ�ջ��Ԫ�غ͵�ǰԪ�ص����ȼ���
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
		//���ջ
		opt.clear();
		num.clear();
	}

	double calculator::calculate(char opt, double x, double y) {
		//���м���
		if (opt == '+')		 return x + y;
		else if (opt == '-') return x - y;
		else if (opt == '*') return x * y;
		else if (opt == '/') return x / y;
		else				 return 0;
	}

	void calculator::convert(char* tmp) {   //��ջת����׺���ʽΪ��׺���ʽ
		using namespace std;
		int cnt = 0;
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		bool pointflag = false;	//����ȷ���Ƿ����ظ���С�������
		stack<char> bracket;	//�ж������Ƿ�ƥ��
		bool matched = false;	//��ʾ�����Ƿ�ƥ���״̬
		for (int i = 0; tmp[i]; i++) {	//���ȴ���һ�飬ɾ���޹ص��ַ�����ɾ�������'.'an 
			//�ж������Ƿ�ƥ��
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
			//ɸѡ����Ч�ַ�
			if (isoperator(tmp[i]) || isdigit(tmp[i])) {	//���������ķ��뻺����
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
		int rem = -1;	//������һ������or�����
		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; tmp[i]; i++) {
			if (tmp[i] == ')' && tmp[i+1] == '(' && tmp[i]) {
				cout << "Error!" << endl;	//��������������ȴ����������ӵ����
				return;
			}
			if (rem != -1) {
				if (caloperator(tmp[i]) && caloperator(rem)) {	//�����ǰ�������������һ��Ҳ���������˵����ͻ���ظ���������֡�
					cout << "Error!" << endl;
					return;
				}
			}
			if (isdigit(tmp[i]) || caloperator(tmp[i])) {
				//��¼��һ������or�����
				rem = i;
			}
			buffer[cnt++] = tmp[i];
		}

		buffer[cnt] = '#';			//���ַ�����'\0'ȥ������������������߼�����stringstreamģ��cin����
		stringstream ss(buffer);	//���������tmp(buffer)װ�streingstream�д�ʹ��
		char ch, op, theta;
		double val, a, b;
		ss >> ch;
		op = '#';
		while (ch != '#' || (op != '#')) {
			if (isdigit(ch)) {  //��ȡ����
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
					cout << "Error!" << endl;	//��������������������
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
			cout << buffer;	//����������ַ���
			cout << '\b' << " = " << num.top() << endl;
		}
		clear();
	}
}
