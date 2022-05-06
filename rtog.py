#!/usr/bin/env python
"""rtog.py is a Random Technology Organization Generator hacked from rig.py."""

# rtog.py

# Michael McMahon

# Depends on argparse and should work on Python 3.2 and onward.

# Run with this command:
#   python3 rtog.py
#
# View help and list all options:
#   python3 rtog.py -h

from random import randrange
from argparse import ArgumentParser  # Add switch arguments for python 2.7&3.2+

# argparse
# This section adds switch -h and argument to the script.
parser = ArgumentParser(
    description='rtog.py is a Random Technology Organization Generator hacked from rig.py.')
parser.add_argument('-F', '--fake', action="store_true",
                    help='Choose only fake phone numbers 555-0100 - 555-0199.')
parser.add_argument('-c', '--count', action='store', dest='count', default=1,
                    type=int, help='Generate N number of identities.')
parser.add_argument('-d', '--datadir', action='store', dest='ddir',
                    default="data/", type=str,
                    help='Generate N number of identities.')
# For Windows users, change 'data/' to 'data\' to make rig.py work.
parser.add_argument('-f', '--female',
                    help='Choose only female names.', action="store_true")
parser.add_argument('-m', '--male',
                    help='Choose only male names.', action="store_true")
#parser.add_argument('-s', '--sqlitedb', action='store', dest='sqldb',
#                    default="data/", type=str,
#                    help='Generate N number of identities.')
# For Windows users, change 'data/' to 'data\' to make rig.py work.
args = parser.parse_args()


def random_line(afile):
    """Choose a random line from a file."""
    # From Alex Martelli at https://stackoverflow.com/questions/3540288
    line = next(afile)
    for num, aline in enumerate(afile):
        if randrange(num + 2): continue
        line = aline
    return line[:-1]


for i in range(1, args.count + 1):
    """Choose a random identity."""
    if 1 < i < args.count + 1:
        """Print a space between each identity."""
        print()

    # Choose a name
    # Randomly decide between Male or Female
    gender = randrange(0, 2)
    if args.male:
        gender = 0
    if args.female:
        gender = 1
    if args.male and args.female:
        gender = 1
    else:
        # Female
        firstname = random_line(open(args.ddir + "fnames.idx", "r"))
    lastname = random_line(open(args.ddir + "lnames.idx", "r"))

    # Choose an address
    streetnumber = str(randrange(0,1000))
    streetname = random_line(open(args.ddir + "street.idx", "r"))
    # Location
    location = random_line(open(args.ddir + "locdata.idx", "r"))
    locationci = location[:-13]
    locationst = location[-12:-10]
    locationzip = location[-5:]

    # Create a phone number
    phonea = location[-9:-6]
    phoneb = str(randrange(0,1000)).zfill(3)
    phonec = str(randrange(0,10000)).zfill(4)
    if args.fake:
        """Only generate numbers between 555-0100 - 555-0199"""
        phoneb = str(555)
        phonec = str(randrange(100,200)).zfill(4)

    print(firstname + " " + lastname)
    print(streetnumber + " " + streetname)
    print(locationci + ", " + locationst + " " + locationzip)
    print("(" + phonea + ") " + phoneb + "-" + phonec)
