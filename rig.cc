/* This is the source code for RIG, a program to generate fake identities.
 * Copyright (c) 1999 Ian Turner
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 * USA. */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

using namespace std;

template <class T>
T getrandnum(T max)
{
  static ifstream urandev("/dev/urandom");
  T rval;
  if (urandev) {
    /* /dev/urandom works. */
    urandev.read((char*)&rval, sizeof(rval));
  } else {
/* this ifdef is messy but does the right thing - we only try /dev/random
 * if it is defined. */
#ifdef DEVRANDOM
    static ifstream randev("/dev/random");
    if (randev) {
      /* /dev/random works. */
      randev.read(&rval, sizeof(rval));
    } else
#endif
    {      
      /* neither /dev/random nor /dev/urandom work; fallback to rand(). */
      static bool seeded = false;
      if (!seeded) {
	srand(time(NULL) ^ (((unsigned int) getpid()) << 15));
	seeded = true;
      }
      unsigned int written = 0;
      char* buf = (char*)(void*)(&rval);
      while (written < sizeof(rval)) {
	int tmp = rand();
	unsigned int bytestocopy = sizeof(rval) - written;
	if (bytestocopy > sizeof(int)) {
	  bytestocopy = sizeof(int);
	}
	memcpy(buf+written, &tmp, bytestocopy);
	written += bytestocopy;
      }
    }
  }
  if (max == 0)
    return max;
  else
    return rval % max;
}

template <class T>
typename T::value_type getrandpart(T& a)
{
  return a[getrandnum(a.size() - 1)];
}

struct place {
  string city, state;
  int ZIP;
  short int areacode;
};

ostream& operator<< (ostream& out, const place& a)
{
  out << a.city << ", " << a.state << "  "
      << setfill('0') << setw(5) << a.ZIP << endl
      << "(" << setfill('0') << setw(3) << a.areacode
      << ") xxx-xxxx";
  return out;
}

istream& operator>> (istream& in, place& a)
{
  in >> a.city >> a.state >> a.areacode >> a.ZIP;
  return in;
}

struct wholeline {
  string name;
};

ostream& operator<< (ostream& out, const wholeline& a)
{
  out << a.name;
  return out;
}

istream& operator>> (istream& in, wholeline& a)
{
  char temp = 'a';
  for (;;) {
    temp = in.get();
    if (temp == '\n' || temp == '\r' || temp == '0' || !in)
      break;
    a.name += temp;
  }
  return in;
}

/* Returns number of records gotten. */
template <class T>
int readfile(T& dest, const char * origin)
{
  int counter = 0;
  ifstream filetoread(origin);
  while (filetoread) {
    typename T::value_type temp;
    filetoread >> temp;
    dest.push_back(temp);
    counter++;
  }
  return counter;
}

void printusage()
{
  cerr << "USAGE: rig [-f | -m ] [ -d datadir ] [ -c num ]" << endl
       << "       datadir - Directory where data files can be found." << endl
       << "       If datadir is not specified, " DATADIR " is used as the" << endl
       << "       default directory." << endl
       << "       num - print num identities." << endl
       << "       -f and -m specify gender of generated identities." << endl << endl;
  exit(-1);
}

int printfileerror(string filename)
{
  cerr << "Unable to read file " << filename << endl << endl;
  printusage();
  exit(-2);
}

/* Holds information about a particular option */
struct option_data {
  /* The character to activate this option. */
  char option;
  /* Does this option take an operand? */
  enum operand_t {ALWAYS, NEVER, OPTIONAL};
  operand_t operand;
  /* Function to call with the operand.
   * First argument option, second operand (or NULL). */
  void (*handler) (char, const char*);

  static void parse_options(int, const char* const[],
                            int, const option_data*);
};

void option_data::parse_options(int argc, const char* const argv[],
                                int numopts,
                                const option_data config[]) {
  for (int i = 1; i < argc; i ++) {
    const char* cp = argv[i];
    if (*cp != '-')
      printusage();
    cp ++;
    do {
      int j;
      for (j = 0; j < numopts; j ++) {
        if (*cp == config[j].option) {
          const char* operand = NULL;
          if (config[j].operand != NEVER) {
            if (*(cp+1) != '\0') {
              operand = cp+1;
              cp = NULL;
            } else if (i + 1 < argc && argv[i+1][0] != '-') {
              i ++;
              operand = argv[i];
              cp = NULL;
            }
          }
          switch (config[j].operand) {
          case ALWAYS:
            if (operand == NULL)
              printusage();
            else
              (*(config[j].handler))(config[j].option, operand);
            break;
          case NEVER:
          case OPTIONAL:
            (*(config[j].handler))(config[j].option, operand);
            break;
          }
          break;
        }
      }
      if (j == numopts)
        printusage();
      if (cp != NULL && *cp != '\0')
        cp ++;
    } while (cp != NULL && *cp != '\0');
  }
}

string locdataidx;
long int numids;
bool male, female;

void set_datadir(char option, const char* dir) {
  assert(option == 'd');
  locdataidx = dir;
}

void set_number(char option, const char* num) {
  assert(option == 'c');
  char * tail;
  numids = strtol(num, &tail, 0);
  
  if (errno || tail == num) {
    printusage();
  }
  // Check that there was no extra stuff in the argument.
  while (*tail != '\0') {
    if (!(*tail == ' ' || *tail == '\t' || *tail == '\n'))
      printusage();
    tail ++;
  }
}

void set_gender(char option, const char* arg) {
  assert((option == 'm' || option == 'f') && arg == NULL);
  if (option == 'm') {
    male = true;
  } else if (option == 'f') {
    female = true;
  }
}

const option_data option_list[] = {{ 'd', option_data::ALWAYS, set_datadir },
                                   { 'c', option_data::ALWAYS, set_number },
                                   { 'f', option_data::NEVER,  set_gender },
                                   { 'm', option_data::NEVER,  set_gender }};

int main(int argc, char *argv[])
{
  string streetidx, mnamesidx, fnamesidx, lnamesidx;
  male = female = false;
  numids = 1;
  locdataidx = DATADIR;

  // four options
  option_data::parse_options(argc, argv, 4, option_list);  

  if (!female && !male)
    female = male = true;

  streetidx = locdataidx + "/street.idx";
  mnamesidx = locdataidx + "/mnames.idx";
  fnamesidx = locdataidx + "/fnames.idx";
  lnamesidx = locdataidx + "/lnames.idx";
  locdataidx += "/locdata.idx";
    
  vector<string> firstname, lastname;
  vector<wholeline> street;
  vector<place> location;
  if (readfile(location, locdataidx.c_str()) == 0)
    printfileerror(locdataidx);
  if (readfile(street, streetidx.c_str()) == 0)
    printfileerror(streetidx);
  if (male) {
      if (readfile(firstname, mnamesidx.c_str()) == 0)
          printfileerror(streetidx);
  }
  if (female) {
    if (readfile(firstname, fnamesidx.c_str()) == 0)
      printfileerror(fnamesidx);
  }
  if (readfile(lastname, lnamesidx.c_str()) == 0)
    printfileerror(lnamesidx);
  
  for (int i = 1; i <= numids; i ++) {
    cout << getrandpart(firstname) << " " << getrandpart(lastname) << endl
	 << getrandnum(1024u) + 1 << " " << getrandpart(street) << endl
	 << getrandpart(location) << endl;
    if (i != numids)
      cout << endl;
  }
}





