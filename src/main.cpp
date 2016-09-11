#include "core/zg_core.h"
#include "SDL2/SDL.h"

class CCustomObject{
	int x;
public:
	CCustomObject(){
		printf("CCustomObject constructing point @%p\n", this);
	}
	void member(){

		printf("hola %p!\n",this);
	}

	void member2(int i1){}

	   virtual ~CCustomObject()
	   {
	       printf("CCustomObject @%p destroyed\n", this);
	   }
};




int pass_string ( int s_int){

	string s = *((string *)&s_int);
	print_info_cr("HHHHHH: %s", s.c_str());


	s=STR(hola);

	print_info_cr("HHHHHH2: %s", s.c_str());

}

bool isprime(int n)
{
  for (int i = 2; i < n; ++i)
  {
    if ((n % i) == 0) {return false;}
  }

  return true;
}


int primes(int n)
{
  int count = 0;
  for (int i = 2; i <= n; ++i)
  {
    if (isprime(i)) {++count;}
  }

  return count;
}








void print1(string s){
	print_info_cr(s.c_str());
}

bool print2(float *f){
	string hola;

	printf("holaaaa: %f",*f);
	//print_info_cr(s.c_str());
	return false;
}

void print3(string * s){
	print_info_cr(s->c_str());
}

/*
void call_print_1p(CVariable *obj){

	fntConversionType fun=getConversionType(obj->getPointerClassStr(),CZG_ScriptCore::primitiveType[CZG_ScriptCore::FLOAT_PTR_TYPE].type_str);

	if(fun != NULL){
		// Normalize argument ...
		int arg1 = fun(obj);
		float arg2=1.2f;
		int result;

		asm(
					"push %[p1]\n\t"
					"push %%esp\n\t"
					"call *%P0\n\t" // call function
					"add $8,%%esp"       // Clean up the stack.
					: "=a" (result) // The result code intgers and pointers from eax.
					: "r"(print2),[p1] "r"(arg2));

		//float h = (float)result;

		print_info_cr("hh:%i",result);


	}


}*/


int main(int argc, char * argv[]){

	CLog::setUseAnsiEscape(true);
	CZG_ScriptCore *zg_script = CZG_ScriptCore::getInstance();

	/*void * c_fun1 = (void *)& CCustomObject::member;
	int c_func = (int)c_fun1;
	CCustomObject obj;
	int ptr_arg = (int )&obj;
	printf("hola %p\n",ptr_arg);*/
	//((int (*)(int))c_fun)(ptr_arg);
	//((int (*)(int))c_func)(ptr_arg);



	//string s = "hola!";
	//int s_int= *((int *)& s);



/*


	CString *s=NEW_STRING();
	s->m_value="hola2";


	call_print_1p(s);

*/



	/*map<string, fntConversionType> typeConversion;

	typeConversion[typeid(float ).name()]=[] (CVariable *obj){return (int)((CNumber *)obj)->m_value;};
	typeConversion[typeid(string).name()]=[] (CVariable *obj){obj->toString();return *((int *)&obj->m_strValue);};

	// ... add more conversion file ...
	mapTypeConversion[typeid(CNumber *).name()]=typeConversion;


	for(map<string,map<string,fntConversionType>>::iterator i = mapTypeConversion.begin(); i!=mapTypeConversion.end(); i++){
		print_info_cr("type: %s has %i conversion functions",i->first.c_str(),i->second.size());
		for(map<string, fntConversionType>::iterator j =i->second.begin() ; j != i->second.end();j++){
			print_info_cr("type conversion \"%s\"", j->first.c_str());
		}
	}


	// try converstion ...
	CNumber n;
	n.m_value=2;

	int jj= mapTypeConversion["P7CNumber"]["Ss"](&n);
	int ff2= mapTypeConversion["P7CNumber"]["f"](&n);

	//string sl = *((string *)&jj);

	print_info_cr("caca1 %s",((string *)&jj)->c_str());
	print_info_cr("caca2 %f",((float)ff2));*/




	/*int j =0;

	++j=0;

	pass_string(s_int);
	int yy[] = {0,1,2,3,4};
*/
	auto vv=[](int i){return i;};

	vv(0);

	// addConverstionFunction(lamba)

	//--yy[0]+yy[0]++;










	printf("%s\n",(char *) typeid(CString *).name());
	printf("%s\n",(char *) typeid(string *).name());


	//int i=1+0==1?2:3*2+10 ? 0 : 1;

	//i=+--i;

	//++i=0;

	CLog::setUseAnsiEscape(true);

	//printf("\nvar %i\n\n",i);

	print_info_cr("sizeof(CVariable)=%i sizeof(float)=%i sizeof(string)=%i",sizeof(CVariable),sizeof(float),sizeof(string));



	if(argc < 2){
		printf("Put file to evaluate.\n");
		printf("\n");
		printf("Example:\n");
		printf("\n");
		printf("file.zs");
		printf("\n");
		printf("\n");
		return 0;
	}
	ByteBuffer *buffer = CIO_Utils::readFile(argv[1]);

	if(buffer != NULL){



			if(zg_script->eval((char *)buffer->data_buffer)){


				//zg_script->execute();
				//for(i=0; i < 20;i++)
				{
					Uint32 t = SDL_GetTicks();
					//zg_script->execute();
					print_info_cr("time:%i",SDL_GetTicks()-t);


					//t = SDL_GetTicks();
					/*time_t start = time(NULL);

					float m=0;

					//primes(1000000000);
					for(int j = 0; j < 1000000;j++){
						for(int kk = 0; kk < 1000000;kk++){
							for(int tt = 0; tt < 1000000;tt++){
								for(int gg = 0; gg < 100000;gg++){
									m=(j/(kk+1))*tt%(gg+1);
								}
							}
						}

					}
				//	for(int j=0; j < 10000000; ++j){j*2;}

					print_info_cr("time2:%i %f",time(NULL)-start,m);*/
				}
			}

		print_info_cr("sizeobject:%i",sizeof(CVariable));
		print_info_cr("sizenumber:%i",sizeof(CNumber));

		print_info_cr("float:%s",typeid(float).name());
		print_info_cr("string:%s",typeid(string).name());
		print_info_cr("bool:%s",typeid(bool).name());


		CZG_ScriptCore::destroy();
		delete buffer;
	}

#if defined(__DEBUG__) && defined(__MEMMANAGER__)
  MEM_ViewStatus();
#endif

	return 0;
}
