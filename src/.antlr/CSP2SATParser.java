// Generated from /Users/roger21gm/CLionProjects/CSP2SAT/src/CSP2SAT.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CSP2SATParser extends Parser {
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
	public static final int
		RULE_csp2sat = 0, RULE_definition = 1, RULE_entityDefinitionBlock = 2, 
		RULE_entityDefinition = 3, RULE_viewpointBlock = 4, RULE_constraintDefinitionBlock = 5, 
		RULE_outputBlock = 6, RULE_varDefinition = 7, RULE_paramDefinition = 8, 
		RULE_arrayDefinition = 9, RULE_expr = 10, RULE_opAggregateExpr = 11, RULE_exprListAgg = 12, 
		RULE_exprAnd = 13, RULE_exprOr = 14, RULE_opEquality = 15, RULE_exprEq = 16, 
		RULE_opRelational = 17, RULE_exprRel = 18, RULE_opSumDiff = 19, RULE_exprSumDiff = 20, 
		RULE_opMulDivMod = 21, RULE_exprMulDivMod = 22, RULE_exprNot = 23, RULE_expr_base = 24, 
		RULE_varAccess = 25, RULE_varAccessObjectOrArray = 26, RULE_valueBaseType = 27, 
		RULE_constraintDefinition = 28, RULE_auxiliarListAssignation = 29, RULE_localConstraintDefinitionBlock = 30, 
		RULE_forall = 31, RULE_ifThenElse = 32, RULE_list = 33, RULE_listResultExpr = 34, 
		RULE_constraint = 35, RULE_constraint_expression = 36, RULE_constraint_double_implication = 37, 
		RULE_implication_operator = 38, RULE_constraint_implication = 39, RULE_constraint_or = 40, 
		RULE_constraint_or_2 = 41, RULE_constraint_and = 42, RULE_constraint_and_2 = 43, 
		RULE_constraint_literal = 44, RULE_constraint_base = 45, RULE_aggregate_op = 46, 
		RULE_constraint_aggreggate_op = 47, RULE_string = 48, RULE_stringTernary = 49, 
		RULE_concatString = 50;
	public static final String[] ruleNames = {
		"csp2sat", "definition", "entityDefinitionBlock", "entityDefinition", 
		"viewpointBlock", "constraintDefinitionBlock", "outputBlock", "varDefinition", 
		"paramDefinition", "arrayDefinition", "expr", "opAggregateExpr", "exprListAgg", 
		"exprAnd", "exprOr", "opEquality", "exprEq", "opRelational", "exprRel", 
		"opSumDiff", "exprSumDiff", "opMulDivMod", "exprMulDivMod", "exprNot", 
		"expr_base", "varAccess", "varAccessObjectOrArray", "valueBaseType", "constraintDefinition", 
		"auxiliarListAssignation", "localConstraintDefinitionBlock", "forall", 
		"ifThenElse", "list", "listResultExpr", "constraint", "constraint_expression", 
		"constraint_double_implication", "implication_operator", "constraint_implication", 
		"constraint_or", "constraint_or_2", "constraint_and", "constraint_and_2", 
		"constraint_literal", "constraint_base", "aggregate_op", "constraint_aggreggate_op", 
		"string", "stringTernary", "concatString"
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

	@Override
	public String getGrammarFileName() { return "CSP2SAT.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CSP2SATParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class Csp2satContext extends ParserRuleContext {
		public ViewpointBlockContext viewpointBlock() {
			return getRuleContext(ViewpointBlockContext.class,0);
		}
		public ConstraintDefinitionBlockContext constraintDefinitionBlock() {
			return getRuleContext(ConstraintDefinitionBlockContext.class,0);
		}
		public EntityDefinitionBlockContext entityDefinitionBlock() {
			return getRuleContext(EntityDefinitionBlockContext.class,0);
		}
		public OutputBlockContext outputBlock() {
			return getRuleContext(OutputBlockContext.class,0);
		}
		public Csp2satContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_csp2sat; }
	}

	public final Csp2satContext csp2sat() throws RecognitionException {
		Csp2satContext _localctx = new Csp2satContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_csp2sat);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(103);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_ENTITIES) {
				{
				setState(102);
				entityDefinitionBlock();
				}
			}

			setState(105);
			viewpointBlock();
			setState(106);
			constraintDefinitionBlock();
			setState(108);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_OUTPUT) {
				{
				setState(107);
				outputBlock();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DefinitionContext extends ParserRuleContext {
		public VarDefinitionContext varDefinition() {
			return getRuleContext(VarDefinitionContext.class,0);
		}
		public ParamDefinitionContext paramDefinition() {
			return getRuleContext(ParamDefinitionContext.class,0);
		}
		public DefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_definition; }
	}

	public final DefinitionContext definition() throws RecognitionException {
		DefinitionContext _localctx = new DefinitionContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_definition);
		try {
			setState(112);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_VAR:
				enterOuterAlt(_localctx, 1);
				{
				setState(110);
				varDefinition();
				}
				break;
			case TK_PARAM:
			case TK_IDENT:
				enterOuterAlt(_localctx, 2);
				{
				setState(111);
				paramDefinition();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EntityDefinitionBlockContext extends ParserRuleContext {
		public TerminalNode TK_ENTITIES() { return getToken(CSP2SATParser.TK_ENTITIES, 0); }
		public TerminalNode TK_COLON() { return getToken(CSP2SATParser.TK_COLON, 0); }
		public List<EntityDefinitionContext> entityDefinition() {
			return getRuleContexts(EntityDefinitionContext.class);
		}
		public EntityDefinitionContext entityDefinition(int i) {
			return getRuleContext(EntityDefinitionContext.class,i);
		}
		public EntityDefinitionBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_entityDefinitionBlock; }
	}

	public final EntityDefinitionBlockContext entityDefinitionBlock() throws RecognitionException {
		EntityDefinitionBlockContext _localctx = new EntityDefinitionBlockContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_entityDefinitionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(114);
			match(TK_ENTITIES);
			setState(115);
			match(TK_COLON);
			setState(119);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_IDENT) {
				{
				{
				setState(116);
				entityDefinition();
				}
				}
				setState(121);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EntityDefinitionContext extends ParserRuleContext {
		public Token name;
		public TerminalNode TK_LBRACKET() { return getToken(CSP2SATParser.TK_LBRACKET, 0); }
		public TerminalNode TK_RBRACKET() { return getToken(CSP2SATParser.TK_RBRACKET, 0); }
		public TerminalNode TK_SEMICOLON() { return getToken(CSP2SATParser.TK_SEMICOLON, 0); }
		public TerminalNode TK_IDENT() { return getToken(CSP2SATParser.TK_IDENT, 0); }
		public List<DefinitionContext> definition() {
			return getRuleContexts(DefinitionContext.class);
		}
		public DefinitionContext definition(int i) {
			return getRuleContext(DefinitionContext.class,i);
		}
		public EntityDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_entityDefinition; }
	}

	public final EntityDefinitionContext entityDefinition() throws RecognitionException {
		EntityDefinitionContext _localctx = new EntityDefinitionContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_entityDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(122);
			((EntityDefinitionContext)_localctx).name = match(TK_IDENT);
			setState(123);
			match(TK_LBRACKET);
			setState(127);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 12)) & ~0x3f) == 0 && ((1L << (_la - 12)) & ((1L << (TK_PARAM - 12)) | (1L << (TK_VAR - 12)) | (1L << (TK_IDENT - 12)))) != 0)) {
				{
				{
				setState(124);
				definition();
				}
				}
				setState(129);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(130);
			match(TK_RBRACKET);
			setState(131);
			match(TK_SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ViewpointBlockContext extends ParserRuleContext {
		public TerminalNode TK_VIEWPOINT() { return getToken(CSP2SATParser.TK_VIEWPOINT, 0); }
		public TerminalNode TK_COLON() { return getToken(CSP2SATParser.TK_COLON, 0); }
		public List<DefinitionContext> definition() {
			return getRuleContexts(DefinitionContext.class);
		}
		public DefinitionContext definition(int i) {
			return getRuleContext(DefinitionContext.class,i);
		}
		public ViewpointBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_viewpointBlock; }
	}

	public final ViewpointBlockContext viewpointBlock() throws RecognitionException {
		ViewpointBlockContext _localctx = new ViewpointBlockContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_viewpointBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(133);
			match(TK_VIEWPOINT);
			setState(134);
			match(TK_COLON);
			setState(138);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 12)) & ~0x3f) == 0 && ((1L << (_la - 12)) & ((1L << (TK_PARAM - 12)) | (1L << (TK_VAR - 12)) | (1L << (TK_IDENT - 12)))) != 0)) {
				{
				{
				setState(135);
				definition();
				}
				}
				setState(140);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstraintDefinitionBlockContext extends ParserRuleContext {
		public TerminalNode TK_CONSTRAINTS() { return getToken(CSP2SATParser.TK_CONSTRAINTS, 0); }
		public TerminalNode TK_COLON() { return getToken(CSP2SATParser.TK_COLON, 0); }
		public List<ConstraintDefinitionContext> constraintDefinition() {
			return getRuleContexts(ConstraintDefinitionContext.class);
		}
		public ConstraintDefinitionContext constraintDefinition(int i) {
			return getRuleContext(ConstraintDefinitionContext.class,i);
		}
		public ConstraintDefinitionBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraintDefinitionBlock; }
	}

	public final ConstraintDefinitionBlockContext constraintDefinitionBlock() throws RecognitionException {
		ConstraintDefinitionBlockContext _localctx = new ConstraintDefinitionBlockContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_constraintDefinitionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(141);
			match(TK_CONSTRAINTS);
			setState(142);
			match(TK_COLON);
			setState(146);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 17)) & ~0x3f) == 0 && ((1L << (_la - 17)) & ((1L << (TK_BOOLEAN_VALUE - 17)) | (1L << (TK_IF - 17)) | (1L << (TK_LPAREN - 17)) | (1L << (TK_FORALL - 17)) | (1L << (TK_CONSTRAINT_OR_PIPE - 17)) | (1L << (TK_CONSTRAINT_AND - 17)) | (1L << (TK_CONSTRAINT_NOT - 17)) | (1L << (TK_CONSTRAINT_AGG_EK - 17)) | (1L << (TK_CONSTRAINT_AGG_EO - 17)) | (1L << (TK_CONSTRAINT_AGG_ALK - 17)) | (1L << (TK_CONSTRAINT_AGG_ALO - 17)) | (1L << (TK_CONSTRAINT_AGG_AMK - 17)) | (1L << (TK_CONSTRAINT_AGG_AMO - 17)) | (1L << (TK_IDENT - 17)))) != 0)) {
				{
				{
				setState(143);
				constraintDefinition();
				}
				}
				setState(148);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OutputBlockContext extends ParserRuleContext {
		public TerminalNode TK_OUTPUT() { return getToken(CSP2SATParser.TK_OUTPUT, 0); }
		public TerminalNode TK_COLON() { return getToken(CSP2SATParser.TK_COLON, 0); }
		public List<StringContext> string() {
			return getRuleContexts(StringContext.class);
		}
		public StringContext string(int i) {
			return getRuleContext(StringContext.class,i);
		}
		public List<TerminalNode> TK_SEMICOLON() { return getTokens(CSP2SATParser.TK_SEMICOLON); }
		public TerminalNode TK_SEMICOLON(int i) {
			return getToken(CSP2SATParser.TK_SEMICOLON, i);
		}
		public OutputBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_outputBlock; }
	}

	public final OutputBlockContext outputBlock() throws RecognitionException {
		OutputBlockContext _localctx = new OutputBlockContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_outputBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(149);
			match(TK_OUTPUT);
			setState(150);
			match(TK_COLON);
			setState(156);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 16)) & ~0x3f) == 0 && ((1L << (_la - 16)) & ((1L << (TK_INT_VALUE - 16)) | (1L << (TK_BOOLEAN_VALUE - 16)) | (1L << (TK_LPAREN - 16)) | (1L << (TK_LCLAUDATOR - 16)) | (1L << (TK_OP_AGG_SUM - 16)) | (1L << (TK_OP_AGG_LENGTH - 16)) | (1L << (TK_OP_AGG_MAX - 16)) | (1L << (TK_OP_AGG_MIN - 16)) | (1L << (TK_OP_LOGIC_NOT - 16)) | (1L << (TK_IDENT - 16)) | (1L << (TK_STRING - 16)))) != 0)) {
				{
				{
				setState(151);
				string(0);
				setState(152);
				match(TK_SEMICOLON);
				}
				}
				setState(158);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarDefinitionContext extends ParserRuleContext {
		public Token type;
		public Token name;
		public TerminalNode TK_VAR() { return getToken(CSP2SATParser.TK_VAR, 0); }
		public ArrayDefinitionContext arrayDefinition() {
			return getRuleContext(ArrayDefinitionContext.class,0);
		}
		public TerminalNode TK_SEMICOLON() { return getToken(CSP2SATParser.TK_SEMICOLON, 0); }
		public TerminalNode TK_IDENT() { return getToken(CSP2SATParser.TK_IDENT, 0); }
		public TerminalNode TK_BASE_TYPE_BOOL() { return getToken(CSP2SATParser.TK_BASE_TYPE_BOOL, 0); }
		public VarDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDefinition; }
	}

	public final VarDefinitionContext varDefinition() throws RecognitionException {
		VarDefinitionContext _localctx = new VarDefinitionContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_varDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(159);
			match(TK_VAR);
			setState(161);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_BASE_TYPE_BOOL) {
				{
				setState(160);
				((VarDefinitionContext)_localctx).type = match(TK_BASE_TYPE_BOOL);
				}
			}

			setState(163);
			((VarDefinitionContext)_localctx).name = match(TK_IDENT);
			setState(164);
			arrayDefinition();
			setState(165);
			match(TK_SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParamDefinitionContext extends ParserRuleContext {
		public Token type;
		public Token name;
		public ArrayDefinitionContext arrayDefinition() {
			return getRuleContext(ArrayDefinitionContext.class,0);
		}
		public TerminalNode TK_SEMICOLON() { return getToken(CSP2SATParser.TK_SEMICOLON, 0); }
		public List<TerminalNode> TK_IDENT() { return getTokens(CSP2SATParser.TK_IDENT); }
		public TerminalNode TK_IDENT(int i) {
			return getToken(CSP2SATParser.TK_IDENT, i);
		}
		public TerminalNode TK_PARAM() { return getToken(CSP2SATParser.TK_PARAM, 0); }
		public TerminalNode TK_BASE_TYPE_BOOL() { return getToken(CSP2SATParser.TK_BASE_TYPE_BOOL, 0); }
		public TerminalNode TK_BASE_TYPE_INT() { return getToken(CSP2SATParser.TK_BASE_TYPE_INT, 0); }
		public ParamDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_paramDefinition; }
	}

	public final ParamDefinitionContext paramDefinition() throws RecognitionException {
		ParamDefinitionContext _localctx = new ParamDefinitionContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_paramDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(170);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_PARAM:
				{
				setState(167);
				match(TK_PARAM);
				setState(168);
				((ParamDefinitionContext)_localctx).type = _input.LT(1);
				_la = _input.LA(1);
				if ( !(_la==TK_BASE_TYPE_INT || _la==TK_BASE_TYPE_BOOL) ) {
					((ParamDefinitionContext)_localctx).type = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				break;
			case TK_IDENT:
				{
				setState(169);
				((ParamDefinitionContext)_localctx).type = match(TK_IDENT);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(172);
			((ParamDefinitionContext)_localctx).name = match(TK_IDENT);
			setState(173);
			arrayDefinition();
			setState(174);
			match(TK_SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArrayDefinitionContext extends ParserRuleContext {
		public ExprContext arraySize;
		public List<TerminalNode> TK_LCLAUDATOR() { return getTokens(CSP2SATParser.TK_LCLAUDATOR); }
		public TerminalNode TK_LCLAUDATOR(int i) {
			return getToken(CSP2SATParser.TK_LCLAUDATOR, i);
		}
		public List<TerminalNode> TK_RCLAUDATOR() { return getTokens(CSP2SATParser.TK_RCLAUDATOR); }
		public TerminalNode TK_RCLAUDATOR(int i) {
			return getToken(CSP2SATParser.TK_RCLAUDATOR, i);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ArrayDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayDefinition; }
	}

	public final ArrayDefinitionContext arrayDefinition() throws RecognitionException {
		ArrayDefinitionContext _localctx = new ArrayDefinitionContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_arrayDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(182);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_LCLAUDATOR) {
				{
				{
				setState(176);
				match(TK_LCLAUDATOR);
				setState(177);
				((ArrayDefinitionContext)_localctx).arraySize = expr();
				setState(178);
				match(TK_RCLAUDATOR);
				}
				}
				setState(184);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ExprTopContext extends ExprContext {
		public ExprListAggContext exprListAgg() {
			return getRuleContext(ExprListAggContext.class,0);
		}
		public ExprTopContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ExprTernaryContext extends ExprContext {
		public ExprAndContext condition;
		public ExprContext op1;
		public ExprContext op2;
		public TerminalNode TK_INTERROGANT() { return getToken(CSP2SATParser.TK_INTERROGANT, 0); }
		public TerminalNode TK_COLON() { return getToken(CSP2SATParser.TK_COLON, 0); }
		public ExprAndContext exprAnd() {
			return getRuleContext(ExprAndContext.class,0);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ExprTernaryContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_expr);
		try {
			setState(192);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				_localctx = new ExprTopContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(185);
				exprListAgg();
				}
				break;
			case 2:
				_localctx = new ExprTernaryContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(186);
				((ExprTernaryContext)_localctx).condition = exprAnd();
				setState(187);
				match(TK_INTERROGANT);
				setState(188);
				((ExprTernaryContext)_localctx).op1 = expr();
				setState(189);
				match(TK_COLON);
				setState(190);
				((ExprTernaryContext)_localctx).op2 = expr();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OpAggregateExprContext extends ParserRuleContext {
		public TerminalNode TK_OP_AGG_LENGTH() { return getToken(CSP2SATParser.TK_OP_AGG_LENGTH, 0); }
		public TerminalNode TK_OP_AGG_MAX() { return getToken(CSP2SATParser.TK_OP_AGG_MAX, 0); }
		public TerminalNode TK_OP_AGG_MIN() { return getToken(CSP2SATParser.TK_OP_AGG_MIN, 0); }
		public TerminalNode TK_OP_AGG_SUM() { return getToken(CSP2SATParser.TK_OP_AGG_SUM, 0); }
		public OpAggregateExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_opAggregateExpr; }
	}

	public final OpAggregateExprContext opAggregateExpr() throws RecognitionException {
		OpAggregateExprContext _localctx = new OpAggregateExprContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_opAggregateExpr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(194);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << TK_OP_AGG_SUM) | (1L << TK_OP_AGG_LENGTH) | (1L << TK_OP_AGG_MAX) | (1L << TK_OP_AGG_MIN))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprListAggContext extends ParserRuleContext {
		public ExprListAggContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprListAgg; }
	 
		public ExprListAggContext() { }
		public void copyFrom(ExprListAggContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ExprListAggregateOpContext extends ExprListAggContext {
		public OpAggregateExprContext opAggregateExpr() {
			return getRuleContext(OpAggregateExprContext.class,0);
		}
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public ListContext list() {
			return getRuleContext(ListContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public ExprListAggregateOpContext(ExprListAggContext ctx) { copyFrom(ctx); }
	}
	public static class ExprAnd2Context extends ExprListAggContext {
		public ExprAndContext exprAnd() {
			return getRuleContext(ExprAndContext.class,0);
		}
		public ExprAnd2Context(ExprListAggContext ctx) { copyFrom(ctx); }
	}

	public final ExprListAggContext exprListAgg() throws RecognitionException {
		ExprListAggContext _localctx = new ExprListAggContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_exprListAgg);
		try {
			setState(202);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_OP_AGG_SUM:
			case TK_OP_AGG_LENGTH:
			case TK_OP_AGG_MAX:
			case TK_OP_AGG_MIN:
				_localctx = new ExprListAggregateOpContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(196);
				opAggregateExpr();
				setState(197);
				match(TK_LPAREN);
				setState(198);
				list();
				setState(199);
				match(TK_RPAREN);
				}
				break;
			case TK_INT_VALUE:
			case TK_BOOLEAN_VALUE:
			case TK_LPAREN:
			case TK_OP_LOGIC_NOT:
			case TK_IDENT:
				_localctx = new ExprAnd2Context(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(201);
				exprAnd();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprAndContext extends ParserRuleContext {
		public List<ExprOrContext> exprOr() {
			return getRuleContexts(ExprOrContext.class);
		}
		public ExprOrContext exprOr(int i) {
			return getRuleContext(ExprOrContext.class,i);
		}
		public List<TerminalNode> TK_OP_LOGIC_AND() { return getTokens(CSP2SATParser.TK_OP_LOGIC_AND); }
		public TerminalNode TK_OP_LOGIC_AND(int i) {
			return getToken(CSP2SATParser.TK_OP_LOGIC_AND, i);
		}
		public ExprAndContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprAnd; }
	}

	public final ExprAndContext exprAnd() throws RecognitionException {
		ExprAndContext _localctx = new ExprAndContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_exprAnd);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(204);
			exprOr();
			setState(209);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,13,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(205);
					match(TK_OP_LOGIC_AND);
					setState(206);
					exprOr();
					}
					} 
				}
				setState(211);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,13,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprOrContext extends ParserRuleContext {
		public List<ExprEqContext> exprEq() {
			return getRuleContexts(ExprEqContext.class);
		}
		public ExprEqContext exprEq(int i) {
			return getRuleContext(ExprEqContext.class,i);
		}
		public List<TerminalNode> TK_OP_LOGIC_OR() { return getTokens(CSP2SATParser.TK_OP_LOGIC_OR); }
		public TerminalNode TK_OP_LOGIC_OR(int i) {
			return getToken(CSP2SATParser.TK_OP_LOGIC_OR, i);
		}
		public ExprOrContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprOr; }
	}

	public final ExprOrContext exprOr() throws RecognitionException {
		ExprOrContext _localctx = new ExprOrContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_exprOr);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(212);
			exprEq();
			setState(217);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,14,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(213);
					match(TK_OP_LOGIC_OR);
					setState(214);
					exprEq();
					}
					} 
				}
				setState(219);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,14,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OpEqualityContext extends ParserRuleContext {
		public TerminalNode TK_OP_REL_EQ() { return getToken(CSP2SATParser.TK_OP_REL_EQ, 0); }
		public TerminalNode TK_OP_REL_NEQ() { return getToken(CSP2SATParser.TK_OP_REL_NEQ, 0); }
		public OpEqualityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_opEquality; }
	}

	public final OpEqualityContext opEquality() throws RecognitionException {
		OpEqualityContext _localctx = new OpEqualityContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_opEquality);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(220);
			_la = _input.LA(1);
			if ( !(_la==TK_OP_REL_EQ || _la==TK_OP_REL_NEQ) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprEqContext extends ParserRuleContext {
		public List<ExprRelContext> exprRel() {
			return getRuleContexts(ExprRelContext.class);
		}
		public ExprRelContext exprRel(int i) {
			return getRuleContext(ExprRelContext.class,i);
		}
		public List<OpEqualityContext> opEquality() {
			return getRuleContexts(OpEqualityContext.class);
		}
		public OpEqualityContext opEquality(int i) {
			return getRuleContext(OpEqualityContext.class,i);
		}
		public ExprEqContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprEq; }
	}

	public final ExprEqContext exprEq() throws RecognitionException {
		ExprEqContext _localctx = new ExprEqContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_exprEq);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(222);
			exprRel();
			setState(228);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,15,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(223);
					opEquality();
					setState(224);
					exprRel();
					}
					} 
				}
				setState(230);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,15,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OpRelationalContext extends ParserRuleContext {
		public TerminalNode TK_OP_REL_LT() { return getToken(CSP2SATParser.TK_OP_REL_LT, 0); }
		public TerminalNode TK_OP_REL_GT() { return getToken(CSP2SATParser.TK_OP_REL_GT, 0); }
		public TerminalNode TK_OP_REL_GE() { return getToken(CSP2SATParser.TK_OP_REL_GE, 0); }
		public TerminalNode TK_OP_REL_LE() { return getToken(CSP2SATParser.TK_OP_REL_LE, 0); }
		public OpRelationalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_opRelational; }
	}

	public final OpRelationalContext opRelational() throws RecognitionException {
		OpRelationalContext _localctx = new OpRelationalContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_opRelational);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(231);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << TK_OP_REL_LT) | (1L << TK_OP_REL_GT) | (1L << TK_OP_REL_GE) | (1L << TK_OP_REL_LE))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprRelContext extends ParserRuleContext {
		public List<ExprSumDiffContext> exprSumDiff() {
			return getRuleContexts(ExprSumDiffContext.class);
		}
		public ExprSumDiffContext exprSumDiff(int i) {
			return getRuleContext(ExprSumDiffContext.class,i);
		}
		public List<OpRelationalContext> opRelational() {
			return getRuleContexts(OpRelationalContext.class);
		}
		public OpRelationalContext opRelational(int i) {
			return getRuleContext(OpRelationalContext.class,i);
		}
		public ExprRelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprRel; }
	}

	public final ExprRelContext exprRel() throws RecognitionException {
		ExprRelContext _localctx = new ExprRelContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_exprRel);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(233);
			exprSumDiff();
			setState(239);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(234);
					opRelational();
					setState(235);
					exprSumDiff();
					}
					} 
				}
				setState(241);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OpSumDiffContext extends ParserRuleContext {
		public TerminalNode TK_OP_ARIT_SUM() { return getToken(CSP2SATParser.TK_OP_ARIT_SUM, 0); }
		public TerminalNode TK_OP_ARIT_DIFF() { return getToken(CSP2SATParser.TK_OP_ARIT_DIFF, 0); }
		public OpSumDiffContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_opSumDiff; }
	}

	public final OpSumDiffContext opSumDiff() throws RecognitionException {
		OpSumDiffContext _localctx = new OpSumDiffContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_opSumDiff);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(242);
			_la = _input.LA(1);
			if ( !(_la==TK_OP_ARIT_SUM || _la==TK_OP_ARIT_DIFF) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprSumDiffContext extends ParserRuleContext {
		public List<ExprMulDivModContext> exprMulDivMod() {
			return getRuleContexts(ExprMulDivModContext.class);
		}
		public ExprMulDivModContext exprMulDivMod(int i) {
			return getRuleContext(ExprMulDivModContext.class,i);
		}
		public List<OpSumDiffContext> opSumDiff() {
			return getRuleContexts(OpSumDiffContext.class);
		}
		public OpSumDiffContext opSumDiff(int i) {
			return getRuleContext(OpSumDiffContext.class,i);
		}
		public ExprSumDiffContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprSumDiff; }
	}

	public final ExprSumDiffContext exprSumDiff() throws RecognitionException {
		ExprSumDiffContext _localctx = new ExprSumDiffContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_exprSumDiff);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(244);
			exprMulDivMod();
			setState(250);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,17,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(245);
					opSumDiff();
					setState(246);
					exprMulDivMod();
					}
					} 
				}
				setState(252);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,17,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class OpMulDivModContext extends ParserRuleContext {
		public TerminalNode TK_OP_ARIT_MULT() { return getToken(CSP2SATParser.TK_OP_ARIT_MULT, 0); }
		public TerminalNode TK_OP_ARIT_DIV() { return getToken(CSP2SATParser.TK_OP_ARIT_DIV, 0); }
		public TerminalNode TK_OP_ARIT_MOD() { return getToken(CSP2SATParser.TK_OP_ARIT_MOD, 0); }
		public OpMulDivModContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_opMulDivMod; }
	}

	public final OpMulDivModContext opMulDivMod() throws RecognitionException {
		OpMulDivModContext _localctx = new OpMulDivModContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_opMulDivMod);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(253);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << TK_OP_ARIT_MULT) | (1L << TK_OP_ARIT_DIV) | (1L << TK_OP_ARIT_MOD))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprMulDivModContext extends ParserRuleContext {
		public List<ExprNotContext> exprNot() {
			return getRuleContexts(ExprNotContext.class);
		}
		public ExprNotContext exprNot(int i) {
			return getRuleContext(ExprNotContext.class,i);
		}
		public List<OpMulDivModContext> opMulDivMod() {
			return getRuleContexts(OpMulDivModContext.class);
		}
		public OpMulDivModContext opMulDivMod(int i) {
			return getRuleContext(OpMulDivModContext.class,i);
		}
		public ExprMulDivModContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprMulDivMod; }
	}

	public final ExprMulDivModContext exprMulDivMod() throws RecognitionException {
		ExprMulDivModContext _localctx = new ExprMulDivModContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_exprMulDivMod);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(255);
			exprNot();
			setState(261);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(256);
					opMulDivMod();
					setState(257);
					exprNot();
					}
					} 
				}
				setState(263);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprNotContext extends ParserRuleContext {
		public Token op;
		public Expr_baseContext expr_base() {
			return getRuleContext(Expr_baseContext.class,0);
		}
		public TerminalNode TK_OP_LOGIC_NOT() { return getToken(CSP2SATParser.TK_OP_LOGIC_NOT, 0); }
		public ExprNotContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprNot; }
	}

	public final ExprNotContext exprNot() throws RecognitionException {
		ExprNotContext _localctx = new ExprNotContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_exprNot);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(265);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_OP_LOGIC_NOT) {
				{
				setState(264);
				((ExprNotContext)_localctx).op = match(TK_OP_LOGIC_NOT);
				}
			}

			setState(267);
			expr_base();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Expr_baseContext extends ParserRuleContext {
		public ValueBaseTypeContext valueBaseType() {
			return getRuleContext(ValueBaseTypeContext.class,0);
		}
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public VarAccessContext varAccess() {
			return getRuleContext(VarAccessContext.class,0);
		}
		public Expr_baseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_base; }
	}

	public final Expr_baseContext expr_base() throws RecognitionException {
		Expr_baseContext _localctx = new Expr_baseContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_expr_base);
		try {
			setState(275);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_INT_VALUE:
			case TK_BOOLEAN_VALUE:
				enterOuterAlt(_localctx, 1);
				{
				setState(269);
				valueBaseType();
				}
				break;
			case TK_LPAREN:
				enterOuterAlt(_localctx, 2);
				{
				setState(270);
				match(TK_LPAREN);
				setState(271);
				expr();
				setState(272);
				match(TK_RPAREN);
				}
				break;
			case TK_IDENT:
				enterOuterAlt(_localctx, 3);
				{
				setState(274);
				varAccess();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarAccessContext extends ParserRuleContext {
		public Token id;
		public TerminalNode TK_IDENT() { return getToken(CSP2SATParser.TK_IDENT, 0); }
		public List<VarAccessObjectOrArrayContext> varAccessObjectOrArray() {
			return getRuleContexts(VarAccessObjectOrArrayContext.class);
		}
		public VarAccessObjectOrArrayContext varAccessObjectOrArray(int i) {
			return getRuleContext(VarAccessObjectOrArrayContext.class,i);
		}
		public VarAccessContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varAccess; }
	}

	public final VarAccessContext varAccess() throws RecognitionException {
		VarAccessContext _localctx = new VarAccessContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_varAccess);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(277);
			((VarAccessContext)_localctx).id = match(TK_IDENT);
			setState(281);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,21,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(278);
					varAccessObjectOrArray();
					}
					} 
				}
				setState(283);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,21,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarAccessObjectOrArrayContext extends ParserRuleContext {
		public Token attr;
		public ExprContext index;
		public Token underscore;
		public TerminalNode TK_DOT() { return getToken(CSP2SATParser.TK_DOT, 0); }
		public TerminalNode TK_IDENT() { return getToken(CSP2SATParser.TK_IDENT, 0); }
		public TerminalNode TK_LCLAUDATOR() { return getToken(CSP2SATParser.TK_LCLAUDATOR, 0); }
		public TerminalNode TK_RCLAUDATOR() { return getToken(CSP2SATParser.TK_RCLAUDATOR, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode TK_UNDERSCORE() { return getToken(CSP2SATParser.TK_UNDERSCORE, 0); }
		public VarAccessObjectOrArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varAccessObjectOrArray; }
	}

	public final VarAccessObjectOrArrayContext varAccessObjectOrArray() throws RecognitionException {
		VarAccessObjectOrArrayContext _localctx = new VarAccessObjectOrArrayContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_varAccessObjectOrArray);
		try {
			setState(293);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,22,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(284);
				match(TK_DOT);
				setState(285);
				((VarAccessObjectOrArrayContext)_localctx).attr = match(TK_IDENT);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(286);
				match(TK_LCLAUDATOR);
				setState(287);
				((VarAccessObjectOrArrayContext)_localctx).index = expr();
				setState(288);
				match(TK_RCLAUDATOR);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(290);
				match(TK_LCLAUDATOR);
				setState(291);
				((VarAccessObjectOrArrayContext)_localctx).underscore = match(TK_UNDERSCORE);
				setState(292);
				match(TK_RCLAUDATOR);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ValueBaseTypeContext extends ParserRuleContext {
		public Token integer;
		public Token boolean;
		public TerminalNode TK_INT_VALUE() { return getToken(CSP2SATParser.TK_INT_VALUE, 0); }
		public TerminalNode TK_BOOLEAN_VALUE() { return getToken(CSP2SATParser.TK_BOOLEAN_VALUE, 0); }
		public ValueBaseTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_valueBaseType; }
	}

	public final ValueBaseTypeContext valueBaseType() throws RecognitionException {
		ValueBaseTypeContext _localctx = new ValueBaseTypeContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_valueBaseType);
		try {
			setState(297);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_INT_VALUE:
				enterOuterAlt(_localctx, 1);
				{
				setState(295);
				((ValueBaseTypeContext)_localctx).integer = match(TK_INT_VALUE);
				}
				break;
			case TK_BOOLEAN_VALUE:
				enterOuterAlt(_localctx, 2);
				{
				setState(296);
				((ValueBaseTypeContext)_localctx).boolean = match(TK_BOOLEAN_VALUE);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstraintDefinitionContext extends ParserRuleContext {
		public TerminalNode TK_SEMICOLON() { return getToken(CSP2SATParser.TK_SEMICOLON, 0); }
		public ForallContext forall() {
			return getRuleContext(ForallContext.class,0);
		}
		public IfThenElseContext ifThenElse() {
			return getRuleContext(IfThenElseContext.class,0);
		}
		public ConstraintContext constraint() {
			return getRuleContext(ConstraintContext.class,0);
		}
		public ConstraintDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraintDefinition; }
	}

	public final ConstraintDefinitionContext constraintDefinition() throws RecognitionException {
		ConstraintDefinitionContext _localctx = new ConstraintDefinitionContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_constraintDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(302);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_FORALL:
				{
				setState(299);
				forall();
				}
				break;
			case TK_IF:
				{
				setState(300);
				ifThenElse();
				}
				break;
			case TK_BOOLEAN_VALUE:
			case TK_LPAREN:
			case TK_CONSTRAINT_OR_PIPE:
			case TK_CONSTRAINT_AND:
			case TK_CONSTRAINT_NOT:
			case TK_CONSTRAINT_AGG_EK:
			case TK_CONSTRAINT_AGG_EO:
			case TK_CONSTRAINT_AGG_ALK:
			case TK_CONSTRAINT_AGG_ALO:
			case TK_CONSTRAINT_AGG_AMK:
			case TK_CONSTRAINT_AGG_AMO:
			case TK_IDENT:
				{
				setState(301);
				constraint();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(304);
			match(TK_SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AuxiliarListAssignationContext extends ParserRuleContext {
		public TerminalNode TK_IDENT() { return getToken(CSP2SATParser.TK_IDENT, 0); }
		public TerminalNode TK_IN() { return getToken(CSP2SATParser.TK_IN, 0); }
		public ListContext list() {
			return getRuleContext(ListContext.class,0);
		}
		public AuxiliarListAssignationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_auxiliarListAssignation; }
	}

	public final AuxiliarListAssignationContext auxiliarListAssignation() throws RecognitionException {
		AuxiliarListAssignationContext _localctx = new AuxiliarListAssignationContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_auxiliarListAssignation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(306);
			match(TK_IDENT);
			setState(307);
			match(TK_IN);
			setState(308);
			list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LocalConstraintDefinitionBlockContext extends ParserRuleContext {
		public List<ConstraintDefinitionContext> constraintDefinition() {
			return getRuleContexts(ConstraintDefinitionContext.class);
		}
		public ConstraintDefinitionContext constraintDefinition(int i) {
			return getRuleContext(ConstraintDefinitionContext.class,i);
		}
		public LocalConstraintDefinitionBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_localConstraintDefinitionBlock; }
	}

	public final LocalConstraintDefinitionBlockContext localConstraintDefinitionBlock() throws RecognitionException {
		LocalConstraintDefinitionBlockContext _localctx = new LocalConstraintDefinitionBlockContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_localConstraintDefinitionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(313);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 17)) & ~0x3f) == 0 && ((1L << (_la - 17)) & ((1L << (TK_BOOLEAN_VALUE - 17)) | (1L << (TK_IF - 17)) | (1L << (TK_LPAREN - 17)) | (1L << (TK_FORALL - 17)) | (1L << (TK_CONSTRAINT_OR_PIPE - 17)) | (1L << (TK_CONSTRAINT_AND - 17)) | (1L << (TK_CONSTRAINT_NOT - 17)) | (1L << (TK_CONSTRAINT_AGG_EK - 17)) | (1L << (TK_CONSTRAINT_AGG_EO - 17)) | (1L << (TK_CONSTRAINT_AGG_ALK - 17)) | (1L << (TK_CONSTRAINT_AGG_ALO - 17)) | (1L << (TK_CONSTRAINT_AGG_AMK - 17)) | (1L << (TK_CONSTRAINT_AGG_AMO - 17)) | (1L << (TK_IDENT - 17)))) != 0)) {
				{
				{
				setState(310);
				constraintDefinition();
				}
				}
				setState(315);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ForallContext extends ParserRuleContext {
		public TerminalNode TK_FORALL() { return getToken(CSP2SATParser.TK_FORALL, 0); }
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public List<AuxiliarListAssignationContext> auxiliarListAssignation() {
			return getRuleContexts(AuxiliarListAssignationContext.class);
		}
		public AuxiliarListAssignationContext auxiliarListAssignation(int i) {
			return getRuleContext(AuxiliarListAssignationContext.class,i);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public TerminalNode TK_LBRACKET() { return getToken(CSP2SATParser.TK_LBRACKET, 0); }
		public LocalConstraintDefinitionBlockContext localConstraintDefinitionBlock() {
			return getRuleContext(LocalConstraintDefinitionBlockContext.class,0);
		}
		public TerminalNode TK_RBRACKET() { return getToken(CSP2SATParser.TK_RBRACKET, 0); }
		public List<TerminalNode> TK_COMMA() { return getTokens(CSP2SATParser.TK_COMMA); }
		public TerminalNode TK_COMMA(int i) {
			return getToken(CSP2SATParser.TK_COMMA, i);
		}
		public ForallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forall; }
	}

	public final ForallContext forall() throws RecognitionException {
		ForallContext _localctx = new ForallContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_forall);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(316);
			match(TK_FORALL);
			setState(317);
			match(TK_LPAREN);
			setState(318);
			auxiliarListAssignation();
			setState(323);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_COMMA) {
				{
				{
				setState(319);
				match(TK_COMMA);
				setState(320);
				auxiliarListAssignation();
				}
				}
				setState(325);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(326);
			match(TK_RPAREN);
			setState(327);
			match(TK_LBRACKET);
			setState(328);
			localConstraintDefinitionBlock();
			setState(329);
			match(TK_RBRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfThenElseContext extends ParserRuleContext {
		public TerminalNode TK_IF() { return getToken(CSP2SATParser.TK_IF, 0); }
		public List<TerminalNode> TK_LPAREN() { return getTokens(CSP2SATParser.TK_LPAREN); }
		public TerminalNode TK_LPAREN(int i) {
			return getToken(CSP2SATParser.TK_LPAREN, i);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> TK_RPAREN() { return getTokens(CSP2SATParser.TK_RPAREN); }
		public TerminalNode TK_RPAREN(int i) {
			return getToken(CSP2SATParser.TK_RPAREN, i);
		}
		public List<TerminalNode> TK_LBRACKET() { return getTokens(CSP2SATParser.TK_LBRACKET); }
		public TerminalNode TK_LBRACKET(int i) {
			return getToken(CSP2SATParser.TK_LBRACKET, i);
		}
		public List<LocalConstraintDefinitionBlockContext> localConstraintDefinitionBlock() {
			return getRuleContexts(LocalConstraintDefinitionBlockContext.class);
		}
		public LocalConstraintDefinitionBlockContext localConstraintDefinitionBlock(int i) {
			return getRuleContext(LocalConstraintDefinitionBlockContext.class,i);
		}
		public List<TerminalNode> TK_RBRACKET() { return getTokens(CSP2SATParser.TK_RBRACKET); }
		public TerminalNode TK_RBRACKET(int i) {
			return getToken(CSP2SATParser.TK_RBRACKET, i);
		}
		public List<TerminalNode> TK_ELSEIF() { return getTokens(CSP2SATParser.TK_ELSEIF); }
		public TerminalNode TK_ELSEIF(int i) {
			return getToken(CSP2SATParser.TK_ELSEIF, i);
		}
		public TerminalNode TK_ELSE() { return getToken(CSP2SATParser.TK_ELSE, 0); }
		public IfThenElseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifThenElse; }
	}

	public final IfThenElseContext ifThenElse() throws RecognitionException {
		IfThenElseContext _localctx = new IfThenElseContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_ifThenElse);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(331);
			match(TK_IF);
			setState(332);
			match(TK_LPAREN);
			setState(333);
			expr();
			setState(334);
			match(TK_RPAREN);
			setState(335);
			match(TK_LBRACKET);
			setState(336);
			localConstraintDefinitionBlock();
			setState(337);
			match(TK_RBRACKET);
			setState(348);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_ELSEIF) {
				{
				{
				setState(338);
				match(TK_ELSEIF);
				setState(339);
				match(TK_LPAREN);
				setState(340);
				expr();
				setState(341);
				match(TK_RPAREN);
				setState(342);
				match(TK_LBRACKET);
				setState(343);
				localConstraintDefinitionBlock();
				setState(344);
				match(TK_RBRACKET);
				}
				}
				setState(350);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(356);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_ELSE) {
				{
				setState(351);
				match(TK_ELSE);
				setState(352);
				match(TK_LBRACKET);
				setState(353);
				localConstraintDefinitionBlock();
				setState(354);
				match(TK_RBRACKET);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ListContext extends ParserRuleContext {
		public ListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_list; }
	 
		public ListContext() { }
		public void copyFrom(ListContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ExplicitListContext extends ListContext {
		public TerminalNode TK_LCLAUDATOR() { return getToken(CSP2SATParser.TK_LCLAUDATOR, 0); }
		public List<ListResultExprContext> listResultExpr() {
			return getRuleContexts(ListResultExprContext.class);
		}
		public ListResultExprContext listResultExpr(int i) {
			return getRuleContext(ListResultExprContext.class,i);
		}
		public TerminalNode TK_RCLAUDATOR() { return getToken(CSP2SATParser.TK_RCLAUDATOR, 0); }
		public List<TerminalNode> TK_COMMA() { return getTokens(CSP2SATParser.TK_COMMA); }
		public TerminalNode TK_COMMA(int i) {
			return getToken(CSP2SATParser.TK_COMMA, i);
		}
		public ExplicitListContext(ListContext ctx) { copyFrom(ctx); }
	}
	public static class RangListContext extends ListContext {
		public ExprContext min;
		public ExprContext max;
		public TerminalNode TK_RANGE_DOTS() { return getToken(CSP2SATParser.TK_RANGE_DOTS, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public RangListContext(ListContext ctx) { copyFrom(ctx); }
	}
	public static class VarAccessListContext extends ListContext {
		public VarAccessContext varAccess() {
			return getRuleContext(VarAccessContext.class,0);
		}
		public VarAccessListContext(ListContext ctx) { copyFrom(ctx); }
	}
	public static class ComprehensionListContext extends ListContext {
		public ExprContext condExpr;
		public TerminalNode TK_LCLAUDATOR() { return getToken(CSP2SATParser.TK_LCLAUDATOR, 0); }
		public ListResultExprContext listResultExpr() {
			return getRuleContext(ListResultExprContext.class,0);
		}
		public TerminalNode TK_CONSTRAINT_OR_PIPE() { return getToken(CSP2SATParser.TK_CONSTRAINT_OR_PIPE, 0); }
		public List<AuxiliarListAssignationContext> auxiliarListAssignation() {
			return getRuleContexts(AuxiliarListAssignationContext.class);
		}
		public AuxiliarListAssignationContext auxiliarListAssignation(int i) {
			return getRuleContext(AuxiliarListAssignationContext.class,i);
		}
		public TerminalNode TK_RCLAUDATOR() { return getToken(CSP2SATParser.TK_RCLAUDATOR, 0); }
		public List<TerminalNode> TK_COMMA() { return getTokens(CSP2SATParser.TK_COMMA); }
		public TerminalNode TK_COMMA(int i) {
			return getToken(CSP2SATParser.TK_COMMA, i);
		}
		public TerminalNode TK_WHERE() { return getToken(CSP2SATParser.TK_WHERE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ComprehensionListContext(ListContext ctx) { copyFrom(ctx); }
	}

	public final ListContext list() throws RecognitionException {
		ListContext _localctx = new ListContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_list);
		int _la;
		try {
			setState(391);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,32,_ctx) ) {
			case 1:
				_localctx = new RangListContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(358);
				((RangListContext)_localctx).min = expr();
				setState(359);
				match(TK_RANGE_DOTS);
				setState(360);
				((RangListContext)_localctx).max = expr();
				}
				break;
			case 2:
				_localctx = new ComprehensionListContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(362);
				match(TK_LCLAUDATOR);
				setState(363);
				listResultExpr();
				setState(364);
				match(TK_CONSTRAINT_OR_PIPE);
				setState(365);
				auxiliarListAssignation();
				setState(370);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==TK_COMMA) {
					{
					{
					setState(366);
					match(TK_COMMA);
					setState(367);
					auxiliarListAssignation();
					}
					}
					setState(372);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(375);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==TK_WHERE) {
					{
					setState(373);
					match(TK_WHERE);
					setState(374);
					((ComprehensionListContext)_localctx).condExpr = expr();
					}
				}

				setState(377);
				match(TK_RCLAUDATOR);
				}
				break;
			case 3:
				_localctx = new ExplicitListContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(379);
				match(TK_LCLAUDATOR);
				setState(380);
				listResultExpr();
				setState(385);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==TK_COMMA) {
					{
					{
					setState(381);
					match(TK_COMMA);
					setState(382);
					listResultExpr();
					}
					}
					setState(387);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(388);
				match(TK_RCLAUDATOR);
				}
				break;
			case 4:
				_localctx = new VarAccessListContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(390);
				varAccess();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ListResultExprContext extends ParserRuleContext {
		public VarAccessContext varAcc;
		public ExprContext resExpr;
		public VarAccessContext varAccess() {
			return getRuleContext(VarAccessContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Constraint_expressionContext constraint_expression() {
			return getRuleContext(Constraint_expressionContext.class,0);
		}
		public StringContext string() {
			return getRuleContext(StringContext.class,0);
		}
		public ListResultExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_listResultExpr; }
	}

	public final ListResultExprContext listResultExpr() throws RecognitionException {
		ListResultExprContext _localctx = new ListResultExprContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_listResultExpr);
		try {
			setState(397);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,33,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(393);
				((ListResultExprContext)_localctx).varAcc = varAccess();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(394);
				((ListResultExprContext)_localctx).resExpr = expr();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(395);
				constraint_expression();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(396);
				string(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstraintContext extends ParserRuleContext {
		public Constraint_expressionContext constraint_expression() {
			return getRuleContext(Constraint_expressionContext.class,0);
		}
		public Constraint_aggreggate_opContext constraint_aggreggate_op() {
			return getRuleContext(Constraint_aggreggate_opContext.class,0);
		}
		public ConstraintContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint; }
	}

	public final ConstraintContext constraint() throws RecognitionException {
		ConstraintContext _localctx = new ConstraintContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_constraint);
		try {
			setState(401);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_BOOLEAN_VALUE:
			case TK_LPAREN:
			case TK_CONSTRAINT_OR_PIPE:
			case TK_CONSTRAINT_AND:
			case TK_CONSTRAINT_NOT:
			case TK_IDENT:
				enterOuterAlt(_localctx, 1);
				{
				setState(399);
				constraint_expression();
				}
				break;
			case TK_CONSTRAINT_AGG_EK:
			case TK_CONSTRAINT_AGG_EO:
			case TK_CONSTRAINT_AGG_ALK:
			case TK_CONSTRAINT_AGG_ALO:
			case TK_CONSTRAINT_AGG_AMK:
			case TK_CONSTRAINT_AGG_AMO:
				enterOuterAlt(_localctx, 2);
				{
				setState(400);
				constraint_aggreggate_op();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_expressionContext extends ParserRuleContext {
		public Constraint_double_implicationContext constraint_double_implication() {
			return getRuleContext(Constraint_double_implicationContext.class,0);
		}
		public Constraint_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_expression; }
	}

	public final Constraint_expressionContext constraint_expression() throws RecognitionException {
		Constraint_expressionContext _localctx = new Constraint_expressionContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_constraint_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(403);
			constraint_double_implication();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_double_implicationContext extends ParserRuleContext {
		public List<Constraint_implicationContext> constraint_implication() {
			return getRuleContexts(Constraint_implicationContext.class);
		}
		public Constraint_implicationContext constraint_implication(int i) {
			return getRuleContext(Constraint_implicationContext.class,i);
		}
		public List<TerminalNode> TK_OP_DOUBLE_IMPLIC() { return getTokens(CSP2SATParser.TK_OP_DOUBLE_IMPLIC); }
		public TerminalNode TK_OP_DOUBLE_IMPLIC(int i) {
			return getToken(CSP2SATParser.TK_OP_DOUBLE_IMPLIC, i);
		}
		public Constraint_double_implicationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_double_implication; }
	}

	public final Constraint_double_implicationContext constraint_double_implication() throws RecognitionException {
		Constraint_double_implicationContext _localctx = new Constraint_double_implicationContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_constraint_double_implication);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(405);
			constraint_implication();
			setState(410);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_OP_DOUBLE_IMPLIC) {
				{
				{
				setState(406);
				match(TK_OP_DOUBLE_IMPLIC);
				setState(407);
				constraint_implication();
				}
				}
				setState(412);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Implication_operatorContext extends ParserRuleContext {
		public TerminalNode TK_OP_IMPLIC_L() { return getToken(CSP2SATParser.TK_OP_IMPLIC_L, 0); }
		public TerminalNode TK_OP_IMPLIC_R() { return getToken(CSP2SATParser.TK_OP_IMPLIC_R, 0); }
		public Implication_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_implication_operator; }
	}

	public final Implication_operatorContext implication_operator() throws RecognitionException {
		Implication_operatorContext _localctx = new Implication_operatorContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_implication_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(413);
			_la = _input.LA(1);
			if ( !(_la==TK_OP_IMPLIC_R || _la==TK_OP_IMPLIC_L) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_implicationContext extends ParserRuleContext {
		public List<Constraint_orContext> constraint_or() {
			return getRuleContexts(Constraint_orContext.class);
		}
		public Constraint_orContext constraint_or(int i) {
			return getRuleContext(Constraint_orContext.class,i);
		}
		public List<Implication_operatorContext> implication_operator() {
			return getRuleContexts(Implication_operatorContext.class);
		}
		public Implication_operatorContext implication_operator(int i) {
			return getRuleContext(Implication_operatorContext.class,i);
		}
		public Constraint_implicationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_implication; }
	}

	public final Constraint_implicationContext constraint_implication() throws RecognitionException {
		Constraint_implicationContext _localctx = new Constraint_implicationContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_constraint_implication);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(415);
			constraint_or();
			setState(421);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_OP_IMPLIC_R || _la==TK_OP_IMPLIC_L) {
				{
				{
				setState(416);
				implication_operator();
				setState(417);
				constraint_or();
				}
				}
				setState(423);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_orContext extends ParserRuleContext {
		public Constraint_orContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_or; }
	 
		public Constraint_orContext() { }
		public void copyFrom(Constraint_orContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class COrExpressionContext extends Constraint_orContext {
		public List<Constraint_or_2Context> constraint_or_2() {
			return getRuleContexts(Constraint_or_2Context.class);
		}
		public Constraint_or_2Context constraint_or_2(int i) {
			return getRuleContext(Constraint_or_2Context.class,i);
		}
		public List<TerminalNode> TK_CONSTRAINT_OR_PIPE() { return getTokens(CSP2SATParser.TK_CONSTRAINT_OR_PIPE); }
		public TerminalNode TK_CONSTRAINT_OR_PIPE(int i) {
			return getToken(CSP2SATParser.TK_CONSTRAINT_OR_PIPE, i);
		}
		public COrExpressionContext(Constraint_orContext ctx) { copyFrom(ctx); }
	}

	public final Constraint_orContext constraint_or() throws RecognitionException {
		Constraint_orContext _localctx = new Constraint_orContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_constraint_or);
		try {
			int _alt;
			_localctx = new COrExpressionContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(424);
			constraint_or_2();
			setState(429);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,37,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(425);
					match(TK_CONSTRAINT_OR_PIPE);
					setState(426);
					constraint_or_2();
					}
					} 
				}
				setState(431);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,37,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_or_2Context extends ParserRuleContext {
		public Constraint_or_2Context(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_or_2; }
	 
		public Constraint_or_2Context() { }
		public void copyFrom(Constraint_or_2Context ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class COrListContext extends Constraint_or_2Context {
		public List<TerminalNode> TK_CONSTRAINT_OR_PIPE() { return getTokens(CSP2SATParser.TK_CONSTRAINT_OR_PIPE); }
		public TerminalNode TK_CONSTRAINT_OR_PIPE(int i) {
			return getToken(CSP2SATParser.TK_CONSTRAINT_OR_PIPE, i);
		}
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public ListContext list() {
			return getRuleContext(ListContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public COrListContext(Constraint_or_2Context ctx) { copyFrom(ctx); }
	}
	public static class CAndContext extends Constraint_or_2Context {
		public Constraint_andContext constraint_and() {
			return getRuleContext(Constraint_andContext.class,0);
		}
		public CAndContext(Constraint_or_2Context ctx) { copyFrom(ctx); }
	}

	public final Constraint_or_2Context constraint_or_2() throws RecognitionException {
		Constraint_or_2Context _localctx = new Constraint_or_2Context(_ctx, getState());
		enterRule(_localctx, 82, RULE_constraint_or_2);
		try {
			setState(439);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_CONSTRAINT_OR_PIPE:
				_localctx = new COrListContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(432);
				match(TK_CONSTRAINT_OR_PIPE);
				setState(433);
				match(TK_CONSTRAINT_OR_PIPE);
				setState(434);
				match(TK_LPAREN);
				setState(435);
				list();
				setState(436);
				match(TK_RPAREN);
				}
				break;
			case TK_BOOLEAN_VALUE:
			case TK_LPAREN:
			case TK_CONSTRAINT_AND:
			case TK_CONSTRAINT_NOT:
			case TK_IDENT:
				_localctx = new CAndContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(438);
				constraint_and();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_andContext extends ParserRuleContext {
		public Constraint_andContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_and; }
	 
		public Constraint_andContext() { }
		public void copyFrom(Constraint_andContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class CAndExpressionContext extends Constraint_andContext {
		public List<Constraint_and_2Context> constraint_and_2() {
			return getRuleContexts(Constraint_and_2Context.class);
		}
		public Constraint_and_2Context constraint_and_2(int i) {
			return getRuleContext(Constraint_and_2Context.class,i);
		}
		public List<TerminalNode> TK_CONSTRAINT_AND() { return getTokens(CSP2SATParser.TK_CONSTRAINT_AND); }
		public TerminalNode TK_CONSTRAINT_AND(int i) {
			return getToken(CSP2SATParser.TK_CONSTRAINT_AND, i);
		}
		public CAndExpressionContext(Constraint_andContext ctx) { copyFrom(ctx); }
	}

	public final Constraint_andContext constraint_and() throws RecognitionException {
		Constraint_andContext _localctx = new Constraint_andContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_constraint_and);
		int _la;
		try {
			_localctx = new CAndExpressionContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(441);
			constraint_and_2();
			setState(446);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TK_CONSTRAINT_AND) {
				{
				{
				setState(442);
				match(TK_CONSTRAINT_AND);
				setState(443);
				constraint_and_2();
				}
				}
				setState(448);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_and_2Context extends ParserRuleContext {
		public Constraint_and_2Context(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_and_2; }
	 
		public Constraint_and_2Context() { }
		public void copyFrom(Constraint_and_2Context ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class CAndListContext extends Constraint_and_2Context {
		public List<TerminalNode> TK_CONSTRAINT_AND() { return getTokens(CSP2SATParser.TK_CONSTRAINT_AND); }
		public TerminalNode TK_CONSTRAINT_AND(int i) {
			return getToken(CSP2SATParser.TK_CONSTRAINT_AND, i);
		}
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public ListContext list() {
			return getRuleContext(ListContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public CAndListContext(Constraint_and_2Context ctx) { copyFrom(ctx); }
	}
	public static class CLitContext extends Constraint_and_2Context {
		public Constraint_literalContext constraint_literal() {
			return getRuleContext(Constraint_literalContext.class,0);
		}
		public CLitContext(Constraint_and_2Context ctx) { copyFrom(ctx); }
	}

	public final Constraint_and_2Context constraint_and_2() throws RecognitionException {
		Constraint_and_2Context _localctx = new Constraint_and_2Context(_ctx, getState());
		enterRule(_localctx, 86, RULE_constraint_and_2);
		try {
			setState(456);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_CONSTRAINT_AND:
				_localctx = new CAndListContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(449);
				match(TK_CONSTRAINT_AND);
				setState(450);
				match(TK_CONSTRAINT_AND);
				setState(451);
				match(TK_LPAREN);
				setState(452);
				list();
				setState(453);
				match(TK_RPAREN);
				}
				break;
			case TK_BOOLEAN_VALUE:
			case TK_LPAREN:
			case TK_CONSTRAINT_NOT:
			case TK_IDENT:
				_localctx = new CLitContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(455);
				constraint_literal();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_literalContext extends ParserRuleContext {
		public Constraint_baseContext constraint_base() {
			return getRuleContext(Constraint_baseContext.class,0);
		}
		public TerminalNode TK_CONSTRAINT_NOT() { return getToken(CSP2SATParser.TK_CONSTRAINT_NOT, 0); }
		public Constraint_literalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_literal; }
	}

	public final Constraint_literalContext constraint_literal() throws RecognitionException {
		Constraint_literalContext _localctx = new Constraint_literalContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_constraint_literal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(459);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_CONSTRAINT_NOT) {
				{
				setState(458);
				match(TK_CONSTRAINT_NOT);
				}
			}

			setState(461);
			constraint_base();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_baseContext extends ParserRuleContext {
		public VarAccessContext varAccess() {
			return getRuleContext(VarAccessContext.class,0);
		}
		public TerminalNode TK_BOOLEAN_VALUE() { return getToken(CSP2SATParser.TK_BOOLEAN_VALUE, 0); }
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public Constraint_expressionContext constraint_expression() {
			return getRuleContext(Constraint_expressionContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public Constraint_baseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_base; }
	}

	public final Constraint_baseContext constraint_base() throws RecognitionException {
		Constraint_baseContext _localctx = new Constraint_baseContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_constraint_base);
		try {
			setState(469);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case TK_IDENT:
				enterOuterAlt(_localctx, 1);
				{
				setState(463);
				varAccess();
				}
				break;
			case TK_BOOLEAN_VALUE:
				enterOuterAlt(_localctx, 2);
				{
				setState(464);
				match(TK_BOOLEAN_VALUE);
				}
				break;
			case TK_LPAREN:
				enterOuterAlt(_localctx, 3);
				{
				setState(465);
				match(TK_LPAREN);
				setState(466);
				constraint_expression();
				setState(467);
				match(TK_RPAREN);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Aggregate_opContext extends ParserRuleContext {
		public TerminalNode TK_CONSTRAINT_AGG_EK() { return getToken(CSP2SATParser.TK_CONSTRAINT_AGG_EK, 0); }
		public TerminalNode TK_CONSTRAINT_AGG_EO() { return getToken(CSP2SATParser.TK_CONSTRAINT_AGG_EO, 0); }
		public TerminalNode TK_CONSTRAINT_AGG_AMK() { return getToken(CSP2SATParser.TK_CONSTRAINT_AGG_AMK, 0); }
		public TerminalNode TK_CONSTRAINT_AGG_AMO() { return getToken(CSP2SATParser.TK_CONSTRAINT_AGG_AMO, 0); }
		public TerminalNode TK_CONSTRAINT_AGG_ALK() { return getToken(CSP2SATParser.TK_CONSTRAINT_AGG_ALK, 0); }
		public TerminalNode TK_CONSTRAINT_AGG_ALO() { return getToken(CSP2SATParser.TK_CONSTRAINT_AGG_ALO, 0); }
		public Aggregate_opContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_aggregate_op; }
	}

	public final Aggregate_opContext aggregate_op() throws RecognitionException {
		Aggregate_opContext _localctx = new Aggregate_opContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_aggregate_op);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(471);
			_la = _input.LA(1);
			if ( !(((((_la - 60)) & ~0x3f) == 0 && ((1L << (_la - 60)) & ((1L << (TK_CONSTRAINT_AGG_EK - 60)) | (1L << (TK_CONSTRAINT_AGG_EO - 60)) | (1L << (TK_CONSTRAINT_AGG_ALK - 60)) | (1L << (TK_CONSTRAINT_AGG_ALO - 60)) | (1L << (TK_CONSTRAINT_AGG_AMK - 60)) | (1L << (TK_CONSTRAINT_AGG_AMO - 60)))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Constraint_aggreggate_opContext extends ParserRuleContext {
		public ExprContext param;
		public Aggregate_opContext aggregate_op() {
			return getRuleContext(Aggregate_opContext.class,0);
		}
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public ListContext list() {
			return getRuleContext(ListContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public TerminalNode TK_COMMA() { return getToken(CSP2SATParser.TK_COMMA, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Constraint_aggreggate_opContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint_aggreggate_op; }
	}

	public final Constraint_aggreggate_opContext constraint_aggreggate_op() throws RecognitionException {
		Constraint_aggreggate_opContext _localctx = new Constraint_aggreggate_opContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_constraint_aggreggate_op);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(473);
			aggregate_op();
			setState(474);
			match(TK_LPAREN);
			setState(475);
			list();
			setState(478);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==TK_COMMA) {
				{
				setState(476);
				match(TK_COMMA);
				setState(477);
				((Constraint_aggreggate_opContext)_localctx).param = expr();
				}
			}

			setState(480);
			match(TK_RPAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StringContext extends ParserRuleContext {
		public TerminalNode TK_LPAREN() { return getToken(CSP2SATParser.TK_LPAREN, 0); }
		public StringContext string() {
			return getRuleContext(StringContext.class,0);
		}
		public TerminalNode TK_RPAREN() { return getToken(CSP2SATParser.TK_RPAREN, 0); }
		public StringTernaryContext stringTernary() {
			return getRuleContext(StringTernaryContext.class,0);
		}
		public VarAccessContext varAccess() {
			return getRuleContext(VarAccessContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ListContext list() {
			return getRuleContext(ListContext.class,0);
		}
		public TerminalNode TK_STRING() { return getToken(CSP2SATParser.TK_STRING, 0); }
		public ConcatStringContext concatString() {
			return getRuleContext(ConcatStringContext.class,0);
		}
		public StringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_string; }
	}

	public final StringContext string() throws RecognitionException {
		return string(0);
	}

	private StringContext string(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		StringContext _localctx = new StringContext(_ctx, _parentState);
		StringContext _prevctx = _localctx;
		int _startState = 96;
		enterRecursionRule(_localctx, 96, RULE_string, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(492);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,44,_ctx) ) {
			case 1:
				{
				setState(483);
				match(TK_LPAREN);
				setState(484);
				string(0);
				setState(485);
				match(TK_RPAREN);
				}
				break;
			case 2:
				{
				setState(487);
				stringTernary();
				}
				break;
			case 3:
				{
				setState(488);
				varAccess();
				}
				break;
			case 4:
				{
				setState(489);
				expr();
				}
				break;
			case 5:
				{
				setState(490);
				list();
				}
				break;
			case 6:
				{
				setState(491);
				match(TK_STRING);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(498);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,45,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new StringContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_string);
					setState(494);
					if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
					setState(495);
					concatString();
					}
					} 
				}
				setState(500);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,45,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class StringTernaryContext extends ParserRuleContext {
		public ExprAndContext condition;
		public StringContext op1;
		public StringContext op2;
		public TerminalNode TK_INTERROGANT() { return getToken(CSP2SATParser.TK_INTERROGANT, 0); }
		public TerminalNode TK_COLON() { return getToken(CSP2SATParser.TK_COLON, 0); }
		public ExprAndContext exprAnd() {
			return getRuleContext(ExprAndContext.class,0);
		}
		public List<StringContext> string() {
			return getRuleContexts(StringContext.class);
		}
		public StringContext string(int i) {
			return getRuleContext(StringContext.class,i);
		}
		public StringTernaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stringTernary; }
	}

	public final StringTernaryContext stringTernary() throws RecognitionException {
		StringTernaryContext _localctx = new StringTernaryContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_stringTernary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(501);
			((StringTernaryContext)_localctx).condition = exprAnd();
			setState(502);
			match(TK_INTERROGANT);
			setState(503);
			((StringTernaryContext)_localctx).op1 = string(0);
			setState(504);
			match(TK_COLON);
			setState(505);
			((StringTernaryContext)_localctx).op2 = string(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConcatStringContext extends ParserRuleContext {
		public TerminalNode TK_STRING_AGG_OP() { return getToken(CSP2SATParser.TK_STRING_AGG_OP, 0); }
		public StringContext string() {
			return getRuleContext(StringContext.class,0);
		}
		public ConcatStringContext concatString() {
			return getRuleContext(ConcatStringContext.class,0);
		}
		public ConcatStringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_concatString; }
	}

	public final ConcatStringContext concatString() throws RecognitionException {
		ConcatStringContext _localctx = new ConcatStringContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_concatString);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(507);
			match(TK_STRING_AGG_OP);
			setState(508);
			string(0);
			setState(510);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,46,_ctx) ) {
			case 1:
				{
				setState(509);
				concatString();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 48:
			return string_sempred((StringContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean string_sempred(StringContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 7);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3F\u0203\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\3\2\5\2j\n\2\3\2\3\2\3\2\5\2o\n\2\3\3\3\3\5\3s\n\3\3\4\3\4\3\4\7\4"+
		"x\n\4\f\4\16\4{\13\4\3\5\3\5\3\5\7\5\u0080\n\5\f\5\16\5\u0083\13\5\3\5"+
		"\3\5\3\5\3\6\3\6\3\6\7\6\u008b\n\6\f\6\16\6\u008e\13\6\3\7\3\7\3\7\7\7"+
		"\u0093\n\7\f\7\16\7\u0096\13\7\3\b\3\b\3\b\3\b\3\b\7\b\u009d\n\b\f\b\16"+
		"\b\u00a0\13\b\3\t\3\t\5\t\u00a4\n\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\5\n\u00ad"+
		"\n\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\7\13\u00b7\n\13\f\13\16\13\u00ba"+
		"\13\13\3\f\3\f\3\f\3\f\3\f\3\f\3\f\5\f\u00c3\n\f\3\r\3\r\3\16\3\16\3\16"+
		"\3\16\3\16\3\16\5\16\u00cd\n\16\3\17\3\17\3\17\7\17\u00d2\n\17\f\17\16"+
		"\17\u00d5\13\17\3\20\3\20\3\20\7\20\u00da\n\20\f\20\16\20\u00dd\13\20"+
		"\3\21\3\21\3\22\3\22\3\22\3\22\7\22\u00e5\n\22\f\22\16\22\u00e8\13\22"+
		"\3\23\3\23\3\24\3\24\3\24\3\24\7\24\u00f0\n\24\f\24\16\24\u00f3\13\24"+
		"\3\25\3\25\3\26\3\26\3\26\3\26\7\26\u00fb\n\26\f\26\16\26\u00fe\13\26"+
		"\3\27\3\27\3\30\3\30\3\30\3\30\7\30\u0106\n\30\f\30\16\30\u0109\13\30"+
		"\3\31\5\31\u010c\n\31\3\31\3\31\3\32\3\32\3\32\3\32\3\32\3\32\5\32\u0116"+
		"\n\32\3\33\3\33\7\33\u011a\n\33\f\33\16\33\u011d\13\33\3\34\3\34\3\34"+
		"\3\34\3\34\3\34\3\34\3\34\3\34\5\34\u0128\n\34\3\35\3\35\5\35\u012c\n"+
		"\35\3\36\3\36\3\36\5\36\u0131\n\36\3\36\3\36\3\37\3\37\3\37\3\37\3 \7"+
		" \u013a\n \f \16 \u013d\13 \3!\3!\3!\3!\3!\7!\u0144\n!\f!\16!\u0147\13"+
		"!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3"+
		"\"\3\"\7\"\u015d\n\"\f\"\16\"\u0160\13\"\3\"\3\"\3\"\3\"\3\"\5\"\u0167"+
		"\n\"\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\7#\u0173\n#\f#\16#\u0176\13#\3#\3#"+
		"\5#\u017a\n#\3#\3#\3#\3#\3#\3#\7#\u0182\n#\f#\16#\u0185\13#\3#\3#\3#\5"+
		"#\u018a\n#\3$\3$\3$\3$\5$\u0190\n$\3%\3%\5%\u0194\n%\3&\3&\3\'\3\'\3\'"+
		"\7\'\u019b\n\'\f\'\16\'\u019e\13\'\3(\3(\3)\3)\3)\3)\7)\u01a6\n)\f)\16"+
		")\u01a9\13)\3*\3*\3*\7*\u01ae\n*\f*\16*\u01b1\13*\3+\3+\3+\3+\3+\3+\3"+
		"+\5+\u01ba\n+\3,\3,\3,\7,\u01bf\n,\f,\16,\u01c2\13,\3-\3-\3-\3-\3-\3-"+
		"\3-\5-\u01cb\n-\3.\5.\u01ce\n.\3.\3.\3/\3/\3/\3/\3/\3/\5/\u01d8\n/\3\60"+
		"\3\60\3\61\3\61\3\61\3\61\3\61\5\61\u01e1\n\61\3\61\3\61\3\62\3\62\3\62"+
		"\3\62\3\62\3\62\3\62\3\62\3\62\3\62\5\62\u01ef\n\62\3\62\3\62\7\62\u01f3"+
		"\n\62\f\62\16\62\u01f6\13\62\3\63\3\63\3\63\3\63\3\63\3\63\3\64\3\64\3"+
		"\64\5\64\u0201\n\64\3\64\2\3b\65\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36"+
		" \"$&(*,.\60\62\64\668:<>@BDFHJLNPRTVXZ\\^`bdf\2\n\3\2\24\25\3\2%(\3\2"+
		"\65\66\3\2\61\64\3\2,-\3\2.\60\3\2\678\3\2>C\2\u020a\2i\3\2\2\2\4r\3\2"+
		"\2\2\6t\3\2\2\2\b|\3\2\2\2\n\u0087\3\2\2\2\f\u008f\3\2\2\2\16\u0097\3"+
		"\2\2\2\20\u00a1\3\2\2\2\22\u00ac\3\2\2\2\24\u00b8\3\2\2\2\26\u00c2\3\2"+
		"\2\2\30\u00c4\3\2\2\2\32\u00cc\3\2\2\2\34\u00ce\3\2\2\2\36\u00d6\3\2\2"+
		"\2 \u00de\3\2\2\2\"\u00e0\3\2\2\2$\u00e9\3\2\2\2&\u00eb\3\2\2\2(\u00f4"+
		"\3\2\2\2*\u00f6\3\2\2\2,\u00ff\3\2\2\2.\u0101\3\2\2\2\60\u010b\3\2\2\2"+
		"\62\u0115\3\2\2\2\64\u0117\3\2\2\2\66\u0127\3\2\2\28\u012b\3\2\2\2:\u0130"+
		"\3\2\2\2<\u0134\3\2\2\2>\u013b\3\2\2\2@\u013e\3\2\2\2B\u014d\3\2\2\2D"+
		"\u0189\3\2\2\2F\u018f\3\2\2\2H\u0193\3\2\2\2J\u0195\3\2\2\2L\u0197\3\2"+
		"\2\2N\u019f\3\2\2\2P\u01a1\3\2\2\2R\u01aa\3\2\2\2T\u01b9\3\2\2\2V\u01bb"+
		"\3\2\2\2X\u01ca\3\2\2\2Z\u01cd\3\2\2\2\\\u01d7\3\2\2\2^\u01d9\3\2\2\2"+
		"`\u01db\3\2\2\2b\u01ee\3\2\2\2d\u01f7\3\2\2\2f\u01fd\3\2\2\2hj\5\6\4\2"+
		"ih\3\2\2\2ij\3\2\2\2jk\3\2\2\2kl\5\n\6\2ln\5\f\7\2mo\5\16\b\2nm\3\2\2"+
		"\2no\3\2\2\2o\3\3\2\2\2ps\5\20\t\2qs\5\22\n\2rp\3\2\2\2rq\3\2\2\2s\5\3"+
		"\2\2\2tu\7\6\2\2uy\7\n\2\2vx\5\b\5\2wv\3\2\2\2x{\3\2\2\2yw\3\2\2\2yz\3"+
		"\2\2\2z\7\3\2\2\2{y\3\2\2\2|}\7D\2\2}\u0081\7\37\2\2~\u0080\5\4\3\2\177"+
		"~\3\2\2\2\u0080\u0083\3\2\2\2\u0081\177\3\2\2\2\u0081\u0082\3\2\2\2\u0082"+
		"\u0084\3\2\2\2\u0083\u0081\3\2\2\2\u0084\u0085\7 \2\2\u0085\u0086\7\13"+
		"\2\2\u0086\t\3\2\2\2\u0087\u0088\7\7\2\2\u0088\u008c\7\n\2\2\u0089\u008b"+
		"\5\4\3\2\u008a\u0089\3\2\2\2\u008b\u008e\3\2\2\2\u008c\u008a\3\2\2\2\u008c"+
		"\u008d\3\2\2\2\u008d\13\3\2\2\2\u008e\u008c\3\2\2\2\u008f\u0090\7\b\2"+
		"\2\u0090\u0094\7\n\2\2\u0091\u0093\5:\36\2\u0092\u0091\3\2\2\2\u0093\u0096"+
		"\3\2\2\2\u0094\u0092\3\2\2\2\u0094\u0095\3\2\2\2\u0095\r\3\2\2\2\u0096"+
		"\u0094\3\2\2\2\u0097\u0098\7\t\2\2\u0098\u009e\7\n\2\2\u0099\u009a\5b"+
		"\62\2\u009a\u009b\7\13\2\2\u009b\u009d\3\2\2\2\u009c\u0099\3\2\2\2\u009d"+
		"\u00a0\3\2\2\2\u009e\u009c\3\2\2\2\u009e\u009f\3\2\2\2\u009f\17\3\2\2"+
		"\2\u00a0\u009e\3\2\2\2\u00a1\u00a3\7\17\2\2\u00a2\u00a4\7\25\2\2\u00a3"+
		"\u00a2\3\2\2\2\u00a3\u00a4\3\2\2\2\u00a4\u00a5\3\2\2\2\u00a5\u00a6\7D"+
		"\2\2\u00a6\u00a7\5\24\13\2\u00a7\u00a8\7\13\2\2\u00a8\21\3\2\2\2\u00a9"+
		"\u00aa\7\16\2\2\u00aa\u00ad\t\2\2\2\u00ab\u00ad\7D\2\2\u00ac\u00a9\3\2"+
		"\2\2\u00ac\u00ab\3\2\2\2\u00ad\u00ae\3\2\2\2\u00ae\u00af\7D\2\2\u00af"+
		"\u00b0\5\24\13\2\u00b0\u00b1\7\13\2\2\u00b1\23\3\2\2\2\u00b2\u00b3\7\35"+
		"\2\2\u00b3\u00b4\5\26\f\2\u00b4\u00b5\7\36\2\2\u00b5\u00b7\3\2\2\2\u00b6"+
		"\u00b2\3\2\2\2\u00b7\u00ba\3\2\2\2\u00b8\u00b6\3\2\2\2\u00b8\u00b9\3\2"+
		"\2\2\u00b9\25\3\2\2\2\u00ba\u00b8\3\2\2\2\u00bb\u00c3\5\32\16\2\u00bc"+
		"\u00bd\5\34\17\2\u00bd\u00be\7:\2\2\u00be\u00bf\5\26\f\2\u00bf\u00c0\7"+
		"\n\2\2\u00c0\u00c1\5\26\f\2\u00c1\u00c3\3\2\2\2\u00c2\u00bb\3\2\2\2\u00c2"+
		"\u00bc\3\2\2\2\u00c3\27\3\2\2\2\u00c4\u00c5\t\3\2\2\u00c5\31\3\2\2\2\u00c6"+
		"\u00c7\5\30\r\2\u00c7\u00c8\7\33\2\2\u00c8\u00c9\5D#\2\u00c9\u00ca\7\34"+
		"\2\2\u00ca\u00cd\3\2\2\2\u00cb\u00cd\5\34\17\2\u00cc\u00c6\3\2\2\2\u00cc"+
		"\u00cb\3\2\2\2\u00cd\33\3\2\2\2\u00ce\u00d3\5\36\20\2\u00cf\u00d0\7*\2"+
		"\2\u00d0\u00d2\5\36\20\2\u00d1\u00cf\3\2\2\2\u00d2\u00d5\3\2\2\2\u00d3"+
		"\u00d1\3\2\2\2\u00d3\u00d4\3\2\2\2\u00d4\35\3\2\2\2\u00d5\u00d3\3\2\2"+
		"\2\u00d6\u00db\5\"\22\2\u00d7\u00d8\7+\2\2\u00d8\u00da\5\"\22\2\u00d9"+
		"\u00d7\3\2\2\2\u00da\u00dd\3\2\2\2\u00db\u00d9\3\2\2\2\u00db\u00dc\3\2"+
		"\2\2\u00dc\37\3\2\2\2\u00dd\u00db\3\2\2\2\u00de\u00df\t\4\2\2\u00df!\3"+
		"\2\2\2\u00e0\u00e6\5&\24\2\u00e1\u00e2\5 \21\2\u00e2\u00e3\5&\24\2\u00e3"+
		"\u00e5\3\2\2\2\u00e4\u00e1\3\2\2\2\u00e5\u00e8\3\2\2\2\u00e6\u00e4\3\2"+
		"\2\2\u00e6\u00e7\3\2\2\2\u00e7#\3\2\2\2\u00e8\u00e6\3\2\2\2\u00e9\u00ea"+
		"\t\5\2\2\u00ea%\3\2\2\2\u00eb\u00f1\5*\26\2\u00ec\u00ed\5$\23\2\u00ed"+
		"\u00ee\5*\26\2\u00ee\u00f0\3\2\2\2\u00ef\u00ec\3\2\2\2\u00f0\u00f3\3\2"+
		"\2\2\u00f1\u00ef\3\2\2\2\u00f1\u00f2\3\2\2\2\u00f2\'\3\2\2\2\u00f3\u00f1"+
		"\3\2\2\2\u00f4\u00f5\t\6\2\2\u00f5)\3\2\2\2\u00f6\u00fc\5.\30\2\u00f7"+
		"\u00f8\5(\25\2\u00f8\u00f9\5.\30\2\u00f9\u00fb\3\2\2\2\u00fa\u00f7\3\2"+
		"\2\2\u00fb\u00fe\3\2\2\2\u00fc\u00fa\3\2\2\2\u00fc\u00fd\3\2\2\2\u00fd"+
		"+\3\2\2\2\u00fe\u00fc\3\2\2\2\u00ff\u0100\t\7\2\2\u0100-\3\2\2\2\u0101"+
		"\u0107\5\60\31\2\u0102\u0103\5,\27\2\u0103\u0104\5\60\31\2\u0104\u0106"+
		"\3\2\2\2\u0105\u0102\3\2\2\2\u0106\u0109\3\2\2\2\u0107\u0105\3\2\2\2\u0107"+
		"\u0108\3\2\2\2\u0108/\3\2\2\2\u0109\u0107\3\2\2\2\u010a\u010c\7)\2\2\u010b"+
		"\u010a\3\2\2\2\u010b\u010c\3\2\2\2\u010c\u010d\3\2\2\2\u010d\u010e\5\62"+
		"\32\2\u010e\61\3\2\2\2\u010f\u0116\58\35\2\u0110\u0111\7\33\2\2\u0111"+
		"\u0112\5\26\f\2\u0112\u0113\7\34\2\2\u0113\u0116\3\2\2\2\u0114\u0116\5"+
		"\64\33\2\u0115\u010f\3\2\2\2\u0115\u0110\3\2\2\2\u0115\u0114\3\2\2\2\u0116"+
		"\63\3\2\2\2\u0117\u011b\7D\2\2\u0118\u011a\5\66\34\2\u0119\u0118\3\2\2"+
		"\2\u011a\u011d\3\2\2\2\u011b\u0119\3\2\2\2\u011b\u011c\3\2\2\2\u011c\65"+
		"\3\2\2\2\u011d\u011b\3\2\2\2\u011e\u011f\7\"\2\2\u011f\u0128\7D\2\2\u0120"+
		"\u0121\7\35\2\2\u0121\u0122\5\26\f\2\u0122\u0123\7\36\2\2\u0123\u0128"+
		"\3\2\2\2\u0124\u0125\7\35\2\2\u0125\u0126\7\f\2\2\u0126\u0128\7\36\2\2"+
		"\u0127\u011e\3\2\2\2\u0127\u0120\3\2\2\2\u0127\u0124\3\2\2\2\u0128\67"+
		"\3\2\2\2\u0129\u012c\7\22\2\2\u012a\u012c\7\23\2\2\u012b\u0129\3\2\2\2"+
		"\u012b\u012a\3\2\2\2\u012c9\3\2\2\2\u012d\u0131\5@!\2\u012e\u0131\5B\""+
		"\2\u012f\u0131\5H%\2\u0130\u012d\3\2\2\2\u0130\u012e\3\2\2\2\u0130\u012f"+
		"\3\2\2\2\u0131\u0132\3\2\2\2\u0132\u0133\7\13\2\2\u0133;\3\2\2\2\u0134"+
		"\u0135\7D\2\2\u0135\u0136\7\26\2\2\u0136\u0137\5D#\2\u0137=\3\2\2\2\u0138"+
		"\u013a\5:\36\2\u0139\u0138\3\2\2\2\u013a\u013d\3\2\2\2\u013b\u0139\3\2"+
		"\2\2\u013b\u013c\3\2\2\2\u013c?\3\2\2\2\u013d\u013b\3\2\2\2\u013e\u013f"+
		"\7$\2\2\u013f\u0140\7\33\2\2\u0140\u0145\5<\37\2\u0141\u0142\7!\2\2\u0142"+
		"\u0144\5<\37\2\u0143\u0141\3\2\2\2\u0144\u0147\3\2\2\2\u0145\u0143\3\2"+
		"\2\2\u0145\u0146\3\2\2\2\u0146\u0148\3\2\2\2\u0147\u0145\3\2\2\2\u0148"+
		"\u0149\7\34\2\2\u0149\u014a\7\37\2\2\u014a\u014b\5> \2\u014b\u014c\7 "+
		"\2\2\u014cA\3\2\2\2\u014d\u014e\7\30\2\2\u014e\u014f\7\33\2\2\u014f\u0150"+
		"\5\26\f\2\u0150\u0151\7\34\2\2\u0151\u0152\7\37\2\2\u0152\u0153\5> \2"+
		"\u0153\u015e\7 \2\2\u0154\u0155\7\31\2\2\u0155\u0156\7\33\2\2\u0156\u0157"+
		"\5\26\f\2\u0157\u0158\7\34\2\2\u0158\u0159\7\37\2\2\u0159\u015a\5> \2"+
		"\u015a\u015b\7 \2\2\u015b\u015d\3\2\2\2\u015c\u0154\3\2\2\2\u015d\u0160"+
		"\3\2\2\2\u015e\u015c\3\2\2\2\u015e\u015f\3\2\2\2\u015f\u0166\3\2\2\2\u0160"+
		"\u015e\3\2\2\2\u0161\u0162\7\32\2\2\u0162\u0163\7\37\2\2\u0163\u0164\5"+
		"> \2\u0164\u0165\7 \2\2\u0165\u0167\3\2\2\2\u0166\u0161\3\2\2\2\u0166"+
		"\u0167\3\2\2\2\u0167C\3\2\2\2\u0168\u0169\5\26\f\2\u0169\u016a\7\27\2"+
		"\2\u016a\u016b\5\26\f\2\u016b\u018a\3\2\2\2\u016c\u016d\7\35\2\2\u016d"+
		"\u016e\5F$\2\u016e\u016f\7;\2\2\u016f\u0174\5<\37\2\u0170\u0171\7!\2\2"+
		"\u0171\u0173\5<\37\2\u0172\u0170\3\2\2\2\u0173\u0176\3\2\2\2\u0174\u0172"+
		"\3\2\2\2\u0174\u0175\3\2\2\2\u0175\u0179\3\2\2\2\u0176\u0174\3\2\2\2\u0177"+
		"\u0178\7#\2\2\u0178\u017a\5\26\f\2\u0179\u0177\3\2\2\2\u0179\u017a\3\2"+
		"\2\2\u017a\u017b\3\2\2\2\u017b\u017c\7\36\2\2\u017c\u018a\3\2\2\2\u017d"+
		"\u017e\7\35\2\2\u017e\u0183\5F$\2\u017f\u0180\7!\2\2\u0180\u0182\5F$\2"+
		"\u0181\u017f\3\2\2\2\u0182\u0185\3\2\2\2\u0183\u0181\3\2\2\2\u0183\u0184"+
		"\3\2\2\2\u0184\u0186\3\2\2\2\u0185\u0183\3\2\2\2\u0186\u0187\7\36\2\2"+
		"\u0187\u018a\3\2\2\2\u0188\u018a\5\64\33\2\u0189\u0168\3\2\2\2\u0189\u016c"+
		"\3\2\2\2\u0189\u017d\3\2\2\2\u0189\u0188\3\2\2\2\u018aE\3\2\2\2\u018b"+
		"\u0190\5\64\33\2\u018c\u0190\5\26\f\2\u018d\u0190\5J&\2\u018e\u0190\5"+
		"b\62\2\u018f\u018b\3\2\2\2\u018f\u018c\3\2\2\2\u018f\u018d\3\2\2\2\u018f"+
		"\u018e\3\2\2\2\u0190G\3\2\2\2\u0191\u0194\5J&\2\u0192\u0194\5`\61\2\u0193"+
		"\u0191\3\2\2\2\u0193\u0192\3\2\2\2\u0194I\3\2\2\2\u0195\u0196\5L\'\2\u0196"+
		"K\3\2\2\2\u0197\u019c\5P)\2\u0198\u0199\79\2\2\u0199\u019b\5P)\2\u019a"+
		"\u0198\3\2\2\2\u019b\u019e\3\2\2\2\u019c\u019a\3\2\2\2\u019c\u019d\3\2"+
		"\2\2\u019dM\3\2\2\2\u019e\u019c\3\2\2\2\u019f\u01a0\t\b\2\2\u01a0O\3\2"+
		"\2\2\u01a1\u01a7\5R*\2\u01a2\u01a3\5N(\2\u01a3\u01a4\5R*\2\u01a4\u01a6"+
		"\3\2\2\2\u01a5\u01a2\3\2\2\2\u01a6\u01a9\3\2\2\2\u01a7\u01a5\3\2\2\2\u01a7"+
		"\u01a8\3\2\2\2\u01a8Q\3\2\2\2\u01a9\u01a7\3\2\2\2\u01aa\u01af\5T+\2\u01ab"+
		"\u01ac\7;\2\2\u01ac\u01ae\5T+\2\u01ad\u01ab\3\2\2\2\u01ae\u01b1\3\2\2"+
		"\2\u01af\u01ad\3\2\2\2\u01af\u01b0\3\2\2\2\u01b0S\3\2\2\2\u01b1\u01af"+
		"\3\2\2\2\u01b2\u01b3\7;\2\2\u01b3\u01b4\7;\2\2\u01b4\u01b5\7\33\2\2\u01b5"+
		"\u01b6\5D#\2\u01b6\u01b7\7\34\2\2\u01b7\u01ba\3\2\2\2\u01b8\u01ba\5V,"+
		"\2\u01b9\u01b2\3\2\2\2\u01b9\u01b8\3\2\2\2\u01baU\3\2\2\2\u01bb\u01c0"+
		"\5X-\2\u01bc\u01bd\7<\2\2\u01bd\u01bf\5X-\2\u01be\u01bc\3\2\2\2\u01bf"+
		"\u01c2\3\2\2\2\u01c0\u01be\3\2\2\2\u01c0\u01c1\3\2\2\2\u01c1W\3\2\2\2"+
		"\u01c2\u01c0\3\2\2\2\u01c3\u01c4\7<\2\2\u01c4\u01c5\7<\2\2\u01c5\u01c6"+
		"\7\33\2\2\u01c6\u01c7\5D#\2\u01c7\u01c8\7\34\2\2\u01c8\u01cb\3\2\2\2\u01c9"+
		"\u01cb\5Z.\2\u01ca\u01c3\3\2\2\2\u01ca\u01c9\3\2\2\2\u01cbY\3\2\2\2\u01cc"+
		"\u01ce\7=\2\2\u01cd\u01cc\3\2\2\2\u01cd\u01ce\3\2\2\2\u01ce\u01cf\3\2"+
		"\2\2\u01cf\u01d0\5\\/\2\u01d0[\3\2\2\2\u01d1\u01d8\5\64\33\2\u01d2\u01d8"+
		"\7\23\2\2\u01d3\u01d4\7\33\2\2\u01d4\u01d5\5J&\2\u01d5\u01d6\7\34\2\2"+
		"\u01d6\u01d8\3\2\2\2\u01d7\u01d1\3\2\2\2\u01d7\u01d2\3\2\2\2\u01d7\u01d3"+
		"\3\2\2\2\u01d8]\3\2\2\2\u01d9\u01da\t\t\2\2\u01da_\3\2\2\2\u01db\u01dc"+
		"\5^\60\2\u01dc\u01dd\7\33\2\2\u01dd\u01e0\5D#\2\u01de\u01df\7!\2\2\u01df"+
		"\u01e1\5\26\f\2\u01e0\u01de\3\2\2\2\u01e0\u01e1\3\2\2\2\u01e1\u01e2\3"+
		"\2\2\2\u01e2\u01e3\7\34\2\2\u01e3a\3\2\2\2\u01e4\u01e5\b\62\1\2\u01e5"+
		"\u01e6\7\33\2\2\u01e6\u01e7\5b\62\2\u01e7\u01e8\7\34\2\2\u01e8\u01ef\3"+
		"\2\2\2\u01e9\u01ef\5d\63\2\u01ea\u01ef\5\64\33\2\u01eb\u01ef\5\26\f\2"+
		"\u01ec\u01ef\5D#\2\u01ed\u01ef\7E\2\2\u01ee\u01e4\3\2\2\2\u01ee\u01e9"+
		"\3\2\2\2\u01ee\u01ea\3\2\2\2\u01ee\u01eb\3\2\2\2\u01ee\u01ec\3\2\2\2\u01ee"+
		"\u01ed\3\2\2\2\u01ef\u01f4\3\2\2\2\u01f0\u01f1\f\t\2\2\u01f1\u01f3\5f"+
		"\64\2\u01f2\u01f0\3\2\2\2\u01f3\u01f6\3\2\2\2\u01f4\u01f2\3\2\2\2\u01f4"+
		"\u01f5\3\2\2\2\u01f5c\3\2\2\2\u01f6\u01f4\3\2\2\2\u01f7\u01f8\5\34\17"+
		"\2\u01f8\u01f9\7:\2\2\u01f9\u01fa\5b\62\2\u01fa\u01fb\7\n\2\2\u01fb\u01fc"+
		"\5b\62\2\u01fce\3\2\2\2\u01fd\u01fe\7F\2\2\u01fe\u0200\5b\62\2\u01ff\u0201"+
		"\5f\64\2\u0200\u01ff\3\2\2\2\u0200\u0201\3\2\2\2\u0201g\3\2\2\2\61inr"+
		"y\u0081\u008c\u0094\u009e\u00a3\u00ac\u00b8\u00c2\u00cc\u00d3\u00db\u00e6"+
		"\u00f1\u00fc\u0107\u010b\u0115\u011b\u0127\u012b\u0130\u013b\u0145\u015e"+
		"\u0166\u0174\u0179\u0183\u0189\u018f\u0193\u019c\u01a7\u01af\u01b9\u01c0"+
		"\u01ca\u01cd\u01d7\u01e0\u01ee\u01f4\u0200";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}