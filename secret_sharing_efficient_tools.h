//
// Created by patrickwang on 15/4/2020.
//

#ifndef PRIVACY_PRESERVING_EFFICENT_DECISION_TREE_SECRET_SHARING_EFFICIENT_TOOLS_H
#define PRIVACY_PRESERVING_EFFICENT_DECISION_TREE_SECRET_SHARING_EFFICIENT_TOOLS_H

#include "network.h"
// #include "secret_sharing.h"
#include <vector>
// #include "decision_tree.h"
#include "utils.h"
#include <algorithm>
#include <cstdint>


// Triplet for beaver's secure multiplication protocol
typedef struct triplet_bit {
	// triplet_bit();

	int u;
	int g;
	int z;

	int us[2];
	int gs[2];
	int zs[2];
} triplet_b;



void ss_decrypt_server_batch(uint64_t plain[], uint64_t share[], int m, NetAdapter *net);

void ss_decrypt_client_batch(uint64_t plain[], uint64_t share[], int m, NetAdapter *net);

void secure_mul_server_batch(uint64_t as[], 
    uint64_t bs[], uint64_t ab_s[], 
    int m, const triplet_b &tri, NetAdapter *net);

void secure_mul_client_batch(uint64_t as[], 
    uint64_t bs[], uint64_t ab_s[], 
    int m, const triplet_b &tri, NetAdapter *net);

#endif //PRIVACY_PRESERVING_EFFICENT_DECISION_TREE_SECRET_SHARING_EFFICIENT_TOOLS_H
