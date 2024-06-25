#include "average.h"

uint64_t addWithOverflowCheck(uint64_t num1, uint64_t num2)
{
  uint64_t sum = num1 + num2;
  assert(sum >= num1);
  assert(sum >= num2);
  return sum;
}
