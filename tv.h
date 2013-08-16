#ifndef TV_H
#define TV_H

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// forward TV operator. Compute the spatial gradients of an input image in 
// with dimensions dim and store the result in the images gradx and grady
void tv_fw( const int *dim, const double *in, double *gradx, double *grady );

// reverse TV operator. Take the computed spatial gradients images gradx
// and grady and apply them back to the output image as if applying the
// transpose of a matrix that computes the spatial gradients.
void tv_bw( const int *dim, const double *gradx, const double *grady, double *out );

#endif