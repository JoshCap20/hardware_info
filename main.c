#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

void execute_command(const char *cmd, const char *label) {
    FILE *fp;
    char buffer[128];

    fp = _popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to execute command\n");
        return;
    }

    printf("%s: ", label);
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    _pclose(fp);
}

void get_hardware_info() {
    printf("CPU Information:\n");
    execute_command("wmic cpu get Name /VALUE", "CPU Model");
    execute_command("wmic cpu get MaxClockSpeed /VALUE", "Max Clock Speed (MHz)");
    execute_command("wmic cpu get NumberOfCores /VALUE", "Number of Cores");
    execute_command("wmic cpu get NumberOfLogicalProcessors /VALUE", "Number of Logical Processors");
    execute_command("wmic cpu get L2CacheSize /VALUE", "L2 Cache Size (KB)");
    execute_command("wmic cpu get L3CacheSize /VALUE", "L3 Cache Size (KB)");

    printf("\nMotherboard Information:\n");
    execute_command("wmic baseboard get Manufacturer,Product,SerialNumber /FORMAT:LIST", "Motherboard");

    printf("\nBIOS Information:\n");
    execute_command("wmic bios get Manufacturer,Name,SerialNumber /FORMAT:LIST", "BIOS");

    printf("\nPhysical Memory Information:\n");
    execute_command("wmic memorychip get Capacity,Speed /FORMAT:LIST", "Memory Chip");

    printf("\nGPU Information:\n");
    execute_command("wmic path win32_VideoController get Name /VALUE", "GPU Model");

    printf("\nStorage Devices:\n");
    execute_command("wmic logicaldisk get Caption,Size,FreeSpace /FORMAT:LIST", "Logical Disk");

    printf("\nDisk Partitions:\n");
    execute_command("wmic partition get DeviceID,Type,Size /FORMAT:LIST", "Partition");

    printf("\nNetwork Interfaces:\n");
    execute_command("wmic nic where \"NetEnabled=true\" get Name,MACAddress,Speed /FORMAT:LIST", "Network Interface");

    printf("\nSystem Uptime:\n");
    execute_command("wmic os get LastBootUpTime /FORMAT:LIST", "Last Boot Up Time");
}

#else

void execute_command(const char *cmd, const char *label) {
    FILE *fp;
    char buffer[128];

    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to execute command\n");
        return;
    }

    printf("%s: ", label);
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

void get_hardware_info() {
    printf("CPU Information:\n");
    execute_command("sysctl -n machdep.cpu.brand_string", "CPU Model");
    execute_command("sysctl -n hw.cpufrequency_max", "Max Clock Speed (Hz)");
    execute_command("sysctl -n hw.physicalcpu_max", "Number of Cores");
    execute_command("sysctl -n hw.logicalcpu_max", "Number of Logical Processors");
    execute_command("sysctl -n hw.l2cachesize", "L2 Cache Size (Bytes)");
    execute_command("sysctl -n hw.l3cachesize", "L3 Cache Size (Bytes)");

    printf("\nMotherboard Information:\n");
    execute_command("system_profiler SPHardwareDataType | grep 'Model Name'", "Model Name");
    execute_command("system_profiler SPHardwareDataType | grep 'Serial Number'", "Serial Number");

    printf("\nBIOS Information:\n");
    execute_command("system_profiler SPHardwareDataType | grep 'Boot ROM Version'", "Boot ROM Version");
    execute_command("system_profiler SPHardwareDataType | grep 'SMC Version'", "SMC Version");

    printf("\nPhysical Memory Information:\n");
    execute_command("sysctl -n hw.memsize", "Total Memory Size (Bytes)");
    execute_command("sysctl -n hw.pagesize", "Page Size (Bytes)");

    printf("\nGPU Information:\n");
    execute_command("system_profiler SPDisplaysDataType | grep 'Chipset Model'", "GPU Model");

    printf("\nStorage Devices:\n");
    execute_command("df -h", "Disk Usage");

    printf("\nDisk Partitions:\n");
    execute_command("diskutil list", "Partition");

    printf("\nNetwork Interfaces:\n");
    execute_command("ifconfig -a | sed 's/[ \t].*//;/^$/d'", "Network Interface");

    printf("\nSystem Uptime:\n");
    execute_command("uptime", "Uptime");
}

#endif

int main() {
    get_hardware_info();
    return 0;
}
