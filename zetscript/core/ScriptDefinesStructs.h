#pragma once


class tASTNode;
typedef tASTNode *PASTNode;
struct tInfoRegisteredFunctionSymbol;
class tInfoScopeVar;
struct tInfoRegisteredClass;
struct tScriptFunctionInfo;
struct tInfoVarScopeBlock;

int insertAstNode(tASTNode * ast_node);
int insertInfoScopeVar(tInfoScopeVar * ast_node);



#define MAX_PARAM_C_FUNCTION 6

enum NODE_TYPE{
	UNKNOWN_NODE=0,
	MAIN_NODE=1,
	PUNCTUATOR_NODE,
	EXPRESSION_NODE,
	KEYWORD_NODE,
	ARGS_DECL_NODE,
	ARGS_PASS_NODE,
	ARRAY_ACCESS_NODE,
	ARRAY_INDEX_NODE,
	ARRAY_OBJECT_NODE,
	FUNCTION_OBJECT_NODE,
	SYMBOL_NODE,
	BODY_NODE,
	GROUP_CASES_NODE,
	CONDITIONAL_NODE,
	PRE_FOR_NODE,
	POST_FOR_NODE,
	CLASS_VAR_COLLECTION_NODE,
	CLASS_FUNCTION_COLLECTION_NODE,
	BASE_CLASS_NODE,
	CALLING_OBJECT_NODE,
	ARRAY_REF_NODE,
	FUNCTION_REF_NODE,
	NEW_OBJECT_NODE,
	ACCESS_OBJECT_MEMBER_NODE,
	STRUCT_NODE,
	MAX_NODE_TYPE
};


enum KEYWORD_TYPE{
	UNKNOWN_KEYWORD=0,
	IF_KEYWORD,
	ELSE_KEYWORD,
	FOR_KEYWORD,
	WHILE_KEYWORD,
	VAR_KEYWORD,
	SWITCH_KEYWORD,
	CASE_KEYWORD,
	DEFAULT_KEYWORD,
	BREAK_KEYWORD,
	RETURN_KEYWORD,
	FUNCTION_KEYWORD,
	CLASS_KEYWORD,
	THIS_KEYWORD,
//	SUPER_KEYWORD,
	NEW_KEYWORD,
	DELETE_KEYWORD,
	MAX_KEYWORD
};

enum PUNCTUATOR_TYPE{

	UNKNOWN_PUNCTUATOR=0,

	//--------------------------------
	// First OPERATORS 2 char size


	SHIFT_LEFT_PUNCTUATOR=1, // <<
	SHIFT_RIGHT_PUNCTUATOR, // >>


	LOGIC_AND_PUNCTUATOR, // &&
	LOGIC_OR_PUNCTUATOR, // ||
	LOGIC_EQUAL_PUNCTUATOR, // =
	LOGIC_NOT_EQUAL_PUNCTUATOR, // !=
	LOGIC_GTE_PUNCTUATOR, // >=
	LOGIC_LTE_PUNCTUATOR, // <=

	PRE_INC_PUNCTUATOR, // ++
	PRE_DEC_PUNCTUATOR, // --

	POST_INC_PUNCTUATOR, // ++
	POST_DEC_PUNCTUATOR, // --

	// Then OPERATORS 1 char size
	ADD_PUNCTUATOR, // +
	SUB_PUNCTUATOR, // -
	MUL_PUNCTUATOR, // *
	DIV_PUNCTUATOR, // /
	MOD_PUNCTUATOR, // %

	FIELD_PUNCTUATOR, // .

	ASSIGN_PUNCTUATOR, // =
	ADD_ASSIGN_PUNCTUATOR, // +=
	SUB_ASSIGN_PUNCTUATOR, // -=
	MUL_ASSIGN_PUNCTUATOR, // *=
	DIV_ASSIGN_PUNCTUATOR, // /=
	MOD_ASSIGN_PUNCTUATOR, // %=

	BINARY_XOR_PUNCTUATOR, // ^
	BINARY_AND_PUNCTUATOR, // &
	BINARY_OR_PUNCTUATOR, // |

	LOGIC_GT_PUNCTUATOR, // >
	LOGIC_LT_PUNCTUATOR, // <
	LOGIC_NOT_PUNCTUATOR, // !

	TERNARY_IF_PUNCTUATOR, // ?
	TERNARY_ELSE_PUNCTUATOR, // :


	MAX_OPERATOR_PUNCTUATORS,


	//---------------------------
	// SPECIAL CHARACTERS

	COMA_PUNCTUATOR=1,
	SEMICOLON_PUNCTUATOR,

	OPEN_PARENTHESIS_PUNCTUATOR,
	CLOSE_PARENTHESIS_PUNCTUATOR,

	OPEN_BRAKET_PUNCTUATOR,
	CLOSE_BRAKET_PUNCTUATOR,

	OPEN_SQUARE_BRAKET_PUNCTUATOR,
	CLOSE_SQUARE_BRAKET_PUNCTUATOR,

	MAX_SPECIAL_PUNCTUATORS


};


enum LOAD_TYPE{

		LOAD_TYPE_NOT_DEFINED=0,
		LOAD_TYPE_NULL,
		LOAD_TYPE_UNDEFINED,
		LOAD_TYPE_CONSTANT,
		LOAD_TYPE_VARIABLE,
		LOAD_TYPE_FUNCTION,
		LOAD_TYPE_ARGUMENT
};

enum SCOPE_TYPE{
	UNKNOWN_SCOPE=0,
	GLOBAL_SCOPE,
	LOCAL_SCOPE,
	THIS_SCOPE,
	SUPER_SCOPE,
	ACCESS_SCOPE
};

enum IDX_OBJ_SPECIAL_VALUE{
	IDX_INVALID = -1,
	IDX_THIS=-10
};

enum PROXY_CREATOR{
	CREATE_FUNCTION=0,
	DESTROY_FUNCTION
};


enum ASM_OPERATOR{
		INVALID_OP=-1,
		NOP=0,
		MOV, // mov expression to var
		LOAD, // primitive value like number/string or boolean...
		EQU,  // ==
		NOT_EQU,  // !=
		LT,  // <
		LTE,  // <=
		NOT, // !
		GT,  // >
		GTE, // >=

		ADD, // +
		NEG, // -a
		LOGIC_AND, // &&
		LOGIC_OR,  // ||
		DIV, // /
		MUL, // *
		MOD,  // %
		AND, // bitwise logic and
		OR, // bitwise logic or
		XOR, // logic xor
		SHL, // shift left
		SHR, // shift right
		// special internal ops...
		JMP,
		JNT, // goto if not true ... goes end to conditional.
		JT, // goto if true ... goes end to conditional.
		CALL, // calling function after all of args are processed...
		PUSH, // push arg
		CLR, // clear args
		VGET, // vector access after each index is processed...

		VPUSH, // Value push for vector
		VPOP, // Value pop for vector

		VEC, // Vector object
		RET, // ret instruction ..

		NEW, // new operator...
		OBJECT_ACCESS, // object access .
		SAVE_I, // save current instruction...
		LOAD_I, // load value that points saved instruction...

		POP_SCOPE,
		DECL_STRUCT,
		PUSH_ATTR,
		MAX_OPERATORS


};

enum ASM_PRE_POST_OPERATORS{
	UNKNOW_PRE_POST_OPERATOR=0,
	PRE_INC, // ++
	POST_INC, // ++
	PRE_DEC, // --
	POST_DEC, // --
	PRE_NEG
};


enum VALUE_INSTRUCTION_TYPE{
	INS_TYPE_NULL=0,
	INS_TYPE_UNDEFINED,
	INS_TYPE_INTEGER, // primitive int
	INS_TYPE_NUMBER, // primitive number
	INS_TYPE_BOOLEAN, // primitive bool
	INS_TYPE_STRING, // primitive string
	INS_TYPE_FUNCTION, // primitive function
	INS_TYPE_VAR, // always is an script class...
	INS_MAX_TYPES
};


#define MAIN_SCRIPT_CLASS_NAME 		"__MainClass__"
#define MAIN_SCRIPT_FUNCTION_NAME 	"__mainFunction__"

typedef int (*fntConversionType)(CScriptVariable *obj);

//typedef tInfoStatementOp *PInfoStatementOp;
enum SYMBOL_INFO_PROPERTIES{
	PROPERTY_C_OBJECT_REF = 0x1 <<0,
	PROPERTY_IS_DERIVATED = 0x1 <<1,
	PROPERTY_VARIABLE = 0x1 << 2,
	PROPERTY_FUNCTION = 0x1 << 3,
	PROPERTY_STATIC_REF = 0x1 << 4,
	PROPERTY_CONSTRUCTOR = 0x1 << 5


};


//typedef tInfoStatementOp *PInfoStatementOp;
enum ALE_INFO_PROPERTIES{
	PROPERTY_IS_ARG = 0x1 <<0,


};


struct tInfoRegisteredVariableSymbol{
	unsigned int	 ref_ptr; // pointer ref to C Var/Function
	string 	 symbol_name;
	int idxClassInfo;//tInfoRegisteredClass		 *class_info;
	int idxInfoScopeVar;//tInfoScopeVar  				*info_var_scope;
	int idxAstNode;
	unsigned int properties; // SYMBOL_INFO_PROPERTIES
	string c_type; // In case is C, we need to know its type ...
	int index;

	tInfoRegisteredVariableSymbol(){
		properties=0;
		c_type="";
		idxAstNode=-1;
		symbol_name = "";
		ref_ptr=0;
		//class_info=NULL;
		//info_var_scope=NULL;
		idxClassInfo=-1;
		idxInfoScopeVar=-1;
		index=-1;

	}
};


typedef struct{
	KEYWORD_TYPE id;
	const char *str;
	char * (* parse_fun )(const char *,int & ,  CScopeInfo *, PASTNode *);
}tInfoKeyword;



typedef struct{
	PUNCTUATOR_TYPE id;
	const char *str;
	bool (* parse_fun )(const char *);
}tInfoPunctuator;


enum{
	LEFT_NODE=0,
	RIGHT_NODE
};

class tASTNode{

	void destroyChildren_Recursive(PASTNode _node){

		if(_node != NULL){

			for(unsigned i = 0; i < _node->children.size(); i++){
				if(_node->children[i]!= NULL){
					destroyChildren_Recursive(_node->children[i]);
				}
			}
    		_node->children.clear();
			delete _node;
			_node = NULL;
		}

	}

	void destroyChildren(){
		for(unsigned i = 0; i < children.size(); i++){
			destroyChildren_Recursive(children[i]);
		}
		children.clear();
	}

public:

	NODE_TYPE node_type;
	tInfoKeyword *keyword_info;
	tInfoPunctuator *operator_info,*pre_post_operator_info;
	string 	symbol_value;
	string type_ptr;
	int idxScopeInfo; // saves scope info ptr (only for global vars).
	string type_class;
	int line_value;
	PASTNode parent;
	vector<PASTNode> children; //left,right;
	void *aux_value;
	int idxAstNode;

	tASTNode(int preallocate_num_nodes=0){
		node_type = UNKNOWN_NODE;
		keyword_info = NULL;
		pre_post_operator_info = NULL;
		line_value=-1;
		operator_info=NULL;
		symbol_value="";
		parent=NULL;
		aux_value=NULL;

		idxAstNode = insertAstNode(this);
		idxScopeInfo = -1;

		if(preallocate_num_nodes > 0){
			for(int i = 0; i < preallocate_num_nodes; i++){
				children.push_back(NULL);
			}
		}
	}

	~tASTNode(){
		destroyChildren();
	}

};

//-----------------------------

class tInfoScopeVar{
public:
	string symbol_ref;
	string name; // var name
	int idxInfoScopeVar;
	int idxAstNode; // ast node info.

	tInfoScopeVar(){
		symbol_ref="";
		name="";
		idxInfoScopeVar = insertInfoScopeVar(this);
	}
};


//-----------------------------


typedef struct{
	const char *op_str;
	ASM_OPERATOR op_id;
	int n_ops;
}tDefOperator;


enum ASM_PROPERTIES{
	ASM_PROPERTY_CALLING_OBJECT = 0x1<<0,
	ASM_PROPERTY_DIRECT_CALL_RETURN = 0x1 << 1
};



struct tInfoAsmOp{

	// string symbol_name;
	VALUE_INSTRUCTION_TYPE variable_type;
	int idxAstNode; // define ast node for give some information at run time
	 //------------------

	 ASM_OPERATOR operator_type;
	 ASM_PRE_POST_OPERATORS pre_post_operator_type;
	 //void *ptr_value; // can be float, bool or string.
	 //------------------

	 int index_op1,index_op2; // left and right respectively
	 int asm_properties;
	 SCOPE_TYPE scope_type; // in case needed.
	 tScriptFunctionInfo *script_info;
	 //string aux_name;

	// bool (* isconvertable)(int value);

	tInfoAsmOp(){
		variable_type = VALUE_INSTRUCTION_TYPE::INS_TYPE_UNDEFINED;
		//variable_type=VAR_TYPE::NOT_DEFINED;
		operator_type=ASM_OPERATOR::INVALID_OP;
		pre_post_operator_type =ASM_PRE_POST_OPERATORS::UNKNOW_PRE_POST_OPERATOR;
		idxAstNode = -1;
		scope_type=LOCAL_SCOPE;
		asm_properties=0;
		index_op1=index_op2=-1;
		//script_info=NULL;
		script_info=NULL;
	}

};

struct tInfoStatementOp{

	vector<tInfoAsmOp *> asm_op;
};

//-------------------------------------------------------

struct tLocalSymbolInfo{
	vector<tInfoRegisteredVariableSymbol> 	m_registeredVariable; // member variables to be copied in every new instance
	vector<tInfoRegisteredFunctionSymbol> 	m_registeredFunction; // member functions
};

struct tScriptFunctionInfo{ // script function is shared by class and function ...
	tInfoRegisteredVariableSymbol 	symbol_info;
	tLocalSymbolInfo 		local_symbols;

	// the info asm op for each function. Will be filled at compile time.
	vector<tInfoStatementOp> statment_op;
	vector<tInfoVarScopeBlock> info_var_scope; // list var per scope in any function ...
};

struct tInfoRegisteredFunctionSymbol{

	tScriptFunctionInfo	object_info;

	//tInfoRegisteredFunctionSymbol *virtual_function;

	// var for function ...
	vector<string> m_arg; // tells var arg name or var type name (in of C )
	int idx_return_type; // -1 not inicialized type return.

	tInfoRegisteredFunctionSymbol(){
		//virtual_function = NULL;
		idx_return_type = -1;
	}
};

/**
 * Stores the basic information to build a object through built AST structure
 */
struct tInfoRegisteredClass{

	tInfoRegisteredFunctionSymbol	metadata_info;
	int idx_function_script_constructor;
	int class_idx;

	std::function<void *()> 		* 	c_constructor;
	std::function<void (void *p)> 	*	c_destructor;
	string classPtrType; // type_id().name();
	vector<tInfoRegisteredClass *> baseClass; // in the case is and extension of class.

	tInfoRegisteredClass(){

		class_idx=-1;
		classPtrType="";
		c_destructor = NULL;
		c_constructor=NULL;
		idx_function_script_constructor=-1;
	}

};

/**
 * Scope register
 */
struct tInfoVarScopeBlock{
	vector<int> var_index;
	int idxScopeInfo;
};





