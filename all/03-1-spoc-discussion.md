# lec5 SPOC思考题


NOTICE
- 有"w3l1"标记的题是助教要提交到学堂在线上的。
- 有"w3l1"和"spoc"标记的题是要求拿清华学分的同学要在实体课上完成，并按时提交到学生对应的git repo上。
- 有"hard"标记的题有一定难度，鼓励实现。
- 有"easy"标记的题很容易实现，鼓励实现。
- 有"midd"标记的题是一般水平，鼓励实现。


## 个人思考题
---

请简要分析最优匹配，最差匹配，最先匹配，buddy systemm分配算法的优势和劣势，并尝试提出一种更有效的连续内存分配算法 (w3l1)
```
  + 采分点：说明四种算法的优点和缺点
  - 答案没有涉及如下3点；（0分）
  - 正确描述了二种分配算法的优势和劣势（1分）
  - 正确描述了四种分配算法的优势和劣势（2分）
  - 除上述两点外，进一步描述了一种更有效的分配算法（3分）
 ```
- [x]  

>  
		最先匹配：
			优点：简单，在高地址上有大块的空闲分区。
			缺点：产生外部碎片，分配大块比较慢。
		最优匹配：
			优点：大部分匹配尺寸较小的时候，效果很好；相对简单；可见小外部碎片的大小。
			缺点：产生外部碎片；释放分区比较慢；容易产生很多无用小碎片。
		最差匹配：
			优点：中等大小的分配较多的时候，效果最好；避免出现太多的小碎片。
			缺点：释放分区较慢；外部碎片；容易破坏最大的空闲分区。
		buddy system:
			优点：释放分区的时候合并算法较快；分配的时候由于分配策略将整个选定块分出去了，留下的空间比较整齐，在搜索的时候比较快。
			缺点：利用率相对小。
		slac分配算法，随机分配。
## 小组思考题

请参考ucore lab2代码，采用`struct pmm_manager` 根据你的`学号 mod 4`的结果值，选择四种（0:最优匹配，1:最差匹配，2:最先匹配，3:buddy system）分配算法中的一种或多种，在应用程序层面(可以 用python,ruby,C++，C，LISP等高语言)来实现，给出你的设思路，并给出测试用例。 (spoc)

		说明：2012080059 mod 4 = 3；buddy system
		数据储存在bdlist用二维向量储存，其中第一个坐标代表空闲空间大小（用2的指数表示），第二则是顺序排放的vector。
		测试用例使用的是老师课件上的示例结果在代码下面粘贴出来。（为了方便阅读31hw.cpp是代码result.txt是结果）
		
		
		代码：
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

		用例结果：
		After ini:
			20:
				start:0=0K size:20
		After Request 100K:
		A got memory starting at 0K with the size of 2**17
			17:
				start:131072=128K size:17
			18:
				start:262144=256K size:18
			19:
				start:524288=512K size:19
		After Request 240K:
		B got memory starting at 256K with the size of 2**18
			17:
				start:131072=128K size:17
			19:
				start:524288=512K size:19
		After Request 64K:
		C got memory starting at 128K with the size of 2**16
			16:
				start:196608=192K size:16
			19:
				start:524288=512K size:19
		After Request 256K:
		D got memory starting at 512K with the size of 2**18
			16:
				start:196608=192K size:16
			18:
				start:786432=768K size:18
		insert2
		After FRee B:
			16:
				start:196608=192K size:16
			18:
				start:262144=256K size:18
				start:786432=768K size:18
		insert1
		After Free A
			16:
				start:196608=192K size:16
			17:
				start:0=0K size:17
			18:
				start:262144=256K size:18
				start:786432=768K size:18
		After Request 75K:
		E got memory starting at 0K with the size of 2**17
			16:
				start:196608=192K size:16
			18:
				start:262144=256K size:18
				start:786432=768K size:18
		insert1
		After FRee C:
			17:
				start:131072=128K size:17
			18:
				start:262144=256K size:18
				start:786432=768K size:18
		insert1
		After Free E
			18:
				start:786432=768K size:18
			19:
				start:0=0K size:19
		insert1
		After Free D
			20:
				start:0=0K size:20
--- 
如何表示空闲块？ 如何表示空闲块列表？ 
[(start0, size0),(start1,size1)...]
在一次malloc后，如果根据某种顺序查找符合malloc要求的空闲块？如何把一个空闲块改变成另外一个空闲块，或消除这个空闲块？如何更新空闲块列表？
在一次free后，如何把已使用块转变成空闲块，并按照某种顺序（起始地址，块大小）插入到空闲块列表中？考虑需要合并相邻空闲块，形成更大的空闲块？
如果考虑地址对齐（比如按照4字节对齐），应该如何设计？
如果考虑空闲/使用块列表组织中有部分元数据，比如表示链接信息，如何给malloc返回有效可用的空闲块地址而不破坏
元数据信息？
伙伴分配器的一个极简实现
http://coolshell.cn/tag/buddy
```

--- 

## 扩展思考题

阅读[slab分配算法](http://en.wikipedia.org/wiki/Slab_allocation)，尝试在应用程序中实现slab分配算法，给出设计方案和测试用例。

## “连续内存分配”与视频相关的课堂练习

### 5.1 计算机体系结构和内存层次
MMU的工作机理？

- [x]  

>  http://en.wikipedia.org/wiki/Memory_management_unit

L1和L2高速缓存有什么区别？

- [x]  

>  http://superuser.com/questions/196143/where-exactly-l1-l2-and-l3-caches-located-in-computer
>  Where exactly L1, L2 and L3 Caches located in computer?

>  http://en.wikipedia.org/wiki/CPU_cache
>  CPU cache

### 5.2 地址空间和地址生成
编译、链接和加载的过程了解？

- [x]  

>  

动态链接如何使用？

- [x]  

>  


### 5.3 连续内存分配
什么是内碎片、外碎片？

- [x]  

>  

为什么最先匹配会越用越慢？

- [x]  

>  

为什么最差匹配会的外碎片少？

- [x]  

>  

在几种算法中分区释放后的合并处理如何做？

- [x]  

>  

### 5.4 碎片整理
一个处于等待状态的进程被对换到外存（对换等待状态）后，等待事件出现了。操作系统需要如何响应？

- [x]  

>  

### 5.5 伙伴系统
伙伴系统的空闲块如何组织？

- [x]  

>  

伙伴系统的内存分配流程？

- [x]  

>  

伙伴系统的内存回收流程？

- [x]  

>  

struct list_entry是如何把数据元素组织成链表的？

- [x]  

>  



