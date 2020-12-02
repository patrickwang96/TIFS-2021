#include "utils.h"

#include <assert.h>
#include <stdio.h>

// void cache_flusher()
// {
  // 8MB L3 cache
	// static const int l3_size = 1024*1024*8;
	// static const int num_gar = l3_size / sizeof(int);
	// static int garbage[num_gar];

	// for(int i=0; i<num_gar; ++i)
		// garbage[i] = rand();
// }


int mod_pos(int x, int d)
{
    // if(d < 0)
    //     exit(0);
    int r = x%d;
    if(r < 0)
        return r+d;
    else
        return r;
}

int mod_bit(int x)
{
	return mod_pos(x, 2);
}

