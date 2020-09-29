
#include "DBOperate.hpp"

int CDBOperate::initialize()
{
    m_pstMysql = mysql_init(NULL);
    if (NULL == m_pstMysql)
    {
        TRACELOG("initialize DB failed !\n");
        return -1;
    }

    return 0;
}

int CDBOperate::open(const string& strHost, const string& strUser, const string& strPassword, const string& strDBName)
{
    // 数据库连接
    m_pstMysql = mysql_real_connect(m_pstMysql.c_str(), strHost.c_str(), strUser.c_str(), strPassword.c_str(), strDBName.c_str(), 0, NULL, 0);
    if (NULL == m_pstMysql)
    {
        TRACELOG("connect to DB failed !\n");
        return -1;
    }

    return 0;
}

int CDBOperate::close()
{
    if (NULL != m_pstMysql)
    {
        mysql_close(m_pstMysql);
    }

    return 0;
}

int CDBOperate::excute(const string& strSql)
{
    if (strSql.size() <= 0)
    {
        TRACELOG("excute error, strSql size error !\n");
        return -1;
    }

    if (NULL == m_pstMysql)
    {
        TRACELOG("excute error, m_pstMysql is NULL !\n");
        return -1;
    }

    // 执行语句失败
    if (0 != mysql_query(m_pstMysql, strSql.c_str()))
    {
        TRACELOG("excute [%s] failed\n", strSql.c_str());
        return -1;
    }

    // 保存查询结果到 m_pstResult
    m_pstResult = mysql_use_result(m_pstMysql);

    // 每次操作完需要释放
    mysql_free_result(m_pstResult);

    return 0;
}

