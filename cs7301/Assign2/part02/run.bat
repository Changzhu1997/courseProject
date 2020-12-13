@echo off
@set inputFile=Example
@set CLASSPATH=.;../lib/soot-3.3.0.jar
javac TestSootCallGraph.java
javac %inputFile%.java
java TestSootCallGraph Example

