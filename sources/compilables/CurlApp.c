#include <stdio.h>
#include <stdlib.h>
#include "curl.h"

#define CURL_OK 0

struct string {
  char *ptr;
  size_t len;
};

/**
 *  Initiallize a string
 */
void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(sizeof(char) * s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}
/**
 * Call back function for curl
 */
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s){
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}
/**
 *  Scrap the URL in argument
 */
void scrap(char* url) {
  //char* url   = "http://google.com";
    CURL *curl = curl_easy_init();
    if(curl) {
        struct string s;
        init_string(&s);

        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);

        if(res == CURL_OK){
            saveIntoFile(s.ptr, url);
        }else{
            const char*  returnMessage = curl_easy_strerror(res);
            printf("%s", returnMessage);
        }


        curl_easy_cleanup(curl);    //free of curl

    }
}

void saveIntoFile(char* str, char* url){
    FILE* f;
    //printf("aaaaaaaaaaa");
    unsigned int urlSize = strlen(url);
    char* filename = malloc(sizeof(char) * (urlSize + 5));

    strcat(filename, url);
    strcat(filename, ".html");
    printf("\n%s\n", filename);

    f = fopen(filename, "w");

    if(f != NULL){
        printf("OUi");
        fprintf(f, str);
    } else {
        printf("Nay");
    }

    fclose(f);
}
