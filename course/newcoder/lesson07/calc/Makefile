src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src))
target=app

CC=gcc

$(target):$(obj)
	$(CC) $(obj) -o $(target)

%.o:%.c
	gcc -c $< -o $@


clean:
	rm $(obj) $(target)


.PHONY:clean # 伪目标