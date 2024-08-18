# Makefile for Prologpp


CPP=clang++-6.0
CPP=g++-7
CPP=clang++

STD=-std=c++11
FLAGS=-Wall -std=c++17
INCS = parse.h predicate.h prolog.h protran.h
SRCS = parse.cc predicate.cc prolog.cc protran.cc

all : prologpp

prologpp : ${SRCS} ${INCS} 
	${CPP} -o prologpp ${SRCS} ${FLAGS}




