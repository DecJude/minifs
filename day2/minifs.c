#include <linux/init.h>	
#include <linux/module.h>
#include <linux/fs.h>

static void minifs_kill_superblock(struct super_block *sb)
{
	kill_aron_super(sb);
} 

struct file_system_type minifs_fs_type = {
    .owner = THIS_MODULE,
    .name = "minifs",
	.mount = minifs_mount,
	.kill_sb = minifs_kill_superblock,
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
