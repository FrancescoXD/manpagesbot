# manpagesbot
A Telegram bot written in C

## Requirements
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
