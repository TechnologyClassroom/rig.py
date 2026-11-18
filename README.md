# rig.py

RIG Random Identity Generator ported to Python

Michael McMahon

When using the classic program [rig](https://rig.sourceforge.net/). I bet you
were thinking to yourself, "This is too fast. I wish it was slower." Well, you
are in luck because now it is ported to Python.

[Rig.py](https://github.com/TechnologyClassroom/rig.py) can be used to fill
development databases with dummy data, build characters for a story, or
convincingly fool telemarketers with misinformation.

The data has been heavily expanded and updated since the original rig release
in 2024.

rip.py depends on argparse and should work with Python 3.2+.

See also
[Random Technology Organization Generator (RTOG)](https://github.com/TechnologyClassroom/rig.py/tree/technology-organization-gen)
branch for a fun variation that generates names for technology organizations.

If you are looking for something a bit more specialized than rig.py, look into
[Faker](https://github.com/joke2k/faker) or
[Ruby Faker](https://github.com/faker-ruby/faker) which are actively developed
as of the last time I checked and integrate with databases.

## Switches and examples

Run the program will all defaults similar to `rig`.

    python3 rig.py

List all switches.

```
$ python3 rig.py -h
usage: rig.py [-h] [-f] [-m] [-F] [-c COUNT] [-d DDIR]

rig.py is a Random Identity Generator ported from rig.

optional arguments:
  -h, --help            show this help message and exit
  -f, --female          Choose only female names.
  -m, --male            Choose only male names.
  -F, --fake            Choose only fake phone numbers 555-0100 - 555-0199.
  -c COUNT, --count COUNT
                        Generate N number of identities.
```

Generate a female identity.

    python3 rig.py -f

Generate a male identity.

    python3 rig.py -m

Generate identity with fictional phone number.

    python3 rig.py -F

Generate 10 identities.

    python3 rig.py -c 10

Use a different folder data folder. Note: This does require the last forward
slash (/) to work.

    python3 rig.py -d /usr/local/share/rig/

Any number of switches can be combined except for `-h`.  If `-m` and `-f` are
combined, the default random gender will be used.

## Forked to github

EinBaum: The original RIG program was downloaded here:

<http://rig.sourceforge.net/>

## Original README:

This is RIG, a program that generates fake identities. Install should be fairly
straightforward, just type "make install". If your system [does] not have
/dev/urandom and you'd like to use /dev/random instead, do
$ make install CFLAGS=-DDEVRANDOM

RIG [orignally] [came] with the top 1000 names from the US census at
http://www.census.gov/genealogy/names/, but Trent Stanley maintains a more
extensive list at http://members.cox.net/gps/rignames_all.zip

If you have any patches, fixes, etc., just send them on over to REDACTED.
