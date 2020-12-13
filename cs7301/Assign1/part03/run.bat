@echo off
@set inputFile=../Test.java
@set CLASSPATH=.;../lib/antlr-4.7-complete.jar
doskey antlr4=java org.antlr.v4.Tool $*
doskey grun=java org.antlr.v4.gui.TestRig $*
javac Java8*.java
grun Java compilationUnit *.java
javac JavaParserTest.java
java JavaParserTest %inputFile%

