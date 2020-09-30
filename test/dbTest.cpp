
#include <stdio.h>

#include "DBOperate.hpp"

int main()
{
	CDBOperate* pstDBOperate = new CDBOperate;
	if (NULL == pstDBOperate)
	{
		printf("new CDBOperate failed \n");
		return -1;
	}

	pstDBOperate->initialize();

	pstDBOperate->open("localhost", "root", "123456", "student");

	pstDBOperate->excute("insert into student_info values(\"20200102\", \"李梅\", 17, \"女\", 3, 499);");

	pstDBOperate->excute("select * from student_info;");

	pstDBOperate->close();

	delete pstDBOperate;

    return 0;
}
