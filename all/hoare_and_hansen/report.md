文件中包括lab7中相关的2个文件：**monitor.c**和**check_sync.c**，以及lab7实验报告。
HOARE实现在lab7的实验报告中已详细说明，这里只表述HANSEN实现和HOARE的区别。

	#ifdef MY_HOARE
下是HOARE，

	#else
下是HANSEN。
**signal()**:这里在HANSEN中next不再需要，直接signal条件变量即可，放弃的mutex由管程出口为您成。这样保证了HANSEN执行顺序。

**wait()**:这里也不用再针对next进行处理，根据管程特点，放弃临界区的锁，然后等待条件变量。但由于放弃了mutex，在被条件变量唤醒以后不能直接执行，需要再等待mutex。
**管程出口**:不需要在判断next，直接放弃mutex即可。HOARE中判断next防止由于signal进行等待的线程无法获得mutex，这里不会出现。
