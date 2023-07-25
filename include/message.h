#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <telebot.h>
#include <ezmanpages/ezmanpages.h>

#define MSG_SIZE 800
#define MAN_LINE 78
#define MAN_CMD 512
#define MAN_ARG_SIZE 128

char *handle_message(telebot_message_t *message);
void get_manpage(char *text, char *res);

#endif
