# Operating-System-Kernel
## Problem Statement

- Part 1: The objective is to understand Linux kernel modules, the file and device management system in Linux, and the interaction between user space and kernel space processes.

Write a module that generates random numbers.
This module will create a character device to allow processes in user space to open and read random numbers.

- Part 2: A program that hooks into a system call:

syscall open: Log the process name that opens a file and the name of the file being opened to dmesg.
syscall write: Log the process name, the name of the file being written to, and the number of bytes written to dmesg.
Reference Link: https://uwnthesis.wordpress.com/2016/12/26/basics-of-making-a-rootkit-from-syscall-to-hook
