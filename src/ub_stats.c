#include "ub_stats.h"



uint32_t ub_links_number(UbChain* chain){
	int32_t links_number = 0;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	while (iter != NULL){
		links_number++;
		UbChain_iter_next(&iter);
	}

	return links_number;
}


#define FRAGMENT_BROKEN(iter, date_diff) ((iter->link.hardness == 0 && \
(iter->link.flags & UB_GHOST_LINK) == 0) || date_diff != 1)


uint32_t ub_fragments_number(UbChain* chain){
	int32_t fragments_number = 1;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	if (iter == NULL) return 0;
	UbDate prev_date;
	int date_diff = 1;
	while (iter != NULL){
		if (FRAGMENT_BROKEN(iter, date_diff)){
			fragments_number++;
		}
		prev_date = int_to_UbDate(iter->date);
		UbChain_iter_next(&iter);
		if (iter != NULL)
			date_diff = cmp_UbDate(prev_date, int_to_UbDate(iter->date));
	}

	return fragments_number;
}


uint32_t ub_largest_fragment_size(UbChain* chain){
	int32_t largest_size = 0;
	int32_t size = 0;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	UbDate prev_date;
	int date_diff = 1;
	while (iter != NULL){
		if (!FRAGMENT_BROKEN(iter, date_diff)){
			size++;
		} else if (size > largest_size){
			largest_size = size;
			size = 0;
		}
		prev_date = int_to_UbDate(iter->date);
		UbChain_iter_next(&iter);
		if (iter != NULL)
			date_diff = cmp_UbDate(prev_date, int_to_UbDate(iter->date));
	}

	if (size > largest_size) return size;
	return largest_size;
}


uint32_t ub_current_fragment_size(UbChain* chain){
	uint32_t size = 0;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	UbDate prev_date;
	int date_diff = 1;
	while (iter != NULL && !FRAGMENT_BROKEN(iter, date_diff)){
		size++;
		prev_date = int_to_UbDate(iter->date);
		UbChain_iter_next(&iter);
		if (iter != NULL)
			date_diff = cmp_UbDate(prev_date, int_to_UbDate(iter->date));
	}

	return size;
}



double ub_fragment_size_mean(UbChain* chain){
	uint32_t fragments_number = ub_fragments_number(chain);
	if (fragments_number == 0) return 0;
	return (double)ub_links_number(chain)/fragments_number;
}


uint8_t ub_hardest_link(UbChain* chain){
	uint8_t hardness = 0;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	while (iter != NULL){
		if (iter->link.hardness > hardness && 
		    (iter->link.flags & UB_GHOST_LINK) == 0){
			hardness = iter->link.hardness;
		}
		UbChain_iter_next(&iter);
	}

	return hardness;
}


double ub_hardness_mean(UbChain* chain){
	int link_num = 0;
	int hardness_sum = 0;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	while (iter != NULL){
		if ((iter->link.flags & UB_GHOST_LINK) == 0){
			link_num++;
			hardness_sum += iter->link.hardness;
		}
		UbChain_iter_next(&iter);
	}

	if (link_num == 0) return 0;
	return hardness_sum/link_num;
}


double ub_ghost_links_ratio(UbChain* chain){
	int link_num = 0;
	int ghost_link_num = 0;

	UbChainIterator* iter = NULL;
	UbChain_iter_first(chain, &iter);
	while (iter != NULL){
		if ((iter->link.flags & UB_GHOST_LINK) != 0){
			ghost_link_num++;
		}
		link_num++;
		UbChain_iter_next(&iter);
	}

	if (link_num == 0) return 0;
	return (double)ghost_link_num/link_num;
}
