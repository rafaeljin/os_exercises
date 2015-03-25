#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
unsigned int MEM[128][32];
unsigned int DISK[128][32];
int temp;
int main(){
	unsigned int PDBR = 0xd80;
	PDBR >>= 5;
	printf("%d\n",PDBR );
	FILE *ifs1 = freopen("mem.data","r",stdin);
	for (int i = 0; i < 128; i++){
		scanf("page %x:",&temp);
		printf("%d\n",temp );
		for(int j = 0; j < 32 ; j++){
			scanf("%x",&MEM[i][j]);
		}
		scanf("\n");
	}

	FILE *ifs2 = freopen("disk.data","r",stdin);
	for (int i = 0; i < 128; i++){
		scanf("disk %x:",&temp);
		printf("%d\n",temp );
		for(int j = 0; j < 32 ; j++){
			scanf("%x",&DISK[i][j]);
		}
		scanf("\n");
	}
	FILE *ifs3 = freopen("41inputdata.txt","r",stdin);
	FILE *ofs2 = freopen("41out.txt","w",stdout);
	for(int i=0;i<5;i++){
		scanf("%x",&temp);
		printf("\t\tVirtual Address 0x%04x:\n",temp);
		unsigned int pde = temp >> 10;
		unsigned int pde_ctt = MEM[PDBR][pde];
		unsigned int valid = pde_ctt >> 7;
		unsigned int pfn = pde_ctt & 0x7f;
		printf("\t\t\t--> pde index:0x%02x  pde contents:(0x%02x, valid %d, pfn 0x%02x)\n",pde,pde_ctt,valid,pfn );
		if(valid){
			unsigned int pte = temp & 0x3e0;
			pte >>= 5;
			unsigned int pte_ctt = MEM[pfn][pte];
			valid = pte_ctt >> 7;
			pfn = pte_ctt & 0x7f;
			printf("\t\t\t\t-->pte index:0x%02x  pte contents:(0x%02x, valid %d, pfn 0x%02x)\n",pte,pte_ctt,valid,pfn );
			if(valid){
				unsigned int offset = temp & 0x1f;
				unsigned int address = (pfn << 5) | offset;
				unsigned int value = MEM[pfn][offset];
				printf("\t\t\t\t\t--> To Physical Address 0x%x --> Value: 0x%02x\n", address,value); 
			}
			else{
				unsigned int offset = temp & 0x1f;
				unsigned int address = (pfn << 5) | offset;
				unsigned int value = DISK[pfn][offset];
				printf("\t\t\t\t\t--> To Disk Sector 0x%x --> Value: 0x%02x\n", address,value);
			}
		}
		else{
			printf("\t\t\t\t--> Fault (page directory entry not valid)\n");
		}
	}
	return 0;
}