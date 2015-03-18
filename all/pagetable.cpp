#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define PDT 0X11
unsigned int MEM[128][32];
int temp;
int main(){
	FILE *ifs1 = freopen("in.txt","r",stdin);
	for (int i = 0; i < 128; i++){
		scanf("page %d:",&temp);
		printf("%d\n",temp );
		for(int j = 0; j < 32 ; j++){
			scanf("%2x",&MEM[i][j]);
		}
		scanf("\n");
	}

	FILE *ofs1 = freopen("temp.txt","w",stdout);
	for (int i = 0; i < 128; i++){
		for(int j = 0; j < 32 ; j++){
			printf("%2x ", MEM[i][j]);
		}
		printf("\n");
	}

	FILE *ifs2 = freopen("inputdata.txt","r",stdin);
	FILE *ofs2 = freopen("out.txt","w",stdout);
	int sign = -1;
	for(int i = 0; i < 10 ; i++ ){
		int va;
		scanf("%4x",&va);
		printf("\t\tVirtual Address %x:\n", va);
		int pdea = va & 0x7C00;
		pdea >>= 10;
		int pde = MEM[PDT][pdea];
		int pfn = pde & 0x7F;
		sign = pde >> 7;
		printf("\t\t--> pde index:0X%x  pde contents:(valid %d, pfn 0X%x)\n",pdea,sign,pfn);
		if(!sign){
			printf("\t\t\t--> Fault (page directory entry not valid)\n\n");
			continue;
		}
		else{
			int ptea = va & 0x3E0;
			ptea >>= 5;
			int pte = MEM[pfn][ptea];
			pfn = pte &0x7F;
			sign = pte >> 7;
			printf("\t\t\t--> pte index:0X%x  pte contents:(valid %d, pfn 0X%x)\n",ptea,sign,pfn);
			if(!sign){
				printf("\t\t\t\t--> Fault (page table entry not valid)\n\n");
			}
			else{
				int add = va &0x1F;
				int data = MEM[pfn][add];
				int phyadd = (pfn << 5) + add;
				printf("\t\t\t\t--> Translates to Physical Address 0X%x --> Value: %d\n\n", phyadd,data);
			}
		}



	} 
	return 0;
}