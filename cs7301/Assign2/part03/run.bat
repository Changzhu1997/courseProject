@echo off
@set inputFile=Example
@set CLASSPATH=.;../lib/soot-3.3.0.jar
javac *.java
java TestSootLogging %inputFile%
java TestSootLogging2 %inputFile%
cd ./sootOutput
java %inputFile%
cd ../
java TestSootLoggingHeap
