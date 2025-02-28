# Compatible Devices
Asus laptops with asus-nb-wmi kernel module maybe. ***IDK THB :D***  
Works for ASUS ROG G531GU. i7-9750H CPU.

## BUILDING

**Void Linux:**

    xbps-install make cmake gcc dbus-devel
    mkdir build && cd build
    cmake .. && make
## Requirements
To grant write permissions for the asusctl to work, add this lines to rc.local.

    chmod o+w /sys/devices/platform/asus-nb-wmi/throttle_thermal_policy
    chmod o+w /sys/devices/system/cpu/cpu[0-9]*/cpufreq/scaling_max_freq
## Usage
    asusctl -cpumodetoggle
    asusctl -fanmodetoggle

