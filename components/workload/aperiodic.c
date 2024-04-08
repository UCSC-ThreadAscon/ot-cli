/**
 * The function that determine the rate at which aperiodic packets are
 * sent is from the paper:
 * https://www.mdpi.com/1424-8220/14/8/14932
 *
 * Additional resources used:
 * https://en.wikibooks.org/wiki/C_Programming/math.h/log
 * https://en.wikibooks.org/wiki/C_Programming/limits.h
*/
#include "workload.h"

#include "math.h"
#include "limits.h"

#define LAMBDA 0.1

double generateToLn() {
  double randomNum = (double) esp_random();
  double normalized = randomNum / UINT32_MAX;
  double toLn = 1 - normalized;
  return toLn;
}

double aperiodicWaitTime() {
  double toLn = 0;
  do {
    toLn = randomToLn();
  }
  while (toLn == 0); // prevents the case of ln(0)

  double lnResult = log(toLn);
  double numerator = -1 * lnResult;
  double result = numerator / LAMBDA;
  return result;
}