#pragma once


#define MAX_UNIQUE_OBJECTS_POINTERS 2048
#define MAX_STACK 256

class CSharedPointerManager{

	static CSharedPointerManager *sharedPointerManager;

	typedef struct{
		CScriptVariable *shared_ptr;
		int n_shares;
		int idx_0_shares;
	}tInfoSharedPointer;


	tInfoSharedPointer shared_pointer[MAX_STACK][MAX_UNIQUE_OBJECTS_POINTERS];
	int pointers_with_0_shares[MAX_STACK][MAX_UNIQUE_OBJECTS_POINTERS],
		n_pointers_with_0_shares[MAX_STACK];

	int indexFreeCell[MAX_STACK][MAX_UNIQUE_OBJECTS_POINTERS],
		n_freeCell[MAX_STACK];

	int idxCurrentStack;



	int getFreeCell();
	void setFreeCell(int index_to_free);


	int insert0Shares(int shared_pointer_idx);


	CSharedPointerManager();
public:
	static CSharedPointerManager * getInstance();
	static void destroySingletons();

	int newSharedPointer(CScriptVariable *var_ptr);
	void removeUnSharedPointers();
	void gc();
	int getIdx0Shares(int index);
	int getNumShares(int index);
	void remove0Shares(int index_0_share_idx);

	bool push(); // push current stack
	bool pop(); // pop stack.

	void sharePointer( int index);
	void unrefSharedPointer( int index);

};
