#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int main(){
	FILE *ifs = freopen("in33.txt","r",stdin);
	FILE *ofs = freopen("out33.txt","w",stdout);
	unsigned int va = 0, pa = 0;
	
	for(int i=0;i<10;i++){
		scanf("va %x, pa %x\n",&va,&pa);
		unsigned int pde_idx = va >> 22;
        unsigned int pde_ctx = ((pde_idx - 0x300 + 1) << 12) | 0x3;
        unsigned int pte_idx = (va  >> 12) & 0X3FF;
        unsigned int pte_ctx = (pa & 0xFFFFF000) | 0x3;
		printf("va 0x%08x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x, \n"\
			,va,pa,pde_idx,pde_ctx,pte_idx,pte_ctx );
	}
	return 0;
}