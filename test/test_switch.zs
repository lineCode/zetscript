function test_switch(a){
	
	
	
	switch(a){
	default:
		print("default ("+a+")");
		break;
	case 0:
	case 1:
	case 2:
		print("Multiple case 0,1 or 2");
		break;
	case 3:
		print("case three and");
		break;
	case 4:
		print("case four");
		break;
	}
	
}

test_switch(-1);
test_switch(0);
test_switch(3);
test_switch(4);

var s="hello";

switch(s){
default:
	print("default-string");
	break;
case "hello":
	print("hello1");
	break;
case "bye":
	print("bye1");
	break;
	
}



