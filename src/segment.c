#include <stdio.h>
#include <stdlib.h>
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

     free( *ppseg );
     *ppseg = NULL;

}



Segment_Text_t *
new_segment_text( size_t init_size )
{
     Segment_Text_t * pseg =
	  (Segment_Text_t *) new_segment ( sizeof(char*) * init_size );

     if(pseg) {
	  
	  pseg->seg_head.seg_size = 0;
	  pseg->seg_head.seg_max_size = init_size;

     }

     return pseg;
}



Segment_Data_t *
new_segment_data( size_t init_size )
{
     Segment_Data_t * pseg =
	  (Segment_Data_t *) new_segment ( sizeof(int64_t) * init_size );

     if(pseg) {
	  
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
	  
	  pseg->seg_head.seg_size = 0;
	  pseg->seg_head.seg_max_size = init_size;

     }

     return pseg;
}


