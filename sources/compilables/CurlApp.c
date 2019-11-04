#include <stdio.h>
#include <stdlib.h>
#include "curl.h"
#include "../headers/Color.h"
#include "../headers/Application.h"

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
 * Remove the headers of the urls
 * @param url
 */
int startSiteName(char* url){
    int ret = 0;

    if(url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p' &&
       url[4] == 's' && url[5] == ':' && url[6] == '/' && url[7] == '/'){
            ret = 8;
    } else if (url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p' &&
               url[4] == ':' && url[5] == '/' && url[6] == '/'){
            ret = 7;
    }
    return ret;
}
/**
 *  Create the allpath with a correct file name
 *  @param url to create the name
 */
char* makeFileName(char* url){
    unsigned int urlSize = strlen(url);
    char* filename = malloc(sizeof(char) * (urlSize + 20));
    //char filename[1000];
    char path[200] = {'r','e','s','s','o','u','r','c','e','s','\\','\0'};
    char extension[6] = {'.','h','t','m','l','\0'};

    int i = 0;
    int yFile = 0;

    while(path[i] != '\0'){
        filename[yFile] = path[i];
        i++;
        yFile++;
    }
    i = startSiteName(url);
    while(url[i] != '\0'){
       if(url[i] == '/' || url[i] == ':'){
            filename[yFile] = '-';
        }else{
            filename[yFile] = url[i];
        }
        i++;
        yFile++;
    }
    i = 0;
    while(i != 6){
        filename[yFile] = extension[i];
        i++;
        yFile++;
    }

    return filename;
}
/**
 * This function is used to save the content of the site into a file
 * @param char* str <- content of the site
 * @param char* url <- url of the site to name the file
 */
void saveIntoFile(char* str, char* url){
    FILE* f;
    char* filename = makeFileName(url);
    //printf("\n%s\n", filename);

    f = fopen(filename, "w");
    if(f != NULL){
        fprintf(f, str);
        color(LIGHT_GREEN, BLACK);
        printf("\n\t\t\t\t\Site Scrapped\n");
        color(WHITE, BLACK);
    } else {
        color(RED, BLACK);
        printf("\n\t\t\t\t\tFailed to create the file\n");
        color(WHITE, BLACK);
    }

    fclose(f);

    free(filename);
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
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);

        if(res == CURL_OK){
            saveIntoFile(s.ptr, url);
//          printf("%s", s.ptr);
        }else{
            const char*  returnMessage = curl_easy_strerror(res);
            color(RED, BLACK);
            printf("\n\t\t\t\t\t%s\n\n", returnMessage);
            color(WHITE, BLACK);
        }

        //saveIntoFile(s.ptr, url);
        curl_easy_cleanup(curl);    //free of curl

    }
}
