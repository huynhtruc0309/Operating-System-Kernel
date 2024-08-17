// random_number_module.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>

#define DEVICE_NAME "random_device"

static int major;
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset);

static struct file_operations fops = {
    .read = device_read,
};

static int __init random_number_module_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", major);
        return major;
    }
    printk(KERN_INFO "Registered random device with major number %d\n", major);
    return 0;
}

static void __exit random_number_module_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Unregistered random device\n");
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    unsigned int rand_num;
    get_random_bytes(&rand_num, sizeof(rand_num));
    if (*offset > 0) {
        return 0;
    }
    if (copy_to_user(buffer, &rand_num, sizeof(rand_num))) {
        return -EFAULT;
    }
    *offset = sizeof(rand_num);
    return sizeof(rand_num);
}

module_init(random_number_module_init);
module_exit(random_number_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module that provides random numbers");
