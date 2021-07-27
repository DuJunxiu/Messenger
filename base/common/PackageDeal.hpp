
#ifndef __PACKAGE_DEAL_HPP__
#define __PACKAGE_DEAL_HPP__

class CPackageDeal
{
public:
    CPackageDeal();
    ~CPackageDeal();

public:
    static int unpackMsg(const CConnector* pConn, const CBuffer* pBuffer, MainMsg& stMsg);
    static int packageMsg();

private:

};

#endif

