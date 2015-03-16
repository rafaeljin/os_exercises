#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

//assume memory size = 1Mb = 2**20b
#define MEMORY_SIZE 20

using namespace std;

//buddy system list


struct block{
	int size;
	int start;
};

vector < vector<block> > bslist;

block my_malloc(int size);
void init();
void my_free(block blc);
int _power(int val,int pow){
	if(pow <= 0)
		return 1;
	return val * _power(val,pow - 1);
}
int getPower(int N){
	if(N == 0)
		return -1;
	N--;
	int count = 0;
	while(N > 0){
		N = N/2;
		count ++;
	}
	return count;
}
void my_print(){
	int count = 0;
	for(vector< vector<block> >::iterator ite = bslist.begin();ite != bslist.end();ite++){
		if((*ite).size() > 0)
			printf("\t%d:\n",count );
		count ++;
		for(vector<block>::iterator iter = (*ite).begin(); iter != (*ite).end(); iter++){
			printf("\t\tstart:%d=%dK size:%d\n",(*iter).start,(*iter).start/1024,(*iter).size);
		}
	}
}

int main(){
	init();
	printf("After ini:\n");
	my_print();

	block A = my_malloc(100*1024);
	printf("After Request 100K:\n");
	printf("A got memory starting at %dK with the size of 2**%d\n",A.start/1024,A.size);
	my_print();

	block B = my_malloc(240*1024);
	printf("After Request 240K:\n");
	printf("B got memory starting at %dK with the size of 2**%d\n",B.start/1024,B.size);
	my_print();
	
	block C = my_malloc(64*1024);
	printf("After Request 64K:\n");
	printf("C got memory starting at %dK with the size of 2**%d\n",C.start/1024,C.size);
	my_print();

	block D = my_malloc(256*1024);
	printf("After Request 256K:\n");
	printf("D got memory starting at %dK with the size of 2**%d\n",D.start/1024,D.size);
	my_print();
	
	my_free(B);
	printf("After FRee B:\n");
	my_print();

	my_free(A);
	printf("After Free A\n");
	my_print();

	block E = my_malloc(75*1024);
	printf("After Request 75K:\n");
	printf("E got memory starting at %dK with the size of 2**%d\n",E.start/1024,E.size);
	my_print();

	my_free(C);
	printf("After FRee C:\n");
	my_print();

	my_free(E);
	printf("After Free E\n");
	my_print();

	my_free(D);
	printf("After Free D\n");
	my_print();
	return 0;
}

void init(){
	vector<block> v;
	for(int i=0;i<MEMORY_SIZE+1;i++){
		bslist.push_back(v);
	}
	block ini; ini.size = MEMORY_SIZE; ini.start = 0;
	bslist[MEMORY_SIZE].push_back(ini);
}

block my_malloc(int size){
	int start = -1;
	int pow = getPower(size);
	// search = collumn to start searching
	int search = pow;
	while(search <= MEMORY_SIZE){
		//printf("search:%d\n", search);
		if(bslist[search].size() > 0){
			//printf("note\n");
			int t_start = -1;
			start = bslist[search][0].start;
			int t_size  = bslist[search][0].size;
			(bslist[search]).erase(bslist[search].begin());
			//printf("t:%d s:%d\n",t_size,size );
			while(t_size > pow){
				//printf("test\n");
				t_size --;
				t_start = start + _power(2,t_size);
				vector<block>::iterator pos = bslist[t_size].begin();
				while(pos != bslist[t_size].end()){
					if(t_start < (*pos).start)
						break;
					pos ++ ;
				}
				block bk; bk.start = t_start; bk.size=t_size;
				(bslist[t_size]).insert(pos,bk);
			}

			break;
		}
		search ++;
	}
	block forReturn; forReturn.start = start; forReturn.size = pow;
	return forReturn;
}
void my_free(block blc){
	int start = blc.start;
	int size = blc.size;
	int toFind;
	//printf("start:%d\n",start);
	if(start % _power(2,size+1) == 0)
		toFind = start + _power(2,size);
	else
		toFind = start - _power(2,size);
	//printf("tofind:%dK\n",toFind/1024 );
	if(bslist[size].size() == 0){
		printf("insert1\n");
		bslist[size].insert(bslist[size].begin(),blc);
		return;
	}
	for(vector<block>::iterator it = bslist[size].begin();it!=bslist[size].end();it++){
		if((*it).start > toFind){
			printf("insert2\n");
			bslist[size].insert(it,blc);
			break;
		}
		else if((*it).start == toFind){
			bslist[size].erase(it);
			block toFree; toFree.size = size + 1; toFree.start = (start % _power(2,size+1) == 0)?start:toFind;
			my_free(toFree);
			return;
		}
	}
}
