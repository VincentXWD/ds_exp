#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>
#include <complex>
#include <cassert>
#include <cstdio>
#include <bitset>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <set>
#include <map>
#include <cmath>

using namespace std;

const int maxn = 20;
int queen[maxn];    //queen[col] = row
int n, cnt;

void print(int n) {	//print the answers
	for(int i = 0; i < 2 * n; i++) {
		printf("=");
	}
	printf("\n");
	for(int cc = 0; cc < n; cc++) {
		for(int rr = 0; rr < n; rr++) {
			if(queen[cc] == rr) {
				printf("* ");
			}
			else {
				printf("- ");
			}
		}
		printf("\n");
	}
	for(int i = 0; i < 2 * n; i++) {
		printf("=");
	}
	printf("\n\n");
}

bool ok(int cc) {
	for(int rr = 0; rr < cc; rr++) {
		if(queen[rr] == queen[cc] || //stright line
			/*for example:
			
			*----- queen[0] == 0
			--*--- queen[1] == 2
			*----- queen[2] == 0
			...
			now queen[0] == queen[2] and have an attack in stright line

			*/
			abs(rr - cc) == abs(queen[rr] - queen[cc])) {	//oblique line
			/*for example:
			
			*----- queen[0] == 0
			--*--- queen[1] == 2
			---*-- queen[2] == 3
			...
			now abs(2 - 1) == abs(queen[2] - queen[1] == 1) and have an attack in oblique line

			*/
			return false;
		}
	}
	return true;
}

void dfs(int cc) {
	if(cc == n) {
		cnt++;
		// print(n);
		// system("pause");
		// system("cls");
		// printf("Total : %d\n\n", cnt);
		return;
	}
	for(int rr = 0; rr < n; rr++) {
		queen[cc] = rr;	//assume and dfs the ccth queen's position from (cc, rr)
		if(ok(cc)) {	//if satisfied then search next line.
			dfs(cc + 1);
		}
	}
}

int main() {
	clock_t start, finish;
	// freopen("input", "r", stdin);	//redirect input and outpu to files.
	// freopen("output", "w", stdout);
	printf("Please input n. (End with 0): ");
	while(~scanf("%d", &n)) {
		cnt = 0;
		start = clock();
		dfs(0);	
		finish = clock();
		printf("Total : %d Time consuming:%lf second.\n\n", cnt, (double)(finish - start) / CLOCKS_PER_SEC);
		printf("Please input n. (End with 0): ");
	}

}
