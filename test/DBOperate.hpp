
#ifndef __DB_OPERATE_HPP__
#define __DB_OPERATE_HPP__

#include <mysql/mysql.h>
#include <string>

class CDBOperate
{
public:
    CDBOperate() {};
    ~CDBOperate() {};

public:
    int initialize()
    {
        m_pstMysql = mysql_init(NULL);
        if (NULL == m_pstMysql)
        {
            printf("initialize DB failed !\n");
            return -1;
        }

        printf("initialize OK !\n");

        return 0;
    }

    int open(const std::string& strHost, const std::string& strUser, const std::string& strPassword, const std::string& strDBName)
    {
        // 数据库连接
        m_pstMysql = mysql_real_connect(m_pstMysql, strHost.c_str(), strUser.c_str(), strPassword.c_str(), strDBName.c_str(), 0, NULL, 0);
        if (NULL == m_pstMysql)
        {
            printf("connect to DB failed !\n");
            return -1;
        }

        printf("connect open OK !\n");

        return 0;
    }

    int close()
    {
        if (NULL != m_pstMysql)
        {
            mysql_close(m_pstMysql);
            m_pstMysql = NULL;
        }

        printf("connect close OK !\n");

        return 0;
    }

    int excute(const std::string& strSql, char cType = 0)
    {
        if (strSql.size() <= 0)
        {
            printf("excute error, strSql size error !\n");
            return -1;
        }

        if (NULL == m_pstMysql)
        {
            printf("excute error, m_pstMysql is NULL !\n");
            return -1;
        }

        // 执行语句前结果集不为空的话，先释放
        if (NULL != m_pstResult)
        {
            mysql_free_result(m_pstResult);
            m_pstResult = NULL;
        }

        printf("start excute [%s]\n", strSql.c_str());

        // 执行语句失败
        if (0 != mysql_query(m_pstMysql, strSql.c_str()))
        {
            printf("excute [%s] failed\n", strSql.c_str());
            return -1;
        }

        // 默认 0 为查询
        if (0 == cType)
        {
            // 执行结果
            m_pstResult = mysql_use_result(m_pstMysql);

            printf("excute result :\n");

            MYSQL_ROW stRow;
            // mysql_field_count() 返回查询结果的列数
            for (int i = 0; i < mysql_field_count(m_pstMysql); ++i)
            {
                // mysql_fetch_row() 返回下一行的二级指针, 可以理解为一个二维数组
                stRow = mysql_fetch_row(m_pstResult);
                if (NULL == stRow)
                {
                    break;
                }

                // mysql_num_fields() 返回结果集中的字段数
                for (int j = 0; j < mysql_num_fields(m_pstResult); ++j)
                {
                    printf(" [%s] ", stRow[j]);
                }

                printf("\n");
            }

            // 每次操作完需要释放
            mysql_free_result(m_pstResult);
        }

        printf("excute OK !\n");

        return 0;
    }

private:
    MYSQL* m_pstMysql;      // 
    MYSQL_RES* m_pstResult; // 结果集

};

#endif
