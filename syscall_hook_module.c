// syscall_hook_module.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/fdtable.h>
#include <linux/uaccess.h>
#include <linux/ptrace.h>
#include <linux/delay.h>

static asmlinkage long (*original_sys_open)(const char __user *, int, umode_t);
static asmlinkage long (*original_sys_write)(unsigned int, const char __user *, size_t);

static asmlinkage long hook_sys_open(const char __user *filename, int flags, umode_t mode) {
    long result;
    result = original_sys_open(filename, flags, mode);
    printk(KERN_INFO "sys_open: process %s opened file %s\n", current->comm, filename);
    return result;
}

static asmlinkage long hook_sys_write(unsigned int fd, const char __user *buf, size_t count) {
    long result;
    struct file *file;
    file = fget(fd);
    if (file) {
        result = original_sys_write(fd, buf, count);
        printk(KERN_INFO "sys_write: process %s wrote %zu bytes to file %s\n", current->comm, count, file->f_path.dentry->d_name.name);
        fput(file);
    } else {
        result = original_sys_write(fd, buf, count);
    }
    return result;
}

static int __init syscall_hook_module_init(void) {
    // Hooking code would go here
    printk(KERN_INFO "Syscall hook module loaded\n");
    return 0;
}

static void __exit syscall_hook_module_exit(void) {
    // Unhooking code would go here
    printk(KERN_INFO "Syscall hook module unloaded\n");
}

module_init(syscall_hook_module_init);
module_exit(syscall_hook_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module that hooks sys_open and sys_write");
