#!/usr/bin/env python3
"""rtog.py is a Random Technology Organization Generator hacked from rig.py."""
# https://github.com/TechnologyClassroom/rig.py

# rtog.py
# Version v1.0.0

# Copyright 2022-2026 Michael McMahon
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
                    default="data-rtog/", type=str,
                    help='Generate N number of technology organizations.')
# For Windows users, change 'data/' to 'data\' to make rtog.py work.
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
