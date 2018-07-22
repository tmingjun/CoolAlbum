TARGET := app
CC := arm-linux-gcc
# CC := arm-none-linux-gnueabi-gcc


CSRCS := $(wildcard *.c)
#CSRCS += $(wildcard sub/*.c)
#CSRCS += $(wildcard mp3/*.c)
INCS := -I../inc 

LIBS := -pthread




OBJS := $(patsubst %.c, %.o, $(CSRCS))

$(TARGET): $(OBJS) 
	$(CC) $+ $(INCS) $(LIBS) -o $@
	cp $(TARGET) /mnt/hgfs/abc/

%.o:%.c
	$(CC) -c $< $(INCS) -o $@


clean:
	rm -rf $(OBJS) $(TARGET)
