#include <cstdio>
#include "bst"
using namespace std;

void show(int x) {
	printf("%d ", x);
}

void foo(int x) {
    return;
}

int main() {
	freopen("input", "r", stdin);
	int n, tmp;
	kirai::bst<int> root;
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			root.insert(tmp);
		}
		printf("Preorder traversal:\n");
		root.preorder(show);
		printf("\nInorder traversal:\n");
		root.inorder(show);
		printf("\nPostorder traversal:\n");
		root.postorder(show);
		printf("\nBreadth first search:\n");
		root.bfs(show);
		printf("\nDepth first search:\n");
		root.dfs(show);
		printf("\nosu!:\n");
		std::cout << root;
		printf("\n\n");
		root.clear();
	}
	return 0;
}
