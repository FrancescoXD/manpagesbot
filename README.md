# manpagesbot
A Telegram bot written in C

## Requirements
- [ezmanpages](https://github.com/FrancescoXD/ezmanpages)
- libcurl
- json-c
- meson
- ninja
- cmake & make

## How to compile
First of all you need to clone the repository:
```bash
$ git clone https://github.com/FrancescoXD/manpagesbot.git
$ cd manpagesbot
```

Now download the telebot library and compile it:
```bash
$ git clone https://github.com/smartnode/telebot.git
$ cd telebot
$ mkdir Build && cd build
$ cmake ../
$ make
```

After compiled the library, go to the main folder and do the same to build the bot yourself:
```bash
$ meson setup build
$ cd build
$ ninja
```
It will produce `manpagesbot`, which is the executable of the bot. To start it create a `.token` file with the token inside (get it from botfather on telegram!).

### TODO & Bugs
- Sometimes you could receive `[ERROR][telebot_core_curl_perform:137]Wrong HTTP response received, response: 400` and I don't know why...
- I think the bug is caused by the telebot lib that doesn't escape the text 
