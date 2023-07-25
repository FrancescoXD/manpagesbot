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

	ret = ezmanpages_init(&parser, name, 3, "DESCRIPTION");
	if (ret != E_PARSER_SUCCESS) {
		strncpy(res, "Error while init ezmanpages!", MSG_SIZE);
	}

	ret = ezmanpages_parse(parser, res);
	if (ret != E_PARSER_SUCCESS) {
		strncpy(res, "Error while parsing ezmanpages!", MSG_SIZE);
	}

	fprintf(stdout, "%s", res);
	fprintf(stdout, "len: %zu\n", strlen(res));
}
