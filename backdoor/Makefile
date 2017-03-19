SOURCES = minivm.h minivm.c miniasm.h miniasm.c
CFLAGS += -Wall -Wextra
BUILDDIR = build

all: $(BUILDDIR) $(BUILDDIR)/libminivm.a $(BUILDDIR)/interpreter

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/libminivm.a: $(BUILDDIR)/minivm.o
	ar rcs $(BUILDDIR)/libminivm.a $(BUILDDIR)/minivm.o

$(BUILDDIR)/minivm.o: minivm.c
	$(CC) $(CFLAGS) -g -c minivm.c -o $@

$(BUILDDIR)/libminiasm.a: $(BUILDDIR)/miniasm.o
	ar rcs $(BUILDDIR)/libminiasm.a $(BUILDDIR)/miniasm.o

$(BUILDDIR)/miniasm.o: miniasm.c
	$(CC) $(CFLAGS) -g -c miniasm.c -o $@

$(BUILDDIR)/interpreter: interpreter.c $(BUILDDIR)/libminivm.a $(BUILDDIR)/libminiasm.a
	$(CC) $(CFLAGS) -g $^ -o $@ -lssl -lcrypto

clean:
	rm -rf $(BUILDDIR)

inspect: bytecode.txt
	od --format=u1 --width=4 bytecode.txt

sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)
