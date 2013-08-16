#ifndef IMAGE_FORMATION_MODEL_H
#define IMAGE_FORMATION_MODEL_H

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// define a forward image formation model, represented in a matrix-
// free linear operator K
void ifm_fw( const int *dim, const double *in, const int psf_count, const double *psf_val, const int *psf_x, const int *psf_y, double *out );

// define the transpose of the image formation model K, K'
void ifm_bw( const int *dim, const double *in, const int psf_count, const double *psf_val, const int *psf_x, const int *psf_y, double *out );


#endif