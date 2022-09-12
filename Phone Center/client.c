#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int min (int nums[]) {
   int result = nums[0];
   for (int i = 0; i < 5; ++i) {
      if (nums[i] < result) {
         result = nums[i];
      }
   }
   return result;
}

int max (int nums[]) {
   int result = nums[0];
   for (int i = 0; i < 5; ++i) {
      if (nums[i] > result) {
         result = nums[i];
      }
   }
   return result;
}

int median (int nums[]) {
   int minNum;
   int newNums[5] = {0,0,0,0,0};
   int n = 0;
   newNums[n] = min(nums);
   ++n;
   for (int k = 0; k < 4; ++k) {
      minNum = max(nums);
      for (int i = 0; i < 5; ++i) {
         if (nums[i] < minNum && nums[i] > newNums[n - 1]) {
            minNum = nums[i];
         }
      }
      newNums[n] = minNum;
      ++n;
   }
   newNums[4] = max(nums);
   return newNums[2];
}

int main(int argc, char *argv[]) {

   int sock = 0;
   struct sockaddr_in serv_addr;
   
   sock = socket(AF_INET, SOCK_STREAM, 0);

   if (sock < 0) {
      printf("Socket creation error \n");
      return -1;
   }

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(atoi(argv[2]));

   if (inet_pton(AF_INET, argv[3], &serv_addr.sin_addr) <= 0) {
      printf("Invalid address \n");
      return -1;
   }
   if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      printf("Connection failed \n");
      return -1;
   }

   printf("cs230 HELLO male@umass.edu \n");

   char sendBuff[200];
   strcpy(sendBuff, "cs230 HELLO male@umass.edu \n");
   send(sock, sendBuff, strlen(sendBuff), 0);

   char receiveBuff[200];
   int len_msg = recv(sock, receiveBuff, 200, 0);
   receiveBuff[len_msg] = '\0';
   int counter = 0;
   char *strings[3];

   int nums[5];
   int result;

   strings[0] = strtok(receiveBuff, " ");
   counter += strlen(strings[0]) + 1;
   strings[1] = strtok(&receiveBuff[counter], " ");
   counter += strlen(strings[1]) + 1;
   strings[2] = strtok(&receiveBuff[counter], " ");
   counter += strlen(strings[2]) + 1;

   while (strcmp(strings[1], "STATUS") == 0) {
      char answer[100];
      for (int i = 0; i < 5; ++i) {
         nums[i] = atoi(strtok(&receiveBuff[counter], " "));
         counter += strlen(strtok(&receiveBuff[counter], " ")) + 1;
      }
      if (strcmp(strings[2], "min") == 0) {
         result = min(nums);
      }
      if (strcmp(strings[2], "max") == 0) {
         result = max(nums);
      }
      if (strcmp(strings[2], "median") == 0) {
         result = median(nums);
      }
      sprintf(answer, "cs230 %i\n", result);
      send(sock, answer, strlen(answer), 0);
      len_msg = recv(sock, receiveBuff, 200, 0);
      receiveBuff[len_msg] = '\0';
      counter = 0;
      strings[0] = strtok(receiveBuff, " ");
      counter += strlen(strings[0]) + 1;
      strings[1] = strtok(&receiveBuff[counter], " ");
      counter += strlen(strings[1]) + 1;
      strings[2] = strtok(&receiveBuff[counter], " ");
      counter += strlen(strings[2]) + 1;
   }
   printf("cs230 %s BYE\n", strings[1]);

   return 0;
}