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

void decode()
{
  CURL *curl = curl_easy_init();
  char *ptr;
  if(!curl)
  {
          printf("Error in curl inti\n");
          exit(1);
  }

  ptr = curl_easy_unescape(curl, query1, 0, 0);
  if(!ptr)
  {
          printf("Error in curl decode\n");
          exit(1);
  }

  snprintf(query2, CONTENTSIZE, "%s", ptr);
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
  decode();

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
     snprintf(content, CONTENTSIZE, "<p>Jai Mahishmati! Welcome to MPTEL Divisor:\n</p>"
                  "<p>The answer is: %s / %s = %d\n</p>Thanks for visiting!\n",
                        arg1, arg2, n1/n2);
  }
  
  printf("\r\n");
  printf("%s", content);
  fflush(stdout);

  return 0;
}
