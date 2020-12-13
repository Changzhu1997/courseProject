@echo off
@set inputFile=HelloThread
@set CLASSPATH=.;../lib/soot-3.3.0.jar
javac TestSoot.java
javac %inputFile%.java
java TestSoot

