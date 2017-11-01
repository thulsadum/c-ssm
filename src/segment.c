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
segment_add_text( Segment_Text_t **ppSeg, const char * text )
{

     // TODO add growth

     if( !ppSeg || !(*ppSeg) || !text)
     {
	  /* insane arguments */

	  return -1;

     }

     (*ppSeg)->seg_text_data[ (*ppSeg)->seg_head.seg_size ] = strdup( text );
     (*ppSeg)->seg_head.seg_size++;

     
     return 0;
}


int
segment_add_data( Segment_Data_t **ppSeg, int64_t data )
{

     // TODO add growth
     if( !ppSeg || !(*ppSeg) )
     {
	  /* insane */
	  return -1;
     }

     (*ppSeg)->seg_data_data[ (*ppSeg)->seg_head.seg_size ] = data;
     (*ppSeg)->seg_head.seg_size++;

     return 0;

}


int
segment_add_code( Segment_Code_t **ppSeg, Semantic_t code )
{

     // TODO add growth
     if( !ppSeg || !(*ppSeg) )
     {
	  /* insane */
	  return -1;
     }

     (*ppSeg)->seg_code_data[ (*ppSeg)->seg_head.seg_size ] = code;
     (*ppSeg)->seg_head.seg_size++;

     return 0;

}

