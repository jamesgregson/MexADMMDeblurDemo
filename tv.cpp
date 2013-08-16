/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// define an indexing scheme for the image
// and a convenience accessor function
#define ID( i, j )     ((j)*dim[0]+(i))
#define V( arr, i, j ) arr[ID((i),(j))]

// apply the TV forward operator to compute the spatial image gradient and
// store the result in the gradx and grady array
void tv_fw( const int *dim, const double *in, double *gradx, double *grady ){
    int id_curr, id_xplus, id_yplus;
    for( int i=0; i<dim[0]; i++ ){
        for( int j=0; j<dim[1]; j++ ){
            id_curr  = ID(i,j);
            id_xplus = i < dim[0]-1 ? ID(i+1,j) : ID(i-1,j);
            id_yplus = j < dim[1]-1 ? ID(i,j+1) : ID(i,j-1);
            
            gradx[id_curr] = in[id_xplus]-in[id_curr];
            grady[id_curr] = in[id_yplus]-in[id_curr];
        }
    }
}

// apply the TV reverse operator to take the spatial image gradient in
// gradx and grady and apply it back to the output image, as if using
// the transpose of a matrix that computes gradients
void tv_bw( const int *dim, const double *gradx, const double *grady, double *out ){
    int id_curr, id_xplus, id_yplus;
    for( int i=0; i<dim[0]; i++ ){
        for( int j=0; j<dim[1]; j++ ){
            out[ID(i,j)] = 0.0;
        }
    }
    for( int i=0; i<dim[0]; i++ ){
        for( int j=0; j<dim[1]; j++ ){
            id_curr  = ID(i,j);
            id_xplus = i < dim[0]-1 ? ID(i+1,j) : ID(i-1,j);
            id_yplus = j < dim[1]-1 ? ID(i,j+1) : ID(i,j-1);
            
            out[id_curr]  += -1.0*gradx[id_curr];
            out[id_xplus] += +1.0*gradx[id_curr];
            
            out[id_curr]  += -1.0*grady[id_curr];
            out[id_yplus] += +1.0*grady[id_curr];
        }
    }
}