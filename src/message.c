#include "message.h"

char *handle_message(telebot_message_t *message) {
	static char str[MSG_SIZE];

	if (strstr(message->text, "/start")) {
		snprintf(str, MSG_SIZE, "Hello @%s!", message->from->username);
	} else if (strstr(message->text, "/man")) {
		snprintf(str, MSG_SIZE, "%s", get_manpage(message->text));
	} else {
		snprintf(str, MSG_SIZE, "%s", message->text);
	}

	return str;
}

int test_man_cmd(const char *arg) {
	char man_cmd[MAN_CMD];
	FILE *output;
	snprintf(man_cmd, MAN_CMD, "man 3 %s 2>&1", arg);
	output = popen(man_cmd, "r");
	if (output == NULL) {
		puts("error...");
	}
	char line[MAN_LINE];
	fgets(line, MAN_LINE, output);
	if (strstr(line, "No entry")) {
		return 0;
	}

	return 1;
}

char *get_manpage(char *text) {
	/**
	 * BUG HERE
	*/
	static char man_res[MSG_SIZE];
	char man_cmd[MAN_CMD];
	FILE *output;

	//memset(man_arg, 0, MAN_ARG);
	//memcpy(man_arg, text, MAN_ARG - 1);
	char *man_arg = strtok(text, " ");
	man_arg = strtok(NULL, " ");

	int res = test_man_cmd(man_arg);
	if (!res) {
		return "No entry found!";
	}
	//strncpy(man_cmd, "TERM=dumb man 3 ", 17);
	//strncat(man_cmd, man_arg, MAN_ARG_SIZE);
	snprintf(man_cmd, MAN_CMD, "man 3 %s | cat | col -bx | awk -v S=SYNOPSIS '$0 ~ S {cap=\"true\"; print} $0 !~ S && /^[A-Z ]+$/ {cap=\"false\"} $0 !~ S && !/^[A-Z ]+$/ {if(cap == \"true\")print}'", man_arg);

	output = popen(man_cmd, "r");
	if (output == NULL) {
		snprintf(man_res, MSG_SIZE, "%s", "Unable to popen()!");
	}
	char line[MAN_LINE];
	
	memset(man_res, 0, MSG_SIZE);
	while (fgets(line, MAN_LINE, output)) {
		if ((strlen(man_res) + MAN_LINE) >= MSG_SIZE - 1) {
			break;
		}
		//line[strlen(line)] = 0;
		strncat(man_res, line, MAN_LINE);
	}
	pclose(output);
	//man_res[strlen(man_res) - 1] = 0;
	printf("STRLEN: %zu: %s\n", strlen(man_res), man_res);
	FILE *write_to = fopen("out.txt", "w");
	fputs(man_res, write_to);
	fclose(write_to);
	//char *new_text = remove_multiple_newlines(man_res);
	//printf("%s\n", new_text);

	return man_res;
}

char *remove_multiple_newlines(char *text) {
	char *new_text = malloc(strlen(text) + 1);
	int i = 0;
	int j = 0;

	int len = strlen(text);
	for (; i < len; ++i) {
		if (text[i] != '\n' || text[i - 1] != '\n') {
			new_text[j++] = text[i];
		}
	}

	printf("new_text: %s\n", new_text);
	new_text[j] = 0;
	return new_text;
}
