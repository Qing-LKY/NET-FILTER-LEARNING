#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/icmp.h>
#include <net/tcp.h>


static const unsigned char u8_bandip[4] = {192u, 168u, 43u, 138u};
#define banned_ip (*(unsigned int *)u8_bandip)
static int bandport = 44444;


static unsigned int nf_hook_in(
    void *priv, struct sk_buff *sk, const struct nf_hook_state *state
) {
    struct iphdr *iph = ip_hdr(sk);
    unsigned int src_ip = iph->saddr;
    // 禁止接收特定 IP 的数据包
    if (src_ip == banned_ip) {
        printk(KERN_NOTICE "Banned a packet from %d.%d.%d.%d!\n", 
            (int)u8_bandip[0], (int)u8_bandip[1], (int)u8_bandip[2], (int)u8_bandip[3]);
        return NF_DROP;
    }
    // 禁止特定端口的数据接收
    switch (iph->protocol) {
        case IPPROTO_TCP: {
            if (tcp_hdr(sk)->dest == bandport) {
                printk(KERN_NOTICE "Banned a tcp packet (recv) with port %d!\n", bandport);
                return NF_DROP;
            }
            break;
        }
        case IPPROTO_UDP: {
            if (udp_hdr(sk)->dest == bandport) {
                printk(KERN_NOTICE "Banned a udp packet (recv) with port %d!\n", bandport);
                return NF_DROP;
            }
            break;
        }
        default: break;
    }
    return NF_ACCEPT;
}

static unsigned int nf_hook_out(
    void *priv, struct sk_buff *sk, const struct nf_hook_state *state
) {
    struct iphdr *iph = ip_hdr(sk);
    switch (iph->protocol) {
        // 禁止特定端口的数据发送
        case IPPROTO_TCP: {
            if (tcp_hdr(sk)->source == bandport) {
                printk(KERN_NOTICE "Banned a tcp packet (send) with port %d!\n", bandport);
                return NF_DROP;
            }
            break;
        }
        case IPPROTO_UDP: {
            if (udp_hdr(sk)->source == bandport) {
                printk(KERN_NOTICE "Banned a udp packet (send) with port %d!\n", bandport);
                return NF_DROP;
            }
            break;
        }
        // 禁止 ping (ICMP ECHO REQUEST) 发送
        case IPPROTO_ICMP: {
            if (icmp_hdr(sk)->type == ICMP_ECHO) {
                printk(KERN_NOTICE "Banned a icmp echo packet!\n");
                return NF_DROP;
            }
            break;
        }
        default: break;
    }
    return NF_ACCEPT;
}


static struct nf_hook_ops nfin = 
{
    .hook = nf_hook_in,
    .hooknum = NF_INET_LOCAL_IN,
    .pf = PF_INET,
    .priority = NF_IP_PRI_FIRST
};

static struct nf_hook_ops nfout=
{
    .hook = nf_hook_out,
    .hooknum = NF_INET_LOCAL_OUT,
    .pf = PF_INET,
    .priority = NF_IP_PRI_FIRST
};


static int __init init_lab10(void) {
    printk(KERN_INFO "Init module: lab10!\n");
    nf_register_net_hook(&init_net, &nfin);
    nf_register_net_hook(&init_net, &nfout);
    printk(KERN_INFO "Register two hook!\n");
    return 0;
}

static void __exit exit_lab10(void) {
    nf_unregister_net_hook(&init_net, &nfin);
    nf_unregister_net_hook(&init_net, &nfout);
    printk(KERN_INFO "Remove module: lab10!\n");
}

module_init(init_lab10);
module_exit(exit_lab10);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Qing-LKY");
MODULE_DESCRIPTION("Lab10: Net-filter");
MODULE_VERSION("0.1.0");
