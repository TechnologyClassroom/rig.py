# rig.py and rtog.py

`rig.py` is the Random Identity Generator (RIG) ported to Python.
[rig.py](https://github.com/TechnologyClassroom/rig.py) can be used to fill
development databases with dummy data, build characters for a story, come up
with a name a child, or convincingly fool telemarketers with misinformation.

`rtog.py` is the Random Technology Organization Generator (RTOG) which
generates real and ficticious technology organizations. Often times the results
are satiracal. rtog.py can be used to generate organization names in a test
database, come up with a new technology non-profit, build organizations for a
fiction story, or start a new religious following.

Michael McMahon

These programs are based on the concept of the classic program
[rig](https://rig.sourceforge.net/). In 2024, the data has been heavily
expanded and updated since the original rig release.

If you are looking for something a bit more specialized than rig.py, look into
[Faker](https://github.com/joke2k/faker) or
[Ruby Faker](https://github.com/faker-ruby/faker) which are actively developed
as of the last time I checked and integrate with databases. If you want to
update the name database in the future, the
[United States Census Bureau](https://www.census.gov/) website is a good place
to get started.

## Getting started

These four commands will generate 5 names and addresses as well as 5
potentially new technology organizations along with bogus phone numbers and
plausible mailing addresses. YOLO!

```
git clone https://github.com/TechnologyClassroom/rig.py
cd rig.py
python3 rig.py -c 5
python3 rtog.py -c 5
```

## Dependencies

rip.py and rtog.py depend on argparse and should work with Python 3.2+.

## Switches and examples

Clone this repository with git.

    git clone https://github.com/TechnologyClassroom/rig.py

Change to this directory.

    cd rig.py

Run rig.py will all defaults similar to the classic `rig` program.

    python3 rig.py

List all switches.

    python3 rig.py -h

Prints this output:

```
usage: rig.py [-h] [-F] [-c COUNT] [-d DDIR] [-f] [-m]

rig.py is a Random Identity Generator ported from rig.

options:
  -h, --help            show this help message and exit
  -F, --fake            Choose only fake phone numbers 555-0100 - 555-0199.
  -c COUNT, --count COUNT
                        Generate N number of identities.
  -d DDIR, --datadir DDIR
                        Generate N number of identities.
  -f, --fem             Choose only feminine names.
  -m, --masc            Choose only masculine names.
```

Generate a feminine identity.

    python3 rig.py -f

Generate a masculine identity.

    python3 rig.py -m

Note that rtog.py does not have the concept of gendered organizations.

Generate identity with a fictional phone number.

    python3 rig.py -F

Generate more than one identity. Replace 10 with the number of identities you
would like to create.

    python3 rig.py -c 10

Use a different folder data folder. Note: This does require the last forward
slash (/) to work.

    python3 rig.py -d /usr/local/share/rig/

Any number of switches can be combined except for `-h`. If `-m` and `-f` are
combined, either source file may be picked at random.

Generate a random technology organization.

    python3 rtog.py

Generate technology organization with fictional phone number.

    python3 rtog.py -F

Generate 10 technology organizations.

    python3 rtog.py -c 10

Use a different folder data folder. Note: This does require the last forward
slash (/) to work.

    python3 rtog.py -d /usr/local/share/rtog/

Any number of switches can be combined except for `-h`. If `-m` and
`-f` are combined, the default random gender will be used.

Continuously run rig in a loop with only names using bash.

    bash run-rig-loop.sh

Continuously run rtog in a loop with only names using bash.

    bash run-rtog-loop.sh

## License

GPL-3.0-or-later

This program is intended for fun.
