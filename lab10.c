#include <linux/module.h>

static int init_lab10(void) {
    printk(KERN_INFO "Hello World!\n");
    return 0;
}

static void exit_lab10(void) {
    printk(KERN_INFO "Goodbye World!\n");
}

module_init(init_lab10);
module_exit(exit_lab10);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Qing-LKY");
MODULE_DESCRIPTION("Lab10: Net-filter");
MODULE_VERSION("0.0.1");
