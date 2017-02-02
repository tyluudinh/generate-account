#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char WORDS_UPCASE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char WORDS_LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char WORDS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBERS[] = "0123456789";
const char NUMBERS_WORDS_UPCASE[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBERS_WORDS[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void result(char *charset)
{
    char prev = 0;
    do
    {
        printf("Press Enter to get Username and Password \n");
        char c = getchar();

        if(c == '\n' && prev == c)
        {
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
            printf("Username:%s\n", u);
            printf("Password:%s\n", p);   
            printf("Time to life: %d minutes\n", timeToLife * 30); 
            // break;
        }

        prev = c; 

        
    }while(1 > 0);
}
int main()
{
   int choice;
    do{
        printf("-----GENERATE USERNAME - PASSWORD - TIME TO LIFE----\n");
        printf("----------------[Mode 1] Only Numbers---------------\n");
        printf("----------------[Mode 2] Only Words-----------------\n");
        printf("----------------[Mode 3] Words and numbers----------\n");
        printf("----------------[Mode 4] Flight tickets-------------\n");
        printf("----------------------[5] Exit----------------------\n");
        printf("---------------Selection [1, 2, 3, 4, 5]:");
        scanf("%d", &choice);
        switch(choice)
           {
               case 1:
                printf("You chose mode 1 Only Numbers\n");
                result("0123456789");
                break;
             
               case 2:
                printf("You chose mode 2 Only Words\n");
               result("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
                break;
                  
               case 3:
                printf("You chose mode 3 Words and numbers\n");
               result("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
                 break;
             
               case 4:
                printf("You chose mode 4 Flight tickets\n");
                result("\0");
                 break;
               case 5:
                printf("GoodBye!\n");
                exit(0);
                 break;
               default:
                 printf("Wrong character. Print menu again\n\n");
                 break;
           }
    }while(choice != 5);
   return 0;
}
