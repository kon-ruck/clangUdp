#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


#define FNAME "./testimg.png"
#define SIZE 200
#define SENDADDR "192.168.0.104"

typedef struct {
  char name[100];
  char data[SIZE];
  int last_f;
} Header;

char *get_file_name(char *);

int main(){
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in addr;

  char file_path[100], *file_name;

  FILE *fp;

  // propaty to nanosleep
  struct timespec req, rem;

  req.tv_sec = 0;
  // req.tv_nsec = 1562500;
  req.tv_nsec = 3125000;
  // setting to UDP Server
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = inet_addr(SENDADDR);

  // stay for console input
  printf("input to Transport File:");
  scanf("%s", file_path);

  // you open file.
  fp = fopen(file_path, "rb");
  if(fp == NULL){
    printf("!! program is error because nasshing file\n");
    exit(1);
  }

  file_name = get_file_name(file_path);
  strcat(file_name, "_copy.png");

  // printf("%s\n", file_path);
  // printf("%s\n", file_name);

  printf("file transport is start.\n");
  printf("file is transporting....\n");

  // int i = 1;
  while (1)
  {
    // printf("%d\n", i);
    // i += 1;
    Header header = {NULL, NULL, 0};
    strcpy(header.name, file_name);
    int img_size = fread(header.data, sizeof(char), SIZE, fp);
    if (img_size == 0)
    {
      header.last_f = 1;
      nanosleep(&req, &rem);
      sendto(sock, &header, sizeof(header), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
      break;
    }
    nanosleep(&req, &rem);
    sendto(sock, &header, sizeof(header), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  }

  printf("file transport finished.\n");
  fclose(fp);
  return 0;
}

char *get_file_name(char *buf){
  if(*buf == NULL){
    printf("!! error to not input.\n");
    exit(1);
  }
  while (1)
  {
    if(*buf == '.' || *buf == '/'){
      buf += 1;
      get_file_name(buf);
    }else{
      // char *tmp = (char *)malloc(sizeof(char) * strlen(buf));
      // strcpy(tmp, buf);
      // return tmp;
      return buf;
    }
  }
}