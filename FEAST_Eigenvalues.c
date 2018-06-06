/* Eigenvector and Eigenvalue calculation using FEAST algorithm
 * Anant Shah
 * Date : 18-12-2017
 * */
#include<stdio.h>
#include<mkl.h>
#include<stdlib.h>
#include<sys/time.h>

int main(int argc,char **argv)
{
        double*         mat; // Cauchy matrix whose eigenvalues are to be found
        MKL_INT         fpm[128]; //128 size array whose paramteres act as inputs to the routines
        MKL_INT         size; // Size of the problem
        MKL_INT         lda; // Sets the leading dimension of the array
        double          epsout; // Contains the relative error of the trace
        MKL_INT         loop; // Number of refinement loops executed
        double          lambda_min,lambda_max; // The range in which the eigenvalues will lie
        MKL_INT         dim_subspace; // Guess of the subspace dimension 
        double*         eigenvalues; // Eigenvalues are stored in the array
        double*         eigenvectors; // Matrix containig the eigenvectors
        MKL_INT         eigen_num; // NUmber of eigenvalues in the range
        double*         res; //Relative residual vector
        MKL_INT         info; // Checks if the execution is successful
        MKL_INT         DIM; // Dimension of the square matrix
        MKL_INT         i,j; // Loop iteration variables        
        struct timeval  First_Time,Last_Time;
        double          overhead; // Time take to find the eigenvalues

        /* Assigning the inputs */
        if(argc!=4)
        {
                printf("error : invalid arguments \n");
                exit(0);
        }


        DIM = atoi(argv[1]);
        lambda_min = atof( argv[2] );
        lambda_max = atof( argv[3] );
        dim_subspace = DIM;
        size = DIM;
        lda  = DIM;

        /* Memory allocation to the matrix */
        mat = (double *)malloc( DIM*DIM*sizeof(double) );
        eigenvalues = (double *)malloc( DIM*sizeof(double) );
        eigenvectors = (double *)malloc( DIM*DIM*sizeof(double) );
        res = (double *)malloc( dim_subspace*sizeof(double) );

        /* Initialize the Cauchy matrix */
        for(i=0;i<DIM;i++)
                for(j=0;j<DIM;j++)
                        mat[i*DIM+j] = (double)1.0/(i+j+2);

        /* Printing the matrix */
        for(i=0;i<DIM;i++){
                for(j=0;j<DIM;j++)
                        printf("%.14f ",mat[i*DIM+j]);
                printf("\n");
        }

        gettimeofday(&First_Time,0);
        /* Initialize the FEAST function */

        feastinit(fpm);

        /* Call the FEAST funciton to find the eigenvalues */

        dfeast_syev( "F"  , &size , mat , &lda , fpm , &epsout , &loop ,&lambda_min, &lambda_max , &dim_subspace , eigenvalues , eigenvectors , &eigen_num , res, &info);

        gettimeofday(&Last_Time,0);

        if(info > 0)
        {
                printf("error : eigenvalue function not executed correctly \n");
                exit(0);
        }


        printf("Eigenvalues : \t \n \n ");

        for(i=0;i<DIM;i++)
                printf("%.20f \n ",eigenvalues[i]);

        overhead = ( (Last_Time.tv_sec + Last_Time.tv_usec*1000000 ) - ( First_Time.tv_sec + First_Time.tv_usec*1000000) )/1000000;

        printf("Time taken by CPU (in micro seconds): %.14f \n",overhead);
        return 0;
}
                                 
