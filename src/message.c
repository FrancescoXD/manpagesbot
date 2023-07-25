#include "message.h"

char *handle_message(telebot_message_t *message) {
	static char str[MSG_SIZE];

	if (strstr(message->text, "/start")) {
		snprintf(str, MSG_SIZE, "Hello @%s!", message->from->username);
	} else if (strstr(message->text, "/man")) {
		char buffer[MSG_SIZE];
		get_manpage(message->text, buffer);
		snprintf(str, MSG_SIZE, "%s", buffer);
	} else {
		snprintf(str, MSG_SIZE, "%s", message->text);
	}

	return str;
}

void get_manpage(char *text, char *res) {
	ezmanpages_t parser;
	parser_error_t ret;
	char *name = strtok(text, " ");
	name = strtok(NULL, " ");

	ret = ezmanpages_init(&parser, name, 3, "SYNOPSIS");
	if (ret != E_PARSER_SUCCESS) {
		strncpy(res, "Error while init ezmanpages!\n", MSG_SIZE);
	}

	ret = ezmanpages_parse(parser, res, MSG_SIZE);
	if (ret != E_PARSER_SUCCESS) {
		strncpy(res, "Error while parsing ezmanpages!\n", MSG_SIZE);
	}

	//fprintf(stdout, "%s", res);
	format_text(res);
	//fprintf(stdout, "%s", res);
	//fprintf(stdout, "len: %zu\n", strlen(res));
}

void format_text(char *text) {
	size_t len = strlen(text);
	for (size_t i = 0; i < len; ++i) {
		if (text[i] == '<') {
			text[i] = ' ';
			//text[i] = '&lt';
		} else if (text[i] == '>') {
			text[i] = ' ';
			//text[i] = '&gt';
		}
	}
}
