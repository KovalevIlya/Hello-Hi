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
  key_t key0, key1;
  printf("SERVER: start\n");
  key0 = ftok("./server_msg", 13);
  fd0 = msgget(key0, IPC_CREAT | 0666);
  key1 = ftok("./server_msg", 1);
  fd1 = msgget(key1, IPC_CREAT | 0666);
  msg.type = 1;
  msg.text[0] = 'H';
  msg.text[1] = 'e';
  msg.text[2] = 'l';
  msg.text[3] = 'l';
  msg.text[4] = 'o';
  msg.text[5] = '!';
  for (i = 6; i < 10; i++)
    msg.text[i] = '\0';
  msgsnd(fd0, &msg, 10, MSG_NOERROR);
  printf("SERVER: sent '%s'\n", msg.text);
  msgrcv(fd1, &msg, 10, 0, MSG_NOERROR);
  printf("SERVER: received '%s'\n", msg.text);
  msgctl(fd0, IPC_RMID, 0);
  msgctl(fd1, IPC_RMID, 0);
  printf("SERVER: finish\n");
  exit(0);
}
