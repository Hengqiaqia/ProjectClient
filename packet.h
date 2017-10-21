#ifndef PACKET_H
#define PACKET_H

#define TYPE_REG             1
#define TYPE_LOGIN           2
#define TYPE_MSG             3
#define TYPE_REG_ERROR       4
#define TYPE_REG_SUCCESS     5
#define TYPE_LOGIN_ERROR     6
#define TYPE_LOGIN_SUCCESS   7
#define TYPE_DEL             9
#define TYPE_DEL_ERROR       10
#define TYPE_DEL_SUCCESS     11
#define TYPE_UPDATE          12
#define TYPE_UPDATE_ERROR    13
#define TYPE_UPDATE_SUCCESS  14
#define TYPE_SELALL          15
#define TYPE_SELALL_ERROR    16
#define TYPE_SELALL_SUCCESS  17
#define TYPE_SEL             18
#define TYPE_SEL_ERROR       19
#define TYPE_SEL_SUCCESS     20
#define TYPE_SEND_VER        21
#define TYPE_SEND_VERERROR   22
#define TYPE_SEND_VERSUCSS   23



typedef struct packet
{
    int type;
    char username[20];
    char nickname[512];
    char passwd[512];
    char phonenumber[20];
    char msg[1024];
    char alluser[1024];//查询所有的用户
}Packet;

#endif // PACKET_H
