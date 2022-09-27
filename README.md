
# CS106B 作业

##  1. <a name=''></a>目录

<!-- vscode-markdown-toc -->
* 1. [目录](#)
* 2. [assign0](#assign0)
* 3. [assign1](#assign1)
	* 3.1. [第一部分 完全数](#-1)
	* 3.2. [第二部分 姓氏编码检索程序](#-1)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

##  2. <a name='assign0'></a>assign0
***1. assign0-0***

- 包含名字的散列值结果：

![assign0-0](./assign0/assign0-0.png)

***2. assign0-1***
- 调试练习文档中的一个中间值结果：

![assign0-1](./assign0/assign0-1.png)

##  3. <a name='assign1'></a>assign1

###  3.1. <a name='-1'></a>第一部分 完全数

***1. Q1***

- 通过``<time.h>``库中的``time()``函数进行计时，得到程序的执行时间为10.0195秒，运行结果截图如下：

![assign1-Q1](./assign1/assign1-Q1.png)

- 1 到 40000 内共有 4 个完全数，分别是 6，28，496，8128。

***2. Q2***

- ``findPerfects()``的执行时间如下表所示：
  
  |搜索范围 |执行时间(s)|
  |---------|----------|
  |10000|0.645|
  |20000|2.479|
  |40000|9.949|
  |50000|15.431|
  |60000|22.006|
  |80000|39.119|
  |110000|73.753|

- ``findPerfects()``的测试截图如下

![assign1-Q2](./assign1/assign1-Q2.png)

- 根据数据量大小以及其执行时间，画出两者间的函数图像如下，可以看到执行时间与搜索数据量大小的平方近似成正比。

![assign1-Q2-plot](./assign1/assign1-Q2-plot.png)

***3. Q3***

- 对于 10 与 1000，计算 ``isPerfect``做的工作不是同样多的。如果n=10，则``isPerfect``中调用的``divisorSum(n)``中的for循环仅仅循环1次，如果n=1000，则``isPerfect``中调用的``divisorSum(n)``中的for循环会循环1000，n=1000的工作量更大。

- 对于搜索范围为 1-1000 的数，``findPerfect``调用的``divisorSum``中的for循环共循环$\frac{(1+1000)*1000}{2}=500500$次，搜索范围为1000-2000的数，``findPerfect``调用的``divisorSum``中的for循环共循环$\frac{(1000+2000)*10010}{2}=1501500$次，搜索范围为1000-2000的数时，``findPerfect``的工作量更大。

***4. Q4***

- 由于花费时间与完全数的平方成正比，第5个完全数是33550336，结合之前程序搜索110000以内的完全数需要73.753秒，所以``findPerfect``找出第5个完全数要花费的时间为
$\frac{33550336^2}{110000^2}*73.753=6.861*10^6 秒 = 79.410 天$。

***5. Q5***

- 这个函数测试失败时，部分测试能通过，部分测试不能通过。原先完全数成立的测试不能通过，而原先完全数不成立的测试依旧能通过测试。

- 测试通过结果如下图所示：

![assign1-Q5](./assign1/assign1-Q5.png)

***6. Q6***

- 测试策略: 首先对``divisorSum()``的已有的案例进行测试，之后针对``smarterSum()``添加新的特殊的案例，例如输入的n是某个数的平方。

***7. Q7***

  - ``findPerfectsSmarter``的执行时间如下表所示：

|搜索范围|执行时间(s)|
|--------|----------|
|375000|3.114|
|750000|8.599|
|1500000|24.080|
|3000000|67.649|

- ``findPerfectsSmarter``的测试结果截图如下：

![assign1-Q7](./assign1/assign1-Q7.png)

***8. Q8***

- 由于花费时间与$n\sqrt{n}$成正比关系，第5个完全数是33550336，结合之前程序搜索3000000以内的完全数需要67.649秒，所以ffindPerfectsSmarter找出第5个完全数要花费的时间为
$\frac{33550336*\sqrt{33550336}}{3000000*\sqrt{3000000}}*67.649=2156.032 秒= 35.934 分$。

***9. Q9***

- 通过``EXPEXT_EQUAL``测试方法判断``findNthPerfectEuclid()``返回的前5个完全数是否等于已有完全数表中对应的数值。

- ``findNthPerfectEuclid()``函数的测试截图如下：
  
![assign1-Q9](./assign1/assign1-Q9.png)

###  3.2. <a name='-1'></a>第二部分 姓氏编码检索程序

***10. Q10***

- "Angelou" 的编码是A524，编码计算过程如下:

Angelou -> 0520400 -> 052040 -> A52040 -> A524

***11. Q11***

- 分解为如下过程：
  1. 去除非字母字符;
  2. 进行编码;
  3. 去除相邻重复数字;
  4. 用首字母替换第一个数字;
  5. 删除0;
  6. 将编码格式化为4个字符。

***12. 添加测试暴露removeNonLetters()的bug***
- 添加一条测试案例，并暴露出函数``removeNonLetters``的 bug的截图：
  
![show_bug](./assign1/show_bug.png)


***13. 实现soundex()***

- 实现``soundex()``后的测试截图如下：

![soundex](./assign1/soundex.png)

***14. 实现soundexSearch()***

- 实现``soundexSearch()``后的运行结果截图如下：

![soundexSearch](./assign1/soundexSearch.png)
