### mount 和 unmount 
文件系统有基于物理存储介质的(block-device based filesystem)，也有非物理设备的文件系统(non-physical filesystems)

Linux系统也提供了不同的 mount 和 kill_sb 方法，供不同类型的文件使用

https://linux-kernel-labs.github.io/master/labs/filesystems_part1.html

When mounting the file system, the kernel calls the mount function defined within the structure file_system_type. The function makes a set of initializations and returns a dentry (the structure struct dentry) that represents the mount point directory. Usually mount() is a simple function that calls one of the functions:

* **mount_bdev()**, which mounts a file system stored on a block device
* **mount_single()**, which mounts a file system that shares an instance between all mount operations
* **mount_nodev()**, which mounts a file system that is not on a physical device
* **mount_pseudo()**, a helper function for pseudo-file systems (sockfs, pipefs, generally file systems that can not be mounted)

These functions get as parameter a pointer to a function fill_super() that will be called after the superblock initialization to finish its initialization by the driver. An example of such a function can be found in the fill_super section.

When unmounting the file system, the kernel calls kill_sb(), which performs cleanup operations and invokes one of the functions:

* **kill_block_super()**, which unmounts a file system on a block device
* **kill_anon_super()**, which unmounts a virtual file system (information is generated when requested)
* **kill_litter_super()**, which unmounts a file system that is not on a physical device (the information is kept in memory)

An example for a file system without disk support is the ramfs_mount() function in the ramfs file system:
```
struct dentry *ramfs_mount(struct file_system_type *fs_type,
        int flags, const char *dev_name, void *data)
{
        return mount_nodev(fs_type, flags, data, ramfs_fill_super);
}
```
An example for a file system from disk is the minix_mount() function in the minix file system:
```
struct dentry *minix_mount(struct file_system_type *fs_type,
        int flags, const char *dev_name, void *data)
{
         return mount_bdev(fs_type, flags, dev_name, data, minix_fill_super);
}
```

### non-physical filesystem
minifs 计划先实现一个 non-physical 版本，再实现一个 block-device based 版本

本篇在day1的基础上，给完全没有功能只有名字的文件系统"minifs" 加上 mount 和 unmount， 基于non-physical的实现





