//
// Created by patrickwang on 15/4/2020.
//

#include "secret_sharing_efficient_tools.h"
#include <memory>


void ss_decrypt_server_batch(uint64_t plain[], uint64_t share[], int m, NetAdapter *net) {
    uint64_t *recv_share = new uint64_t[m];
    net->recv(reinterpret_cast<unsigned char *> (recv_share), sizeof(uint64_t) * m);
    for (int i = 0; i < m; i++)
        plain[i] = mod_bit(share[i] + recv_share[i]);
    net->send(reinterpret_cast<unsigned char *>(plain), sizeof(uint64_t) * m);
    delete[] recv_share;
}

void
secure_mul_server_batch(uint64_t as[], uint64_t bs[], uint64_t ab_s[], int m, const triplet_b &tri, NetAdapter *net) {
    auto *e = new uint64_t[m * 2];
    auto *es = new uint64_t[m * 2];
    auto f = e + m;
    auto fs = es + m;

    for (int i = 0; i < m; i++) {
        es[i] = mod_bit(as[i] - tri.us[0]);
        fs[i] = mod_bit(bs[i] - tri.gs[0]);
    }
    ss_decrypt_server_batch(e, es, m  * 2, net);
//    ss_decrypt_server_batch(f, fs, m, net);

    for (int i = 0; i < m; i++) {
        ab_s[i] = mod_bit(0 * e[i] * f[i] + e[i] * tri.gs[0] + f[i] * tri.us[0] + tri.zs[0]);
    }
    delete[] e;
    delete[] es;
}


void ss_decrypt_client_batch(uint64_t plain[], uint64_t share[], int m, NetAdapter *net) {
    net->send(reinterpret_cast<unsigned char *>(share), sizeof(uint64_t) * m);
    net->recv(reinterpret_cast<unsigned char *>(plain), sizeof(uint64_t) * m);
}


void
secure_mul_client_batch(uint64_t as[], uint64_t bs[], uint64_t ab_s[], int m, const triplet_b &tri, NetAdapter *net) {
    auto *e = new uint64_t[m * 2];
    auto *es = new uint64_t[m * 2];
    auto f = e + m;
    auto fs = es + m;

    for (int i = 0; i < m; i++) {
        es[i] = mod_bit(as[i] - tri.us[1]);
        fs[i] = mod_bit(bs[i] - tri.gs[1]);
    }
    ss_decrypt_client_batch(e, es, m * 2, net);
//    ss_decrypt_client_batch(f, fs, m, net);

    for (int i = 0; i < m; i++) {
        ab_s[i] = mod_bit(1 * e[i] * f[i] + e[i] * tri.gs[1] + f[i] * tri.us[1] + tri.zs[1]);
    }
    delete[] e;
    delete[] es;
}


