
#ifndef __DB_OPERATE_HPP__
#define __DB_OPERATE_HPP__

#include <mysql/mysql.h>
#include <string>

#include "LogDeal.hpp"

using namespace MyMessenger;

class CDBOperate
{
public:
    CDBOperate() {};
    ~CDBOperate() {};

public:
    int initialize();

    int open(const string& strHost, const string& strUser, const string& strPassword, const string& strDBName);

    int close();

    int excute(const string& strSql, char cType = 0);

private:
    MYSQL* m_pstMysql;      // 
    MYSQL_RES* m_pstResult; // 结果集

};

#endif
