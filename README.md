
# CS_106-B 作业

##  1. <a name='-0'></a>目录

<!-- vscode-markdown-toc -->
* 1. [目录](#-0)
* 2. [assign0](#assign0)
* 3. [assign1](#assign1)
	* 3.1. [第一部分 完全数](#-1)
	* 3.2. [第二部分 姓氏编码检索程序](#-2)
* 4. [assign2](#assign2)

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

###  3.2. <a name='-2'></a>第二部分 姓氏编码检索程序

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

##  4. <a name='assign2'></a>assign2

***1. Q1***

- 当 Stack 仅包含一个元素时，这两个标签将显示为“bottom/top”，如下图中变量区所示:

![assign2-Q1](./assign2/assign2-Q1.png)

***2. Q2***

- 这种情况是由于``duplicateNegatives()``函数中``for``循环的判断语句不当造成的，因为程序执行过程中如果队列顶部的元素是负数的情况下队列会增大，导致``for``循环不能及时停止，且当``duplicateNegatives()``函数的输入队列q中的所有元素都是负数的情况下是无限循环，只要队列``q``中含有正的元素，程序的终究会停止，并不是正真的无限循环，所以程序是否会陷入无限循环和队列中负值的位置的关系不大（当``q``中元素个数很小的情况下会受到位置的影响）。``duplicateNegatives``中的``for``循环下标``i``每循环1次都会递增1，每次循环中如果``q``顶部的元素是负数的情况下，``q.size()``才会递增1，``q``顶部的元素是正数的情况下，``q.size()``保持不变。这样每当``q``顶部的元素是正数的情况下，循环下标``i``与``q`.size()``的差距就会减小1，最终程序总会停止，并不是真的无限循环，只不过循环的时间长短和q中的负数元素与正数元素的个数相关，而且由于``q``顶部的元素是负数的情况下，``q``中负数元素的个数都会增加1个，导致``q``中负数的个数会逐渐翻倍，导致``q``顶部遇到的正元素所经过的时间会翻倍，循环下标``i``与``q.size()``的差距就会减小1所消耗的时间就会曾长。

***3. Q3***

- 因为程序执行过程中如果队列顶部的元素是负数的情况下队列会增大，所以专门用一个变量存储队列q最初所含元素的个数即可避免bug。修复bug后的测试截图如下：

![assign2-Q3](./assign2/assign2-Q3.png)

***4. Q4***

- ``sumStack``函数在``while``循环中已经对``s``是否为空进行了判断，所以没必要在函数最初对栈进行弹出操作，为不影响计算结果，直接将变量``total``初始化为0即可。

***5. Q5***

- 因为``validatePath``函数中需要对``path``进行遍历来判断路径中是符合移动规则，而``path``是个栈，除了``pop``没有其他方法可以对其进行遍历，而``pop``方法会修改``path``中的内容，如果使用引用方式传递参数的话会使得原始变量被修改，从而对后续的代码产生影响，``validatePath``函数的测试截图如下：

![assign2-Q5](./assign2/assign2-Q5.png)

***6. Q7***

- index的内容如下：

```
{
  "5lb_m&ms":{"www.shoppinglist.com"}, 
  "blue":{"www.dr.seuss.net", "www.rainbow.org"}, 
  "bread":{"www.shoppinglist.com"}, 
  "eat":{"www.bigbadwolf.com"}, 
  "fish":{"www.bigbadwolf.com", "www.dr.seuss.net", "www.shoppinglist.com"}, 
  "green":{"www.rainbow.org"}, 
  "i":{"www.bigbadwolf.com"}, 
  "milk":{"www.shoppinglist.com"}, 
  "one":{"www.dr.seuss.net"}, 
  "red":{"www.dr.seuss.net", "www.rainbow.org"}, 
  "two":{"www.dr.seuss.net"}
}
```

***7. maze测试及运行截图***

![maze](./assign2/maze.png)

***8. searchEngine运行截图***

![searchEngine](./assign2/searchEngine.png)