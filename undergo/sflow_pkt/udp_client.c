#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <sys/socket.h>             /* socket(), bind(), listen(), ... */
#include <netinet/in.h>             /* AF_INET, AF_INET6 addr family and their corresponding protocol family PF_INET, PFINET6 */
#include <arpa/inet.h>              /* hton(), inet_ntop() */
#include <unistd.h>                 /* read(), write(), close() */


#define COLLECTOR_IP "127.0.0.1"
#define SFLOW_PORT   8000

#define SAMPLE_NUM 1


typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;

struct sflow_hdr_t {
    u32 version;
    u32 agent_addr_type;
    u32 agent_addr;
    u32 sub_agent_id;
    u32 seq_num;
    u32 sys_uptime;
    u32 sample_num;
};

struct sflow_sample_t {
    u32 sample_type;
    u32 sample_len;
    u32 seq_num;
    u32 idx;
    u32 sample_rate;
    u32 sample_pool;
    u32 dropped_pkt;
    u32 input_intf;
    u32 output_intf;
    u32 flow_record;
};

struct raw_pkt_hdr_t { 
    u32 format;
    u32 flow_data_len;
    u32 hdr_protocol;
    u32 frame_len;
    u32 payload_removed;
    u32 ori_pkt_len;
};

struct ipv4_hdr_t {
    u8 version: 4,
       hdr_len: 4;
    u8  dsf;
    u16 total_len;
    u16 id;
    u16 flag;
    u8  ttl;
    u8  protocol;
    u16 hdr_chksum;
    u32 src_ip;
    u32 dst_ip;
};

struct icmpv4_hdr_t {
    u8  type;
    u8  code;
    u16 chksum;
    u16 id;
    u16 seq_num;
};

struct sampled_pkt {
    // ethernet, len = 14
    u8 eth_hdr[14];

    // ipv4, len = 20
    
    // icmp, udp, ...
    
};

int make_sflow_hdr(u8 **msg) {

    struct sflow_hdr_t* sflow_hdr;
    sflow_hdr = (struct sflow_hdr_t*) calloc(1, sizeof(struct sflow_hdr_t));
    sflow_hdr->version = htonl(5);
    sflow_hdr->agent_addr_type = htonl(1);
    sflow_hdr->agent_addr = htonl(0xac152311);
    sflow_hdr->sub_agent_id = htonl(1);
    sflow_hdr->seq_num = htonl(0x01a2);
    sflow_hdr->sys_uptime = htonl(0x673e7f08);
    sflow_hdr->sample_num = htonl(SAMPLE_NUM);

    int ret_len = (int) sizeof(struct sflow_hdr_t);
    u8* ret = (u8*) calloc(1, ret_len);
    memcpy(ret, sflow_hdr, ret_len);

    *msg = ret;
    return ret_len;
}

int make_sflow_sample(u8 **msg, int raw_pkt_hdr_len) {

    struct sflow_sample_t* sflow_sample;
    sflow_sample = (struct sflow_sample_t*) calloc(1, sizeof(struct sflow_sample_t));
    sflow_sample->sample_type = htonl(1);
    sflow_sample->sample_len = htonl(raw_pkt_hdr_len+(int)sizeof(struct sflow_sample_t)-8);
    sflow_sample->seq_num = htonl(6);
    sflow_sample->idx = htonl(1043);
    sflow_sample->sample_rate = htonl(2048);
    sflow_sample->sample_pool = htonl(12288);
    sflow_sample->dropped_pkt = 0;
    sflow_sample->input_intf = htonl(1048);
    sflow_sample->output_intf = htonl(0x00000413);
    sflow_sample->flow_record = htonl(1);

    int ret_len = (int) sizeof(struct sflow_sample_t);
    u8* ret = (u8*) calloc(1, ret_len);
    memcpy(ret, sflow_sample, ret_len);

    *msg = ret;
    return ret_len;
}

int make_sampled_pkt(u8 **msg, int sampled_pkt_payload_len) {
    u8 eth_data[14] = { 0x00, 0x19, 0xb9, 0xdd, 0xb2, 0x64,
                        0x00, 0x1c, 0x23, 0x9f, 0x15, 0x0b,
                        0x81, 0x00 };
    
    struct ipv4_hdr_t* ipv4_hdr;
    ipv4_hdr = (struct ipv4_hdr_t*) calloc(1, sizeof(struct ipv4_hdr_t));
    ipv4_hdr->version = 0x4;
    ipv4_hdr->hdr_len = 0x5;
    ipv4_hdr->dsf = 0;
    ipv4_hdr->total_len = htons(20+sampled_pkt_payload_len);
    ipv4_hdr->id = htons(23559);
    ipv4_hdr->flag = 0;
    ipv4_hdr->ttl = 124;
    ipv4_hdr->protocol = 1;     // 1 for icmpv4
    ipv4_hdr->hdr_chksum = htons(0x9487);
    ipv4_hdr->src_ip = htonl(0xac1520fe);
    ipv4_hdr->dst_ip = htonl(0xac1520f1);


    struct icmpv4_hdr_t *icmpv4_hdr;
    icmpv4_hdr = (struct icmpv4_hdr_t*) calloc(1, sizeof(struct icmpv4_hdr_t));
    icmpv4_hdr->type = 8;
    icmpv4_hdr->code = 0;
    icmpv4_hdr->chksum = htons(0x9487);
    icmpv4_hdr->id = htons(0xa948);
    icmpv4_hdr->seq_num = htons(0x0cb2);

    u8 *ret;
    int ret_len = 0;
    ret = (u8*) malloc(14 + sizeof(struct ipv4_hdr_t) + sizeof(struct icmpv4_hdr_t));

    memcpy(ret, eth_data, 14);
    ret_len += 14;
    memcpy(ret+ret_len, (void*) ipv4_hdr, sizeof(struct ipv4_hdr_t));
    ret_len += sizeof(struct ipv4_hdr_t);
    memcpy(ret+ret_len, (void*) icmpv4_hdr, sizeof(struct icmpv4_hdr_t));
    ret_len += sizeof(struct icmpv4_hdr_t);

    *msg = ret;
    return ret_len;
}

int make_raw_pkt_hdr(u8 **msg, int sampled_pkt_len) {
    
    struct raw_pkt_hdr_t* raw_pkt_hdr;
    raw_pkt_hdr = (struct raw_pkt_hdr_t*) calloc(1, sizeof(struct raw_pkt_hdr_t));
    raw_pkt_hdr->format = htonl(1);
    raw_pkt_hdr->flow_data_len = htonl(sampled_pkt_len+(int)sizeof(struct raw_pkt_hdr_t)-8);
    raw_pkt_hdr->hdr_protocol = htonl(1);
    raw_pkt_hdr->frame_len = htonl(sampled_pkt_len);
    raw_pkt_hdr->payload_removed = htonl(0);
    raw_pkt_hdr->ori_pkt_len = htonl(sampled_pkt_len);
    
    int ret_len = (int) sizeof(struct raw_pkt_hdr_t);
    u8 *ret = (u8*) calloc(1, ret_len);
    memcpy(ret, raw_pkt_hdr, ret_len);
    
    *msg = ret;
    return ret_len;
}


int make_sflow_packet(u8 **msg) {

    int sampled_pkt_len = 0;
    u8 *sampled_pkt;
    int sampled_pkt_payload_len = 8;    // icmpv4 length
    sampled_pkt_len = make_sampled_pkt(&sampled_pkt, sampled_pkt_payload_len);
    

    int raw_pkt_hdr_len = 0;
    u8 *raw_pkt_hdr;
    raw_pkt_hdr_len = make_raw_pkt_hdr(&raw_pkt_hdr, sampled_pkt_len);


    int sflow_sample_len = 0;
    u8* sflow_sample;
    sflow_sample_len = make_sflow_sample(&sflow_sample, raw_pkt_hdr_len);


    int sflow_hdr_len = 0;
    u8* sflow_hdr;
    sflow_hdr_len = make_sflow_hdr(&sflow_hdr);

    int sflow_pkt_len = sampled_pkt_len + raw_pkt_hdr_len + sflow_sample_len + sflow_hdr_len;




    
}

int main () {

    u8 *msg;
    int len;
    len = make_sflow_payload(&msg);

    int sockfd, n;
    struct sockaddr_in serv_addr;

    // init
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(COLLECTOR_IP);
    serv_addr.sin_port = htons(SFLOW_PORT);
    serv_addr.sin_family = AF_INET;

    // create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("connect fail\n");
        exit(1);
    }

    sendto(sockfd, (void*) msg, len, 0, (struct sockaddr*) NULL, sizeof(serv_addr));
    close(sockfd);
}
