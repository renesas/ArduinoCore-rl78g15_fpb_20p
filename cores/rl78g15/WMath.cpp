/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Wiring project - http://wiring.org.co
  Copyright (c) 2004-06 Hernando Barragan
  Modified 13 August 2006, David A. Mellis for Arduino - http://www.arduino.cc/
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/
/*
 * Modified  5 Mar  2017 by Yuuki Okamiya for RL78/G13
*/

extern "C" {
  #include "stdlib.h"
}

void randomSeed(unsigned long seed)
{
  if (seed != 0) {
#ifndef __RL78__
    srandom(seed);
#else
    srand((unsigned int)seed);
#endif
  }
}

long random(long howbig)
{
  unsigned long value = 0;
  if (howbig == 0) {
    return 0;
  }
#ifndef __RL78__
  return random() % howbig;
#else
  value = ((unsigned long)rand() << 16);
  value |= ((unsigned long)rand() << 1);
  value |= ((unsigned long)rand() & 0x01);
  return (signed long)value % howbig;
#endif
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned int makeWord(unsigned int w) { return w; }
unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }
