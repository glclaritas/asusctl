#include <stdio.h>
#include <string.h>
#include "./mode.h"

int main(int argc, char *argv[]){
    if ( argc != 2 ) {
        printf("\nUsage: command mode\n");
        printf("\nAvailable modes:  --cpumodetoggle, --fanmodetoggle");
        printf("\n                  --display");
        printf("\nExample: asusctl --cpumodetoggle\n");
        printf("Need Nerd Fonts.\n");
    }
    if ( strcmp(argv[1], "--cpumodetoggle") == 0 ) {
        cpumode_toggle();
    }else if ( strcmp(argv[1], "--fanmodetoggle") == 0 ) {
        fanmode_toggle();
    }else if ( strcmp(argv[1], "--display") == 0 ) {
        const char *cpu_display[]={"L","M","H"};
        const char *fan_display[]={"󱑳","󱑴","󱑲"};
        printf("%s %s\n", cpu_display[cpumode_id()], fan_display[fanmode_id()]);
    }
    return 0;
}
