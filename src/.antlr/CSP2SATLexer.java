// Generated from /Users/roger21gm/CLionProjects/CSP2SAT/src/CSP2SAT.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CSP2SATLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		WS=1, LINE_COMMENT=2, BLOCK_COMMENT=3, TK_ENTITIES=4, TK_VIEWPOINT=5, 
		TK_CONSTRAINTS=6, TK_OUTPUT=7, TK_COLON=8, TK_SEMICOLON=9, TK_UNDERSCORE=10, 
		TK_ASSIGN=11, TK_PARAM=12, TK_VAR=13, TK_AUX=14, TK_CONSTRAINT=15, TK_INT_VALUE=16, 
		TK_BOOLEAN_VALUE=17, TK_BASE_TYPE_INT=18, TK_BASE_TYPE_BOOL=19, TK_IN=20, 
		TK_RANGE_DOTS=21, TK_IF=22, TK_ELSEIF=23, TK_ELSE=24, TK_LPAREN=25, TK_RPAREN=26, 
		TK_LCLAUDATOR=27, TK_RCLAUDATOR=28, TK_LBRACKET=29, TK_RBRACKET=30, TK_COMMA=31, 
		TK_DOT=32, TK_WHERE=33, TK_FORALL=34, TK_OP_AGG_SUM=35, TK_OP_AGG_LENGTH=36, 
		TK_OP_AGG_MAX=37, TK_OP_AGG_MIN=38, TK_OP_LOGIC_NOT=39, TK_OP_LOGIC_AND=40, 
		TK_OP_LOGIC_OR=41, TK_OP_ARIT_SUM=42, TK_OP_ARIT_DIFF=43, TK_OP_ARIT_MULT=44, 
		TK_OP_ARIT_DIV=45, TK_OP_ARIT_MOD=46, TK_OP_REL_LT=47, TK_OP_REL_GT=48, 
		TK_OP_REL_GE=49, TK_OP_REL_LE=50, TK_OP_REL_EQ=51, TK_OP_REL_NEQ=52, TK_OP_IMPLIC_R=53, 
		TK_OP_IMPLIC_L=54, TK_OP_DOUBLE_IMPLIC=55, TK_INTERROGANT=56, TK_CONSTRAINT_OR_PIPE=57, 
		TK_CONSTRAINT_AND=58, TK_CONSTRAINT_NOT=59, TK_CONSTRAINT_AGG_EK=60, TK_CONSTRAINT_AGG_EO=61, 
		TK_CONSTRAINT_AGG_ALK=62, TK_CONSTRAINT_AGG_ALO=63, TK_CONSTRAINT_AGG_AMK=64, 
		TK_CONSTRAINT_AGG_AMO=65, TK_IDENT=66, TK_STRING=67, TK_STRING_AGG_OP=68;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"WS", "LINE_COMMENT", "BLOCK_COMMENT", "TK_ENTITIES", "TK_VIEWPOINT", 
		"TK_CONSTRAINTS", "TK_OUTPUT", "TK_COLON", "TK_SEMICOLON", "TK_UNDERSCORE", 
		"TK_ASSIGN", "TK_PARAM", "TK_VAR", "TK_AUX", "TK_CONSTRAINT", "TK_INT_VALUE", 
		"TK_BOOLEAN_VALUE", "TK_BASE_TYPE_INT", "TK_BASE_TYPE_BOOL", "TK_IN", 
		"TK_RANGE_DOTS", "TK_IF", "TK_ELSEIF", "TK_ELSE", "TK_LPAREN", "TK_RPAREN", 
		"TK_LCLAUDATOR", "TK_RCLAUDATOR", "TK_LBRACKET", "TK_RBRACKET", "TK_COMMA", 
		"TK_DOT", "TK_WHERE", "TK_FORALL", "TK_OP_AGG_SUM", "TK_OP_AGG_LENGTH", 
		"TK_OP_AGG_MAX", "TK_OP_AGG_MIN", "TK_OP_LOGIC_NOT", "TK_OP_LOGIC_AND", 
		"TK_OP_LOGIC_OR", "TK_OP_ARIT_SUM", "TK_OP_ARIT_DIFF", "TK_OP_ARIT_MULT", 
		"TK_OP_ARIT_DIV", "TK_OP_ARIT_MOD", "TK_OP_REL_LT", "TK_OP_REL_GT", "TK_OP_REL_GE", 
		"TK_OP_REL_LE", "TK_OP_REL_EQ", "TK_OP_REL_NEQ", "TK_OP_IMPLIC_R", "TK_OP_IMPLIC_L", 
		"TK_OP_DOUBLE_IMPLIC", "TK_INTERROGANT", "TK_CONSTRAINT_OR_PIPE", "TK_CONSTRAINT_AND", 
		"TK_CONSTRAINT_NOT", "TK_CONSTRAINT_AGG_EK", "TK_CONSTRAINT_AGG_EO", "TK_CONSTRAINT_AGG_ALK", 
		"TK_CONSTRAINT_AGG_ALO", "TK_CONSTRAINT_AGG_AMK", "TK_CONSTRAINT_AGG_AMO", 
		"TK_IDENT", "ESCAPED_QUOTE", "TK_STRING", "TK_STRING_AGG_OP"
	};

	private static final String[] _LITERAL_NAMES = {
		null, null, null, null, "'entities'", "'viewpoint'", "'constraints'", 
		"'output'", "':'", "';'", "'_'", "':='", "'param'", "'var'", "'aux'", 
		"'constraint'", null, null, "'int'", "'bool'", "'in'", "'..'", "'if'", 
		"'else if'", "'else'", "'('", "')'", "'['", "']'", "'{'", "'}'", "','", 
		"'.'", "'where'", "'forall'", "'sum'", "'length'", "'max'", "'min'", "'not'", 
		"'and'", "'or'", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'>='", 
		"'<='", "'=='", "'!='", "'->'", "'<-'", "'<->'", "'?'", "'|'", "'&'", 
		"'!'", "'EK'", "'EO'", "'ALK'", "'ALO'", "'AMK'", "'AMO'", null, null, 
		"'++'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "WS", "LINE_COMMENT", "BLOCK_COMMENT", "TK_ENTITIES", "TK_VIEWPOINT", 
		"TK_CONSTRAINTS", "TK_OUTPUT", "TK_COLON", "TK_SEMICOLON", "TK_UNDERSCORE", 
		"TK_ASSIGN", "TK_PARAM", "TK_VAR", "TK_AUX", "TK_CONSTRAINT", "TK_INT_VALUE", 
		"TK_BOOLEAN_VALUE", "TK_BASE_TYPE_INT", "TK_BASE_TYPE_BOOL", "TK_IN", 
		"TK_RANGE_DOTS", "TK_IF", "TK_ELSEIF", "TK_ELSE", "TK_LPAREN", "TK_RPAREN", 
		"TK_LCLAUDATOR", "TK_RCLAUDATOR", "TK_LBRACKET", "TK_RBRACKET", "TK_COMMA", 
		"TK_DOT", "TK_WHERE", "TK_FORALL", "TK_OP_AGG_SUM", "TK_OP_AGG_LENGTH", 
		"TK_OP_AGG_MAX", "TK_OP_AGG_MIN", "TK_OP_LOGIC_NOT", "TK_OP_LOGIC_AND", 
		"TK_OP_LOGIC_OR", "TK_OP_ARIT_SUM", "TK_OP_ARIT_DIFF", "TK_OP_ARIT_MULT", 
		"TK_OP_ARIT_DIV", "TK_OP_ARIT_MOD", "TK_OP_REL_LT", "TK_OP_REL_GT", "TK_OP_REL_GE", 
		"TK_OP_REL_LE", "TK_OP_REL_EQ", "TK_OP_REL_NEQ", "TK_OP_IMPLIC_R", "TK_OP_IMPLIC_L", 
		"TK_OP_DOUBLE_IMPLIC", "TK_INTERROGANT", "TK_CONSTRAINT_OR_PIPE", "TK_CONSTRAINT_AND", 
		"TK_CONSTRAINT_NOT", "TK_CONSTRAINT_AGG_EK", "TK_CONSTRAINT_AGG_EO", "TK_CONSTRAINT_AGG_ALK", 
		"TK_CONSTRAINT_AGG_ALO", "TK_CONSTRAINT_AGG_AMK", "TK_CONSTRAINT_AGG_AMO", 
		"TK_IDENT", "TK_STRING", "TK_STRING_AGG_OP"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public CSP2SATLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "CSP2SAT.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2F\u01bd\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\3\2\6\2\u008f\n"+
		"\2\r\2\16\2\u0090\3\2\3\2\3\3\3\3\3\3\3\3\7\3\u0099\n\3\f\3\16\3\u009c"+
		"\13\3\3\3\3\3\3\4\3\4\3\4\3\4\7\4\u00a4\n\4\f\4\16\4\u00a7\13\4\3\4\3"+
		"\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6"+
		"\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\f\3\f\3\f\3\r\3"+
		"\r\3\r\3\r\3\r\3\r\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3\20\3\20\3"+
		"\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\21\3\21\7\21\u00f8\n\21"+
		"\f\21\16\21\u00fb\13\21\3\21\5\21\u00fe\n\21\3\22\3\22\3\22\3\22\3\22"+
		"\3\22\3\22\3\22\3\22\5\22\u0109\n\22\3\23\3\23\3\23\3\23\3\24\3\24\3\24"+
		"\3\24\3\24\3\25\3\25\3\25\3\26\3\26\3\26\3\27\3\27\3\27\3\30\3\30\3\30"+
		"\3\30\3\30\3\30\3\30\3\30\3\31\3\31\3\31\3\31\3\31\3\32\3\32\3\33\3\33"+
		"\3\34\3\34\3\35\3\35\3\36\3\36\3\37\3\37\3 \3 \3!\3!\3\"\3\"\3\"\3\"\3"+
		"\"\3\"\3#\3#\3#\3#\3#\3#\3#\3$\3$\3$\3$\3%\3%\3%\3%\3%\3%\3%\3&\3&\3&"+
		"\3&\3\'\3\'\3\'\3\'\3(\3(\3(\3(\3)\3)\3)\3)\3*\3*\3*\3+\3+\3,\3,\3-\3"+
		"-\3.\3.\3/\3/\3\60\3\60\3\61\3\61\3\62\3\62\3\62\3\63\3\63\3\63\3\64\3"+
		"\64\3\64\3\65\3\65\3\65\3\66\3\66\3\66\3\67\3\67\3\67\38\38\38\38\39\3"+
		"9\3:\3:\3;\3;\3<\3<\3=\3=\3=\3>\3>\3>\3?\3?\3?\3?\3@\3@\3@\3@\3A\3A\3"+
		"A\3A\3B\3B\3B\3B\3C\3C\7C\u01a9\nC\fC\16C\u01ac\13C\3D\3D\3D\3E\3E\3E"+
		"\7E\u01b4\nE\fE\16E\u01b7\13E\3E\3E\3F\3F\3F\4\u00a5\u01b5\2G\3\3\5\4"+
		"\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22"+
		"#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C"+
		"#E$G%I&K\'M(O)Q*S+U,W-Y.[/]\60_\61a\62c\63e\64g\65i\66k\67m8o9q:s;u<w"+
		"=y>{?}@\177A\u0081B\u0083C\u0085D\u0087\2\u0089E\u008bF\3\2\7\5\2\13\f"+
		"\17\17\"\"\4\2\f\f\17\17\5\2C\\aac|\6\2\62;C\\aac|\3\2$$\2\u01c4\2\3\3"+
		"\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2"+
		"\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3"+
		"\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2"+
		"%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61"+
		"\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2"+
		"\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I"+
		"\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2"+
		"\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2"+
		"\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2m\3\2\2\2\2o"+
		"\3\2\2\2\2q\3\2\2\2\2s\3\2\2\2\2u\3\2\2\2\2w\3\2\2\2\2y\3\2\2\2\2{\3\2"+
		"\2\2\2}\3\2\2\2\2\177\3\2\2\2\2\u0081\3\2\2\2\2\u0083\3\2\2\2\2\u0085"+
		"\3\2\2\2\2\u0089\3\2\2\2\2\u008b\3\2\2\2\3\u008e\3\2\2\2\5\u0094\3\2\2"+
		"\2\7\u009f\3\2\2\2\t\u00ad\3\2\2\2\13\u00b6\3\2\2\2\r\u00c0\3\2\2\2\17"+
		"\u00cc\3\2\2\2\21\u00d3\3\2\2\2\23\u00d5\3\2\2\2\25\u00d7\3\2\2\2\27\u00d9"+
		"\3\2\2\2\31\u00dc\3\2\2\2\33\u00e2\3\2\2\2\35\u00e6\3\2\2\2\37\u00ea\3"+
		"\2\2\2!\u00fd\3\2\2\2#\u0108\3\2\2\2%\u010a\3\2\2\2\'\u010e\3\2\2\2)\u0113"+
		"\3\2\2\2+\u0116\3\2\2\2-\u0119\3\2\2\2/\u011c\3\2\2\2\61\u0124\3\2\2\2"+
		"\63\u0129\3\2\2\2\65\u012b\3\2\2\2\67\u012d\3\2\2\29\u012f\3\2\2\2;\u0131"+
		"\3\2\2\2=\u0133\3\2\2\2?\u0135\3\2\2\2A\u0137\3\2\2\2C\u0139\3\2\2\2E"+
		"\u013f\3\2\2\2G\u0146\3\2\2\2I\u014a\3\2\2\2K\u0151\3\2\2\2M\u0155\3\2"+
		"\2\2O\u0159\3\2\2\2Q\u015d\3\2\2\2S\u0161\3\2\2\2U\u0164\3\2\2\2W\u0166"+
		"\3\2\2\2Y\u0168\3\2\2\2[\u016a\3\2\2\2]\u016c\3\2\2\2_\u016e\3\2\2\2a"+
		"\u0170\3\2\2\2c\u0172\3\2\2\2e\u0175\3\2\2\2g\u0178\3\2\2\2i\u017b\3\2"+
		"\2\2k\u017e\3\2\2\2m\u0181\3\2\2\2o\u0184\3\2\2\2q\u0188\3\2\2\2s\u018a"+
		"\3\2\2\2u\u018c\3\2\2\2w\u018e\3\2\2\2y\u0190\3\2\2\2{\u0193\3\2\2\2}"+
		"\u0196\3\2\2\2\177\u019a\3\2\2\2\u0081\u019e\3\2\2\2\u0083\u01a2\3\2\2"+
		"\2\u0085\u01a6\3\2\2\2\u0087\u01ad\3\2\2\2\u0089\u01b0\3\2\2\2\u008b\u01ba"+
		"\3\2\2\2\u008d\u008f\t\2\2\2\u008e\u008d\3\2\2\2\u008f\u0090\3\2\2\2\u0090"+
		"\u008e\3\2\2\2\u0090\u0091\3\2\2\2\u0091\u0092\3\2\2\2\u0092\u0093\b\2"+
		"\2\2\u0093\4\3\2\2\2\u0094\u0095\7\61\2\2\u0095\u0096\7\61\2\2\u0096\u009a"+
		"\3\2\2\2\u0097\u0099\n\3\2\2\u0098\u0097\3\2\2\2\u0099\u009c\3\2\2\2\u009a"+
		"\u0098\3\2\2\2\u009a\u009b\3\2\2\2\u009b\u009d\3\2\2\2\u009c\u009a\3\2"+
		"\2\2\u009d\u009e\b\3\2\2\u009e\6\3\2\2\2\u009f\u00a0\7\61\2\2\u00a0\u00a1"+
		"\7,\2\2\u00a1\u00a5\3\2\2\2\u00a2\u00a4\13\2\2\2\u00a3\u00a2\3\2\2\2\u00a4"+
		"\u00a7\3\2\2\2\u00a5\u00a6\3\2\2\2\u00a5\u00a3\3\2\2\2\u00a6\u00a8\3\2"+
		"\2\2\u00a7\u00a5\3\2\2\2\u00a8\u00a9\7,\2\2\u00a9\u00aa\7\61\2\2\u00aa"+
		"\u00ab\3\2\2\2\u00ab\u00ac\b\4\2\2\u00ac\b\3\2\2\2\u00ad\u00ae\7g\2\2"+
		"\u00ae\u00af\7p\2\2\u00af\u00b0\7v\2\2\u00b0\u00b1\7k\2\2\u00b1\u00b2"+
		"\7v\2\2\u00b2\u00b3\7k\2\2\u00b3\u00b4\7g\2\2\u00b4\u00b5\7u\2\2\u00b5"+
		"\n\3\2\2\2\u00b6\u00b7\7x\2\2\u00b7\u00b8\7k\2\2\u00b8\u00b9\7g\2\2\u00b9"+
		"\u00ba\7y\2\2\u00ba\u00bb\7r\2\2\u00bb\u00bc\7q\2\2\u00bc\u00bd\7k\2\2"+
		"\u00bd\u00be\7p\2\2\u00be\u00bf\7v\2\2\u00bf\f\3\2\2\2\u00c0\u00c1\7e"+
		"\2\2\u00c1\u00c2\7q\2\2\u00c2\u00c3\7p\2\2\u00c3\u00c4\7u\2\2\u00c4\u00c5"+
		"\7v\2\2\u00c5\u00c6\7t\2\2\u00c6\u00c7\7c\2\2\u00c7\u00c8\7k\2\2\u00c8"+
		"\u00c9\7p\2\2\u00c9\u00ca\7v\2\2\u00ca\u00cb\7u\2\2\u00cb\16\3\2\2\2\u00cc"+
		"\u00cd\7q\2\2\u00cd\u00ce\7w\2\2\u00ce\u00cf\7v\2\2\u00cf\u00d0\7r\2\2"+
		"\u00d0\u00d1\7w\2\2\u00d1\u00d2\7v\2\2\u00d2\20\3\2\2\2\u00d3\u00d4\7"+
		"<\2\2\u00d4\22\3\2\2\2\u00d5\u00d6\7=\2\2\u00d6\24\3\2\2\2\u00d7\u00d8"+
		"\7a\2\2\u00d8\26\3\2\2\2\u00d9\u00da\7<\2\2\u00da\u00db\7?\2\2\u00db\30"+
		"\3\2\2\2\u00dc\u00dd\7r\2\2\u00dd\u00de\7c\2\2\u00de\u00df\7t\2\2\u00df"+
		"\u00e0\7c\2\2\u00e0\u00e1\7o\2\2\u00e1\32\3\2\2\2\u00e2\u00e3\7x\2\2\u00e3"+
		"\u00e4\7c\2\2\u00e4\u00e5\7t\2\2\u00e5\34\3\2\2\2\u00e6\u00e7\7c\2\2\u00e7"+
		"\u00e8\7w\2\2\u00e8\u00e9\7z\2\2\u00e9\36\3\2\2\2\u00ea\u00eb\7e\2\2\u00eb"+
		"\u00ec\7q\2\2\u00ec\u00ed\7p\2\2\u00ed\u00ee\7u\2\2\u00ee\u00ef\7v\2\2"+
		"\u00ef\u00f0\7t\2\2\u00f0\u00f1\7c\2\2\u00f1\u00f2\7k\2\2\u00f2\u00f3"+
		"\7p\2\2\u00f3\u00f4\7v\2\2\u00f4 \3\2\2\2\u00f5\u00f9\4\63;\2\u00f6\u00f8"+
		"\4\62;\2\u00f7\u00f6\3\2\2\2\u00f8\u00fb\3\2\2\2\u00f9\u00f7\3\2\2\2\u00f9"+
		"\u00fa\3\2\2\2\u00fa\u00fe\3\2\2\2\u00fb\u00f9\3\2\2\2\u00fc\u00fe\7\62"+
		"\2\2\u00fd\u00f5\3\2\2\2\u00fd\u00fc\3\2\2\2\u00fe\"\3\2\2\2\u00ff\u0100"+
		"\7v\2\2\u0100\u0101\7t\2\2\u0101\u0102\7w\2\2\u0102\u0109\7g\2\2\u0103"+
		"\u0104\7h\2\2\u0104\u0105\7c\2\2\u0105\u0106\7n\2\2\u0106\u0107\7u\2\2"+
		"\u0107\u0109\7g\2\2\u0108\u00ff\3\2\2\2\u0108\u0103\3\2\2\2\u0109$\3\2"+
		"\2\2\u010a\u010b\7k\2\2\u010b\u010c\7p\2\2\u010c\u010d\7v\2\2\u010d&\3"+
		"\2\2\2\u010e\u010f\7d\2\2\u010f\u0110\7q\2\2\u0110\u0111\7q\2\2\u0111"+
		"\u0112\7n\2\2\u0112(\3\2\2\2\u0113\u0114\7k\2\2\u0114\u0115\7p\2\2\u0115"+
		"*\3\2\2\2\u0116\u0117\7\60\2\2\u0117\u0118\7\60\2\2\u0118,\3\2\2\2\u0119"+
		"\u011a\7k\2\2\u011a\u011b\7h\2\2\u011b.\3\2\2\2\u011c\u011d\7g\2\2\u011d"+
		"\u011e\7n\2\2\u011e\u011f\7u\2\2\u011f\u0120\7g\2\2\u0120\u0121\7\"\2"+
		"\2\u0121\u0122\7k\2\2\u0122\u0123\7h\2\2\u0123\60\3\2\2\2\u0124\u0125"+
		"\7g\2\2\u0125\u0126\7n\2\2\u0126\u0127\7u\2\2\u0127\u0128\7g\2\2\u0128"+
		"\62\3\2\2\2\u0129\u012a\7*\2\2\u012a\64\3\2\2\2\u012b\u012c\7+\2\2\u012c"+
		"\66\3\2\2\2\u012d\u012e\7]\2\2\u012e8\3\2\2\2\u012f\u0130\7_\2\2\u0130"+
		":\3\2\2\2\u0131\u0132\7}\2\2\u0132<\3\2\2\2\u0133\u0134\7\177\2\2\u0134"+
		">\3\2\2\2\u0135\u0136\7.\2\2\u0136@\3\2\2\2\u0137\u0138\7\60\2\2\u0138"+
		"B\3\2\2\2\u0139\u013a\7y\2\2\u013a\u013b\7j\2\2\u013b\u013c\7g\2\2\u013c"+
		"\u013d\7t\2\2\u013d\u013e\7g\2\2\u013eD\3\2\2\2\u013f\u0140\7h\2\2\u0140"+
		"\u0141\7q\2\2\u0141\u0142\7t\2\2\u0142\u0143\7c\2\2\u0143\u0144\7n\2\2"+
		"\u0144\u0145\7n\2\2\u0145F\3\2\2\2\u0146\u0147\7u\2\2\u0147\u0148\7w\2"+
		"\2\u0148\u0149\7o\2\2\u0149H\3\2\2\2\u014a\u014b\7n\2\2\u014b\u014c\7"+
		"g\2\2\u014c\u014d\7p\2\2\u014d\u014e\7i\2\2\u014e\u014f\7v\2\2\u014f\u0150"+
		"\7j\2\2\u0150J\3\2\2\2\u0151\u0152\7o\2\2\u0152\u0153\7c\2\2\u0153\u0154"+
		"\7z\2\2\u0154L\3\2\2\2\u0155\u0156\7o\2\2\u0156\u0157\7k\2\2\u0157\u0158"+
		"\7p\2\2\u0158N\3\2\2\2\u0159\u015a\7p\2\2\u015a\u015b\7q\2\2\u015b\u015c"+
		"\7v\2\2\u015cP\3\2\2\2\u015d\u015e\7c\2\2\u015e\u015f\7p\2\2\u015f\u0160"+
		"\7f\2\2\u0160R\3\2\2\2\u0161\u0162\7q\2\2\u0162\u0163\7t\2\2\u0163T\3"+
		"\2\2\2\u0164\u0165\7-\2\2\u0165V\3\2\2\2\u0166\u0167\7/\2\2\u0167X\3\2"+
		"\2\2\u0168\u0169\7,\2\2\u0169Z\3\2\2\2\u016a\u016b\7\61\2\2\u016b\\\3"+
		"\2\2\2\u016c\u016d\7\'\2\2\u016d^\3\2\2\2\u016e\u016f\7>\2\2\u016f`\3"+
		"\2\2\2\u0170\u0171\7@\2\2\u0171b\3\2\2\2\u0172\u0173\7@\2\2\u0173\u0174"+
		"\7?\2\2\u0174d\3\2\2\2\u0175\u0176\7>\2\2\u0176\u0177\7?\2\2\u0177f\3"+
		"\2\2\2\u0178\u0179\7?\2\2\u0179\u017a\7?\2\2\u017ah\3\2\2\2\u017b\u017c"+
		"\7#\2\2\u017c\u017d\7?\2\2\u017dj\3\2\2\2\u017e\u017f\7/\2\2\u017f\u0180"+
		"\7@\2\2\u0180l\3\2\2\2\u0181\u0182\7>\2\2\u0182\u0183\7/\2\2\u0183n\3"+
		"\2\2\2\u0184\u0185\7>\2\2\u0185\u0186\7/\2\2\u0186\u0187\7@\2\2\u0187"+
		"p\3\2\2\2\u0188\u0189\7A\2\2\u0189r\3\2\2\2\u018a\u018b\7~\2\2\u018bt"+
		"\3\2\2\2\u018c\u018d\7(\2\2\u018dv\3\2\2\2\u018e\u018f\7#\2\2\u018fx\3"+
		"\2\2\2\u0190\u0191\7G\2\2\u0191\u0192\7M\2\2\u0192z\3\2\2\2\u0193\u0194"+
		"\7G\2\2\u0194\u0195\7Q\2\2\u0195|\3\2\2\2\u0196\u0197\7C\2\2\u0197\u0198"+
		"\7N\2\2\u0198\u0199\7M\2\2\u0199~\3\2\2\2\u019a\u019b\7C\2\2\u019b\u019c"+
		"\7N\2\2\u019c\u019d\7Q\2\2\u019d\u0080\3\2\2\2\u019e\u019f\7C\2\2\u019f"+
		"\u01a0\7O\2\2\u01a0\u01a1\7M\2\2\u01a1\u0082\3\2\2\2\u01a2\u01a3\7C\2"+
		"\2\u01a3\u01a4\7O\2\2\u01a4\u01a5\7Q\2\2\u01a5\u0084\3\2\2\2\u01a6\u01aa"+
		"\t\4\2\2\u01a7\u01a9\t\5\2\2\u01a8\u01a7\3\2\2\2\u01a9\u01ac\3\2\2\2\u01aa"+
		"\u01a8\3\2\2\2\u01aa\u01ab\3\2\2\2\u01ab\u0086\3\2\2\2\u01ac\u01aa\3\2"+
		"\2\2\u01ad\u01ae\7^\2\2\u01ae\u01af\7$\2\2\u01af\u0088\3\2\2\2\u01b0\u01b5"+
		"\7$\2\2\u01b1\u01b4\5\u0087D\2\u01b2\u01b4\n\6\2\2\u01b3\u01b1\3\2\2\2"+
		"\u01b3\u01b2\3\2\2\2\u01b4\u01b7\3\2\2\2\u01b5\u01b6\3\2\2\2\u01b5\u01b3"+
		"\3\2\2\2\u01b6\u01b8\3\2\2\2\u01b7\u01b5\3\2\2\2\u01b8\u01b9\7$\2\2\u01b9"+
		"\u008a\3\2\2\2\u01ba\u01bb\7-\2\2\u01bb\u01bc\7-\2\2\u01bc\u008c\3\2\2"+
		"\2\f\2\u0090\u009a\u00a5\u00f9\u00fd\u0108\u01aa\u01b3\u01b5\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}