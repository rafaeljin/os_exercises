#lec 3 SPOC Discussion

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
1. 比较UEFI和BIOS的区别。
		UEFI:Unified Extensible Firmware Interface
		BIOS:Basic Input/Output System
		UEFI是BIOS的继任者，是为了解决BIOS的众多缺点在90年代提出的一种新的方案，特点是，1，相对于BIOS固定的(如针对不同的结构的磁盘需要BIOS_MBT,GBR等)，UEFI为不同平台上提供统一的服务;2,比BIOS安全，可以抵御bootkit攻击;3，启动快。
 
2. 描述PXE的大致启动流程。
		1,客户端个人电脑开机后， 在 TCP/IP Bootrom 获得控制权之前先做自我测试。
		2,Bootprom 送出 BOOTP/DHCP 要求以取得 IP。
		3,如果服务器收到个人电脑所送出的要求， 就会送回 BOOTP/DHCP 回应，内容包括
		4,客户端的 IP 地址， 预设网关， 及开机映像文件。否则，服务器会忽略这个要求。
		5,Bootprom 由 TFTP 通讯协议从服务器下载开机映像文件。
		6,个人电脑通过这个开机映像文件开机， 这个开机文件可以只是单纯的开机程式也可
		以是操作系统。
		7,开机映像文件将包含 kernel loader 及压缩过的 kernel，此 kernel 将支持NTFS root
		系统。
		8,远程客户端根据下载的文件启动机器。
		来自：http://baike.baidu.com/link?url=ql_3Temm5OCSLuWz4ViLSypuInRTBiNJtKmMQu4_Lvbk09Mg56WP-6eFpAZu-AeLGBfW2wQMpBWZGbn0p996F_

## 3.2 系统启动流程
 1. 了解NTLDR的启动流程。
		NTLDR文件的是一个隐藏的，只读的系统文件，位置在系统盘的根目录，用来装载操作系统。
		一般情况系统的引导过程是这样的代码
		1、电源自检程序开始运行
		2、主引导记录被装入内存，并且程序开始执行
		3、活动分区的引导扇区被装入内存
		4、NTLDR从引导扇区被装入并初始化
		5、将处理器的实模式改为32位平滑内存模式
		6、NTLDR开始运行适当的小文件系统驱动程序。
		小文件系统驱动程序是建立在NTLDR内部的，它能读FAT或NTFS。
		7、NTLDR读boot.ini文件
		8、NTLDR装载所选操作系统
		如果windows NT/windows 2000/windows XP/windows server 2003这些操作系统被选择，NTLDR运行Ntdetect。
		对于其他的操作系统，NTLDR装载并运行Bootsect.dos然后向它传递控制。
		windows NT过程结束。
		9.Ntdetect搜索计算机硬件并将列表传送给NTLDR，以便将这些信息写进\\HKE Y_LOCAL_MACHINE\HARDWARE中。
		10.然后NTLDR装载Ntoskrnl.exe，Hal.dll和系统信息集合。
		11.Ntldr搜索系统信息集合，并装载设备驱动配置以便设备在启动时开始工作
		12.Ntldr把控制权交给Ntoskrnl.exe，这时,启动程序结束,装载阶段开始
		来源：http://baike.baidu.com/link?url=Z3cdq0gdN9oGLO3J4WteItXc0kMgiu-YesCfb6dycNOv0-i3Lcs_qaLE4hRzvJ5-pW1qyu9LSwyt2w5u5xSRaq

 1. 了解GRUB的启动流程。
		硬盘启动以后转向MBR，装载GRUB。GRUB再将控制权给实际操作系统。

1. 比较NTLDR和GRUB的功能有差异。
		NTLDR功能单一，不能启动其他系统；NTLDR的MBR仅仅是指向操作系统所在的分区中的扇区。
 1. 了解u-boot的功能。
		Universal Boot Loader，可以充当bootloader也可以通过特殊手段从PC机中下载到目标板中（下载模式）。

## 3.3 中断、异常和系统调用比较
 1. 举例说明Linux中有哪些中断，哪些异常？
		外设硬件请求中断，异常有page fault（页缺失），traps（陷阱），除0，溢出

 1. Linux的系统调用有哪些？大致的功能分类有哪些？  (w2l1)
		在http://syscalls.kernelgrok.com/上查到有300多个不同的系统调用，文件操作的有sys_fork,sys_read,sys_write,sys_open,sys_close,sys_create等；进程管理的有：sys_getpid（获得进程号）,sys_waitpid（等待进程）等，内存管理sys_mremap,sys_mmap,get_mempolicy等。
		系统调用在内核态执行，以保证用户程序不对内核操作，但开放接口，方便用户程序实现功能。
```
  + 采分点：说明了Linux的大致数量（上百个），说明了Linux系统调用的主要分类（文件操作，进程管理，内存管理等）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
 1. 以ucore lab8的answer为例，uCore的系统调用有哪些？大致的功能分类有哪些？(w2l1)
 lab8中syscall.c中有如下代码：
		[SYS_exit]              sys_exit,
		[SYS_fork]              sys_fork,
		[SYS_wait]              sys_wait,
		[SYS_exec]              sys_exec,
		[SYS_yield]             sys_yield,
		[SYS_kill]              sys_kill,
		[SYS_getpid]            sys_getpid,
		[SYS_putc]              sys_putc,
		[SYS_pgdir]             sys_pgdir,
		[SYS_gettime]           sys_gettime,
		[SYS_lab6_set_priority] sys_lab6_set_priority,
		[SYS_sleep]             sys_sleep,
		[SYS_open]              sys_open,
		[SYS_close]             sys_close,
		[SYS_read]              sys_read,
		[SYS_write]             sys_write,
		[SYS_seek]              sys_seek,
		[SYS_fstat]             sys_fstat,
		[SYS_fsync]             sys_fsync,
		[SYS_getcwd]            sys_getcwd,
		[SYS_getdirentry]       sys_getdirentry,
		[SYS_dup]               sys_dup,
		文件操作的有[SYS_write]，[SYS_read]，[SYS_close] ，[SYS_open] 等，进程管理的有[SYS_fork]，[SYS_getpid]，[SYS_wait]，[SYS_sleep]等，系统功能有 [SYS_gettime]，[SYS_fsync]，[SYS_getcwd]等。
 ```
  + 采分点：说明了ucore的大致数量（二十几个），说明了ucore系统调用的主要分类（文件操作，进程管理，内存管理等）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
## 3.4 linux系统调用分析
 1. 通过分析[lab1_ex0](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex0.md)了解Linux应用的系统调用编写和含义。(w2l1)
		objdump：linux下的反汇编命令，通过objdump -d(二进制) 文件名(编译生成的文件)可以得到程序的汇编代码,得到内容的首尾：
		Disassembly of section .init:
		00000000004003a8 <_init>:
		4003a8:	48 83 ec 08          	sub    $0x8,%rsp
		4003ac:	48 8b 05 45 0c 20 00 	mov    0x200c45(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>

			......
			......
		Disassembly of section .fini:

		0000000000400564 <_fini>:
		400564:	48 83 ec 08          	sub    $0x8,%rsp
		400568:	48 83 c4 08          	add    $0x8,%rsp
		40056c:	c3                   	retq   

		nm:list symbols from object files（从object文件中列出符号），如下：
		0000000000000002 a AF_INET
		......
		......
		0000000000000004 a SYS_write
		0000000000601060 D __TMC_END__

		file:检测文件属性，得到如下:
		ELF 64-bit LSB  executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=99b37bd56345b41dcc64b67810845f108cafdf8a, not stripped

		汇编文件的系统调用的含义：int $0x80代表通过interrupt启动syscall，%eax中存放所需要的系统调用（这里是sys_write）,%ebx中STDOUT表示文件描述符（标准输出），%ecx为字符串指针，%edx为buffer大小（12）。

 ```
  + 采分点：说明了objdump，nm，file的大致用途，说明了系统调用的具体含义
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 
 ```
 
 1. 通过调试[lab1_ex1](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex1.md)了解Linux应用的系统调用执行过程。(w2l1)
		 	strace的用途：strace常用来跟踪进程执行时的系统调用和所接收的信号，strace可以跟踪到一个进程产生的系统调用,包括参数，返回值，执行消耗的时间。strace必须由用户态转到核心态。
			more指令：file perusal filter for crt viewing，可以显示文件细节，其中：more /proc/interrupts可以看到有关进程中断的信息。
			系统调用的过程：
		strace结果：
		------ ----------- ----------- --------- --------- ----------------
		22.81    0.000052           7         8           mmap
		13.60    0.000031          16         2           open
		13.16    0.000030           8         4           mprotect
		12.28    0.000028           9         3         3 access
		9.21    0.000021          21         1           execve
		8.33    0.000019          19         1           munmap
		7.89    0.000018          18         1           brk
		5.26    0.000012          12         1           write
		3.51    0.000008           3         3           fstat
		1.75    0.000004           4         1           read
		1.32    0.000003           2         2           close
		0.88    0.000002           2         1           arch_prctl
		------ ----------- ----------- --------- --------- ----------------
		mmap为一个复杂的系统调用，用于内存管理，这里应该是分配内存；open之后保护mprotect保护内存映像；access访问文件，execve执行；之后mummap删除映像（释放内存），系统调用write写文件，fstat观察句柄状态（给硬件发中断，这里应该是给屏幕发送中断请求），arch_prctl为特殊命令。
		应用从打开后每次执行系统调用的时候等待操作结果；CPU通过中断和CPU沟通；操作系统每次执行系统调用的时候转换到内核态，调用结束返回用户态。

 ```
  + 采分点：说明了strace的大致用途，说明了系统调用的具体执行过程（包括应用，CPU硬件，操作系统的执行过程）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
## 3.5 ucore系统调用分析
 1. ucore的系统调用中参数传递代码分析。
 1. ucore的系统调用中返回结果的传递代码分析。
 1. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
 1. 以ucore lab8的answer为例，尝试修改并运行代码，分析ucore应用的系统调用执行过程。
 
## 3.6 请分析函数调用和系统调用的区别
 1. 请从代码编写和执行过程来说明。
   1. 说明`int`、`iret`、`call`和`ret`的指令准确功能
 
