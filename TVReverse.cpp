/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include<stdio.h>
#include"mex.h"
#include"tv.h"

#define GRADX prhs[0]
#define GRADY prhs[1]

#define IMG  plhs[0]

// define the MEX wrapper for the tv_bw() function to allow it to be used
// in Matlab
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ){
    int dim[] = { mxGetM(GRADX), mxGetN(GRADX) };
    double *out, *gradx, *grady;
    
    IMG = mxCreateDoubleMatrix(dim[0],dim[1],mxREAL);
    out = mxGetPr(IMG);
    gradx = mxGetPr(GRADX);
    grady = mxGetPr(GRADY);
    
    tv_bw( dim, gradx, grady, out );
}