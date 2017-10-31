/** Unit Test for Segments */
#include <stdio.h>
#include "mu.h"
#include "../src/segment.h"

int tests_run = 0;


/* TODO: add concatenation of segments */
/* TODO: add addition to segments */


static char *
test_segment_lifecycle_general( void )
{

     Segment_t * pseg = new_segment(0);
     mu_assert( "Allocation shall succeed.",
		pseg != NULL );

     del_segment( &pseg );
     mu_assert( "Deallocation shall succeed.",
		pseg == NULL );

     return 0;

}


static char *
test_segment_lifecycle_text( void )
{

     Segment_Text_t * pseg = new_segment_text(0);
     mu_assert( "Allocation shall succeed.",
		pseg != NULL );

     del_segment_text( &pseg );
     mu_assert( "Deallocation shall succeed.",
		pseg == NULL );

     return 0;

}


static char *
test_segment_lifecycle_data( void )
{

     Segment_Data_t * pseg = new_segment_data(0);
     mu_assert( "Allocation shall succeed.",
		pseg != NULL );

     del_segment_data( &pseg );
     mu_assert( "Deallocation shall succeed.",
		pseg == NULL );

     return 0;

}


static char *
test_segment_lifecycle_code( void )
{

     Segment_Code_t * pseg = new_segment_code(0);
     mu_assert( "Allocation shall succeed.",
		pseg != NULL );

     del_segment_code( &pseg );
     mu_assert( "Deallocation shall succeed.",
		pseg == NULL );

     return 0;

}


static char *
test_segment_lifecycle( void )
{

     mu_run_test( test_segment_lifecycle_general );
     mu_run_test( test_segment_lifecycle_text );
     mu_run_test( test_segment_lifecycle_data );
     mu_run_test( test_segment_lifecycle_code );

     return 0;

}



static char *
all_tests ( void )
{
     
     mu_run_test( test_segment_lifecycle );

     return 0;

}
