#ifndef CURLAPP_H_INCLUDED
#define CURLAPP_H_INCLUDED

struct string {
  char *ptr;
  size_t len;
};
void init_string(struct string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
void scrap(char*);
void saveIntoFile(char* str, char* url);
int startSiteName(char* url);
char* makeFileName(char* url);

#endif // CURLAPP_H_INCLUDED
