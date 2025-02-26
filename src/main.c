#include "./cpuctl.h"
#include "./fanctl.h"
#include <string.h>

int main(int argc, char *argv[]){
    if ( argc != 2 ) {
        printf("\nUsage: command mode\n");
        printf("\nAvailable modes: -cpumodetoggle, -fanmodetoggle");
        printf("\nExample: asusctl -cpumodetoggle\n");
        return 1;
    }
    if ( strcmp(argv[1], "-cpumodetoggle") == 0 ) {
        cpumode_toggle();
    }else if ( strcmp(argv[1], "-fanmodetoggle") == 0 ) {
        fanmode_toggle();
    }
    return 0;
}
