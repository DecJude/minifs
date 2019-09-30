#include <linux/init.h>	
#include <linux/module.h>
#include <linux/fs.h>

struct file_system_type minifs_fs_type = {
    .owner = THIS_MODULE,
    .name = "minifs"
};

static int minifs_init(void)
{
    int ret;

    ret = register_filesystem(&minifs_fs_type);
    if (ret)
        printk("register minifs failed\n");

    return ret;
}
static void minifs_exit(void)
{
    unregister_filesystem(&minifs_fs_type);
}

module_init(minifs_init);
module_exit(minifs_exit);
MODULE_LICENSE("GPL");
