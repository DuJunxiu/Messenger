
// https://dev.mysql.com/doc/dev/mysql-server/latest/mysql_8h_source.html

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

    int open(const std::string& strHost, const std::string& strUser, const std::string& strPassword, const std::string& strDBName);

    int close();

    int excute(const std::string& strSql);

private:
    MYSQL* m_pstMysql;      // 
    MYSQL_RES* m_pstResult; // 结果集

};

#endif
