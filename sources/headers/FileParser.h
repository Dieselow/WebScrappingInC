//
// Created by Retr0 on 27/10/2019.
//

#ifndef WEBSCRAPPINGINC_FILEPARSER_H
#define WEBSCRAPPINGINC_FILEPARSER_H
typedef struct Option {
    char *name;
    char *value;
} Option;
typedef struct Action {
    char *name;
    char *url;
    Option *options;
} Action;
typedef struct Task {
    char *name;
    Action *actions;
    double extTimeStamp;
    int seconds;
    int minutes;
    int hours;
} Task;
#endif //WEBSCRAPPINGINC_FILEPARSER_H
