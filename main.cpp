#include <stdio.h>
#include <iostream>
#include "HilbertCurve.cpp"
#include "ZorderCurve.cpp"
using namespace std;

int main()
{
	unsigned int X[3] = {5,10,20}; // any position in 32x32x32 cube
	HilbertCurve::AxestoTranspose(X, 5, 3); // Hilbert transpose for 5 bits and 3 dimensions
	printf("Hilbert integer = %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d = 7865 check\n",
			X[0]>>4 & 1, X[1]>>4 & 1, X[2]>>4 & 1, X[0]>>3 & 1, X[1]>>3 & 1,
			X[2]>>3 & 1, X[0]>>2 & 1, X[1]>>2 & 1, X[2]>>2 & 1, X[0]>>1 & 1,
			X[1]>>1 & 1, X[2]>>1 & 1, X[0]>>0 & 1, X[1]>>0 & 1, X[2]>>0 & 1);

	uint64_t x = 6;
	uint64_t y = 4;
	cout << "Morton code = " << ZOrder::mortonEncode_for(x, y) << endl;

    return 0;
}