#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Hello_world");
MODULE_LICENSE("GPL");

static int hello_init(void)
{
        printk(KERN_INFO "alan: hello world\n");
        return 0;
}

static void hello_exit(void)
{
        printk(KERN_INFO "alan: Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);
