## 注册文件系统

这是一个没有任何功能的文件系统，只是把一个名为 minifs 的东西注册到了系统的文件系统列表
```
cd day1/
make
insmod minifs.ko

cat /proc/filesystems

```
