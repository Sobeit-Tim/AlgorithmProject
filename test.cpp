#include <cstdio>
#include "RBtree.h"

int main(){
	Tree T;
	Path p;
	p.source = 1;
	char s[20] = "hi";
	int id = 0;
	Node *t;
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.insert(s, p);
	T.printBST();
	
	printf("# of nodes %d, height %d\n",T.num_node, T.getHeight());
	
	int check = T.remove(4);
	if(check == 0) // 4 �� ����
		printf("4�� ����\n");
	else
		printf("4�� ���������� ����\n"); 
	T.printBST();
	printf("# of nodes %d, height %d\n",T.num_node, T.getHeight());
	
	
	t = T.search(T.root, id, T.root, 1);
	printf("\n");
	if(t->reserve_id != id){
		printf("%d �� ���� x\n",id);
	}else{
		printf("%d %d %s\n", t->reserve_id, t->path.source, t->name);
	}
	return 0;
}

