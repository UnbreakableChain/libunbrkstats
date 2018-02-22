#include <glib.h>
#include <stdio.h>
#include "ub_stats.h"



void test_ub_largest_fragment_size(){
	UbChain* chain = new_UbChain("");
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=1, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=UB_GHOST_LINK},
		   (UbDate){.day=2, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=3, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=0},
		   (UbDate){.day=4, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=5, .mon=3, .year=1990});
	g_assert_cmpint(ub_largest_fragment_size(chain), ==, 3);
	free_UbChain(chain);

	chain = new_UbChain("");
	g_assert_cmpint(ub_largest_fragment_size(chain), ==, 0);
	free_UbChain(chain);
}


void test_ub_current_fragment_size(){
	UbChain* chain = new_UbChain("");
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=1, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=0},
		   (UbDate){.day=2, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=3, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=UB_GHOST_LINK},
		   (UbDate){.day=4, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=5, .mon=3, .year=1990});
	g_assert_cmpint(ub_current_fragment_size(chain), ==, 3);
	free_UbChain(chain);

	chain = new_UbChain("");
	g_assert_cmpint(ub_current_fragment_size(chain), ==, 0);
	free_UbChain(chain);
}


void test_ub_fragment_size_mean(){
	UbChain* chain = new_UbChain("");
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=1, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=0},
		   (UbDate){.day=2, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=3, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=UB_GHOST_LINK},
		   (UbDate){.day=4, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=5, .mon=3, .year=1990});
	g_assert(ub_fragment_size_mean(chain) == 2);
	free_UbChain(chain);

	chain = new_UbChain("");
	g_assert(ub_fragment_size_mean(chain) == 0);
	free_UbChain(chain);
}


void test_ub_hardest_link(){
	UbChain* chain = new_UbChain("");
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=1, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=0},
		   (UbDate){.day=2, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=3, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=3, .flags=UB_GHOST_LINK},
		   (UbDate){.day=4, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=2, .flags=0},
		   (UbDate){.day=5, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=7, .mon=3, .year=1990});
	g_assert_cmpint(ub_hardest_link(chain), ==, 2);
	free_UbChain(chain);

	chain = new_UbChain("");
	g_assert_cmpint(ub_hardest_link(chain), ==, 0);
	free_UbChain(chain);
}


void test_ub_hardness_mean(){
	UbChain* chain = new_UbChain("");
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=1, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=0},
		   (UbDate){.day=2, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=3, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=3, .flags=UB_GHOST_LINK},
		   (UbDate){.day=4, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=2, .flags=0},
		   (UbDate){.day=5, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=7, .mon=3, .year=1990});
	g_assert_cmpint(ub_hardness_mean(chain), ==, 1);
	free_UbChain(chain);

	chain = new_UbChain("");
	g_assert_cmpint(ub_hardness_mean(chain), ==, 0);
	free_UbChain(chain);
}


void test_ub_ghost_links_ratio(){
	UbChain* chain = new_UbChain("");
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=0},
		   (UbDate){.day=1, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=0, .flags=0},
		   (UbDate){.day=2, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=UB_GHOST_LINK},
		   (UbDate){.day=3, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=3, .flags=UB_GHOST_LINK},
		   (UbDate){.day=4, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=2, .flags=0},
		   (UbDate){.day=5, .mon=3, .year=1990});
	add_UbLink(chain,
		   (UbLink){.hardness=1, .flags=UB_GHOST_LINK},
		   (UbDate){.day=7, .mon=3, .year=1990});
	g_assert(ub_ghost_links_ratio(chain) == 0.5);
	free_UbChain(chain);

	chain = new_UbChain("");
	g_assert_cmpint(ub_ghost_links_ratio(chain), ==, 0);
	free_UbChain(chain);
}

	
int main(int argc, char** argv){
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/set1/largest fragment size test", test_ub_largest_fragment_size);
	g_test_add_func("/set1/current fragment size test", test_ub_current_fragment_size);
	g_test_add_func("/set1/fragment size mean test", test_ub_fragment_size_mean);
	g_test_add_func("/set1/hardest link test", test_ub_hardest_link);
	g_test_add_func("/set1/hardness mean test", test_ub_hardness_mean);
	g_test_add_func("/set1/ghost links ratio test", test_ub_ghost_links_ratio);
	return g_test_run();

}
