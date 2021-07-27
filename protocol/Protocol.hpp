
#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

/////////////////////////////////////////////////////////////////////
////////////////////////////// 宏定义 ///////////////////////////////
#define MAX_MSGID_COUNT                 255     // 最大主协议数量

#define LOGIN_STATUS_ONLINE             1       // 角色登录状态_在线
#define LOGIN_STATUS_OFFLINE            2       // 角色登录状态_离线
#define LOGIN_STATUS_STEALTH            3       // 角色登录状态_隐身
#define LOGIN_STATUS_BUSY               4       // 角色登录状态_忙碌

#define GROUP_STATUS_ACTIVE             1       // 群组状态_激活
#define GROUP_STATUS_BANNED             2       // 群组状态_封禁
#define GROUP_STATUS_DISSOLVE           3       // 群组状态_解散
         
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
////////////////////////////// 主协议 ///////////////////////////////
#define MSGID_LOGINSERVER_REQUEST       101     // 登录请求
#define MSGID_LOGINSERVER_RESPONSE      102     // 登录响应
#define MSGID_LOGINSERVER_NOTIFY        103     // 登录通知
#define MSGID_LOGINOUTSERVER_REQUEST    104     // 登出请求
#define MSGID_LOGINOUTSERVER_RESPONSE   105     // 登出响应
#define MSGID_LOGINOUTSERVER_NOTIFY     106     // 登出通知
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
////////////////////////////// 子协议 ///////////////////////////////

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//////////////////////////// 主协议结构 /////////////////////////////
typedef struct stMsgHead
{
    unsigned short m_usVersion;
    unsigned short m_usMsgID;
    unsigned char m_ucMsgType;
    unsigned int m_uiMsgLength;
} MsgHead;

typedef union stMsgBody
{
} MsgBody;

typedef struct stMainMsg
{
    MsgHead stMsgHead;
    MsgBody stMsgBody;
} MainMsg;
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//////////////////////////// 子协议结构 /////////////////////////////
typedef struct stOneGroupMsg
{
    int m_iUserID;
    char cMsgType;              // 1文字消息 2图片消息 3文件消息
    char* pszMsgInfo[1024];
} OneGroupMsg;

typedef struct stGroup
{
    unsigned short m_usMsgCount;
    OneGroupMsg m_stMsgList[1000];
} Group;
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//////////////////////////// 入库的结构 /////////////////////////////
typedef struct stDBFriendInfo
{
    int m_iUID;
} DBFriendInfo;

typedef struct stDBRoleInfo
{
    int m_iUsrerID;
    unsigned int m_uiCreateTime;            // 用户创建时间
    DBFriendInfo m_stFriendList;
} DBRoleInfo;

typedef struct stDBMemberInfo
{
} DBMemberInfo;

typedef struct stDBGroupInfo
{
    int m_iGroupID;
    int m_iManagerUID;
    unsigned char m_ucStatus;
    unsigned int m_uiCreateTime;            // 群创建时间
    unsigned int m_uiLastActiveTime;        // 最后活跃时间
    unsigned short m_usMemberCount;
    DBMemberInfo m_stOneMemberInfo[1000];
} DBGroupInfo;

typedef struct stDBGroupMsgList
{
    unsigned short m_usMemberCount;
    OneGroupMsg m_stOneMsgInfo[1000];
} DBGroupMsgList;
/////////////////////////////////////////////////////////////////////

#endif
