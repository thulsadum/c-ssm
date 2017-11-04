/** Unit Test for Segments */
#include <stdio.h>
#include <string.h>
#include "mu.h"
#include "../src/segment.h"

int tests_run = 0;


/* TODO: add concatenation of segments */


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
test_segment_add_text( void )
{
     Segment_Text_t * pseg = new_segment_text( 10 );
     mu_assert( "Init: type == ST_TEXT",
		pseg->seg_head.seg_type == ST_TEXT );
     mu_assert( "Init: size == 0",
		pseg->seg_head.seg_size == 0 );
     mu_assert( "Init: max_size == 10",
		pseg->seg_head.seg_max_size == 10 );

     mu_assert( "Addition succeeds.",
		! segment_add_text( &pseg, "Hello." ) );

     mu_assert( "Invariant: type == ST_TEXT",
		pseg->seg_head.seg_type == ST_TEXT );
     mu_assert( "Effect: size == 1",
		pseg->seg_head.seg_size == 1 );
     mu_assert( "Invariant: max_size == 10",
		pseg->seg_head.seg_max_size == 10 );
     
     mu_assert( "Item equality.",
		strcmp("Hello.", pseg->seg_text_data[0]) == 0);

     del_segment_text( &pseg );

     return 0;
     
}

static char *
test_segment_growth_text( void )
{
     Segment_Text_t * pseg = new_segment_text( 1 );

     mu_assert( "Init: size == 0",
		pseg->seg_head.seg_size == 0 );
     mu_assert( "Init: max_size == 1",
		pseg->seg_head.seg_max_size == 1 );

     mu_assert( "Action succeeds.",
		! segment_add_text( &pseg, "1" ) );
     mu_assert( "Action succeeds.",
		! segment_add_text( &pseg, "2" ) );
     
     mu_assert( "Effect: resize - max_size == 2",
		pseg->seg_head.seg_max_size == 2 );
     mu_assert( "Action succeeds.",
		! segment_add_text( &pseg, "3" ) );

     mu_assert( "Effect: resize - max_size == 4",
		pseg->seg_head.seg_max_size == 4 );
     mu_assert( "Action succeeds.",
		! segment_add_text( &pseg, "4" ) );

     mu_assert( "Effect: size == 4",
		pseg->seg_head.seg_size == 4 );
     mu_assert( "Invariant: max_size == 4",
		pseg->seg_head.seg_max_size == 4 );
     
     mu_assert( "Effect: Item[0]",
		strcmp( "1", pseg->seg_text_data[0] ) == 0 );
     mu_assert( "Effect: Item[1]",
		strcmp( "2", pseg->seg_text_data[1] ) == 0 );
     mu_assert( "Effect: Item[2]",
		strcmp( "3", pseg->seg_text_data[2] ) == 0 );
     mu_assert( "Effect: Item[3]",
		strcmp( "4", pseg->seg_text_data[3] ) == 0 );
     
     return 0;
}


static char *
test_segment_text( void )
{
     mu_run_test( test_segment_add_text );
     mu_run_test( test_segment_growth_text );
     
     return 0;
}



static char *
test_segment_add_data( void )
{
     Segment_Data_t * pseg = new_segment_data( 10 );
     mu_assert( "Init: type == ST_DATA",
		pseg->seg_head.seg_type == ST_DATA );
     mu_assert( "Init: size == 0",
		pseg->seg_head.seg_size == 0 );
     mu_assert( "Init: max_size == 10",
		pseg->seg_head.seg_max_size == 10 );

     mu_assert( "Addition succeeds.",
		! segment_add_data( &pseg, 0x42 ) );

     mu_assert( "Invariant: type == ST_DATA",
		pseg->seg_head.seg_type == ST_DATA );
     mu_assert( "Effect: size == 1",
		pseg->seg_head.seg_size == 1 );
     mu_assert( "Invariant: max_size == 10",
		pseg->seg_head.seg_max_size == 10 );
     
     mu_assert( "Item equality.",
		pseg->seg_data_data[0] == 0x42 );

     del_segment_data( &pseg );

     return 0;
     
}


static char *
test_segment_growth_data( void )
{
     Segment_Data_t * pseg = new_segment_data( 1 );

     mu_assert( "Init: size == 0",
		pseg->seg_head.seg_size == 0 );
     mu_assert( "Init: max_size == 1",
		pseg->seg_head.seg_max_size == 1 );

     mu_assert( "Action succeeds.",
		! segment_add_data( &pseg, 1 ) );
     mu_assert( "Action succeeds.",
		! segment_add_data( &pseg, 2 ) );
     
     mu_assert( "Effect: resize - max_size == 2",
		pseg->seg_head.seg_max_size == 2 );
     mu_assert( "Action succeeds.",
		! segment_add_data( &pseg, 3 ) );

     mu_assert( "Effect: resize - max_size == 4",
		pseg->seg_head.seg_max_size == 4 );
     mu_assert( "Action succeeds.",
		! segment_add_data( &pseg, 4 ) );

     mu_assert( "Effect: size == 4",
		pseg->seg_head.seg_size == 4 );
     mu_assert( "Invariant: max_size == 4",
		pseg->seg_head.seg_max_size == 4 );
     

     mu_assert( "Effect: Item[0]",
		pseg->seg_data_data[0] == 1 );
     mu_assert( "Effect: Item[1]",
		2 == pseg->seg_data_data[1] );
     mu_assert( "Effect: Item[2]",
		3 == pseg->seg_data_data[2] );
     mu_assert( "Effect: Item[3]",
	        4 == pseg->seg_data_data[3] );
     
     return 0;
}


static char *
test_segment_data( void )
{

     mu_run_test( test_segment_add_data );
     mu_run_test( test_segment_growth_data );

     return 0;
}


static char *
test_segment_add_code( void )
{
     Segment_Code_t * pseg = new_segment_code( 10 );
     mu_assert( "Init: type == ST_CODE",
		pseg->seg_head.seg_type == ST_CODE );
     mu_assert( "Init: size == 0",
		pseg->seg_head.seg_size == 0 );
     mu_assert( "Init: max_size == 10",
		pseg->seg_head.seg_max_size == 10 );

     mu_assert( "Addition succeeds.",
		! segment_add_code( &pseg, (Semantic_t) 0x42 ) );

     mu_assert( "Invariant: type == ST_CODE",
		pseg->seg_head.seg_type == ST_CODE );
     mu_assert( "Effect: size == 1",
		pseg->seg_head.seg_size == 1 );
     mu_assert( "Invariant: max_size == 10",
		pseg->seg_head.seg_max_size == 10 );
     
     mu_assert( "Item equality.",
		pseg->seg_code_data[0] == (Semantic_t) 0x42 );

     del_segment_code( &pseg );

     return 0;
     
}


static char *
test_segment_growth_code( void )
{
     Segment_Code_t * pseg = new_segment_code( 1 );

     mu_assert( "Init: size == 0",
		pseg->seg_head.seg_size == 0 );
     mu_assert( "Init: max_size == 1",
		pseg->seg_head.seg_max_size == 1 );

     mu_assert( "Action succeeds.",
		! segment_add_code( &pseg, (Semantic_t)1 ) );
     mu_assert( "Action succeeds.",
		! segment_add_code( &pseg, (Semantic_t)2 ) );
     
     mu_assert( "Effect: resize - max_size == 2",
		pseg->seg_head.seg_max_size == 2 );
     mu_assert( "Action succeeds.",
		! segment_add_code( &pseg, (Semantic_t)3 ) );

     mu_assert( "Effect: resize - max_size == 4",
		pseg->seg_head.seg_max_size == 4 );
     mu_assert( "Action succeeds.",
		! segment_add_code( &pseg, (Semantic_t)4 ) );

     mu_assert( "Effect: size == 4",
		pseg->seg_head.seg_size == 4 );
     mu_assert( "Invariant: max_size == 4",
		pseg->seg_head.seg_max_size == 4 );

     mu_assert( "Effect: Item[0]",
		(Semantic_t)1 == pseg->seg_code_data[0] );
     mu_assert( "Effect: Item[1]",
		(Semantic_t)2 == pseg->seg_code_data[1] );
     mu_assert( "Effect: Item[2]",
		(Semantic_t)3 == pseg->seg_code_data[2] );
     mu_assert( "Effect: Item[3]",
	        (Semantic_t)4 == pseg->seg_code_data[3] );
     
     return 0;
}


static char *
test_segment_code( void )
{

     mu_run_test( test_segment_add_code );
     mu_run_test( test_segment_growth_code );

     return 0;
}


static char *
all_tests ( void )
{
     
     mu_run_test_collection( test_segment_lifecycle );
     mu_run_test_collection( test_segment_text );
     mu_run_test_collection( test_segment_data );
     mu_run_test_collection( test_segment_code );
     
     return 0;

}
