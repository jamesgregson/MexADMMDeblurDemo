%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                       %%
%% Matlab + Mex Image Deblurring with ADMM Demo                          %%
%% Author: James Gregson 2013                                            %%
%% License: GPL                                                          %%
%%                                                                       %%
%% Notes:                                                                %%
%% Uses the ADMM algorithm to deblur synthetically blurred and noise-    %%
%% corrupted images, enforcing sparsity of the solution via the          %%
%% anisotropic total-variation regularizer. ADMM is applied using the    %%
%% Generalized Lasso formulation from Stephen Boyd et al.'s "Distributed %%
%% Optimization and Statistical Learning via the Alternating Direction   %%
%% Method of Multipliers" paper.                                         %%
%%                                                                       %%
%% Most of the meat is in .h and .cpp files that implement the linear    %%
%% operators (and their transposes) defining the image formation model   %%
%% and the constraint matrix needed to implement isotropic TV. I did     %%
%% this to get more familiar with using MEX and representing these       %%
%% operations using matrix-free representations.                         %%
%%                                                                       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;
close all;

% remove any lingering compiled modules, then build the forward and reverse
% operators for the image-formation model and the anisotropic TV prior
system('rm *.mexmaci64');
mex CFLAGS="\$CFLAGS -O3 -DNDEBUG" IFMForward.cpp image_formation_model.cpp
mex CFLAGS="\$CFLAGS -O3 -DNDEBUG" IFMReverse.cpp image_formation_model.cpp
mex CFLAGS="\$CFLAGS -O3 -DNDEBUG" TVForward.cpp tv.cpp
mex CFLAGS="\$CFLAGS -O3 -DNDEBUG" TVReverse.cpp tv.cpp

% define the image width and height as well as standard deviation of the
% noise to be added to the blurred image
width  = 400;
height = 400; 
noise_sigma = 0.03;

% ADMM parameters, rho is the penalty term weight, lambda is the prior
% weight, outer iterations is the number of full ADMM steps to run and
% inner_iterations is the number of gradient-descent steps to run for
% each outer iteration, i.e. related to how accurately the data subproblem 
% is solved.
rho = 0.1;
lambda = 0.025;
outer_iterations = 50;
inner_iterations = 3;

% generate a simple start image consisting of all zeros except a square
% in the middle of value 1
in = zeros( width, height );
in( width/4:3*width/4, height/4:3*height/4 ) = 1.0;

% generate an input image to the deblurring problem by blurring by the
% forward model, use this as an initial guess for the sharp solution
blur = IFMForward( in );
blur = blur + noise_sigma*randn( size(blur) );
x = blur;

figure;
subplot( 121 );
imagesc( in );
colormap jet;
subplot( 122 );
imagesc( blur );
colormap jet;
drawnow;

% initialize the Lagrange multipliers for the X and Y directions, then
% initialize the X and Y splitting variable by evaluating the Anisotropic
% Total-Variation function
ux = zeros( width, height );
uy = zeros( width, height );
[dx,dy] = TVForward( x );

% estimate the singular values of the operator to determine the maximum
% stable step length that can be taken for the data subproblem
blurfwhandle = @IFMForward;
blurbwhandle = @IFMReverse;
sing_max = power_iteration( size(in), blurfwhandle, blurbwhandle, 10 );

% create figure to display results as the solver proceeds
figure;

% main solver loop
for j=1:outer_iterations,

    % print out the current outer iteration index
    %if mod(j,10) == 0
        fprintf( 'iteration [%d/%d]\n', j, outer_iterations );
    %end
    
    % plot a slice through the sharp image, the blurred image and the 
    % current solution estimate and update this plot as the algorithm 
    % proceeds to get a feel for the convergence behavior
    subplot( 131 )
    plot( in( size(blur,1)/2,: ), 'k' );
    hold on
    plot( blur( size(blur,1)/2,: ), 'r-' );
    plot( x( size(blur,1)/2,: ), 'bo' );
    hold off
    drawnow;
    subplot( 132 );
    imagesc( x );
    drawnow;
    subplot( 133 );
    imagesc( abs(x-in) );
    colormap jet;
    drawnow;
    
    % Perform the data-subproblem update, use inner_iterations steps of
    % gradient-descent combined with solf-thresholding of the splitting
    % variables
    for m=1:inner_iterations,
        % one gradient descent iteration on the data-subproblem
        [ gradx, grady ] = TVForward( x );
        x = x - (1.0/sing_max)*( ...
                IFMReverse( IFMForward( x ) - blur ) + ...
                rho*TVReverse(gradx-dx+ux,grady-dy+uy) ...
            );   
        
        % perform the z-update using shrinkage for the 
        % regularizer subproblem, re-evaluate gradx,grady 
        % to use the updated values of x
        [gradx, grady] = TVForward(x);
        dx = shrink( gradx+ux, lambda/rho );
        dy = shrink( grady+uy, lambda/rho );       
    end
    
    % update the Lagrange multipliers based on the error in 
    % the constraint term
    ux = ux + (gradx - dx);
    uy = uy + (grady - dy); 
    
end

