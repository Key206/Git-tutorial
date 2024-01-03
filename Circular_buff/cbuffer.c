#include  "cbuffer.h"

void cb_init(cbuffer_t *cb, void *buf, uint32_t size){
    cb->data = (uint8_t*)buf;
    cb->size = size;
    cb->reader = 0;
    cb->writer = 0;
    cb->overflow = 0;
    cb->active = true;
}
void cb_clear(cbuffer_t *cb){
    cb->reader = 0;
    cb->writer = 0;
    cb->overflow = 0;
}
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes){
    uint32_t received_bytes = 0;
    for(received_bytes = 0; received_bytes < nbytes; ++received_bytes){
        if(cb_data_count(cb) > 0){ 
            *((uint8_t*)buf + received_bytes) = *(cb->data + (cb->reader++));
            if(cb->reader > cb->size) cb->reader = 0;
        }else break;
    }
    return received_bytes;
}
uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes){
    uint32_t written_bytes = 0;
    for(written_bytes = 0; written_bytes < nbytes; ++written_bytes){
        if(cb_space_count(cb) > 0){
            *(cb->data + (cb->writer++)) = *((uint8_t*)buf + written_bytes);
            if(cb->writer > cb->size) cb->writer = 0;
        }else break;
    }
    return written_bytes;
}
uint32_t cb_data_count(cbuffer_t *cb){
    uint32_t data_count = cb->reader <= cb->writer ? (cb->writer - cb->reader) : 
                                                     (cb->writer + cb->size - cb->reader);
    return data_count;
}
uint32_t cb_space_count(cbuffer_t *cb){
    uint32_t space_count = cb->size - cb_data_count(cb) - 1;
    return space_count;
}
