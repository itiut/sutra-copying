CC := gcc
CFLAGS := -lapue

OPENC_OBJS := main.o csopen.o
OPEND_OBJS := opend.o handle-request.o buf-args.o cli-args.o

.PHONY: all clean
.SUFFIXES: .c .o

.c.o:
	$(CC) -c $(CFLAGS) $<

all: openc opend

clean:
	rm -f $(OPENC_OBJS) $(OPEND_OBJS) openc opend

openc: $(OPENC_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

opend: $(OPEND_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
