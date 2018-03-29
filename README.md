# rig.py

RIG Random Identity Generator ported to Python

Michael McMahon

Rig.py can be used to fill databases with dummy data, build characters for a
story, or convincingly fool telemarketers with fake data.

The data has been expanded and updated since the original release.


## Forked to github

EinBaum: The original RIG program was downloaded here:

http://rig.sourceforge.net/

## Original README:

This is RIG, a program that generates fake identities. Install should be
fairly straightforward, just type "make install". If your system dosen't 
have /dev/urandom and you'd like to use /dev/random instead, do
$ make install CFLAGS=-DDEVRANDOM

RIG comes with the top 1000 names from the US census at 
http://www.census.gov/genealogy/names/, but Trent Stanley maintains a 
more extensive list at http://members.cox.net/gps/rignames_all.zip

If you have any patches, fixes, etc., just send 'em on over to
vectro@RIG.sourceforge.net.
