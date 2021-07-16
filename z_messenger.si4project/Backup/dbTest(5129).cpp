
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

    pstDBOperate->execute("insert into student_info values(\"20200102\", \"李梅\", 17, \"女\", 3, 499)", 1);

    pstDBOperate->execute("select * from student_info");

    pstDBOperate->close();

    delete pstDBOperate;

    return 0;
}

/*

运行结果：

initialize OK !
connect open OK !
start excute [insert into student_info values("20200102", "李梅", 17, "女", 3, 499)]
excute OK !
start excute [select * from student_info]
excute result :
 [20200101]  [张三]  [15]  [男]  [3]  [500] 
 [20200102]  [李梅]  [17]  [女]  [3]  [499] 
excute OK !
connect close OK !

*/


/*

问题1、致命错误：mysql/mysql.h：没有那个文件或目录
解决方法：依赖库未安装，sudo yum install mysql-deve

问题2、对‘mysql_init’未定义的引用
解决方法：编译时加上 -L/usr/lib64/mysql -lmysqlclient 选项（查看库文件位置 mysql_config --libs）

*/
