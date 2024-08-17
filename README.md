# Linux Kernel Module and Syscall Hooking

This repository contains a project that demonstrates the creation of a Linux kernel module and hooking into system calls. The project is divided into two parts:

## Part 1: Random Number Generator Module

### Objective
The goal of this part is to understand Linux kernel modules and the file and device management system in Linux, as well as the interaction between user space and kernel space processes.

### Description
- A kernel module is developed to generate random numbers.
- This module creates a character device that allows user space processes to open and read random numbers.

### How to Use
1. Compile the module using the provided Makefile.
2. Load the module into the kernel using the `insmod` command.
3. A character device will be created, which can be accessed to read random numbers.

### Example
```bash
# Compile the module
make

# Insert the module into the kernel
sudo insmod random_number_module.ko

# Check if the device is created
ls /dev/random_device

# Read a random number
cat /dev/random_device
```

## Part 2: System Call Hooking

### Objective
This part focuses on hooking into system calls to monitor and log specific operations performed by processes.

### Description
The program hooks into the `open` and `write` system calls.

- **syscall `open`**: Logs the process name that opens a file and the name of the file being opened to `dmesg`.
- **syscall `write`**: Logs the process name, the name of the file being written to, and the number of bytes written to `dmesg`.

### How to Use
1. Compile the hooking module using the provided Makefile.
2. Load the module into the kernel using the `insmod` command.
3. The system calls `open` and `write` will now be monitored and logged.

### Example
```bash
# Compile the module
make

# Insert the hooking module into the kernel
sudo insmod syscall_hook_module.ko

# Check the logs using dmesg
dmesg | tail
```

## Reference
For more details on syscall hooking and kernel module development, refer to [Basics of Making a Rootkit - From Syscall to Hook](https://uwnthesis.wordpress.com/2016/12/26/basics-of-making-a-rootkit-from-syscall-to-hook).


## License
This project is licensed under the MIT License - see the LICENSE file for details.

