#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);

void HandleTCPClient(int clntSocket)
{
  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize;

  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("recv() failed");

  if (recvMsgSize == 1)
    printf("Received 1 byte as expected");
  else
    printf("Received unexpected number of bytes");

  if (echoBuffer[0] == 1)
    printf("Received expected value on first byte");

  while (recvMsgSize > 0)
  {
    if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
      DieWithError("send() failed");

    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("recv() failed");
  }

  close(clntSocket);
}
