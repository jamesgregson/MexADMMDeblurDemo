/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include<stdio.h>
#include<math.h>
#include"mex.h"
#include"image_formation_model.h"

#define IMG  prhs[0]
#define BLUR plhs[0]

#define psf_cnt 25
#define sigma 4.0

// define a mex wrapper for the ifm_fw() function, also defines a PSF that
// MUST MATCH that of IFMReverse.cpp
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ){
    double *in, *out;
    int dim[] = { mxGetM(IMG), mxGetN(IMG) };

    int psf_x[psf_cnt*psf_cnt];
    int psf_y[psf_cnt*psf_cnt];
    double psf_v[psf_cnt*psf_cnt], sum=0.0;
    int id = 0;
    for( int i=0; i<psf_cnt; i++ ){
        for( int j=0; j<psf_cnt; j++ ){
            int dx = i-psf_cnt/2;
            int dy = j-psf_cnt/2;
            psf_x[id] = dx;
            psf_y[id] = dy;
            psf_v[id] = exp( -double(dx*dx+dy*dy)/(sigma*sigma) );
            sum += psf_v[id];
            id++;
        }
    }
    for( int i=0; i<psf_cnt*psf_cnt; i++ ){
        psf_v[i] /= sum;
    }
    
    in = mxGetPr(IMG);        
    BLUR = mxCreateDoubleMatrix(dim[0],dim[1],mxREAL);
    out = mxGetPr(BLUR);
    
    ifm_fw( dim, in, psf_cnt*psf_cnt, psf_v, psf_x, psf_y, out );
}