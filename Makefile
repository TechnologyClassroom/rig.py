PREFIX=/usr/local
BINDIR=${PREFIX}/bin
MANDIR=${PREFIX}/man
DATADIR=${PREFIX}/share/rig

all: rig rig.6
rig: rig.cc
	g++ -g rig.cc -o rig -Wall -DDATADIR="\"$(DATADIR)\""

rig.6: rig.6.in
	sed s@DATADIR@"$(DATADIR)"@g < rig.6.in > rig.6

install: rig rig.6
	install -g 0 -m 755 -o 0 -s rig $(BINDIR)
	install -g 0 -m 644 -o 0 rig.6 $(MANDIR)/man6/rig.6
	install -g 0 -m 755 -o 0 -d $(DATADIR)
	install -g 0 -m 644 -o 0 data/*.idx $(DATADIR)

clean:
	rm -rf *~ *.rej *.orig *.o rig rig.6
