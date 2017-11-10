/** a simple symbol table */
/* implemented using a double hashing hash table */
#ifndef SYMTAB_H
#define SYMTAB_H 1

#include <stddef.h>

typedef char * ste_key_t;
typedef size_t ste_value_t;

/* TODO implement these function */
typedef struct {
     ste_key_t   ste_key;
     ste_value_t ste_value;
     size_t h1, h2; // the hashes
} symbol_table_entry_t;

typedef struct {

     size_t st_load;
     size_t st_size;
     symbol_table_entry_t st_data[];

} symbol_table_t;


symbol_table_t * new_symbol_table( size_t init_size );
void             del_symbol_table( symbol_table_t ** ppSymTab );
int              symbol_table_rehash( symbol_table_t *dst, symbol_table_t *src );

symbol_table_entry_t * new_symbol_table_entry( ste_key_t k, ste_value_t v );
void                   del_symbol_table_entry( symbol_table_entry_t ** ppSymTabEnt );


int symbol_table_add( symbol_table_t ** ppSymTab, ste_key_t k, ste_value_t v );
unsigned int * symbol_table_get( symbol_table_t * pSymTab, ste_key_t k );

#endif
