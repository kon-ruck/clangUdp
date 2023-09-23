#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

char *get_file_name(char *buf){
  if(*buf == NULL){
    printf("error to not input.\n");
    exit(1);
  }
  while (1)
  {
    if(*buf == '.' || *buf == '/'){
      buf += 1;
      get_file_name(buf);
    }else{
      return buf;
    }
  }
}

int main(){
  char tmp[100], n[100];
  printf("入力してください:");
  scanf("%s", tmp);
  char *rc, *rc2;
  rc = get_file_name(tmp);
  // strcpy(n, rc);
  rc2 = (char *)malloc(sizeof(char) * strlen(rc));
  strcpy(rc2, rc);
  strcat(rc, "_copy.png");
  // printf("%s\n", tmp);
  // char rc[100] = (char)get_file_name(tmp);
  printf("%s\n", rc);
}