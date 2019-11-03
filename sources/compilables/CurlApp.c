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
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);

        if(res == CURL_OK){
            saveIntoFile(s.ptr, url);
//          printf("%s", s.ptr);
        }else{
            const char*  returnMessage = curl_easy_strerror(res);
            printf("\n\t\t\t\t\t%s\n\n", returnMessage);
        }

        //saveIntoFile(s.ptr, url);

        curl_easy_cleanup(curl);    //free of curl

    }
}

/**
 * This function is used to save the content of the site into a file
 * @param char* str <- content of the site
 * @param char* url <- url of the site to name the file
 */
void saveIntoFile(char* str, char* url){
    FILE* f;
    unsigned int urlSize = strlen(url);
    //char* filename = malloc(sizeof(char) * (urlSize + 5));
    char filename[1000];
    char path[200] = {'r','e','s','s','o','u','r','c','e','s','\\','\0'};
    char extension[6] = {'.','h','t','m','l','\0'};

    int i = 0;
    int yFile = 0;

    while(path[i] != '\0'){
//      printf("%c", path[i]);
        filename[yFile] = path[i];
        i++;
        yFile++;
    }

    i = startSiteName(url);

    while(url[i] != '\0'){
       if(url[i] == '/'){
            filename[yFile] = '-';
        }else{
            filename[yFile] = url[i];
        }
        i++;
        yFile++;
    }
    i = 0;
    while(i != 6){
    //while(extension[i] != '\0'){
//        printf("%c", extension[i]);
        filename[yFile] = extension[i];
        i++;
        yFile++;
    }

    printf("\n%s\n", filename);

    //ressources\\site.html
    f = fopen(filename, "w");

    if(f != NULL){
        fprintf(f, str);
        printf("File created\n");
    } else {
        printf("Failed to create the file\n");
    }

    fclose(f);

    //free(filename);
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
