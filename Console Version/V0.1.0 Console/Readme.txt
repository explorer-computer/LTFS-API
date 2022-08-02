关于此版本:


1.解决了一些bug
2.可以在磁带里存储文件

注意事项:

1.块大小一定要设置为65536字节！

使用方法:

输入gettapestatus查询设备状态
输入gettapepost获取磁头位置的块地址(分高低位)
输入settapepost设置磁头位置的块地址(分高低位,别输入其它数字)
输入gettapeinfo、getdriveinfo获取磁带/磁带机信息
输入settapeblocksiz设置磁带块大小
load加载磁带
unload卸载磁带
lock锁定磁带弹出机制
unlock解锁磁带弹出机制
erasetape擦除磁带。(erasetype为0时:在开头写一个数据结束标示 为1时,从头到尾擦除)
list列出当前路径的文件和文件夹
cd进入文件夹
cd..退出当前文件夹
copyfile将文件复制到当前磁带路径
delete删除当前磁带路径的文件
getfile把当前磁带路径的文件复制到电脑
rename重命名磁带中的文件
move将磁带中的文件移到磁带的其他路径

Version 0.1.0(Tape Console)
