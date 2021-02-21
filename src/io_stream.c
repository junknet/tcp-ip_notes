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