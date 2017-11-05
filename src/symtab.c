#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symtab.h"




symbol_table_t *
new_symbol_table( size_t size )
{
     symbol_table_t * pSymTab;
     size_t totSize = sizeof(symbol_table_t) + size*sizeof(pSymTab->st_data[0]);

     pSymTab = malloc( totSize );


     if( ! pSymTab )
     {

	  perror(__func__);
	  return NULL;

     }

     memset( pSymTab, 0, totSize );
     pSymTab->st_size = size;
     
     return pSymTab;
     
}


void
del_symbol_table( symbol_table_t ** ppSymTab )
{

     if( ! ppSymTab || !(*ppSymTab) )
     {
	  /* insane */
	  return;
     }

     
     for(int i = 0; i < (*ppSymTab)->st_size; i++)
     {
	  /* clean allocated keys */

	  char *it = (*ppSymTab)->st_data[i].ste_key;

	  if( it )
	  {

	       free( it );
	       
	  }
	  
     }

     
     free( *ppSymTab );

     *ppSymTab = NULL;
     
}
