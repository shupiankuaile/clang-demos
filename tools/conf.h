//
// Created by tjx on 11/8/22.
//

#ifndef MY_TOOLS_CONF_H
#define MY_TOOLS_CONF_H

typedef struct Conf_st Conf_t;
struct Conf_st {
    char* conf_file;

};

void conf_load(char* file);

#endif //MY_TOOLS_CONF_H
