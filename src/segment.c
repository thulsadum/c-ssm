#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segment.h"

/** allocates a new segment */
Segment_t *
new_segment ( size_t payload_size )
{

     Segment_t * pseg = malloc( sizeof(Segment_t) + payload_size);

     if(!pseg) {
	  perror("new_segment");
	  return NULL;
     }

     return pseg;

}


/** deallocates a segment */
void
del_segment ( Segment_t ** ppseg )
{

     if( !ppseg || !(*ppseg) )
     {
	  /* insane */
	  return;
     }

     free( *ppseg );
     *ppseg = NULL;

}


/** copies a segment header data */
int
cpy_segment ( Segment_t * dst, const Segment_t * src )
{

     if( !dst || !src || dst->seg_max_size < src->seg_max_size )
     {
	  return -1;
     }

     memcpy( dst, src, sizeof(Segment_t) );

     return 0;
}


Segment_Text_t *
new_segment_text( size_t init_size )
{
     Segment_Text_t * pseg =
	  (Segment_Text_t *) new_segment ( sizeof(char*) * init_size );

     if(pseg) {

	  pseg->seg_head.seg_type = ST_TEXT;
	  
	  pseg->seg_head.seg_size = 0;
	  pseg->seg_head.seg_max_size = init_size;

     }

     return pseg;
}


void
del_segment_text( Segment_Text_t **ppSeg )
{
     
     if( !ppSeg || !(*ppSeg) )
     {
	  /* insane */
	  return;
     }

     for(int i = 0; i < (*ppSeg)->seg_head.seg_size; i++)
     {
	  if((*ppSeg)->seg_text_data[i])
	  {
	       free( (*ppSeg)->seg_text_data[i] );
	  }
     }

     del_segment( (Segment_t **) ppSeg );
     
}


int
cpy_segment_text( Segment_Text_t * dst, const Segment_Text_t * src )
{

     int ret = cpy_segment( (Segment_t*) dst, (Segment_t*) src );

     if( ret )
     {
	  /* i.e. insane */
	  return ret;
     }
     
     for(int i = 0; i < src->seg_head.seg_size; i++)
     {
	  dst->seg_text_data[i] = strdup( src->seg_text_data[i] );
     }


     return 0;
     
}


Segment_Data_t *
new_segment_data( size_t init_size )
{
     Segment_Data_t * pseg =
	  (Segment_Data_t *) new_segment ( sizeof(int64_t) * init_size );

     if(pseg) {

	  pseg->seg_head.seg_type = ST_DATA;	  
	  
	  pseg->seg_head.seg_size = 0;
	  pseg->seg_head.seg_max_size = init_size;

     }

     return pseg;
}


int
cpy_segment_data( Segment_Data_t *dst, Segment_Data_t *src )
{

     int ret = cpy_segment( (Segment_t*) dst, (Segment_t*) src);

     if( ret )
     {
	  
	  return ret;
	  
     }

     memcpy( dst->seg_data_data, src->seg_data_data,
	     src->seg_head.seg_size * sizeof( src->seg_data_data[0] ) );

     return 0;
     
}



Segment_Code_t *
new_segment_code( size_t init_size )
{
     Segment_Code_t * pseg =
	  (Segment_Code_t *) new_segment ( sizeof(int64_t) * init_size );

     if(pseg) {

	  pseg->seg_head.seg_type = ST_CODE;	  
	  
	  pseg->seg_head.seg_size = 0;
	  pseg->seg_head.seg_max_size = init_size;

     }

     return pseg;
}


int
cpy_segment_code( Segment_Code_t *dst, Segment_Code_t *src )
{

     int ret = cpy_segment( (Segment_t*) dst, (Segment_t*) src);

     if( ret )
     {
	  
	  return ret;
	  
     }

     memcpy( dst->seg_code_data, src->seg_code_data,
	     src->seg_head.seg_size * sizeof( src->seg_code_data[0] ) );

     return 0;
     
}




int
segment_add_text( Segment_Text_t **ppSeg, const char * text )
{

     if( !ppSeg || !(*ppSeg) || !text)
     {
	  /* insane arguments */

	  return -1;

     }

     if( (*ppSeg)->seg_head.seg_size == (*ppSeg)->seg_head.seg_max_size )
     {
	  /* grow */
	  Segment_Text_t *tmpSeg = new_segment_text( (*ppSeg)->seg_head
						         .seg_max_size << 1 );
	  if( ! tmpSeg )
	  {
	       perror(__func__);
	       return -1;
	  }
	  cpy_segment_text( tmpSeg, *ppSeg );
	  tmpSeg->seg_head.seg_max_size <<= 1;

	  del_segment_text( ppSeg ); // free resources
	  
	  *ppSeg = tmpSeg;
     }	  

     (*ppSeg)->seg_text_data[ (*ppSeg)->seg_head.seg_size ] = strdup( text );
     (*ppSeg)->seg_head.seg_size++;

     
     return 0;
}


int
segment_add_data( Segment_Data_t **ppSeg, int64_t data )
{

     if( !ppSeg || !(*ppSeg) )
     {
	  /* insane */
	  return -1;
     }

     if( (*ppSeg)->seg_head.seg_size == (*ppSeg)->seg_head.seg_max_size )
     {
	  /* grow */
	  Segment_Data_t *tmpSeg = new_segment_data( (*ppSeg)->seg_head
						         .seg_max_size << 1 );
	  if( ! tmpSeg )
	  {
	       perror(__func__);
	       return -1;
	  }

	  cpy_segment_data( tmpSeg, *ppSeg );
	  tmpSeg->seg_head.seg_max_size <<= 1;

	  del_segment_data( ppSeg ); // free resources
	  
	  *ppSeg = tmpSeg;
     }	  

     (*ppSeg)->seg_data_data[ (*ppSeg)->seg_head.seg_size ] = data;
     (*ppSeg)->seg_head.seg_size++;


     return 0;

}


int
segment_add_code( Segment_Code_t **ppSeg, Semantic_t code )
{

     if( !ppSeg || !(*ppSeg) )
     {
	  /* insane */
	  return -1;
     }

     if( (*ppSeg)->seg_head.seg_size == (*ppSeg)->seg_head.seg_max_size )
     {
	  /* grow */
	  Segment_Code_t *tmpSeg = new_segment_code( (*ppSeg)->seg_head
						         .seg_max_size << 1 );
	  if( ! tmpSeg )
	  {
	       perror(__func__);
	       return -1;
	  }

	  cpy_segment_code( tmpSeg, *ppSeg );
	  tmpSeg->seg_head.seg_max_size <<= 1;

	  del_segment_code( ppSeg ); // free resources
	  
	  *ppSeg = tmpSeg;
     }	  


     (*ppSeg)->seg_code_data[ (*ppSeg)->seg_head.seg_size ] = code;
     (*ppSeg)->seg_head.seg_size++;

     return 0;

}

