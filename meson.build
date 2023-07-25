project('manpagesbot', 'c', version: '0.1.0', default_options: ['warning_level=2', 'buildtype=release', 'strip=true', 'debug=false', 'optimization=3'])
sources = ['src/main.c', 'src/message.c']

compiler = meson.get_compiler('c')
dir_base = meson.current_source_dir()

incdir = include_directories(['./include/', './telebot/include'])
telebot_dep = compiler.find_library('telebot_static', dirs: [join_paths(dir_base, './telebot/Build/')], static: true, required: true)
ezmanpages_dep = compiler.find_library('ezmanpages', required: true)

jsonc_dep = dependency('json-c')
curl_dep = dependency('libcurl')

executable('manpagesbot', sources, dependencies: [ezmanpages_dep, telebot_dep, jsonc_dep, curl_dep], include_directories: incdir)
