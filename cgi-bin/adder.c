#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <curl/curl.h>

#define BUFSIZE     1024 
#define OUTPUT_SIZE 2048 * 10 + 1
#define RETURN_SIZE 2048 * 11

char *decode(char *buf)
{
  CURL *curl = curl_easy_init();
  if(!curl)
  {
	  printf("Error in curl inti\n");
	  exit(1);
  }

  buf = curl_easy_unescape(curl, buf, 0, 0);
  if(!buf)
  {
          printf("Error in curl decode\n");
	  exit(1);
  }

  return buf;
}

int main() {
  
  char *buf;
  char *arg1, *arg2;
  char content[RETURN_SIZE];
  char buffer_init[BUFSIZE];
  char buffer_final[OUTPUT_SIZE+1] = {0};
  char buffer_extra[BUFSIZE];

  //Read input from env variable set by tiny.c
  if ((buf = getenv("QUERY_STRING")) == NULL) {
    exit(1);
  }
  
  //Decode input from url encoding
  arg1 = decode(buf);

  //Find second arg
  arg2 = strchr(arg1, '&');
  if(!arg2 || strlen(arg2+1) == 0)
  {
	  printf("Adder: Requires 2 args\n");
	  exit(1);
  }

  *arg2 = 0;
  arg2++;

  //make command to add numbers
  snprintf(buffer_init, BUFSIZE, "expr %s + %s", arg1, arg2);

  //it will hold the remaining capacity of buffer_final
  int rem = OUTPUT_SIZE;

  //Execute the command. it will return fp to read the output
  FILE *fd = popen(buffer_init, "r"); 
  if(!fd)
  {
	  printf("Adder: Could not execute cmd '%s'\n", buffer_init);
	  exit(1);
  }

  //read the command output line by line
  while (rem > 0 && (buf = fgets(buffer_extra, BUFSIZE, fd)) != NULL)
  {
    strncat(buffer_final, buf, rem);
    rem = OUTPUT_SIZE - strlen(buffer_final);
  }

  snprintf(content, RETURN_SIZE, "<p>Jai Mahishmati! Welcome to MPTEL Adder:\n</p>"
		  "<p>The answer is: %s + %s = %s\n</p>Thanks for visiting!\n", 
	  		arg1, arg2, buffer_final);

  printf("\r\n");
  printf("%s", content);
  fflush(stdout);
  exit(0);
}
