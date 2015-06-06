CC = gcc
CF =
DEFINES =

build:
	$(CC) test.c $(CF) $(DEFINES) -Wall -o test

embedded:
	$(eval DEFINES += -D__EMBEDDED__)

nomacfix:
	$(eval DEFINES += -DMAC_OVERRIDE)

uk:
	$(eval DEFINES += -DUK)

8color:
	$(eval DEFINES += -DNO256)