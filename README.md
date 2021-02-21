[TOC]

## TCP/IP  笔记



### IO分流

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

```c
#include <stdio.h>
#include <unistd.h>

int main() {
  int fd1, fd2;
  char str1[] = "hello";
  char str2[] = "world";
  fd1 = dup(1);
  fd2 = dup2(fd1, 7);
  printf("fd1: %d\n,fd2: %d\n", fd1, fd2);
  write(fd1, str1, sizeof(str1));
  write(fd2, str2, sizeof(str2));
  close(fd1);
  close(fd2);
}
```

调用` dup`复制文件描述符，`fdopen`(fd,"r"),打开只读模式，半关闭使用 `shutdown`() 函数 

```c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unistdio.h>
#define BUFF_SIZE 1024

int main(int argc, char *argv[]) {
  int server_socket, client_socket;
  FILE *readfp;
  FILE *writefp;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_size;
  char buf[BUFF_SIZE] = {0};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(argv[1]));

  bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_socket, 5);
  client_addr_size = sizeof(client_addr);
  client_socket =
      accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
  readfp = fdopen(client_socket, "r");
  writefp = fdopen(dup(client_socket), "w");
  fputs("from server", writefp);
  fputs("hello from client", writefp);
  fflush(writefp);
  shutdown(fileno(writefp), SHUT_WR);
  fclose(writefp);
  fgets(buf, sizeof(buf), readfp);
  fputs(buf, stdout);
  fclose(readfp);
  return 0;
}
```

