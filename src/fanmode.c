#include <stdio.h>
#include <stdlib.h>

const char *AS_WMI_THERMAL="/sys/devices/platform/asus-nb-wmi/throttle_thermal_policy";

int fanmode_toggle(){
    FILE *fptr = fopen(AS_WMI_THERMAL, "r");
    if (fptr == NULL) {
        return -1;
    }
    short fanmode = (fgetc(fptr)- '0') + 1;
    fclose(fptr);
    if ( fanmode > 2 ) { fanmode = 0; }
    fptr = fopen(AS_WMI_THERMAL, "w");
    if ( fptr == NULL) {
        return -1;
    }
    fprintf(fptr, "%d\n", fanmode);
    fclose(fptr);
    return (int)fanmode;
}

int fanmode_id(){
    FILE *fptr = fopen(AS_WMI_THERMAL, "r");
    if ( fptr == NULL ) {
        return -1;
    }
    short fanmode = (fgetc(fptr)- '0');
    fclose(fptr);
    return (int)fanmode;
}
