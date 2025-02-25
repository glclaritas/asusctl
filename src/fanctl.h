#ifndef FANCTL_H
#define FANCTL_H

#include <stdio.h>
#include <stdlib.h>
#include "./notify.h"

void fanmode_toggle(){
    const char *MODES[] = { "balanced", "turbo", "silent" };
    const char *AS_WMI_THERMAL="/sys/devices/platform/asus-nb-wmi/throttle_thermal_policy";
    FILE *fptr = fopen(AS_WMI_THERMAL, "r");
    if (fptr == NULL) {
        return;
    }
    short fanmode = (fgetc(fptr)- '0') + 1;
    fclose(fptr);
    if ( fanmode > 2 ) { fanmode = 0; }
    fptr = fopen(AS_WMI_THERMAL, "w");
    fprintf(fptr, "%d\n", fanmode);
    fclose(fptr);

    //char *NAME="ASUS Control";
    //uint32_t ID=0;
    //char *ICON="";
    //char *BODY="";
    //int32_t EXPIRE=2000;
    char SUMMARY[16];
    snprintf(SUMMARY, sizeof(SUMMARY),"Fan: %s",MODES[fanmode]);
    // NAME,ID,ICON,SUMMARY,BODY,EXPIRE
    send_notification("ASUS Control",0,"",SUMMARY,"",2000);

    return;
}
#endif
