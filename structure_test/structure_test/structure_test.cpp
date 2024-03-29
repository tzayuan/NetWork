/*
Function:
	结构体概念相关剖析及测试.

编译环境:
	x86, C++11;
	C声明       32位机器（X86）     64位机器（X64）
    char              1                 1
    short int         2                 2
    int               4                 4
    long int          4                 8
    long long int     8                 8
    char *            4                 8
	float             4                 4
	double            8                 8
	(Reference:https://www.cnblogs.com/ryzz/p/9418171.html)
  【Addition】
	1)指针类型变量的大小只取决于计算机系统的位数,它的大小也等于该计算机系统的int类型大小,即该计算机系统“字”的大小;【见Example 0.0 ~ Example 0.3】
		  (这里的int实质上是指上面表格中的long int,因为C语言为了保持跨平台的统一,所以char, short int, int, long long int规定采用固定位数, 不随系统位数变化而变化, 但long int类型由系统位数决定)
	2)32位系统下的long long int(64位数据类型)的操作是编译器通过一系列位运算完成的.

Reference:
	1)结构体深度剖析（内存对齐，对齐参数，偏移量）, https://blog.csdn.net/dai_wen/article/details/78304568；
	2)初学者对于结构体内存对齐与补齐的理解, https://blog.csdn.net/Apollon_krj/article/details/51302859;
	3)结构体大小计算（内存对齐问题和修改默认对齐数）, https://blog.csdn.net/QLH04_04/article/details/84194919;
	4)结构体对齐问题, https://blog.csdn.net/sevanco/article/details/68921148;
	5)C语言结构体对齐与不对齐设置总结, https://blog.csdn.net/gll028/article/details/39896353;
	6)C语言字节对齐、结构体对齐最详细的解释, https://blog.csdn.net/lanzhihui_10086/article/details/44353381 【未读完】;

Summary:
	1)Q.什么是结构体？
		A.结构体是一系列数据的集合所定义而成的,用以集中描述一个物体的一系列给定属性或对一个问题的参数的抽象的数据类型.如对于定义一个个体"人"时,无法用简单的数据类型int、char等来定义,此时借助于结构体,可定义如下:
			struct people {
				char name[20];
				int age;
				char gender[];
				float height;
			};
	2)Q.一般什么情况下用到结构体?
		A.1)当编译语言内置数据类型无法满足用户编程及功能实现需求,没有合适的数据类型以对应对象时,需要封装特定的结构体类型;
		  2)当函数有多个参数需要返回时,将所需要参数打包为结构体,通过返回结构体数据类型打包返回多个特定数据类型的参数;
	3)Q.什么是结构体内存对齐/补齐?为什么要设置对齐/补齐?怎样对齐/补齐?
		A.一般的,结构体中存放的是不同数据类型的混合数据, 比如结构体成员列表可为数组, 指针, 整型, 字符型, 浮点型等组合,
		  而这些不同数据类型的元素是按照定义顺序一个一个放到内存中去的, 但并不是亲密排列, 需满足对齐原则与补齐原则. 
		  在大多数计算机体系结构中, 对内存操作时按整字存取才能达到最高效率,因此总体来说结构体的内存对齐是拿空间来换取时间的做法;
		    对齐原则:从为结构体分配的首地址开始,结构体中出现的每个元素放置到内存中时,它都会认为内存是按照自己的大小来划分的,因此元素放置的位置一定会在自己宽度的整数倍上开始.
		      x86/32位平台下,int占4Bytes,char占1Byte,double占8Bytes.
		      如下面【Example 1.0】, st1结构体中,按照平台定义及对齐原则:
			    int a从0偏移开始,占4Bytes(即偏移0、偏移1、偏移2、偏移3),现可用偏移为4;
			    接下来顺序出现的是char b,由于4是1的倍数,因而char b占用1Byte(即偏移4),现可用偏移为5;
			    接下来顺序出现的是double c,可用偏移5、6、7均不是8的倍数,直至8为8的倍数,因而double c占用8Bytes(即偏移8 ~ 偏移15),现可用偏移为16;
			    最后顺序出现的是char d,可用偏移16是1的倍数,因而char d占用1Byte(即偏移16),现处于偏移17.
		      此时完成对齐原则分析后,牵扯到一个补齐原则:检查计算出的存储单元是否为所有元素中所占内存最大的元素的长度的整数倍,若是,则结束;若不是,则补齐为它的整数倍.
			    根据此原则,此处min(默认对齐参数,类型最大字节数,此处即为double,占用8Bytes) = 8Bytes,因为偏移17不是8的倍数,所以继续偏移,偏移18~23均不是8的倍数,直至偏移24处时,24是8的倍数,因而该结构体大小为24Bytes.
	4)Q.对齐参数如何设置?可以设置为按照任意字节数对齐吗?
		A.在某些计算机体系结构中,比如ARM是支持非对齐字传输的,也就是说变量并不一定要按照字长对齐,尽管这样可能会降低效率,但换来的是存储空间上的节约;
		  对于程序员来讲,则需要将结构体声明为紧凑型结构体.声明的关键字,如使用#pragma pack(1)////设置默认对齐数为1以达到最紧凑状态,即最省存储空间的做法.
		  在设置结构体时，我们既要满足对齐, 又要节省空间, 只能让占用空间小的成员尽量集中在一起。那么结构体在对齐方式不合理时我们可以修改默认对齐数.
			在Windows中,VS编译器下,默认对齐数为1个字节对齐, 即为8的倍数;
		    在Linux中，默认对齐数为4;
		    (默认参数只能设置成1, 2, 4, 8, 16, 即内置数据类型已有的字节数);
		    设置对齐参数可在结构体struct之前加上#pragma pack(对齐数)，在struct之后加上#pragma pack; 便可以设置对齐参数.【见Example 2.0】
			用来对齐的,包括栈对齐,变量地址对齐内存分配对齐的几种方式如下：
				#pragma pack(n)
					n的取值可以为1、2、4、8、16, 在编译过程中按照n个字结对齐
				#pragma pack()
					取消对齐, 按照编译器的优化对齐方式对齐
				__attribute__ ((packed));
					是说取消结构在编译过程中的优化对齐
				__attribute__ ((aligned (n)));
					让所作用的成员对齐在n字节自然边界上, 如果结构中有成员的长度大于n, 则按照最大成员的长度来对齐
		【Addition】在C语言中也可以通过设置位域来达到节省存储空间的目的,每个位域有一个域名，允许在程序中按域名进行操作,这样就可以把几个不同的对象用一个字节的二进制位域来表示.
					(Reference:https://bbs.csdn.net/topics/210072839 【未读完】)
	5)Q.如何知道结构体某个成员相对于结构体起始位置的偏移量?
		A.使用offsetof宏来判断结构体中成员的偏移地址.【见Example 2.1 ~ 2.2】
		    使用offsetof宏需要包含stddef.h头文件，该宏定义如下:
		      #define offsetof(type,menber) (size_t)&(((type*)0)->member)//该宏在Linux内核代码(版本2.6.22)中有定义
		    巧妙之处在于将地址0强制转换为type类型的指针, 从而定位到member在结构体中偏移位置, 编译器认为0是一个有效的地址, 从而认为0是type指针的起始地址.
			(Reference:
			  1)http://www.cplusplus.com/reference/cstddef/offsetof/;
			  2)https://www.iteye.com/blog/xiva-1176115;
			  3)https://blog.csdn.net/u014114046/article/details/52122693;
			  4)https://www.cnblogs.com/budapeng/p/5340514.html;
			  5)https://www.cnblogs.com/zhangfeionline/p/6212375.html.
			)
*/

#include "pch.h"
#include <iostream>
#include <stddef.h> //该头文件中包含 #define offsetof(type, menber) (size_t)&(((type*)0)->member)

//Example 0.0
struct a {
	int a;
}st00;
//Example 0.1
struct b {
	int *a;
}st01;
//Example 0.2
struct c {
	char *b;
}st02;
//Example 0.3
struct d {
	double *c;
}st03;
//----------------------------------------------------------
//Exmaple 1.0
struct A {
	int a;
	char b;
	double c;
	char d;
}st10;
//Example 1.1
struct B {
	char a;
	int b;
	char c;
}st11;
//Example 1.2
struct C {
	char a;
	double b;
}st12;
//Example 1.3
struct D {
	char a;
	char b;
	double c;
}st13;
//Example 1.4
struct E{
	char a;
	double b;
	char c;
}st14;
//----------------------------------------------------------
//Example 2.0
#pragma pack(4)////设置默认对齐数为4
struct A_Pack4{
	int a;
	char b;
	double c;
	char d;
}st10_Pack4;
#pragma pack()//取消设置的默认对齐数，还原为默认设置
//Example 2.1
struct A_offsetof_test {
	int a;
	char b;
	double c;
	char d;
};
//Example 2.2
int main()
{
	printf_s("The size of st00 is :%d\n", sizeof(st00));
	printf_s("The size of st01 is :%d\n", sizeof(st01));
	printf_s("The size of st02 is :%d\n", sizeof(st02));
	printf_s("The size of st03 is :%d\n", sizeof(st03));
	printf_s("\n");
	printf_s("The size of st10 is :%d\n", sizeof(st10));
	printf_s("The size of st11 is :%d\n", sizeof(st11));
	printf_s("The size of st12 is :%d\n", sizeof(st12));
	printf_s("The size of st13 is :%d\n", sizeof(st13));
	printf_s("The size of st14 is :%d\n", sizeof(st14));
	printf_s("\n");
	printf_s("The size of st10 is :%d\n", sizeof(st10));
	printf_s("The size of st10_Pack(4) is :%d\n", sizeof(st10_Pack4));
	printf_s("\n");
	printf_s("The size of struct A_Pack4->a is :%d\n", (int)offsetof(struct A_Pack4, a));
	printf_s("The size of struct A_Pack4->b is :%d\n", (int)offsetof(struct A_Pack4, b));
	printf_s("The size of struct A_Pack4->c is :%d\n", (int)offsetof(struct A_Pack4, c));
	printf_s("The size of struct A_Pack4->d is :%d\n", (int)offsetof(struct A_Pack4, d));
	printf_s("The size of struct A_Pack4 is :%d\n", sizeof(A_Pack4));
	printf_s("\n");
	printf_s("The size of A_offsetof_test->a is :%d\n", (int)offsetof(struct A_offsetof_test, a));
	printf_s("The size of A_offsetof_test->b is :%d\n", (int)offsetof(struct A_offsetof_test, b));
	printf_s("The size of A_offsetof_test->c is :%d\n", (int)offsetof(struct A_offsetof_test, c));
	printf_s("The size of A_offsetof_test->d is :%d\n", (int)offsetof(struct A_offsetof_test, d));
	printf_s("The size of A_offsetof_test is :%d\n", sizeof(A_offsetof_test));
	printf_s("\n");
}