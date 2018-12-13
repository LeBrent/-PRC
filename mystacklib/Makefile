# Makefile for shared library

CC = gcc
LD = gcc
CPPFLAGS = -DDEBUG=1
CFLAGS =  -fPIC -Wall -Wextra -std=c11 -O -g
LDFLAGS = -shared
RM = rm -f
TARGET_LIB = libmystack.so

SRCS = mystack.c
OBJS = $(SRCS:.c=.o)


UNITY_DIR = ./Unity/src/

.PHONY: all clean
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(LD) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

test: stackTest.c
	$(CC) -Wall -Wextra -Werror -O3 -std=c11 -I$(UNITY_DIR) $^ $(UNITY_DIR)/unity.c -o $@

clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) test
