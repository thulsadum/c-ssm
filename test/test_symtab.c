#include <stdio.h>

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
all_tests( void )
{

     mu_run_test( test_symtab_lifecycle );

     return 0;

}
