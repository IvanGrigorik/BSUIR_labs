#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>

static int my_init(void)
{
    printk(KERN_INFO "Hello world.\n");
    return  0;
}

static void my_exit(void)
{
    printk(KERN_INFO "Goodbye world.\n");

    return;
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shubham Dubey <shubham0d@protonmail.coms>");
MODULE_DESCRIPTION("PCI config MMIO driver");