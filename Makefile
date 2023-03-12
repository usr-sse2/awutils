
ifeq ($(shell uname -s),Darwin)
EXTRACFLAGS:=-I/opt/local/include -L/opt/local/lib -fsanitize=address
endif

all:		log2bin$(EXE) awimage$(EXE) awflash$(EXE) add_checksum$(EXE)

clean:
		rm -f awimage$(EXE) awflash$(EXE) log2bin$(EXE) parsecfg$(EXE) add_checksum$(EXE)

log2bin$(EXE):	log2bin.c
		$(CC) $(EXTRACFLAGS) -Wall -o $@ $^

awimage$(EXE):	awimage.c parsecfg.c twofish.c rc6.c
		$(CC) $(EXTRACFLAGS) -Wall -o $@ $^

awflash$(EXE):	awflash.c
		$(CC) $(EXTRACFLAGS) -Wall -o $@ $^ -lusb

parsecfg$(EXE):	parsecfg.c
		$(CC) $(EXTRACFLAGS) -DSTANDALONE -Wall -o $@ $^

add_checksum$(EXE): add_checksum.c
		$(CC) $(EXTRACFLAGS) -Wall -o $@ $^
