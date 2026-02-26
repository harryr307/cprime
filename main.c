#include <stdio.h>

int test(int rhs)
{
  if (rhs<2) return 0;
  for (int i=2;i*i<=rhs;i++)
    if (rhs%i==0)
      return 0;
  return 1;
}

int main()
{
  int curnum = 1;

  while (curnum<=1000000000)
  {
    curnum++;
    if (test(curnum)==1)
      printf("%d\n", curnum);
  }
}
