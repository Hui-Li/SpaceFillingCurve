//+++++++++++++++++++++++++++ PUBLIC-DOMAIN SOFTWARE ++++++++++++++++++++++++++
// Functions:	TransposetoAxes AxestoTranspose
// Purpose:		Transform in-place between Hilbert transpose and geometrical axes
// Example:		b=5 bits for each of n=3 coordinates.
//				15-bit	Hilbert	integer	= A B C D E F G H I J K L M N O is stored
//				as its Transpose
//				X[0] = A D G J M				X[2]|
//				X[1] = B E H K N 	<-------> 		| /X[1]
//				X[2] = C F I L O 			    axes|/
//					   high  low					0------ X[0]
//				Axes are stored conventially as b-bit integers.
// Author:		John Skilling	20 Apr 2001 to 11 Oct 2003
// Source:      Programming the Hilbert curve
//-----------------------------------------------------------------------------

namespace HilbertCurve {

    typedef unsigned int coord_t; // char,short,int for up to 8,16,32 bits per word
    void TransposetoAxes(coord_t *X, int b, int n) // position, #bits, dimension
    {
        coord_t N = 2 << (b - 1), P, Q, t;
        int i;
    // Gray decode by H ^ (H/2)
        t = X[n - 1] >> 1;
        for (i = n - 1; i >= 0; i--) X[i] ^= X[i - 1];
        X[0] ^= t;
    // Undo excess work
        for (Q = 2; Q != N; Q <<= 1) {
            P = Q - 1;
            for (i = n - 1; i >= 0; i--)
                if (X[i] & Q) X[0] ^= P;                             // invert
                else {
                    t = (X[0] ^ X[i]) & P;
                    X[0] ^= t;
                    X[i] ^= t;
                }
        } // exchange
    }

    void AxestoTranspose(coord_t *X, int b, int n) // position, #bits, dimension
    {
        coord_t M = 1 << (b - 1), P, Q, t;
        int i;
    // Inverse undo
        for (Q = M; Q > 1; Q >>= 1) {
            P = Q - 1;
            for (i = 0; i < n; i++)
                if (X[i] & Q) X[0] ^= P;                             // invert
                else {
                    t = (X[0] ^ X[i]) & P;
                    X[0] ^= t;
                    X[i] ^= t;
                }
        } // exchange
    // Gray encode
        for (i = 1; i < n; i++) X[i] ^= X[i - 1];
        t = 0;
        for (Q = M; Q > 1; Q >>= 1)
            if (X[n - 1] & Q) t ^= Q - 1;
        for (i = 0; i < n; i++) X[i] ^= t;
    }

    int main() {
        coord_t X[3] = {5, 10, 20}; // any position in 32x32x32 cube
        AxestoTranspose(X, 5, 3); // Hilbert transpose for 5 bits and 3 dimensions
        printf("Hilbert integer = %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d = 7865 check\n",
               X[0] >> 4 & 1, X[1] >> 4 & 1, X[2] >> 4 & 1, X[0] >> 3 & 1, X[1] >> 3 & 1,
               X[2] >> 3 & 1, X[0] >> 2 & 1, X[1] >> 2 & 1, X[2] >> 2 & 1, X[0] >> 1 & 1,
               X[1] >> 1 & 1, X[2] >> 1 & 1, X[0] >> 0 & 1, X[1] >> 0 & 1, X[2] >> 0 & 1);

        return 0;
    }
}