
#define NEW_STRUCT (new CStruct()) //CScriptClassFactory::getInstance()->getRegisteredClassByIdx(CScriptClassFactory::getInstance()->getIdxClassStruct())))

class CStruct:public CScriptVariable{

public:
	CStruct();

	virtual bool unrefSharedPtr();
	virtual bool refSharedPtr();


};
