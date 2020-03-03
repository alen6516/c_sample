#ifndef MAIN_H
#define MAIN_H

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

struct arp_hdr_t {
    u16 hd_type;
    u16 prot_type;
    u8 hd_size;
    u8 prot_size;
    u16 op_code;
    u8 smac[6];
    u32 sip;
    u8 dmac[6];
    u32 dip;
} __attribute__((packed));;

struct ipv4_hdr_t {
    u8 hdr_len: 4,
       version: 4;
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

#endif
