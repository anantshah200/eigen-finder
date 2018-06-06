/* Anant Shah
 * Eigenvalues using LAPACK
 * Date : 15-12-2017
 * */
#include<stdio.h>
#include<stdlib.h>
#include<mkl.h>
#include<sys/time.h>

void mat_gen(int DIM,double* mat);

int main(int argc,char **argv)
{
        /* Variable INitialization */
        MKL_INT         M,N; // Read matrices size from the command line 
        double*         mat; // Matrix whose eigenvectors are to be found
        MKL_INT         i,j;// Variables iterating through the matrix row and column
        MKL_INT         Size,lda,loop; // Store the size and leading dimension of the array
        double*         eigenvalues; // Array of length m0 ; first m entries are the eigenvalues in the interval
        double          val;
        MKL_INT         info; //Will contain if the execution was successful
        struct timeval  First_Time,Last_Time; // These will be use dto calculate the time taken for the process
        float           overhead; // Time taken by the CPU to comput the function


        if(argc!=3) // Tests invalid number of arguments
        {
                printf("error :  Invalid number of arguments \n");
                exit(0);
        }

        /* Reading row ad column from the command line */
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        /* Set the leading dimesnion of the matrix */
        lda = M; // Leading dimension : Lenght of the first dimension of the array
        Size = N;

        if(M==0)
        {
                printf("error : Invalid ROW dimension entered \n");
                exit(0);
        }
        if(N==0)
        {
                printf("error : Invalid COLUMN dimension entered \n");
                exit(0);
        }
        /* Memory allocation of the matrix */

        mat=(double *)malloc( M*N*sizeof(double) );

        eigenvalues = (double *)malloc( M*sizeof(double) );

        /* Calling the matrix generator function */

        mat_gen( M,mat );
        /*for(i=0;i<M;i++)
                for(j=0;j<N;j++)
                        mat[i*M+j]=(double)1.0/((i+1)+(j+1));
        */

        /* Printing the matrix */
        printf("Cauchy  Matrix :\n \n ");

        for(i=0;i<M;i++){
                for(j=0;j<N;j++)
                        printf("%.14f ",mat[i*M+j]);
                printf("\n");
        }

        gettimeofday(&First_Time,0);
        /* Find eigenvectors in the given range usign dsyev*/

        info = LAPACKE_dsyev( LAPACK_COL_MAJOR, 'N' , 'L' , M , mat , lda , eigenvalues );

        gettimeofday(&Last_Time,0);


        if(info>0){
                printf("Algorithm failed to print eigenvalues \n");
                exit(0);
        }
        /* Printing the eigenvalues themselves */


        for(i=0;i<M;i++)
                printf(" %d. Eigenvalue : \t \t %.14f \n",i,eigenvalues[i]);

        overhead = ( ( Last_Time.tv_sec*1000000 + Last_Time.tv_usec) - ( First_Time.tv_sec*1000000 + First_Time.tv_usec) )/1000000 ;

        printf(" Time Taken for Computation ( In Seconds ): \t \t %.14f \n",overhead);

        free(mat);
        free(eigenvalues);
}

void mat_gen(int DIM,double* mat)
{
        int             i,j; // Loop iteration variables

        /* Assign values to the elements in the matrix */
        for(i=0;i<DIM;i++)
                for(j=0;j<DIM;j++)
                        mat[i*DIM+j] = (double)1.0/((i+1)+(j+1));

}

