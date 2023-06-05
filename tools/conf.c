//
// Created by tjx on 11/8/22.
//
#include <stdio.h>
#include <stdlib.h>

#include <cJSON.h>

#include "conf.h"
#include "utils.h"
#include "log.h"

static Conf_t conf;

void conf_load(char* file) {

    long filesz = utils_file_size(file);
    if(filesz <= 0) {
        log_info("filesz negative %ld ", filesz);
        exit(-1);
    }

    char buf[filesz + 1];
    utils_read_file(file, buf);

    log_info("file_content: %s ", buf);

    cJSON* json = cJSON_Parse(buf);
    if (json == NULL) {
        const char* err = cJSON_GetErrorPtr();
        if(err != NULL) {
            log_info("cJSON_Parse Error: %s", err);
            exit(-1);
        }
    }

    //TODO init config data

    cJSON_Delete(json);
}