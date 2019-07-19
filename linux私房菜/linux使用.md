[TOC]
# linux常用指令
|指令|说明|
|---|---|
|alias|设置别名|
|unalias|删除别名|
|mount|挂载；查看挂载信息|
|umount|取消挂载|
|ctrl+c|终止命令|
|ctrl+d|键盘结束EOF；可取代exit|
|cat|读取文件内容|
|chgrp|改变文件群组|
|chown|改变文件拥有者|
|chmod|改变文件权限|
|cp|文件复制|
|history|从查看历史指令|
|sync|将数据同步写入硬盘|
|reboot|重启|
|【tab】|命令补全；文件补齐|
|cd|变更目录|
|pwd|显示目前目录路径|
|mkdir|创建新目录|
|rmdir|删除空目录|
|ps|查看系统中的进程|
|top|动态显示系统进程|
|nice|按用户指定优先级运行|
kill|终止进程|
|bg|将挂起进程释放到后台运行|
# vim常用指令

| 指令 |说明|
|:---:|---|
|:open|打开文件|
|:split :sp|水平显示两个文件|
|：vsplit ：sp|竖直显示两个文件|
|ctrl+6|下一个文件|
|：bn|下一个文件|
|:bp|上一个文件|
|ctrl+w+方向键（hjkl）|切换窗格|
|ctrl+ww|切换到下一窗格|
|v|可视化块选择|
|y|复制|
|p|粘贴|
|d|剪切|

## vim剪贴板

1. vim含有多个粘贴版，分别为`0-9、a、+、"`;使用`:reg`查看各个粘贴版的内容：、

2. 使用`"Ny`将数据复制到指定粘贴版，N为粘贴板编号，使用y默认将数据复制到`"`粘贴版

3. `“`为临时粘贴版，可以直接用y和p进行复制粘贴

4. +粘贴板是系

5. 复制粘贴基本指令

   ```
   yy   Y //复制游标所在行
   2yy		y2y  //复制两行，以此类推
   y^		y0 		//复制至行首，不含游标所在字元
   y$				//复制至行尾，含所在字元
   yw				//复制一个word
   y2w				//复制两个字
   yG				//复制至档尾
   ynG	nyG			//复制到第n行
   y1G				//复制至档首
   p				//粘贴至游标后
   P				//粘贴至游标前
   ```

6. 剪切。 与粘贴类似

### vim调试



# linux使用中遇到的问题


- [x] linux与windows共享统一分区时，linux无法修改分区内容
>  关闭windows的快速启动，快速启动可以在电源计划中的电源键设置中设置
- [ ] linux修改文件权限
- [x] 修改文件名
> mv oldname newname
- [x] vim打开多个文件
> vim file1 file2   
> :open file2

- [x] vim无法输入任何信息

  > 误按了`ctrl+s`阻断了终端输出
  >
  > 按下`ctrl+q`恢复终端输出

- [ ] 软件安装失败

```
在处理时有错误发生：
 linux-firmware
 initramfs-tools
E: Sub-process /usr/bin/dpkg returned an error code (1)
```

- 错误原因： 内核软件包过多，空间不足
- 解决方法：删除旧的内核软件包

```pascal
uname -a 	//查看当前*Ubuntu*系统使用的内核版本*
//结果
Linux hostname 3.0.0-16-generic
#29-Ubuntu SMP Tue Feb 14 12:49:42 UTC 2012i686 i686 i386 GNU/Linux
//3.*删除多余内核：
sudo apt-get purge linux-headers-3.0.0-12 linux-image-3.0.0-12-generic 
# 更新*grub*：*
sudo update-grub
```





