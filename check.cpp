#include <iostream>
#include <vector>
#include <cblas.h>
//#include "f77blas.h"
//#include "lapacke.h"
//#include "lapacke_config.h"
//#include "lapacke_mangling.h"
//#include "lapacke_utils.h"
//#include "openblas_config.h"

//#include <OpenBlas/common.h>
#include <cstring>
//#include "options.h"
//#include "calculate_model.h"
using namespace std;
int main()
{
	int n = 10;
    int in_x =1;
    int in_y =1;

    std::vector<double> x(n);
    std::vector<double> y(n);

    double alpha = 10;

    std::fill(x.begin(),x.end(),1.0);
    std::fill(y.begin(),y.end(),2.0);

    cblas_daxpy( n, alpha, &x[0], in_x, &y[0], in_y );

    //Print y
    for(int j=0;j<n;j++)
        std::cout << y[j] << "\t";

    std::cout << "Everything is OK! :)" << std::endl;
    return 0;
}