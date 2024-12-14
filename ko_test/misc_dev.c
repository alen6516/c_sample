#include <linux/init.h>
#include <linux/module.h>

static struct miscdevice my_miscdev = {
    .minor  = 11,
    .name   = "misc_dev",
    .fops   = &mydev_fops,
};

static int __init init_modules(void)
{
    int ret;
    ret = misc_register(&my_miscdev);
    if (ret
}
