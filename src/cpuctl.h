#ifndef CPUCTL_H
#define CPUCTL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "./notify.h"

unsigned long read_freq(const char *CPUDIR,int cpu_num, char *filename ){
    char readfile[100];
    int chars_written = snprintf(readfile, sizeof(readfile), "%s/cpu%d/cpufreq/%s",CPUDIR,cpu_num,filename);
    if ( chars_written < 0 || chars_written > sizeof(readfile) ) {
        fprintf(stderr, "unknown file to read.\n");
        return NULL;
    }
    FILE *fptr = fopen (readfile, "r");
    if ( fptr == NULL ) {
        fprintf(stderr, "failed.\n");
        return NULL;
    }
    unsigned long freq;
    if ( fscanf(fptr, "%lu", &freq ) != 1 ) {
        fprintf(stderr, "Error: reading from file: %s\n",readfile);
        return NULL;
    }
    fclose(fptr);
    return freq;
}

void write_freq(const char *CPUDIR, int cpu_num, unsigned long freq){
    char writefile[100];
    int chars_written = snprintf(writefile, sizeof(writefile), "%s/cpu%d/cpufreq/scaling_max_freq",CPUDIR,cpu_num);
    if ( chars_written < 0 || chars_written > sizeof(writefile) ) {
        fprintf(stderr, "unknown file to write\n.");
        return;
    }
    FILE *fptr = fopen (writefile, "w");
    if ( fptr == NULL ) {
        fprintf(stderr, "Error: writing to file: %s\n",writefile);
        return;
    }
    fprintf(fptr,"%lu",freq);
    fclose(fptr);
}

void cpumode_toggle(){
    const char *MODES[] = {"powersave","balanced","turbo"};
    short mode_idx; 
    const char *CPUDIR = "/sys/devices/system/cpu";
    long num_cores = sysconf(_SC_NPROCESSORS_CONF);
    if ( num_cores == -1 ) {
        perror("Can't get core numbers");
        return;
    }
    for ( int cpu_num = 0; cpu_num < num_cores; cpu_num++ ){
        char filename[100];
        unsigned long max_freq  = read_freq(CPUDIR,cpu_num,"cpuinfo_max_freq");
        unsigned long min_freq  = read_freq(CPUDIR,cpu_num,"cpuinfo_min_freq");
        unsigned long base_freq  = read_freq(CPUDIR,cpu_num,"base_frequency");
        unsigned long current_max_freq  = read_freq(CPUDIR,cpu_num,"scaling_max_freq");

        if ( current_max_freq == min_freq ) {
            current_max_freq = base_freq;
            mode_idx=1;
        } else if ( current_max_freq == base_freq ) {
            current_max_freq = max_freq;
            mode_idx=2;
        } else if ( current_max_freq == max_freq ) {
            current_max_freq = min_freq;
            mode_idx=0;
        }
        write_freq(CPUDIR,cpu_num,current_max_freq);
    }
    //char *NAME="ASUS Control";
    //uint32_t ID=0;
    //char *ICON="";
    //char *BODY="";
    //int32_t EXPIRE=2000;
    char SUMMARY[16];
    snprintf(SUMMARY, sizeof(SUMMARY),"CPU: %s",MODES[mode_idx]);
    
    send_notification("ASUS Control",0,"",SUMMARY,"",2000);
}

#endif
