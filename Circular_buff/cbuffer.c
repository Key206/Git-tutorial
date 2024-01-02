#include  "cbuffer.h"

void cb_init(cbuffer_t *cb, void *buf, uint32_t size){
    cb->data = buf;
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
    uint32_t receivedBytes;
    for(receivedBytes = 0; receivedBytes <= nbytes; ++receivedBytes){
        if(cb_data_count(cb) >= 0){ 
            *((uint8_t*)buf + receivedBytes) = *(cb->data + (cb->reader++));
        }
    }
    return receivedBytes;
}
uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes){
    uint32_t writtenBytes;
    for(writtenBytes = 0; writtenBytes <= nbytes; ++writtenBytes){
        if(cb_space_count(cb) >= 0){
            *(cb->data + (cb->writer++)) = *((uint8_t*)buf + writtenBytes);
        }
    }
    return writtenBytes;
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
