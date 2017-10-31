/** definition of the segment data structure */
#ifndef SEGMENT_H
#define SEGMENT_H 1

#include <stdint.h>

typedef enum {
     ST_TEXT,
     ST_DATA,
     ST_CODE
} Segment_Type;



typedef struct {
     Segment_Type seg_type;
     uint32_t     seg_size;
     uint32_t     seg_max_size;
} Segment_t;


typedef struct {
     Segment_t    seg_head;
     const char *seg_text_data[1];
} Segment_Text_t;


typedef struct {
     Segment_t seg_head;
     int64_t seg_code_data[1];
} Segment_Code_t;


typedef struct {
     Segment_t seg_head;
     int64_t *seg_data_data[1];
} Segment_Data_t;



Segment_t * new_segment ( size_t payload_size);
void        del_segment ( Segment_t ** ppSeg );
#define _del_segment(PPSEG) del_segment( (Segment_t**) PPSEG )


Segment_Text_t * new_segment_text ( size_t i );
// void del_segment_text ( Segment_Text_t ** ppSeg );
#define del_segment_text(PPSEG) _del_segment(PPSEG) 


Segment_Data_t * new_segment_data ( size_t i );
// void del_segment_data ( Segment_Data_t ** ppSeg );
#define del_segment_data(PPSEG) _del_segment(PPSEG) 


Segment_Code_t * new_segment_code ( size_t i );
// void del_segment_code ( Segment_Code_t ** ppSeg );
#define del_segment_code(PPSEG) _del_segment(PPSEG) 


/* TODO */

#endif
