#!/usr/bin/env python
"""rig.py is a Random Identity Generator ported from rig."""

from random import randrange
# import argparse  # TODO Add switches from rig


def random_line(afile):
    """Choose a random line from a file."""
    # From Alex Martelli at https://stackoverflow.com/questions/3540288
    line = next(afile)
    for num, aline in enumerate(afile):
        if randrange(num + 2): continue
        line = aline
    return line


# Choose a name
# Randomly decide between Male or Female
gender = randrange(0, 2)
if gender == 0:
	# Male
	firstname = random_line(open("data/mnames.idx", "r"))
else:
	# Female
	firstname = random_line(open("data/fnames.idx", "r"))
lastname = random_line(open("data/lnames.idx", "r"))

# Choose an address
streetnumber = str(randrange(0,1000))
streetname = random_line(open("data/street.idx", "r"))
# Location
location = random_line(open("data/locdata.idx", "r"))
locationci = location[:-14]
locationst = location[-13:-11]
locationzip = location[-6:-1]

# Create a phone number
phonea = location[-10:-7]
phoneb = str(randrange(100,1000))  # TODO Improve this to allow 001
phonec = str(randrange(1000,10000))  # TODO Change this to allow 0001

print(firstname + " " + lastname)
print(streetnumber + " " + streetname)
print(locationci + ", " + locationst + " " + locationzip)
print("(" + phonea + ") " + phoneb + "-" + phonec)
