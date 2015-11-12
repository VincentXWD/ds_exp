//calculator.h
#pragma once
#include "lib/stack"

namespace kirai {
	class calculator {
	public:
		calculator() { clear(); opt.push('#'); }
		~calculator() { clear(); }
		void clear();
		//void convert();
		void convert(char*);
	protected:
		double calculate(char, double ,double);
		friend bool isoperator(char);
		friend bool caloperator(char);
		friend int leftpriority(char);
		friend int rightpriority(char);

	protected:
		stack<char> opt;	//���ڴ�Ų���
		stack<double> num;	//���ڴ������
	};
}
