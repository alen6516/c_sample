#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#include <sys/socket.h>             /* socket(), bind(), listen(), ... */
#include <netinet/in.h>             /* AF_INET, AF_INET6 addr family and their corresponding protocol family PF_INET, PFINET6 */
#include <arpa/inet.h>              /* hton(), inet_ntop() */
#include <unistd.h>                 /* read(), write(), close() */

#include "main.h"


#define COLLECTOR_IP "127.0.0.1"
#define SFLOW_PORT   6343

#define SAMPLE_NUM 1

#define ARP

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

int make_sflow_sample(u8 **msg, int curr_len) 
{

    struct sflow_sample_t* sflow_sample;
    sflow_sample = (struct sflow_sample_t*) calloc(1, sizeof(struct sflow_sample_t));
    sflow_sample->sample_type = htonl(1);
    sflow_sample->sample_len = htonl(curr_len+(int)sizeof(struct sflow_sample_t)-8);
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

int make_sampled_pkt(u8 **msg, int sampled_pkt_payload_len) 
{

#ifdef ARP
    u8 eth_data[14] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0xd8, 0x50, 0xe6, 0x94, 0x2c, 0xf8,
                        0x08, 0x06 };
#else
    u8 eth_data[14] = { 0x00, 0x1c, 0x23, 0x9f, 0x15, 0x0b,
                        0x00, 0x19, 0xb9, 0xdd, 0xb2, 0x64,
                        0x08, 0x00 };
#endif


#ifdef ARP
    int arp_hdr_len = sizeof(struct arp_hdr_t);
    printf("%d\n", arp_hdr_len);
    struct arp_hdr_t* arp_hdr;
    arp_hdr = (struct arp_hdr_t*) calloc(1, arp_hdr_len);
    arp_hdr->hd_type = htons(1);
    arp_hdr->prot_type = htons(0x0800);
    arp_hdr->hd_size = 6;
    arp_hdr->prot_size = 4;
    arp_hdr->op_code = htons(1);

    u8 smac[6] = { 0xd8, 0x50, 0xe6, 0x94, 0x2c, 0xf8 };
    memcpy((void*) arp_hdr->smac, (void*) smac, 6);

    arp_hdr->sip = htonl(0xc0a862fb);

    u8 dmac[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    memcpy((void*) arp_hdr->dmac, (void*) dmac, 6);

    arp_hdr->dip = htonl(0xc0a86298);

#else
    int ipv4_hdr_len = sizeof(struct ipv4_hdr_t);
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

    /*
    int icmpv4_hdr_len = sizeof(struct icmpv4_hdr_t);
    struct icmpv4_hdr_t *icmpv4_hdr;
    icmpv4_hdr = (struct icmpv4_hdr_t*) calloc(1, sizeof(struct icmpv4_hdr_t));
    icmpv4_hdr->type = 8;
    icmpv4_hdr->code = 0;
    icmpv4_hdr->chksum = htons(0x9487);
    icmpv4_hdr->id = htons(0xa948);
    icmpv4_hdr->seq_num = htons(0x0cb2);
    */

#endif


    u8 *ret;
    int ori_len = 0;
    int padding_len = 0;
    int ret_len = 0;

#ifdef ARP
    ori_len = 14+arp_hdr_len;
    if (ori_len % 4 != 0) {
        padding_len = (ori_len/4 +1)*4 -ori_len;
    }
    ret = (u8*) calloc(1, ori_len + padding_len);
    memcpy(ret, eth_data, 14);
    ret_len += 14;
    memcpy(ret+ret_len, (void*) arp_hdr, arp_hdr_len);
    ret_len += arp_hdr_len;

#else
    ori_len = 14+ipv4_hdr_len;
    if (ori_len % 4 != 0) {
        padding_len = (ori_len/4 +1)*4 -ori_len;
    }
    //ret = (u8*) calloc(1, 14 + ipv4_hdr_len + icmpv4_hdr_len);
    ret = (u8*) calloc(1, ori_len + padding_len);

    memcpy(ret, eth_data, 14);
    ret_len += 14;
    memcpy(ret+ret_len, (void*) ipv4_hdr, ipv4_hdr_len);
    //memcpy(ret+ret_len, (void*) icmpv4_hdr, icmpv4_hdr_len);
    
#endif

    *msg = ret;
    return ret_len;
}

int make_raw_pkt_hdr(u8 **msg, int sampled_pkt_len, int padding_len) 
{
    

    struct raw_pkt_hdr_t* raw_pkt_hdr;
    raw_pkt_hdr = (struct raw_pkt_hdr_t*) calloc(1, sizeof(struct raw_pkt_hdr_t));
    raw_pkt_hdr->format = htonl(1);
    raw_pkt_hdr->flow_data_len = htonl(sampled_pkt_len + padding_len +(int)sizeof(struct raw_pkt_hdr_t) - 8);
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


int make_sflow_packet(u8 **msg) 
{

    // make sampled packet
    int sampled_pkt_len = 0;
    u8 *sampled_pkt;
    //int sampled_pkt_payload_len = 8;    // icmpv4 length
    int sampled_pkt_payload_len = 0;
    sampled_pkt_len = make_sampled_pkt(&sampled_pkt, sampled_pkt_payload_len);
    printf("sampled_pkt_len: %d\n", sampled_pkt_len);
    

    // make raw packet header
    int raw_pkt_hdr_len = 0;
    u8 *raw_pkt_hdr;
    int padding_len = 0;
    if (sampled_pkt_len % 4 != 0) {
        padding_len = (sampled_pkt_len/4 +1)*4 -sampled_pkt_len;
    }
    printf("padding_len: %d\n", padding_len);
    raw_pkt_hdr_len = make_raw_pkt_hdr(&raw_pkt_hdr, sampled_pkt_len, padding_len);
    printf("raw_pkt_hdr_len: %d\n", raw_pkt_hdr_len);


    // make sflow sample
    int sflow_sample_hdr_len = 0;
    u8* sflow_sample;
    sflow_sample_hdr_len = make_sflow_sample(&sflow_sample, sampled_pkt_len+raw_pkt_hdr_len);
    printf("sflow_sample_hdr_len: %d\n", sflow_sample_hdr_len);


    // make sflow header
    int sflow_hdr_len = 0;
    u8* sflow_hdr;
    sflow_hdr_len = make_sflow_hdr(&sflow_hdr);
    printf("sflow_hdr_len: %d\n", sflow_hdr_len);


    // make sflow packet
    int sflow_pkt_len = sampled_pkt_len + padding_len + raw_pkt_hdr_len + sflow_sample_hdr_len + sflow_hdr_len;
    printf("sflow_pkt_len: %d\n", sflow_pkt_len);
    u8* ret = (u8*) calloc(1, sflow_pkt_len);


    // copy all stuff into
    int curr_len = 0;
    memcpy(ret, sflow_hdr, sflow_hdr_len);
    curr_len += sflow_hdr_len;
    memcpy(ret+curr_len, sflow_sample, sflow_sample_hdr_len);
    curr_len += sflow_sample_hdr_len;
    memcpy(ret+curr_len, raw_pkt_hdr, raw_pkt_hdr_len);
    curr_len += raw_pkt_hdr_len;
    memcpy(ret+curr_len, sampled_pkt, sampled_pkt_len);
    curr_len += sampled_pkt_len;
    curr_len += padding_len;

    assert(curr_len == sflow_pkt_len);

    *msg = ret;
    return curr_len;
}

int main () {

    u8 *msg;
    int len = make_sflow_packet(&msg);


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
