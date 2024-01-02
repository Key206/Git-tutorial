#include "cbuffer.h"

cbuffer_t cb;
uint8_t cb_buff[6];

int main(){
    cb_init(&cb, cb_buff, 5);
    cb_clear(&cb);
    char a[] = {0, 1, 2, 3, 4};
    cb_write(&cb, a, 5);
    char b[5];
    cb_read(&cb, b, 5);
    return 0;
}