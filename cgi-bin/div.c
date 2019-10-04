#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <curl/curl.h>

#define BUFSIZE 16
#define CONTENTSIZE 1024


char *buf, *p;
char query1[CONTENTSIZE];
char query2[CONTENTSIZE];

void hex_decoding()
{
  int temp1=0;
  int temp2=0;
  int len=strlen(query1);
  /* hex-encoding for input query*/
  temp1 = 0;
  while(query1[temp1] != '\0') {
      int num;
      if(temp1 + 1 < len){
          if ((query1[temp1] >= '0' && query1[temp1] <= '9') && (query1[temp1+1] >= '0' && query1[temp1+1] <= '9')){
              num = (query1[temp1]-'0')*16 + (query1[temp1+1]-'0');
          }
          else if ((query1[temp1] >= '0' && query1[temp1] <= '9') && (query1[temp1+1] >= 'a' && query1[temp1+1] <= 'f')){
            num = (query1[temp1]-'0')*16 + (query1[temp1+1]-'a'+ 10);
          }
          else if ((query1[temp1] >= 'a' && query1[temp1] <= 'f') && (query1[temp1+1] >= '0' && query1[temp1+1] <= '9')){
            num = (query1[temp1]-'a'+ 10)*16 + (query1[temp1+1]-'0');
          }
          else if ((query1[temp1] >= 'a' && query1[temp1] <= 'f') && (query1[temp1+1] >= 'a' && query1[temp1+1] <= 'f')){
            num = (query1[temp1]-'a'+ 10)*16 + (query1[temp1+1]-'a'+10);
          }
          query2[temp2++] = num + '\0';
          temp1 += 2;
      }
      else{
        break;
      }          
  }
}

char *decode(char *buf)
{
  CURL *curl = curl_easy_init();
  char *ptr;
  if(!curl)
  {
          printf("Error in curl inti\n");
          exit(1);
  }

  ptr = curl_easy_unescape(curl, buf, 0, 0);
  if(!buf)
  {
          printf("Error in curl decode\n");
          exit(1);
  }

  snprintf(query2, CONTENTSIZE, "%s", ptr);
  return ptr;
}

int main() {
  
  char arg2[BUFSIZE];
  char arg1[BUFSIZE];
  char content[CONTENTSIZE];

  int n1, n2;

  memset(arg1, 0 , BUFSIZE);
  memset(arg2, 0 , BUFSIZE);
  memset(query1, 0 , CONTENTSIZE);
  memset(query2, 0 , CONTENTSIZE);
  memset(content, 0 , CONTENTSIZE);
  
  if (getenv("QUERY_STRING") == NULL) {
    exit(1);
  }

  snprintf(query1, CONTENTSIZE, "%s\n", getenv("QUERY_STRING"));
  //hex_decoding();
  //snprintf(query2, CONTENTSIZE, "%s\n", getenv("QUERY_STRING"));
  decode(query1);

  p = strchr(query2, '&');
  *p = '\0';

  strcpy(arg1, query2);
  strcpy(arg2, p+1);

  if (strlen(arg1)>=5 || strlen(arg2) >= 5){
    snprintf(content, CONTENTSIZE ,"Welcome to Division.com: THE Internet Division portal.\n<p>Sorry! Max Value exceeded.\n<p>Try with lesser value.\n<p>Thanks for visiting! %p\n", arg2);      
  }
  else{
    n1 = atoi(arg1);
    n2 = atoi(arg2);
    snprintf(content, CONTENTSIZE ,"Welcome to Division.com: THE Internet Division portal.\n<p>The answer is: %s / %s = %d, %p\n<p>Thanks for visiting!\n", 
      arg1, arg2, n1/n2, arg2);  
  }
  
  printf("\r\n");
  printf("%s", content);
  fflush(stdout);

  return 0;
}
