//
// Created by Retr0 on 27/10/2019.
//

#ifndef WEBSCRAPPINGINC_FILEPARSER_H
#define WEBSCRAPPINGINC_FILEPARSER_H
typedef struct Option {
    char *name;
    char *value;
}Option;
typedef struct Action{
    char * name;
    char * url;
    Option * options;
}Action;
#endif //WEBSCRAPPINGINC_FILEPARSER_H
