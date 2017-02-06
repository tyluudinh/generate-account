
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>

const char WORDS_UPCASE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char WORDS_LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char WORDS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBERS[] = "0123456789";
const char NUMBERS_WORDS_UPCASE[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBERS_WORDS[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char *getAccount(char *charset){
    srand(time(NULL));
    int timeToLife = rand() % 20 + 1;
    int  length = rand() % 5 + 5;
    char u[length], p[length];
    u[length] = '\0';
    p[length] = '\0';
    if (charset[0] == '\0')
    {
        length = 7;
        for (int i = 0; i < length; i++)
        {
            if (i < 3)
            {
                u[i] = WORDS_UPCASE[rand() % (int) (strlen(WORDS_UPCASE) - 1)];
                p[i] = WORDS_UPCASE[rand() % (int) (strlen(WORDS_UPCASE) - 1)];
            }else{
                u[i] = NUMBERS_WORDS_UPCASE[rand() % (int) (strlen(NUMBERS_WORDS_UPCASE) - 1)];
                p[i] = NUMBERS_WORDS_UPCASE[rand() % (int) (strlen(NUMBERS_WORDS_UPCASE) - 1)];
            }
        }

    }else{

        for (int i = 0; i < length; i++)
        {
            u[i] = charset[rand() % (int) (strlen(charset) - 1)];
            p[i] = charset[rand() % (int) (strlen(charset) - 1)];
        }   
    }
    char ttl[10];
    ttl[10] = '\0';
    snprintf(ttl, 10, "%d", timeToLife * 30);
    char result[100];
    result[100] = '\0';
    strcpy(result, "Username=");
    strcat(result, u);
    strcat(result, "&Password=");
    strcat(result, p);
    strcat(result, "&TimeToLife=");
    return strcat(result, ttl);
}
int menu() {
  int choice;
  printf("-----GENERATE USERNAME - PASSWORD - TIME TO LIFE----\n");
  printf("----------------[Mode 1] Only Numbers---------------\n");
  printf("----------------[Mode 2] Only Words-----------------\n");
  printf("----------------[Mode 3] Words and numbers----------\n");
  printf("----------------[Mode 4] Flight tickets-------------\n");
  printf("---------------Selection [1, 2, 3, 4]:");
  scanf("%d", & choice);
  switch (choice) {
  case 1:
    printf("You chose mode 1 Only Numbers\n");
    break;

  case 2:
    printf("You chose mode 2 Only Words\n");
    break;

  case 3:
    printf("You chose mode 3 Words and numbers\n");
    break;

  case 4:
    printf("You chose mode 4 Flight tickets\n");
    break;
  case 5:
    printf("GoodBye!\n");
    exit(0);
    break;
  default:
    printf("Wrong character. Print menu again\n\n");
    break;
  }
  return choice;
}
int main()
{
  int sock, bytes_recieved;  
  char send_data[1024],recv_data[1024];
  struct hostent *host;
  struct sockaddr_in server_addr;  
  host = gethostbyname("127.0.0.1");
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("Socket");
      exit(1);
  }
  server_addr.sin_family = AF_INET;     
  server_addr.sin_port = htons(5000);   
  server_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(server_addr.sin_zero),8); 
  if (connect(sock, (struct sockaddr *)&server_addr,
            sizeof(struct sockaddr)) == -1) {
      perror("Connect");
      exit(1);
  }
  int choice = menu();
  while(1){
      bytes_recieved=recv(sock,recv_data,1024,0);
      recv_data[bytes_recieved] = '\0';
      printf("\nServer response:  %s\n" , recv_data);
      printf("\n\nPress Enter to get Username and Password \n");
      char prev = 0;
      char c = getchar();
      putchar(c);
      char *x;
      if(c == '\n' && prev == c){
      }else{
        switch(choice){
          case 1:
            x = getAccount("0123456789");
            break;
          case 2:
            x = getAccount("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            break;
          case 3:
            x = getAccount("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            break;
          case 4:
            x = getAccount("\0");
            break;
      }
      int length = strlen(x);
      char ss[length];
      ss[length] = '\0';
      strcpy(ss, x);
      printf("\nSEND: %s ", ss);
      send(sock,ss,length, 0); 
      }
      prev = c; 
  }   
  return 0;
}