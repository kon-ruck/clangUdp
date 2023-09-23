#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>/*-pthread*/
#include <signal.h>
#include <string.h>


#define FCNAME "./testimg_copy.png"
#define SIZE 200

typedef struct {
  char name[100];
  char data[SIZE];
  int last_f;
} Header;

int main(){
  char buf[100];
  pthread_t thread1;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  int sock_a;
  struct sockaddr_in addr, send_addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  printf("server is start.\n");
  bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  // int i = 1;
  while (1)
  {
    // printf("%d\n", i);
    // i += 1;
    Header header;
    recvfrom(sock, &header, sizeof(header), 0, (struct sockaddr *)&send_addr, (int *)sizeof(struct sockaddr_in));

    FILE *fcp = fopen(header.name, "ab");
    if (fcp == NULL)
    {
      printf("!! program is error because can not create file\n");
      exit(1);
    }
    fseek(fcp, 0, SEEK_END);
    fwrite(header.data, SIZE, 1, fcp);
    fclose(fcp);
    // printf("%d\n", c);
    // c += 1;
    if(header.last_f == 1){
      break;
    }
  }

  printf("file is sened!\n");
  return 0;
}
