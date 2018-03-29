# rig.py

RIG Random Identity Generator ported to Python

Michael McMahon

Rig.py can be used to fill databases with dummy data, build characters for a
story, or convincingly fool telemarketers with fake data.

The data has been heavily expanded and updated since the original release.

## Switches and examples

Run the program will all defaults similar to ```rig```.

```python3 rig```

List all switches.

```python3 rig.py -h```

Generate a male identity.

```python3 rig.py -m```

Generate a female identity.

```python3 rig.py -f```

Generate 10 identities.

```python3 rig.py -c 10```

Generate identity with fictional phone number.

```python3 rig.py -F```

Use a different folder data folder.

```python3 rig.py -d /usr/local/share/rig```

Any number of switches can be combined except for ```-h```.  If ```-m``` and
```-f``` are combined, the default random gender will be used.


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
