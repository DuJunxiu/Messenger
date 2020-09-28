
#ifndef __DB_OPERATE_HPP__
#define __DB_OPERATE_HPP__

#include <mysql/mysql.h>

#include "LogDeal.hpp"

using namespace MyMessenger;

class CDBOperate
{
public:
    CDBOperate() {};
    ~CDBOperate() {};

public:
    int initialize();

private:
    MYSQL* m_pstMysql;

};

#endif
