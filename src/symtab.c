#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symtab.h"


#define H1_P1 23606321
#define H1_P2 178413881

#define H2_P1 86667557
#define H2_P2 622120817

#define HK_PRIME 8497243039
#define HK_INIT  133403

static size_t hash(size_t key, size_t p1, size_t p2);
static size_t hash_key(ste_key_t key, size_t prime);


static size_t
hash_key(ste_key_t key, size_t p)
{

     if( ! key )
     {
	  // FIXME I bet this makes it exploitable
	  
	  return 0;

     }
     
     size_t h = HK_INIT;

     for(;*key;key++)
     {

	  h = h*p + *key;
	  
     }

     return h;
     
}


static size_t
hash(size_t key, size_t p1, size_t p2)
{

     return key * p1 + p2;
     
}


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
	  /* clean allocated entries */

	  char *it = (*ppSymTab)->st_data[i].ste_key;

	  if( it )
	  {

	       free( it );
	       
	  }
	  
     }

     
     free( *ppSymTab );

     *ppSymTab = NULL;
     
}



symbol_table_entry_t *
new_symbol_table_entry( const ste_key_t k, ste_value_t v )
{

     symbol_table_entry_t *ent = malloc( sizeof(symbol_table_entry_t) );
     if( !ent )
     {
	  perror(__func__);
	  return NULL;
     }
     
     return init_symbol_table_entry(ent, k, v);
}


symbol_table_entry_t *
init_symbol_table_entry(symbol_table_entry_t *ent,  const ste_key_t k, ste_value_t v)
{

     if( ! ent || ! k )
     {
	  
	  return NULL;

     }

     size_t k_hash = hash_key( k, HK_PRIME ); // the hash value of k

     ent->ste_key = strdup( k );
     ent->ste_value = v;

     ent->h1 = hash( k_hash, H1_P1, H1_P2 );
     ent->h2 = hash( k_hash, H2_P1, H2_P2 );

     return ent;

}


void
del_symbol_table_entry( symbol_table_entry_t ** ppSTE )
{

     if( ! ppSTE || !(*ppSTE) )
     {
	  /* insane */
	  return;

     }

     if( (*ppSTE)->ste_key )
     {
	  /* free the key */
	  free( (*ppSTE)->ste_key );

     }

     free( *ppSTE );

     *ppSTE = NULL;

     return;
     
}


int
symbol_table_add( symbol_table_t **ppSymTab, const ste_key_t key, ste_value_t value)
{
     // TODO add growth and rehashing
     if( !ppSymTab || !(*ppSymTab) || !key )
     {
	  /* insane */
	  return -1;
	  
     }

     symbol_table_entry_t ent;
     if( !init_symbol_table_entry( &ent, key, value ) )
     {
	  return -1;
     }

     // FIXME implement propper double hashing
     int free_pos = (*ppSymTab)->st_size; // for trying everything? //- (*ppSymTab)->st_load;
     size_t h;
     for(int i=0; i<free_pos; i++)
     {
	  h = (ent.h1 + i*ent.h2) % (*ppSymTab)->st_size;
	  if( (*ppSymTab)->st_data[h].ste_key == NULL )
	  {
	       /* found a spot */
	       memcpy( &(*ppSymTab)->st_data[h], &ent,
		       sizeof( symbol_table_entry_t ) );
	       (*ppSymTab)->st_load++;
	       return 0;
	  }
     }

     return -1;
     
}


size_t *
symbol_table_get( symbol_table_t *pSymTab, const ste_key_t key )
{

     if( !pSymTab || !key )
     {

	  return NULL;

     }

     symbol_table_entry_t ent;

     if( !init_symbol_table_entry( &ent, key, 0 ) )
     {

	  return NULL;
	  
     }


     size_t h;
     const char *candidate;
     for(int i=0; i<pSymTab->st_size; i++)
     {
	  h = (ent.h1 + i*ent.h2) % (pSymTab)->st_size;
	  candidate = (pSymTab)->st_data[h].ste_key;
	  if( !candidate )
	  {
	       /* is not contained */
	       return NULL;
	  } else if( strcmp( candidate, key ) == 0 ) {
	       /* match */
	       return &pSymTab->st_data[h].ste_value;
	  }
     }


     return NULL;
     
}
