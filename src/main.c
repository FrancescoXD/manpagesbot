#include "manpagesbot.h"

int main(void) {
	fprintf(stdout, "[info] Starting Telegram Bot...\n");

	FILE *token_file = fopen(".token", "r");
	if (token_file == NULL) {
		perror("[error] .token file");
		exit(EXIT_FAILURE);
	}

	char token[TOKEN_SIZE];
	fscanf(token_file, "%s", token);
	fprintf(stdout, "[info] Token: %s\n", token);
	fclose(token_file);

	telebot_handler_t handler;
	if (telebot_create(&handler, token) != TELEBOT_ERROR_NONE) {
		fprintf(stderr, "[error] Failed creating bot\n");
		exit(EXIT_FAILURE);
	}

	telebot_user_t me;
	if (telebot_get_me(handler, &me) != TELEBOT_ERROR_NONE) {
		fprintf(stderr, "[error] Failed to get telegram bot information\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "ID: %d\n", me.id);
	fprintf(stdout, "Firstname: %s\n", me.first_name);
	fprintf(stdout, "Username: %s\n", me.username);

	telebot_put_me(&me);

	int index;
	int count;
	int offset = -1;
	telebot_error_e ret;
	telebot_message_t message;
	telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};

	while (1) {
		telebot_update_t *updates;
		ret = telebot_get_updates(handler, offset, 20, 0, update_types, 0,
								  &updates, &count);
		if (ret != TELEBOT_ERROR_NONE) {
			continue;
		}

		for (index = 0; index < count; ++index) {
			message = updates[index].message;
			if (message.text) {
				char *str = handle_message(&message);
				ret =
					telebot_send_message(handler, message.chat->id, str, "HTML", 1, 0, message.message_id, "");
				if (ret != TELEBOT_ERROR_NONE) {
					fprintf(stderr, "[error] Unable to send message!\n");
				}
			}
			offset = updates[index].update_id + 1;
		}
		telebot_put_updates(updates, count);
		sleep(1);
	}

	telebot_destroy(handler);

	return 0;
}
