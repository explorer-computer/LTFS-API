关于此版本:


1.可以查看磁带/磁带机信息
2.可以查看磁头位置
3.可以设置磁带块大小(暂不支持修改磁带机信息)
4.可以装载/卸载磁带(包括锁定/解锁磁带弹出机制)
5.获取磁带机状态
6.写/读磁带数据(暂不支持写文件，只支持写入字符串)
7.可以长/短擦除磁带

注意事项:

1.块大小一定要设置为65536字节，只有支持可变长度块模式的磁带机才能设置为0！
2.写数据/读数据记得勤查磁头位置
3.别轻易擦除磁带！

使用方法:

输入gettapestatus查询设备状态
输入gettapepost获取磁头位置的块地址(分高低位)
输入settapepost设置磁头位置的块地址(分高低位,输入分区直接输入0,别输入其它数字)
输入write在当前磁头位置的块地址写入字符串(字符串大小不得超过65535字节!)
输入read读取磁头当前块地址的数据(65536字节)
输入gettapeinfo、getdriveinfo获取磁带/磁带机信息
输入settapeblocksiz设置磁带块大小
load加载磁带
unload卸载磁带
lock锁定磁带弹出机制
unlock解锁磁带弹出机制
erasetape擦除磁带。(erasetype为0时:在开头写一个数据结束标示 为1时,从头到尾擦除)

Version 0.0.1(Tape Console)
Copyright (C) 2022  explorer-computer
