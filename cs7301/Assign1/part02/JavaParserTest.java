import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.antlr.v4.runtime.ANTLRFileStream;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;

public class JavaParserTest extends Java8BaseListener{
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
    Java8Parser parser = new Java8Parser(tokens); //create parser

    ParseTree tree = parser.compilationUnit();
    ParseTreeWalker walker = new ParseTreeWalker(); // create standard walker
    JavaParserTest listener = new JavaParserTest(); // create a parse tree listener
    walker.walk(listener, tree); // traverse parse tree with listener
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
					System.out.println(stmt + " " + ctx.getStart().getLine());
				}
		}
	}
}
