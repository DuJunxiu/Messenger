
#include "DBOperate.hpp"

int CDBOperate::initialize()
{
    m_pstMysql = mysql_init(nullptr);
    if (nullptr == m_pstMysql)
    {
        TRACELOG("initialize DB failed !\n");
        return -1;
    }

    return 0;
}

int CDBOperate::open(const std::string& strHost, const std::string& strUser, const std::string& strPassword, const std::string& strDBName)
{
    // 数据库连接
    m_pstMysql = mysql_real_connect(m_pstMysql, strHost.c_str(), strUser.c_str(), strPassword.c_str(), strDBName.c_str(), 0, nullptr, 0);
    if (nullptr == m_pstMysql)
    {
        TRACELOG("connect to DB failed !\n");
        return -1;
    }

    return 0;
}

int CDBOperate::close()
{
    if (nullptr != m_pstMysql)
    {
        mysql_close(m_pstMysql);
        m_pstMysql = nullptr;
    }

    return 0;
}

int CDBOperate::execute(const std::string& strSql)
{
    if (strSql.size() <= 0)
    {
        TRACELOG("execute error, strSql size error !\n");
        return -1;
    }

    if (nullptr == m_pstMysql)
    {
        TRACELOG("execute error, m_pstMysql is nullptr !\n");
        return -1;
    }

    // 执行语句前结果集不为空的话，先释放
    if (nullptr != m_pstResult)
    {
        mysql_free_result(m_pstResult);
        m_pstResult = nullptr;
    }

    // 执行语句失败
    if (0 != mysql_query(m_pstMysql, strSql.c_str()))
    {
        TRACELOG("execute [%s] failed\n", strSql.c_str());
        return -1;
    }

    // 执行结果
    m_pstResult = mysql_use_result(m_pstMysql);

    MYSQL_ROW stRow;
    // mysql_field_count() 返回查询结果的列数
    for (int i = 0; i < mysql_field_count(m_pstMysql); ++i)
    {
        // mysql_fetch_row() 返回下一行的二级指针, 可以理解为一个二维数组
        stRow = mysql_fetch_row(m_pstResult);
        if (nullptr == stRow)
        {
            break;
        }

        // mysql_num_fields() 返回结果集中的字段数
        for (int j = 0; j < mysql_num_fields(m_pstResult); ++j)
        {
            // TODO...
        }
    }

    // 每次操作完需要释放
    mysql_free_result(m_pstResult);

    return 0;
}

