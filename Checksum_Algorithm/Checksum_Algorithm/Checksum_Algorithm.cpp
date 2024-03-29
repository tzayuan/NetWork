/*
Function:
	Simulation the Algorithm of CheckSum;
Reference:
	1)Lecture01差错检测技术-6.pdf;
	2)https://www.cnblogs.com/ne-liqian/p/9804214.html;
	3)https://blog.csdn.net/m0_37697335/article/details/83867199;
	4)http://www.aiuxian.com/article/p-632044.html;
	5)http://www.aiuxian.com/article/p-1603260.html;
	6)http://www.aiuxian.com/article/p-1407696.html;
	7)https://www.cnblogs.com/dpf-learn/p/6109012.html;
	8)https://www.runoob.com/cplusplus/cpp-inline-functions.html;
	9)https://www.runoob.com/w3cnote/cpp-inline-usage.html;
	10)http://c.biancheng.net/view/199.html;
*/

#include "pch.h"
#include <iostream>
#include <cstdio>

static inline uint16_t check_sum(const uint16_t *buffer, int size)
{
	unsigned long cksum = 0;

	//16位为单位数字相加
	while (size > 1) {
		cksum += *buffer++;
		size -= sizeof(uint16_t);
	}

	//长度奇数情况
	if (size)
		cksum += *((unsigned char *)buffer);

	//高位有进位，进位到低位，下面两行代码保证了高16位为0。
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);

	//最后取反
	return (uint16_t)(~cksum);
}