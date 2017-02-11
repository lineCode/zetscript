#include "../../CZetScript.h"

#define MAX_STATMENT_LENGTH 2096
#define MAX_VAR_LENGTH 100

int n_anonymouse_func=0;
vector<CScopeInfo *> * CScopeInfo::vec_index_scope_node=NULL;
vector<tInfoScopeVar *> * CScopeInfo::vec_index_registered_var=NULL;

int CScopeInfo::insertInfoScopeVar(tInfoScopeVar *isv){

	vec_index_registered_var->push_back(isv);
	return vec_index_registered_var->size()-1;

}

int insertInfoScopeVar(tInfoScopeVar *isv){

	return CScopeInfo::insertInfoScopeVar(isv);
}


tInfoScopeVar * CScopeInfo::getInfoScopeVarByIdx(int idx){
	if(idx < 0 || (unsigned)idx >= vec_index_registered_var->size()){
		print_error_cr("tInfoScopeVar node out of bound");
		return NULL;
	}

	return vec_index_registered_var->at(idx);
}
//------------------------------------------------------------------------------------------------

void CScopeInfo::createSingletons(){
	if(CScopeInfo::vec_index_scope_node==NULL){
		CScopeInfo::vec_index_scope_node = new vector<CScopeInfo *>();
	}

	if(CScopeInfo::vec_index_registered_var==NULL){
		CScopeInfo::vec_index_registered_var = new vector<tInfoScopeVar *>();
	}
}

//------------------------------------------------------------------------------------------------

int CScopeInfo::insertScopeInfoNode(CScopeInfo *scp){
	vec_index_scope_node->push_back(scp);
	return vec_index_scope_node->size()-1;
}

CScopeInfo * CScopeInfo::getScopeInfoByIdx(int idx){
	if(idx < 0 || (unsigned)idx >= vec_index_scope_node->size()){
		print_error_cr("CScopeInfo node out of bound");
		return NULL;
	}

	return vec_index_scope_node->at(idx);
}

//------------------------------------------------------------------------------------------------

CScopeInfo::CScopeInfo(CScopeInfo * _parent){//, int _index){
	m_parentScope = _parent;
	//m_index = _index;
	m_currentScopePointer=NULL;
	//m_baseScope = this;


	if(_parent == NULL){
		m_baseScope = this;
		m_currentScopePointer=this;
		//totalScopes = 0;
	//	m_index = 0;
	}else{
		m_baseScope = _parent->getBaseScope();
		//m_baseScope->getScopeList()->push_back(this);
		//m_index = m_baseScope->getScopeList()->size()-1;
	}


	m_index = insertScopeInfoNode(this);


}
/*
int CScopeInfo::incTotalScopes(){
	totalScopes++;
	return totalScopes;
}
*/
CScopeInfo * CScopeInfo::getBaseScope(){
	return m_baseScope;
}



CScopeInfo * CScopeInfo::getParent(){
	return m_parentScope;
}

CScopeInfo * CScopeInfo::getCurrentScopePointer(){
	return m_baseScope->m_currentScopePointer;
}

void CScopeInfo::resetScopePointer(){
	m_baseScope->m_currentScopePointer = m_baseScope;
}

CScopeInfo * CScopeInfo::pushScope(){



	CScopeInfo *new_scope = new CScopeInfo(m_baseScope->m_currentScopePointer);//, m_baseScope->incTotalScopes());
	m_baseScope->m_currentScopePointer->m_scopeList.push_back(new_scope);
	m_baseScope->m_currentScopePointer = new_scope;
	return m_baseScope->m_currentScopePointer;

}

CScopeInfo * CScopeInfo::popScope(){

	if(m_baseScope->m_currentScopePointer->m_parentScope != NULL){
		m_currentScopePointer = m_baseScope->m_currentScopePointer->m_parentScope;
		return m_baseScope->m_currentScopePointer;
	}

	return NULL;
}

/*void CScopeInfo::generateScopeListRecursive(CScopeInfo * scope, vector<CScopeInfo *> & lstScope){

	lstScope.push_back(scope);

	vector<CScopeInfo *> * scope_list = scope->getScopeList();
	for(unsigned i = 0; i < scope_list->size(); i++){
		generateScopeListRecursive(scope_list->at(i), lstScope);
	}

}

void CScopeInfo::generateScopeList(vector<CScopeInfo *> & lstScope){

	//return &m_baseScope->m_scopeList;

	generateScopeListRecursive(m_baseScope,lstScope);
}*/

int          CScopeInfo::getIndex(){
	return m_index;
}

vector<CScopeInfo *> * CScopeInfo::getScopeList(){

	return &m_scopeList;
}

vector<CScopeInfo *> * CScopeInfo::getVecIndexScopeNode(){

	return vec_index_scope_node;
}

vector<tInfoScopeVar *> * CScopeInfo::getRegisteredVariableList(){
	return &m_registeredVariable;
}

vector<tInfoScopeVar *> * CScopeInfo::getRegisteredSymbolsList(){
	return &m_baseScope->m_registeredVariable;
}

void CScopeInfo::destroySingletons(){
	if(vec_index_scope_node != NULL){
		delete vec_index_scope_node;
		delete vec_index_registered_var;
	}
}
/*
//-----------------------------------------------------------------------------------------------------------
int CScopeInfo::getScopeIndex(){

	return m_index;
	//int index=0;
	//return CScopeInfo::getScopeIndexRecursive(scope_to_find->getBaseScope(),scope_to_find, index);
}*/
//-----------------------------------------------------------------------------------------------------------
/*int CScopeInfo::getScopeIndexRecursive(CScopeInfo * current_scope, CScopeInfo * scope_to_find, int & _index){

	int r=0;
	if(current_scope == scope_to_find){
		return _index;
	}
	vector<CScopeInfo *> * scope_list = current_scope->getScopeList();

	for(unsigned i = 0; i < scope_list->size(); i++){
		_index++;
		if((r=getScopeIndexRecursive(scope_list->at(i), scope_to_find,_index))!=-1){
			return r;
		}

	}

	return -1;
}*/

//-----------------------------------------------------------------------------------------------------------
//
// SCOPE VARIABLE MANAGEMENT
//
tInfoScopeVar * CScopeInfo::registerAnonymouseFunction(PASTNode ast){ // register anonymous function in the top of scope ...

	tInfoScopeVar * irv = new tInfoScopeVar;


	string var_name = "_afun_"+CStringUtils::intToString(n_anonymouse_func++);
	string symbol_ref = "_"+var_name;


	irv->symbol_ref = symbol_ref;
	irv->name=var_name;
	irv->idxAstNode=-1;
	if(ast != NULL){
		irv->idxAstNode=ast->idxAstNode;
	}
	m_baseScope->m_registeredVariable.push_back(irv);

	return irv;
}

int CScopeInfo::registerSymbol(const string & var_name, PASTNode ast){
	int idxAstNode=-1;// * irv;


	if((idxAstNode = existRegisteredSymbol(var_name))==-1){ // check whether is local var registered scope ...

		string symbol_ref = var_name;
		symbol_ref = "_"+symbol_ref;
		tInfoScopeVar * irv = new tInfoScopeVar;
		//irv->m_obj=NULL;

		irv->symbol_ref = symbol_ref;
		irv->name=var_name;
		irv->idxAstNode=-1;
		if(ast != NULL){
			irv->idxAstNode=ast->idxAstNode;
		}
		m_registeredVariable.push_back(irv);
		return irv->idxInfoScopeVar;
	}else{

		int m_line=-1;
		if(ast != NULL) {
			m_line = ast->line_value;

		}

		if(idxAstNode != -1) { // if not null is defined in script scope, else is C++ var
			print_error_cr("(line %i): error var \"%s\" already registered at line %i!", m_line,var_name.c_str(), AST_LINE_VALUE(idxAstNode));
		}else{
			print_error_cr("(line %i): error var \"%s\" already registered as C++!", m_line,var_name.c_str());
		}
	}
	return -1;
}

int CScopeInfo::existRegisteredSymbol(const string & var_name){

	string symbol_ref = var_name;
	symbol_ref = "_"+symbol_ref;

	for(unsigned i = 0; i < m_registeredVariable.size(); i++){
		if(m_registeredVariable[i]->symbol_ref==symbol_ref){
			return m_registeredVariable[i]->idxInfoScopeVar;
		}
	}

	CScopeInfo * parent =  getParent();
	if(parent != NULL){
		return parent->existRegisteredSymbol(var_name);
	}

	return -1;

}


int CScopeInfo::getInfoRegisteredSymbol(const string & var_name, bool print_msg){
	int idxInfoScopeVar=-1;// * irv;

	if((idxInfoScopeVar = existRegisteredSymbol(var_name))!=-1){ // check whether is local var registered scope ...

		return idxInfoScopeVar;
	}else{
		if(print_msg){
			print_error_cr("var \"%s\" doesn't exist!", var_name.c_str());
		}
	}
	return -1;
}

void CScopeInfo::deleteScopeRecursive(CScopeInfo *scope_info){

	for(unsigned i = 0; i < scope_info->getRegisteredVariableList()->size(); i++){
		delete scope_info->getRegisteredVariableList()->at(i);
	}


	for(unsigned i = 0; i < scope_info->getScopeList()->size(); i++){

		deleteScopeRecursive(scope_info->getScopeList()->at(i));
		delete scope_info->getScopeList()->at(i);
	}

}

void CScopeInfo::destroyScopes(){
	deleteScopeRecursive(this);
}

//-----------------------------------------------------------------------------------------------------------
CScopeInfo::~CScopeInfo(){

	//deleteScope(this);
	/*for(unsigned i = 0; i < m_scopeList.size(); i++){
		delete m_scopeList[i];
	}*/

}