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
     // TODO
} Runtime_State_t;


typedef void (*Semantic_t)(Runtime_State_t *);


typedef struct {
     Segment_Type seg_type;
     uint32_t     seg_size;
     uint32_t     seg_max_size;
} Segment_t;


typedef struct {
     Segment_t seg_head;
     char     *seg_text_data[];
} Segment_Text_t;


typedef struct {
     Segment_t  seg_head;
     Semantic_t seg_code_data[];
} Segment_Code_t;


typedef struct {
     Segment_t seg_head;
     int64_t   seg_data_data[];
} Segment_Data_t;



Segment_t * new_segment ( size_t payload_size );
void        del_segment ( Segment_t ** ppSeg );
int         cpy_segment ( Segment_t * dst, const Segment_t * src );
#define _del_segment(PPSEG) del_segment( (Segment_t**) PPSEG )
#define _cpy_segment(PDST, PSRC, S) \
     cpy_segment( ((Segment_t*) PDST), ((Segment_t*) PSRC), S ) 
Segment_t * segment_concat ( Segment_t * pFst, Segment_t * pSnd ); 
#define _segment_concat(T, PSEG1, PSEG2) \
     ((T) segment_concat( ((Segment_t*) PSEG1), ((Segment_t*) PSEG2) ))


Segment_Text_t * new_segment_text ( size_t i );
void del_segment_text ( Segment_Text_t ** ppSeg );
int cpy_segment_text ( Segment_Text_t * dst, const Segment_Text_t * src );
int segment_add_text ( Segment_Text_t **ppSeg, const char * text );
#define segment_text_concat(SEG1, SEG2) \
     _segment_concat(Segment_Text_t*, SEG1, SEG2)


Segment_Data_t * new_segment_data ( size_t i );
#define del_segment_data(PPSEG) _del_segment(PPSEG) 
int     cpy_segment_data(Segment_Data_t *dst, Segment_Data_t *src);
int segment_add_data ( Segment_Data_t **ppSeg, int64_t data);
#define segment_data_concat(SEG1, SEG2) \
     _segment_concat(Segment_Data_t*, SEG1, SEG2)


Segment_Code_t * new_segment_code ( size_t i );
#define del_segment_code(PPSEG) _del_segment(PPSEG) 
int     cpy_segment_code(Segment_Code_t *dst, Segment_Code_t *src);
int segment_add_code ( Segment_Code_t **ppSeg, Semantic_t code);
#define segment_code_concat(SEG1, SEG2) \
     _segment_concat(Segment_Code_t*, SEG1, SEG2)


/* TODO */

#endif
