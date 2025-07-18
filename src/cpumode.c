#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CPUFREQ_PATH "/sys/devices/system/cpu/cpufreq/"
const char* CPU_MAX_FILE="/sys/devices/system/cpufreq/policy0/cpuinfo_max_freq";
const char* CPU_MIN_FILE="/sys/devices/system/cpufreq/policy0/cpuinfo_min_freq";
const char* CPU_BASE_FILE="/sys/devices/system/cpufreq/policy0/base_frequency";
const char* SCALING_MAX_FILE="/sys/devices/system/cpufreq/policy0/scaling_max_freq";

unsigned long read_freq(const char *path) {
    FILE *fptr = fopen(path, "r");
    if ( !fptr ) {
        perror(path);
        exit(255);
    }
    char buf[32];
    if ( !fgets(buf, sizeof(buf), fptr)) {
        fclose(fptr);
        exit(255);
    }
    fclose(fptr);
    return strtoul(buf, NULL, 10);
}

void write_freq(const char *path, unsigned long freq) {
    FILE *fptr = fopen (path, "w");
    if ( fptr == NULL ) {
        perror(path);
        exit(255);
    }
    if ( fprintf(fptr, "%lu\n", freq) < 0 ) {
        perror("Can't write");
        fclose(fptr);
        exit(255);
    }
    fclose(fptr);
}

int cpumode_toggle(){
    unsigned long freqs[3]; //min,base,max
    freqs[0] = read_freq(CPUFREQ_PATH "/policy0/cpuinfo_min_freq");
    freqs[1] = read_freq(CPUFREQ_PATH "/policy0/base_frequency");
    freqs[2] = read_freq(CPUFREQ_PATH "/policy0/cpuinfo_max_freq");
    unsigned long cpumax_current = read_freq(CPUFREQ_PATH "/policy0/scaling_max_freq");
    int index=0;

    for ( int i=0; i < 3; i++){
        if ( cpumax_current == freqs[i] ) {
            index = (i+1) % 3;
            if ( cpumax_current != freqs[index] ) {
                break;
            }
        }
    }
    cpumax_current=freqs[index];
        
    int cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    if ( cpu_count < 1 ) {
        return -1;
    }
    
    char path[128];
    for ( int i = 0; i < cpu_count; i++) {
        snprintf(path, sizeof(path), CPUFREQ_PATH "/policy%d/scaling_max_freq", i);
        write_freq(path, cpumax_current);
    }
    return index;
}
int cpumode_id(){
    unsigned long freqs[3]; //min,base,max
    freqs[0] = read_freq(CPUFREQ_PATH "/policy0/cpuinfo_min_freq");
    freqs[1] = read_freq(CPUFREQ_PATH "/policy0/base_frequency");
    freqs[2] = read_freq(CPUFREQ_PATH "/policy0/cpuinfo_max_freq");
    unsigned long cpumax_current = read_freq(CPUFREQ_PATH "/policy0/scaling_max_freq");
    
    for ( int i = 0; i < 3; i++ ) {
        if ( cpumax_current <= freqs[i] ) {
            return i;
        }
    }
    return -1;
}
