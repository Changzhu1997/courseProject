import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.antlr.v4.runtime.ANTLRFileStream;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import org.antlr.v4.runtime.TokenStreamRewriter;
import org.antlr.v4.runtime.Token;

public class JavaParserTest extends Java8BaseListener{
  public static TokenStreamRewriter rewriter;
  public static void main(String[] args) throws IOException {
    if(args.length<1)
    {
      System.err.println("java JavaParserTest input-filename\n"
          +"Example: java JavaParserTest Test.java");
      return;
    }
    String inputFile = args[0];
    CharStream input = new ANTLRFileStream(inputFile);
    Java8Lexer lexer = new Java8Lexer(input);
    CommonTokenStream tokens = new CommonTokenStream(lexer);
    rewriter = new TokenStreamRewriter(tokens);
    Java8Parser parser = new Java8Parser(tokens); //create parser

    ParseTree tree = parser.compilationUnit();
    ParseTreeWalker walker = new ParseTreeWalker(); // create standard walker
    JavaParserTest listener = new JavaParserTest(); // create a parse tree listener
    walker.walk(listener, tree); // traverse parse tree with listener
  }
  
  public String indention = "";
  public String getWhiteSpace(TokenStreamRewriter rewriter, int index){
    String curr = ""; 
    String ifIndention = "";
    String prevIndention = "";
    while (index > 0) {
      index--;
      curr = rewriter.getTokenStream().get(index).getText();
      if (curr.contains("\n") && ifIndention.length() == 0) {
        
        ifIndention += curr;
        
      } else if (curr.contains("\n") && curr.contains("\t") && ifIndention.length() > curr.length()) {
        
        prevIndention += curr;
        break;
        
      }
    }
    
    indention = ifIndention.substring(prevIndention.length(), ifIndention.length());
    return ifIndention + indention;
  }

  /**
   * {@inheritDoc}
   */
  @Override
  public void enterStatement(Java8Parser.StatementContext ctx){
    
    if (ctx.getStart().getText().equals("if")) {
        String stmt = ctx.getChild(0).getChild(2).getText();
        Pattern pattern = Pattern.compile("^[A-Za-z]+[A-Za-z0-9_]*$");
        Matcher matcher = pattern.matcher(stmt);
        if (stmt.length() > 3 && matcher.find()) {          
          int start = ctx.getChild(0).getChild(4).getSourceInterval().a;
          int end = ctx.getChild(0).getChild(4).getSourceInterval().b;
          
          String whitespace = getWhiteSpace(rewriter, ctx.getChild(0).getSourceInterval().a);
          
          if (rewriter.getTokenStream().get(start).getText().equals("{")) {
            start++;
            rewriter.insertBefore(rewriter.getTokenStream().get(start), whitespace + "System.out.println(\"" + stmt + " " + ctx.getStart().getLine() + "\");\n");
          } else {
            rewriter.insertBefore(rewriter.getTokenStream().get(start), "{" + whitespace + "System.out.println(\"" + stmt + " " + ctx.getStart().getLine() + "\");" + whitespace);
            rewriter.insertAfter(rewriter.getTokenStream().get(end), whitespace.substring(0, whitespace.length() - indention.length()) + "}\n");
          }
          System.out.println(rewriter.getText());
        }
    }
  }
}
