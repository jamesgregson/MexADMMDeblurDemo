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

#define IMG  prhs[0]

#define GRADX plhs[0]
#define GRADY plhs[1]

// define the MEX wrapper for the tv_fw() function to allow it to be used
// in Matlab
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ){
    int dim[] = { mxGetM(IMG), mxGetN(IMG) };
    double *in, *gradx, *grady;
    
    in = mxGetPr(IMG);
    GRADX = mxCreateDoubleMatrix(dim[0],dim[1],mxREAL);
    GRADY = mxCreateDoubleMatrix(dim[0],dim[1],mxREAL);
    gradx = mxGetPr(GRADX);
    grady = mxGetPr(GRADY);
    
    tv_fw( dim, in, gradx, grady );
}