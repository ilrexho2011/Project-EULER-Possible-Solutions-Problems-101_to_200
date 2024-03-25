#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sheet_cmp( const void *a, const void *b ) {
	int ia = *((int *)a);
	int ib = *((int *)b);
	return ia-ib;
}

#	define DRAWER_CAPACITY 12 // lets us use fix-sized buffers as drawers
#	define _ 9	// Used as padding, describes a non-sheet, must be higher than 2,3,4,5
struct drawer_state {
	int used;	// set to 0 for pad items
	int sheets[DRAWER_CAPACITY]; // can be 2, 3, 4, or 5
	double p_of_arriving_here;
};

static int state_cmp( const void *a, const void *b ) {
	struct drawer_state dsa = *((struct drawer_state *)a);
	struct drawer_state dsb = *((struct drawer_state *)b);

	// put used states before dummy padding states
	if( dsa.used && !dsb.used ) return -1;
	if( !dsa.used && dsb.used ) return 1;
	if( !dsa.used && !dsb.used ) return 0;

	// Both are used, now compare sheets
	
	for(int i=0; i<DRAWER_CAPACITY; i++) {
		if(dsa.sheets[i] < dsb.sheets[i] ) return -1;	
		if(dsa.sheets[i] > dsb.sheets[i] ) return 1;	
	}

	return 0;	
}

int main() {
	
	// The answer, once accumulated
	double p_next_draw_is_solo = 0.0;


#	define MAX_STATES_PER_BATCH 12 // enough for max # sheets + some swapping space
	struct drawer_state dsa[ MAX_STATES_PER_BATCH ];
	struct drawer_state dsb[ MAX_STATES_PER_BATCH ];

	struct drawer_state *last = dsa;
	struct drawer_state *this = dsb;

	memset( &dsb, 0, sizeof dsb);

	// This is the known state before batch #2
	this[0] = (struct drawer_state){ 1, { 2,3,4,5,_,_,_,_,_,_,_,_ }, 1.0 };

	while(1) {
		
		// Rotate last & this
		last = this;
		this = (last==dsa) ? dsb : dsa;
		memset( this, 0, sizeof dsa);

		int is_last_batch = 0;

		// Iterate through possible last-states
		for( struct drawer_state *ds = last; ds->used; ++ds ) {

			int sheet_count = 0;
			for( int *sheet = ds->sheets; *sheet != _; ++sheet_count, ++sheet );

			if( sheet_count == 1 ) {
				printf("p was %f, adding %f\n", p_next_draw_is_solo, ds->p_of_arriving_here );
				p_next_draw_is_solo += ds->p_of_arriving_here;
			}

			// Iterate through sheets in the drawer
			for( int *sheet = ds->sheets; *sheet != _; ++sheet ) {
				struct drawer_state tmp;
				memcpy( &tmp, ds, sizeof *ds );

				// In temp copy, replace sheet with post-cut sheets
				tmp.sheets[ sheet - ds->sheets ] = _;
				switch( *sheet ) {
				case 1: // for completeness, but unused
					tmp.sheets[ DRAWER_CAPACITY-4 ] = 2;
				case 2:
					tmp.sheets[ DRAWER_CAPACITY-3 ] = 3;
				case 3:
					tmp.sheets[ DRAWER_CAPACITY-2 ] = 4;
				case 4:
					tmp.sheets[ DRAWER_CAPACITY-1 ] = 5;
				}
				// Normalize the sheet order
				qsort( tmp.sheets, DRAWER_CAPACITY, sizeof(int), &sheet_cmp );

				
				int state_count = 0;
				for( struct drawer_state *one_state = this; one_state->used; ++one_state, ++state_count );

				// find any existing state with this sheet pattern from a prev iteration
				qsort( this, MAX_STATES_PER_BATCH, sizeof(struct drawer_state), state_cmp );
				struct drawer_state *existing = 
					bsearch( &tmp, this, state_count, sizeof tmp, state_cmp );

				if( !existing ) {

					is_last_batch = !state_count;

					// Add a new item
					existing = this + state_count;
					existing->used = 1;
					existing->p_of_arriving_here = 0.0;
					memcpy( existing->sheets, tmp.sheets, sizeof tmp.sheets );
				}

				existing->p_of_arriving_here += 
					( ds->p_of_arriving_here / sheet_count );
				
			}
		}

		if( is_last_batch ) break;

	}

	printf("p_next_draw_is_solo = %f\n", p_next_draw_is_solo);
}