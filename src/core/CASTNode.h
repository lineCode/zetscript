#pragma once

#define MAX_EXPRESSION_LENGTH 8192

#define MAIN_AST_ROOT_PTR					(CASTNode::getAstNodePtr(0))
#define MAIN_AST_ROOT						(CASTNode::getAstNode(0))
#define MAIN_SCOPE_ROOT						(CASTNode::getScope(0))
#define AST_NODE(idx) 						CASTNode::getAstNode(idx)
#define AST_SCOPE_INFO_IDX(idx) 			CASTNode::getScopeIdx(idx)
#define AST_SCOPE_INFO(idx) 				CASTNode::getScope(idx)
#define AST_LINE_VALUE(idx) 				CASTNode::getAstLine(idx)
#define AST_SYMBOL_VALUE(idx) 				CASTNode::getAstSymbolName(idx)
#define AST_SYMBOL_VALUE_CONST_CHAR(idx) 	CASTNode::getAstSymbolNameConstChar(idx)

enum GROUP_TYPE{
	GROUP_0=0, // +,-,||
	GROUP_1, // *,/,==,>,<,<=,>=
	GROUP_2, // &&
	GROUP_3, // !
	GROUP_4, // .
	GROUP_5, // .
	GROUP_6, // .
	GROUP_7, // .
	MAX_GROUPS
};




class CScope;
class CASTNode{

public:

	static tInfoKeyword defined_keyword[MAX_KEYWORD];
	static tInfoPunctuator defined_operator_punctuator[MAX_OPERATOR_PUNCTUATORS];
	static tInfoPunctuator defined_special_punctuator[MAX_SPECIAL_PUNCTUATORS];


	static void setVectorASTNode(vector<CASTNode *> 	* set_vec_ast_node);


	static char * generateAST_Recursive(const char *s, int & m_line, CScope *scope_info, bool & error, PASTNode *node_to_be_evaluated=NULL, bool allow_breaks = false, bool is_main_node=false);
	/**
	 * Get CASTNode Node by its idx, regarding current state.
	 */

	static void 					init();
	static CASTNode				*  	newASTNode();
	static vector<CASTNode *>	*	getVectorASTNodeNode(); // ast collection register...

	static PASTNode 			* 	getAstNodePtr(int ast_idx);
	static CASTNode 			* 	getAstNode(int ast_idx);
	static int 				  		getScopeIdx(int ast_idx);
	static CScope 				*	getScope(int ast_idx);
	static int 				  		getAstLine(int ast_idx);
	static const char 			* 	getAstSymbolName(int ast_idx);
	static const char 			*	getAstSymbolNameConstChar(int ast_idx);

	static CASTNode * getNodeByIdx(int idx);
	static CScope * getScopeByIdx(int idx);
	static int getLineValueByIdx(int idx);
	static const string & getSymbolValueByIdx(int idx);
	static const char * getSymbolValueConstCharByIdx(int idx);

	CASTNode(int preallocate_num_nodes=0);

	NODE_TYPE node_type;
	tInfoKeyword *keyword_info;
	tInfoPunctuator *operator_info,*pre_post_operator_info;
	string 	symbol_value;
	string type_ptr;
	int idxScope; // saves scope info ptr (only for global vars).
	string type_class;
	int line_value;
	PASTNode parent;
	vector<PASTNode> children; //left,right;
	void *aux_value;
	int idxAstNode;


	~CASTNode();

private:

	// main ast class
	static vector<CASTNode *> 						* vec_ast_node; // ast collection register...



	static tInfoKeyword * isKeyword(const char *c);

	//static int insertAstNode(CASTNode *ast_node);
	//static string *aux_str;

	//-----------------------------------------------
	//


	static PASTNode  findAstRecursive(const string & _name_to_find, NODE_TYPE _node_type, KEYWORD_TYPE _keyword_type, PASTNode _node);
	static PASTNode  findAst(const string & _name_to_find, NODE_TYPE _node_type_to_find, KEYWORD_TYPE _keyword_type_to_find);
	static char * 	 isClassMember(const char *s,int & m_line, string & _class_name, string & var_name, PASTNode & _class_node, bool & error);


	// string generic utils...
	static char *getSymbolName(const char *s,int & m_startLine);
	static char * getEndWord(const char *s, int m_line);


	//static PASTNode preNodePunctuator(tInfoPunctuator * punctuator,PASTNode affected_op);
	//static PASTNode postOperator(tInfoPunctuator * punctuator,PASTNode affected_op);

	static bool printErrorUnexpectedKeywordOrPunctuator(const char *current_string_ptr, int m_line);

	// Punctuators...
	static bool parsePlusPunctuator(const char *s);
	static bool parseMinusPunctuator(const char *s);
	static bool parseMulPunctuator(const char *s);
	static bool parseDivPunctuator(const char *s);
	static bool parseModPunctuator(const char *s);

	static bool parseFieldPunctuator(const char *s);
	static bool parseInlineIfPunctuator(const char *s);
	static bool parseInlineElsePunctuator(const char *s);

	static bool parseAssignPunctuator(const char *s);
	static bool parseAddAssignPunctuator(const char *s);
	static bool parseSubAssignPunctuator(const char *s);
	static bool parseMulAssignPunctuator(const char *s);
	static bool parseDivAssignPunctuator(const char *s);
	static bool parseModAssignPunctuator(const char *s);


	static bool parseBinaryXorPunctuator(const char *s);
	static bool parseBinaryAndPunctuator(const char *s);
	static bool parseBinaryOrPunctuator(const char *s);
	static bool parseShiftLeftPunctuator(const char *s);
	static bool parseShiftRightPunctuator(const char *s);

	static bool parseLogicAndPunctuator(const char *s);
	static bool parseLogicOrPunctuator(const char *s);
	static bool parseLogicEqualPunctuator(const char *s);
	static bool parseLogicNotEqualPunctuator(const char *s);
	static bool parseLogicGreatherThanPunctuator(const char *s);
	static bool parseLogicLessThanPunctuator(const char *s);
	static bool parseLogicGreatherEqualThanPunctuator(const char *s);
	static bool parseLessEqualThanPunctuator(const char *s);
	static bool parseNotPunctuator(const char *s);


	static tInfoPunctuator *checkPreOperatorPunctuator(const char *s);
	static tInfoPunctuator *checkPostOperatorPunctuator(const char *s);

	static bool parseIncPunctuator(const char *s);
	static bool parseDecPunctuator(const char *s);



	static tInfoPunctuator * parsePunctuatorGroup0(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup1(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup2(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup3(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup4(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup5(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup6(const char *s);
	static tInfoPunctuator * parsePunctuatorGroup7(const char *s);

	static tInfoPunctuator *  isOperatorPunctuator(const char *s);
	static tInfoPunctuator *  isSpecialPunctuator(const char *s);
	static tInfoPunctuator * isPunctuator(const char *s);


	// AST core functions ...
	static char * parseExpression(const char *s, int & m_line, CScope *scope_info, PASTNode * ast_node_to_be_evaluated=NULL);
	static char * parseExpression_Recursive(const char *s, int & m_line, CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL,GROUP_TYPE type_group=GROUP_TYPE::GROUP_0,PASTNode parent=NULL);


	static char *   functionArrayAccess_Recursive(const char *str, int & m_line, CScope *scope_info, PASTNode *ast_node_to_be_evaluated, PASTNode parent);
	static char *   functionArrayAccess(const char *str, int & m_line, CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL, PASTNode parent=NULL);
	/**
	 * this functions tries to evaluate expression that was get from getSymbolValue and didn't know as trivial expression like (), function(), etc.
	 * Must be evaluated later with this function.
	 */
	static char *   deduceExpression(const char *str, int & m_line, CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL, PASTNode parent=NULL);


	// parse block { }
	static char * parseBlock(const char *s,int & m_line,  CScope *scope_info, bool & error, PASTNode *ast_node_to_be_evaluated=NULL, bool push_scope=true);


	// keyword...

	static char * parseKeyWord(const char *s, int & m_start_line, CScope *scope_info, bool & error, PASTNode *ast_node_to_be_evaluated=NULL);

	static char * parseStruct_Recursive(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseStruct(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseIf(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseFor(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseWhile(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseSwitch(const char *s,int & m_line, CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseVar(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseMemberVar(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseReturn(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseFunction(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseNew(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static char * parseDelete(const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);

	static char * parseClass(const char *s,int & m_line,  CScope *scope_info,PASTNode *ast_node_to_be_evaluated);


	static char * parseArgs(char c1, char c2,const char *s,int & m_line,  CScope *scope_info, PASTNode *ast_node_to_be_evaluated=NULL);
	static bool isMarkEndExpression(char c);

	/**
	 * Try to get symbol. It can be trivial (i.e values or names) or not trivial ( inline functions, if-else, etc). At the end, the parse will perform to
	 * parse non-trivial symbols with a special function.
	 */
	static char * getSymbolValue(
			const char *current_string_ptr,
			int & m_line,
			CScope *scope_info,
			string & symbol_name,
			int & m_definedSymbolLine,
			tInfoPunctuator *pre_operator,
			tInfoPunctuator **post_operator,
			bool & is_symbol_trivial
	);


	//-----------------------------------------------
	// OWN FUNCTIONS...

	//void destroyChildren_Recursive(PASTNode _node);
	//void destroyChildren();



};

