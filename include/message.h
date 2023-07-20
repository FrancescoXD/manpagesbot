#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <telebot.h>

#define MSG_SIZE 1024
#define MAN_LINE 78
#define MAN_CMD 512
#define MAN_ARG_SIZE 128

char *handle_message(telebot_message_t *message);
char *get_manpage(char *cmd);
int test_man_cmd(const char *arg);
char *remove_multiple_newlines(char *text);

#endif
