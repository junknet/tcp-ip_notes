## TCP/IP  笔记



## IO分流

- 概念：读写流分离 （流概念：读取一点点，立刻处理一点点，例如MP4实时解码，一点点字节长度小于人类最高分辨率{视觉处理速度}，看起来连续，反例：等待4GB视频全部下载至内存，解码，播放）

- 优点 

  - 分离读写，代码结构优雅
  - 只读只写的FILE指针提速
  - 区分IO缓冲提速

- 半关闭问题

  <img src="README.assets/image-20210221174043895.png" alt="image-20210221174043895" style="zoom: 50%;" />![image-20210221174110250](README.assets/image-20210221174110250.png)

  **单纯调用fclose 转换的FILE指针，直接关闭套接字**

<img src="README.assets/image-20210221174515011.png" alt="image-20210221174515011" style="zoom:50%;" />

复制文件描述符，并且close，也并非进入半关闭状态。可以操作上面的文件描述符进行IO输出。（未发送EOF） 	