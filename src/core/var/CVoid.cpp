#include "../../CZetScript.h"


CVoid::CVoid(){//tInfoScriptClass *info_registered_class):CScriptVariable(info_registered_class, this){
	this->init(CScriptClass::getInstance()->getRegisteredClassVoid(), (void *)this);
}