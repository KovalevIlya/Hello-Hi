#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
  long type;
  char text[10];
};

void main(void)
{
  struct msgbuf msg;
  int fd0, fd1, i;
  key_t key;
  printf("CLIENT: start\n");
  key = ftok("./server_msg", 13);
  fd0 = msgget(key, 0);
  key = ftok("./server_msg", 1);
  fd1 = msgget(key, 0);
  msgrcv(fd0, &msg, 10, 0, MSG_NOERROR);
  printf("CLIENT: received '%s'\n", msg.text);
  msg.type = 1;
  msg.text[0] = 'H';
  msg.text[1] = 'i';
  msg.text[2] = '!';
  for (i = 3; i < 10; i++)
    msg.text[i] = '\0';
  msgsnd(fd1, &msg, 10, MSG_NOERROR);
  printf("CLIENT: sent '%s'\n", msg.text);
  printf("CLIENT: finish\n");
  exit(0);
}
