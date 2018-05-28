# coding=utf-8

FLAGS = [
    '-Xclang',
    '-flto-visibility-public-std',
    '-xc++',
    '-std=c++14',
    '-Wpedantic',
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wshadow',
    '-O3',
    '-g',
    '-pipe',
    "-I./include/bmce",
    "-I./gui/include/bmce",
    "-I./core/include/bmce",
    '-isystem/usr/include/freetype2',
    '-isystem./third_party/googletest/googlemock/include',
    '-isystem./third_party/googletest/googletest/include',
]
