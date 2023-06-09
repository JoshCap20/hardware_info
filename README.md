# Hardware Information Tool

This C program retrieves and displays hardware information for your system, including CPU, memory, GPU, storage devices, and network interfaces. It works on Windows and Unix systems like macOS and Linux.

## Prerequisites

- GCC (GNU Compiler Collection) installed on your system.

## Compilation

To compile the program, run the following command:
make


This command will create an executable named `hardware_info`.

## Usage

To run the program, execute the compiled binary:

- On Unix-based systems (macOS and Linux):
./hardware_info

- On Windows:
hardware_info.exe

The program will display detailed hardware information for your system.
- CPU Information (Model, Clock Speed, # of Cores, # of Logical Processors, L2 Cache Size, L3 Cache Size)
- Motherboard Information (Make, Name, Serial Number)
- Physical Memory Information (Capacity, Speed)
- BIOS Information (Total Memory Size, Page Size)
- GPU Information (Model)
- Storage Devices
- Disk Partitions
- Network Interfaces
- System Uptime

## Cleaning up

To remove the compiled binary, run the following command:
make clean


## Note

Some commands may require administrative privileges. You may need to run the program as an administrator on Windows or use `sudo` on Unix-based systems.


