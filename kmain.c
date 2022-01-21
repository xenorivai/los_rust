#include "fb.h"
#include "serial_port.h"

#define SERIAL_COM1_PORT 0x3F8

void configure_default(unsigned int port){
    serial_configure_baud_rate(port, 2);
    serial_configure_line(port);
    serial_configure_fifo(port);
    serial_configure_modem(port);

}

int main(){
    unsigned int len = 10;
    char buf[10] = "Hello Neo!";

    fb_clear(FB_MAGENTA);
    fb_write(buf, len);

    configure_default(SERIAL_COM1_PORT);

    if (serial_is_transmit_fifo_empty(SERIAL_COM1_PORT)!=0){
        outb(SERIAL_COM1_PORT, 'A');
    }

    return 0;
}
