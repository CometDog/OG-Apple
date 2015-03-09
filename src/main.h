  /*
  In this file, you map each point of the hand. A good way to do this is to draw the file in something like GIMP or Photoshop. Center the newly drawn hand in a 144x168 size file and then figure out the coordinates of the points by scrolling your cursor over top each point you want mapped. Then it is as simple as subtracting 72x84 from the points you just mapped to get the coordinates here. You can find that easily by saving the coordinates in a .csv file, opening it in Excel and using the following formula to get the points:
    =CONCATENATE("{ ", A1 - 72,", ", B1 - 84, " },")
  Then you can just copy and paste the coordinates from Excel and you will get something like what follows. It does not matter where you start or stop as long as you map all the points you map (don't map points twice)
*/

#pragma once

#include "pebble.h"

// Minute hand
static const GPathInfo MINUTE_HAND_POINTS = {
  // Number of points that are going to be used
  9,
  (GPoint []) {
    { 6, 0 },
    { -6, 0 },
    {-6, -54},
    { -5, -55 },
    { -4, -57 },
    { -2, -59 },
    { 2, -59 },
    { 4, -57 },
    { 5, -55 },
    { -6, -54}
  }
};

// Hour hand
static const GPathInfo HOUR_HAND_POINTS = {
  // Number of points that are going to be used
  3,
  (GPoint []) {
    { 15, 0 },
    { -15, 0 },
    { 0, -45 }
  }
};

// Second hand
static const GPathInfo SECOND_HAND_POINTS = {
  // Number of points that are going to be used.
  // Normally you would never have this many points but the curvy second hand required it.
  112,
  (GPoint []) {
    { 2, 11 },
    { 5, 10 },
    { 6, 9 },
    { 7, 8 },
    { 8, 7 },
    { 9, 6 },
    { 10, 5 },
    { 11, 2 },
    { 11, -2 },
    { 10, -5 },
    { 9, -6 },
    { 8, -7 },
    { 7, -8 },
    { 6, -9 },
    { 5, -10 },
    { -8, -12 },
    { -5, -11 },
    { -7, -11 },
    { -10, -15 },
    { -10, -22 },
    { -7, -26 },
    { -4, -26 },
    { -4, -27 },
    { 2, -27 },
    { 2, -28 },
    { 5, -28 },
    { 8, -31 },
    { 8, -32 },
    { 9, -33 },
    { 9, -35 },
    { 10, -36 },
    { 10, -39 },
    { 9, -40 },
    { 9, -42 },
    { 8, -43 },
    { 8, -44 },
    { 6, -46 },
    { 5, -46 },
    { 4, -47 },
    { 3, -47 },
    { 2, -48 },
    { -4, -48 },
    { -5, -49 },
    { -6, -49 },
    { -10, -53 },
    { -10, -55 },
    { -8, -57 },
    { -7, -57 },
    { -6, -58 },
    { -2, -58 },
    { -1, -59 },
    { 0, -59 },
    { 0, -60 },
    { 2, -62 },
    { 2, -66 },
    { -3, -66 },
    { -3, -63 },
    { -6, -62 },
    { -7, -61 },
    { -9, -61 },
    { -10, -60 },
    { -11, -60 },
    { -13, -58 },
    { -13, -56 },
    { -14, -55 },
    { -14, -52 },
    { -13, -51 },
    { -13, -50 },
    { -9, -46 },
    { -8, -46 },
    { -7, -45 },
    { -6, -45 },
    { -5, -44 },
    { 1, -44 },
    { 2, -43 },
    { 3, -43 },
    { 4, -42 },
    { 5, -41 },
    { 5, -39 },
    { 6, -38 },
    { 6, -37 },
    { 5, -36 },
    { 5, -34 },
    { 2, -31 },
    { -4, -31 },
    { -5, -30 },
    { -7, -30 },
    { -8, -29 },
    { -9, -29 },
    { -13, -25 },
    { -13, -24 },
    { -14, -23 },
    { -14, -14 },
    { -13, -13 },
    { -13, -12 },
    { -9, -8 },
    { -8, -8 },  
    { -2, -11 },
    { -5, -10 },
    { -6, -9 },
    { -7, -8 },
    { -8, -7 },
    { -9, -6 },
    { -10, -5 },
    { -11, -2 },
    { -11, 2 },
    { -10, 5 },
    { -9, 6 },
    { -8, 7 },
    { -7, 8 },
    { -6, 9 },
    { -5, 10 }   
  }
};
