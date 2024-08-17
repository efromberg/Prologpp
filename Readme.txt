Readme.txt		Summary of Prologpp S/W		8/15/24

Intro
	Prologpp is an implementation of basic Prolog in C++;
it is based on a very bare bones implementation in 250 LOC
by A.Mycroft (Ref.1).   The current version contains a
translator to convert a standard prolog text program(database)
into C++ structures. 
	Prologpp is a simplified version of standard prolog; it was
developed to reveal the implementation of the basic prolog search
algorithm which is used to solve logical queries against a database
of facts and relations.  Prologpp will eventually be a C++ library,
which implements the prolog search algorithm, accept inputs
from a C++ program, and return results to that program.  Prolog
does not need to be a standalone programming language and environment,
but will be implemented as a C++ library, which implements the
prolog search algorithm.
	There is a simple CLI which allows the user to enter
queries against the pre-loaded prolog text program. 
Prologpp implements integer arithmetic, and it uses prefix
notation only, not infix notation, except for lists, where it 
uses the standard prolog list notation.  The cut (!) operator
is not implemented.
	Prologpp can execute many of the programs given in
introductory texts (Ref.2), after conversion to pre-fix
notation. A collection of test and demo programs is in the
/scripts directory.

Compile
	The S/W consists of 8 files; the Makefile compiles them into
the executable  prologpp, using the command  $ make.  Each user should 
edit the Makefile to use his C++ compiler, typically g++ or clang++.
No external libraries are needed.
	Compilation using Apple clang++ version 14.0.0 on macOS Monterey
Version 12.7.6 results in 1 warning message.
	Compilation using g++ version 9.4.0 on Ubuntu 20.04.6 results
in no warning messages.

Usage
	The executable and test file Nqueens2.pl should be in the same
directory, so the initial test case at the command line is:
$ ./prologpp Nqueens2.pl	
	should give the 10 solutions for Nqueens problem with N=5.
	The query is at the end of the program file.
	The program accepts queries after the ?- prompt:
?- solution(6, X).
	Will give the 4 solutions, with N=6.








References:
1.	A.Mycroft, https://www.cl.cam.ac.uk/~am21/research/funnel
2.  P.Blackburn,J.Bos,K.Striegnitz, "Learn Prolog Now!"

