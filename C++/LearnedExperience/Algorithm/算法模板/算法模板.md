# 0 前言

> 该文档于2023/11/6日建立，用于记录学习中常用的算法，便于日后复习，
> 资料收集大部分来自网络及书本

# 0.1程序速率优化

见文章，[卡常技巧,速率优化](https://zhuanlan.zhihu.com/p/608989466#:~:text=)

#  1基础知识



## 0.1 小tips

> 1.使用遍历去重时，`nums[i] == nums[i+1]`是将下标移动到同一块相同区间的最有边，`nums[i] == nums[i - 1]`是将下标移动到每个不同重复数区间的开头，若可能需要用到重复数时，让其停留在左边
>
> 2.如果使用for循环遍历，需要对循环数进行操作，如果只++，则continue，不要++操作，否则会加两次，，如果进行其他复杂操作，可以使用while来循环。
>
> 3.使用string s；容器时，不要使用`s = (char)a + s;`这种操作，使用`s += (char)a;`



## 1 快速排序

> 快速排序用于对一段区间的数按某个指标大小进行排序，不稳定排序
> 在遇到需要排序的题目时，一般排序作为一个中间步骤，快速排序是使用较为广泛的一种排序
>
> 时：均值$O(nlogn)$   空：$O(logn)$
>
> 在算法题中常用标准库中函数来进行排序 [std::sort ](https://www.apiref.com/cpp-zh/cpp/algorithm/sort.html)

> 原理：
>
> 使用了分治的思想，取一个值，将区间按该值分为两段小区间，在两段小区间中重复该步骤，区间长度为1时停止
>
> 1. 确定分界点
> 2. 调整区间
> 3. 递归处理左右区间
>
> ```c++
> void quick_sort(int q[], int l, int r){
>     if(l>=r) return;
>     
>     int x=q[l], i=l-1, j=r+1;  //取分界值,注意分界值不能取r，i,j有偏移量
>     while(i < j){
>         do i++ ; while (q[i] < x);   //偏移量作用，同时找到i，j该交换的位置
>         do j-- ; while (q[j] > x);
>         
>         if(i < j) swap(q[i],q[j]);  //由于do~while，会先执行一步加减，需要判断
>     }
>     
>     quick_sort(q,l,j);    //递归左右区间
>     quick_sort(q,j+1,r);
> }
> ```
>
> 快速排序中边界问题较为繁琐，可以参考[快速排序中的边界问题](https://blog.csdn.net/SHU15121856/article/details/109839618)

## 2 归并排序

> 与快速排序不同的是，归并排序是先排序，后合并，属于稳定排序。适用于将两个排好序的区间合并的题，
> 参考标准库使用方法  [std::merge](https://zh.cppreference.com/w/cpp/algorithm/merge)
>
> 1. 确定分界点
> 2. 递归排序
> 3. 合二为一
>
> 时：$O(nlogn)$  空：$O(n+logn)$额外数组+压入栈所需空间
>
> ```C++
> void merge_sort(int q[], int l, int r)
> {
>     if (l >= r) return;
> 
>     int mid = l + r >> 1;
>     merge_sort(q, l, mid);
>     merge_sort(q, mid + 1, r);
> 
>     int k = 0, i = l, j = mid + 1;
>     while (i <= mid && j <= r)
>         if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
>         else tmp[k ++ ] = q[j ++ ];
> 
>     while (i <= mid) tmp[k ++ ] = q[i ++ ];
>     while (j <= r) tmp[k ++ ] = q[j ++ ];
> 
>     for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
> }
> 
> ```
>
> 

## 3 二分

> 根据某种性质，可以将某个区间一分为二，二分可以用于寻找该性质的边界点
>
> 注意：单调，二分不仅仅用于找某个值，还可以用于寻找性质边界



### 01 整数二分

> ```C++
> //在全局中有一个数组，传入的是下标
> 
> bool check(int x) {/* ... */} // 检查x是否满足某种性质
> 
> //*****************************************************************************
> //此版本[)，寻找的是左边界
> int bsearch_1(int l, int r)
> {
> while (l < r)
> {
> int mid = l + r >> 1;
> if (check(mid)) r = mid;    // check()判断mid是否满足性质
> else l = mid + 1;
> }
> return l;
> }
> 
> 
> 
> int bsearch_2(int l, int r)
> {
> while (l < r)
> {
> int mid = l + r + 1 >> 1;
> if (check(mid)) l = mid;
> else r = mid - 1;
> }
> return l;
> }
> 
> 
> //容易理解版本
> int binary_search3(vector<int>& nums, int target) {
> //定义区间为左闭右闭
> int left = 0, right = nums.size() - 1;
> 
> while (left <= right) {   //等于有意义
>   int middle = left + ((right - left) >> 1);  //防止变量内存溢出
>   if (nums[middle] > target)              //移动右边界
>       right = middle - 1;
>   else if (nums[middle] < target)          //移动左边界
>       left = middle + 1;
>   else if(nums[middle] == target)   
>       return middle;			//找到目标返回
> }
> 
> return -1; //找不到则返回-1；
> }
> 
> ```

#### 二分边界

> 二分法在存在重复元素时，可以用于寻找元素边界
>
> + 某段的边界，如最小符合，最大符合等
>
> ​			若发现目标时不立即退出，最后都会出现 `left = right + 1` 的情况，即right在left左边一单位
> ​	同时，在寻找左边界时，相同移动right，结束时，若目标存在，则left指向第一个元素，若目标不存在则left指向待插入位置。
> ​		在寻找右边界时，相同移动left，结束时，若目标存在，则right = left -1 指向未元素。若目标不存在，则不论移动左右，left最后均处于待插入的地方。
> ​			注意，左右边界的移动，可能使得下标越界，在访问之前进行处理。比如首尾元素需要插入，用二分法确定插入位置时，right为-1 / left下标为size（） 		
>
> ```c++
> //单独寻找左右边界
> int binary_searchL(vector<int>& nums, int target){
>     int left = 0, right = nums.size() - 1;
> 
>     while(left <= right){
>         int middle = left + ((right - left) >> 1);
>         if(nums[middle] >= target) right = middle -1; //右边界将=号删除，最后返回right
>         else left = middle + 1;
>     }
>     return left;    //left可能是首元素，可能是插入位置，根据需要进行更改
> }
> 
> 
> ```
>
> 

### 02 浮点数二分

> ```C++
> bool check(double x) {/* ... */} // 检查x是否满足某种性质
> 
> double bsearch_3(double l, double r)
> {
>     const double eps = 1e-6;   // eps 表示精度，取决于题目对精度的要求
>     while (r - l > eps)
>     {
>         double mid = (l + r) / 2;
>         if (check(mid)) r = mid;
>         else l = mid;
>     }
>     return l;
> }
> ```
>
> 

## 4 递推与递归

> 相关参考资料
>
> + [递推与递归的关系](https://www.zhoulujun.cn/html/theory/engineering/model/7307.html)



## 5 高精度

## 6 前缀和与差分

> 滑动窗口

```c++
int minLen(array v,int target){
int l=0,r=0;
int n =v.size();

int len=999999;
int sum = 0;
while(r<v){
    sum+=v[r];
    while(sum >= target){
        len=r-l+1<target?r-l+1:target;
        sum-=v[l];
	   l++;
    }
    r++;
}

return len==99999?0:len;
```
}

## 7 双指针算法

> 双指针算法，快慢指针算法，通过同时维护两个指向数据的变量，来进行一些操作
>
> + 在遍历的时候对自身进行一些操作

### 常见问题

> 代码方式带来的问题，使用while循环去寻找目标元素，可能会出现：在正常结束前，因为慢指针快于快指针而导致结束
>
> ```c++
> int minLen(array v,int target){
>     int l=0,r=0;
>     int n =v.size();
>     
>     int len=999999;
>     int sum = 0;
>     while(r<v){
>         sum+=v[r];
>         while(sum >= target){
>             len=r-l+1<target?r-l+1:target;
> 		   l++;
>         }
>         r++;
>     }
>     
>     return len==99999?0:len;
> }
> ```
>
> 

## 8 位运算

## 9 离散化

## 10 RMQ



# 2 搜索







