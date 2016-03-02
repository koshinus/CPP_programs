#include <stdio.h>

int main()
{
  double α;
  printf ("Enter the real number: ");
  scanf ("%lf", &α);
	
	if (α < 0) α = -α;
	
	printf ("Absolute value of this number is %lf", α);
	
  return 0;
}