#lec9 虚存置换算法spoc练习

## 个人思考题
1. 置换算法的功能？

2. 全局和局部置换算法的不同？

3. 最优算法、先进先出算法和LRU算法的思路？

4. 时钟置换算法的思路？

5. LFU算法的思路？

6. 什么是Belady现象？

7. 几种局部置换算法的相关性：什么地方是相似的？什么地方是不同的？为什么有这种相似或不同？

8. 什么是工作集？

9. 什么是常驻集？

10. 工作集算法的思路？

11. 缺页率算法的思路？

12. 什么是虚拟内存管理的抖动现象？

13. 操作系统负载控制的最佳状态是什么状态？

## 小组思考题目

----
(1)（spoc）请证明为何LRU算法不会出现belady现象
```
	基于栈分析."1":栈大的那个一定包含栈小的中所有元素.
	b(t)属于S(t),b(t)属于S'(t)时,b(t)在二者里面都提到栈顶,都是命中.
	b(t)不属于S(t),b(t)不属于S'(t),都是缺失.
	b(t)不属于S(t),b(t)属于S'(t),在S'(t)命中,S(t)缺失.
	只要证明"1".归纳假设应该可以证明.
	所以不会出现belady.
```

(2)（spoc）根据你的`学号 mod 4`的结果值，确定选择四种替换算法（0：LRU置换算法，1:改进的clock 页置换算法，2：工作集页置换算法，3：缺页率置换算法）中的一种来设计一个应用程序（可基于python, ruby, C, C++，LISP等）模拟实现，并给出测试。请参考如python代码或独自实现。
 - [页置换算法实现的参考实例](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab3/page-replacement-policy.py)
```
	WINDOW_SIZE = 2

	def main():
	    sequence = ['c', 'c', 'd', 'b', 'c', 'e', 'c', 'e', 'a', 'd']
	    pages = set(['a', 'd', 'e'])
	    last_fault = -1
	    page_trace = set()
	    print 'initial ==> ',
	    print pages
	    for i in range(len(sequence)):
		page = sequence[i]
		print 'visit',
		print page,
		if page not in pages:
		    if last_fault >= 0 and i - last_fault > WINDOW_SIZE:
		        new_pages = set()
		        for each in pages:
		            if each in page_trace:
		                new_pages.add(each)
		        pages = new_pages
		    last_fault = i
		    page_trace = set()
		    pages.add(page)
		page_trace.add(page)
		print '==> ',
		print pages


	if __name__ == '__main__':
	    main()
```
 
## 扩展思考题
（1）了解LIRS页置换算法的设计思路，尝试用高级语言实现其基本思路。此算法是江松博士（导师：张晓东博士）设计完成的，非常不错！

参考信息：

 - [LIRS conf paper](http://www.ece.eng.wayne.edu/~sjiang/pubs/papers/jiang02_LIRS.pdf)
 - [LIRS journal paper](http://www.ece.eng.wayne.edu/~sjiang/pubs/papers/jiang05_LIRS.pdf)
 - [LIRS-replacement ppt1](http://dragonstar.ict.ac.cn/course_09/XD_Zhang/(6)-LIRS-replacement.pdf)
 - [LIRS-replacement ppt2](http://www.ece.eng.wayne.edu/~sjiang/Projects/LIRS/sig02.ppt)
