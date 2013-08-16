%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [ eigval ] = power_iteration( dim, FW, BW, iters )
%power_iteration Estimate the largest Eigenvalue of a linear operator
% provided by the FW and BW functions, corresponding to the application of
% the operator and its transpose
    b = rand( dim(1), dim(2) );
    L = 0.0;
    for i=1:iters,
        b = BW( FW( b ) );
        eigval = norm(b);
        b = b/eigval;
    end
end

