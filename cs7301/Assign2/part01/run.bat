@echo off
@set inputFile=GCD
@set CLASSPATH=.;../lib/soot-3.3.0.jar
javac *.java
java TestDominatorFinder

