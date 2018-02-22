#pragma once

#include "ub_core.h"



uint32_t ub_links_number(UbChain* chain);

uint32_t ub_fragments_number(UbChain* chain);

uint32_t ub_largest_fragment_size(UbChain* chain);

uint32_t ub_current_fragment_size(UbChain* chain);

double ub_fragment_size_mean(UbChain* chain);

uint8_t ub_hardest_link(UbChain* chain); //No cuenta los ghost

double ub_hardness_mean(UbChain* chain);

double ub_ghost_links_ratio(UbChain* chain);
