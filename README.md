# eigen-finder
Finding the eigenvalues of a cauchy matrix using different math libraries.

LAPACK Library used for calculating the eigenvalues of a Cauchy matrix

Intel MKL required for LAPACK. 
Install MKL.
LAPACK is a standard software library for numerical linear algebra.

Operating System : Ubuntu

Compiler : icc

Script :
#!/bin/bash
icc $@ -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl -DMKL_ILP64 -I${MKLROOT}/include

Save the script as a <command>, example : mklcc in /bin folder
Executable of the script : chmod +x <script_name>
To support different environments,tools and interfaces MKL provides multiple libraries to choose from.
Depending on the specification of your system, the flags will change. 
