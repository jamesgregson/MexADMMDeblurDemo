/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// define a convenience indexing macro
#define V( arr, i, j ) arr[(j)*dim[0]+(i)]

// apply the forward model to the input image in, using the psf defined as
// psf_cnt triplets consisting of a value and x&y offsets from the center
// pixel, i.e. in sparse-stencil form
void ifm_fw( const int *dim, const double *in, const int psf_cnt, const double *psf_val, const int *psf_x, const int *psf_y, double *out ){
    for( int i=0; i<dim[0]; i++ ){
        for( int j=0; j<dim[1]; j++ ){
            V(out,i,j) = 0.0;
            for( int k=0; k<psf_cnt; k++ ){
                V(out,i,j) += V(in,(dim[0]+i+psf_x[k])%dim[0],(dim[1]+j+psf_y[k])%dim[1])*psf_val[k];
            }
        }
    }
}

// apply the reverse model from ifm_fw, i.e. if ifm_fw could be represented
// as a matrix K, apply K' using the same approach as above
void ifm_bw( const int *dim, const double *in, const int psf_cnt, const double *psf_val, const int *psf_x, const int *psf_y, double *out ){
    for( int i=0; i<dim[0]; i++ ){
        for( int j=0; j<dim[1]; j++ ){
            V(out,i,j) = 0.0;
            for( int k=0; k<psf_cnt; k++ ){
                V(out,i,j) += V(in,(dim[0]+i-psf_x[k])%dim[0],(dim[1]+j-psf_y[k])%dim[1])*psf_val[k];
            }
        }
    }
}