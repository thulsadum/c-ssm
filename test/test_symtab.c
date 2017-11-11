#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "mu.h"
#include "../src/symtab.h"


int tests_run = 0;


static char *
test_symtab_lifecycle( void )
{

     symbol_table_t *pSymTab = new_symbol_table( 10 );

     mu_assert( "Allocation.",
		pSymTab );

     mu_assert( "is empty",
		pSymTab->st_load == 0 );

     mu_assert( "is initialized",
		pSymTab->st_size == 10 );


     del_symbol_table( &pSymTab );

     mu_assert( "deallocation",
		!pSymTab );


     return 0;
     
}


static char *
test_symtab_entry_lifecycle( void )
{
     char * key = strdup( "the truth" );
     symbol_table_entry_t *pSymTabEnt = new_symbol_table_entry( key, 42 );

     mu_assert( "Allocation.",
		pSymTabEnt );

     mu_assert( "copied key",
		key != pSymTabEnt->ste_key );
     mu_assert( "key stored",
		strcmp( key, pSymTabEnt->ste_key ) == 0 );

     mu_assert( "value stored",
		pSymTabEnt->ste_value == 42 );

     printf("h1: %lu, h2: %lu\n", pSymTabEnt->h1, pSymTabEnt->h2 );

     del_symbol_table_entry( &pSymTabEnt );

     mu_assert( "deallocation",
		!pSymTabEnt );

     free( key );

     return 0;
     
}


static char *
test_symtab_access( void )
{
     // adds some symbols without rehashing and retrieves them
     symbol_table_t *pSymTab = new_symbol_table( 10 );
     size_t *get = 0;
     
     mu_assert( "Allocation.",
		pSymTab );

     mu_assert( "Success 1",
		! symbol_table_add( &pSymTab, "the-truth", 42 ));
     mu_assert( "add #1",
		pSymTab->st_load == 1 );
     mu_assert( "  #1 inv. st_size",
		pSymTab->st_size == 10 );

     
     mu_assert( " get #1?",
		get = symbol_table_get( pSymTab, "the-truth" ) );
     mu_assert( " get #1!",
		*get = 42 );

     
     mu_assert( "Success 2",
		! symbol_table_add( &pSymTab, "two", 2 ));
     mu_assert( "add #2",
		pSymTab->st_load == 2 );
     mu_assert( "  #2 inv. st_size",
		pSymTab->st_size == 10 );

     mu_assert( "Success 3",
		! symbol_table_add( &pSymTab, "three", 3 ));
     mu_assert( "add #3",
		pSymTab->st_load == 3 );
     mu_assert( "  #3 inv. st_size",
		pSymTab->st_size == 10 );

     mu_assert( "Success 4",
		! symbol_table_add( &pSymTab, "four", 4 ));
     mu_assert( "add #4",
		pSymTab->st_load == 4 );
     mu_assert( "  #4 inv. st_size",
		pSymTab->st_size == 10 );

     mu_assert( "Success 5",
		! symbol_table_add( &pSymTab, "five", 5 ));
     mu_assert( "add #5",
		pSymTab->st_load == 5 );
     mu_assert( "  #5 inv. st_size",
		pSymTab->st_size == 10 );

     
     mu_assert( " Get #1?",
		get = symbol_table_get( pSymTab, "the-truth" ) );
     mu_assert( " Get #1!",
		*get = 42 );
     mu_assert( " Get #2?",
		get = symbol_table_get( pSymTab, "two" ) );
     mu_assert( " Get #2!",
		*get = 2 );
     mu_assert( " Get #3?",
		get = symbol_table_get( pSymTab, "three" ) );
     mu_assert( " Get #3!",
		*get = 3 );
     mu_assert( " Get #4?",
		get = symbol_table_get( pSymTab, "four" ) );
     mu_assert( " Get #4!",
		*get = 4 );
     mu_assert( " Get #5?",
		get = symbol_table_get( pSymTab, "five" ) );
     mu_assert( " Get #5!",
		*get = 5 );
     
     del_symbol_table( &pSymTab );

     return 0;
}



static char *
all_tests( void )
{

     mu_run_test( test_symtab_lifecycle );
     mu_run_test( test_symtab_entry_lifecycle );
     mu_run_test( test_symtab_access );
     
     return 0;

}
