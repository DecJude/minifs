#include <linux/init.h>	
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/time.h>

int minifs_fill_super(struct super_block *sb, void *data, int silent)
{
	printk(KERN_ERR "=====MINIFS %s \n", __func__);

	struct inode *root_inode;

	root_inode = new_inode(sb);
	root_inode->i_ino = 1;
	inode_init_owner(root_inode, NULL, S_IFDIR);
	root_inode->i_sb = sb;
	root_inode->i_atime = root_inode->i_mtime = root_inode->i_ctime = current_kernel_time();

	sb->s_root = d_make_root(root_inode);

	return 0;
}

static struct dentry *minifs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	return mount_nodev(fs_type, flags, data, minifs_fill_super);
}

static void minifs_kill_superblock(struct super_block *sb)
{
	kill_anon_super(sb);
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
	printk(KERN_ERR "=====MINIFS %s \n", __func__);
	unregister_filesystem(&minifs_fs_type);
}

module_init(minifs_init);
module_exit(minifs_exit);
MODULE_LICENSE("GPL");
