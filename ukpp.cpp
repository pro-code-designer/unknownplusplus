#include<iostream>
#include<fstream>
#include <stdlib.h>
using namespace std;
#define AZAD 0
#define NEWVAR 1
#define VAR 2
#define DELIM 3
#define NUM 4
#define PRINT 5
#define GET 6
#define IF 7
#define WHILE 8
#define ERROR 9
#define FINISH 10
#define STRING 11
#define CHAR 12
#define EQ 13
#define FL 14 
#define PO 15 
#define PC 16
#define NOVAR 17
class vari
{
	public:
	string name="";
	int nvar=0;
	double vvar;
	vari *next;
}firstv,*lastv,*nextv;
char code[100]="D:\\unknownpp\\code.dat";
char ch,tok;
int varcode=0;
string token; 
ifstream fpc;
bool iswhite(char c);
bool isnvar();
bool isvar();
char getToken();
void makevar();
void valuevar();
void getvalue();
void lvl1();
int main()
{
	lastv=&firstv;
	fpc.open(code);
	while(!fpc.eof())
	{
		
		tok=getToken();
		cout<<token;
		switch(tok)
		{
			case NEWVAR: 
				cout<<" new";
				tok=getToken();
				if(tok==AZAD)
				{
					makevar();
					tok=getToken();
					//if(tok==EQ)
					
					if(tok!=FL)
						cout<< token<<" ridi5";
				}	
				else
					cout<<" ridi2";
			 break;
			case VAR:
				cout<<" var"; 
			 break;
			case PRINT: cout<<" print"; 
			 break;
			case GET:getvalue(); cout<<" get";
			 break;
			case IF: cout<<" if";
			 break;
			case WHILE:
				cout<<" while"; 
			 break;
			case ERROR: cout<<"ridi"<<endl; break;
			case FINISH: exit(0); 
			 break;
		}
			cout<<endl;
	}
	cout<<firstv.vvar;
}
bool iswhite(char c)
{
	if(c=='\0'||c=='\n'||c=='\t'||c==' ')
	{
		return 1;
	}
	return 0;
}
bool isnvar()
{
	if(token=="Sahih")
	{
		varcode=1;
		return 1;
	}
	else if(token=="Ashari")
	{
		varcode=2;
		return 1;
	}
	else if(token=="Harf")
	{
		varcode=3;
		return 1;
	}
	else 
		return 0;
}


bool isvar()
{
	
	nextv=&firstv;
	while (lastv!=nextv)
	{
		if(nextv->name==token)
		{
			return 1;
		}
		nextv=nextv->next;
	}
	return 0;
}


char getToken()
{
	tok=AZAD;
	token="";	
	while(!fpc.eof())
	{
		fpc.get(ch);
		if(!iswhite(ch))
		{
			token+=ch;
			break;
		}
		
	}
	if(token=="\""&&!fpc.eof())
	{
		while(ch!=','&&!fpc.eof()){
			fpc.get(ch);
			token+=ch;
		}
		return NOVAR;
	}
	if(token=="(")
		return PO;
	if(token==")")
		return PC;
	if(token=="^")
		return FL;
	if(token=="=")
		return EQ;
	while(!fpc.eof())
	{
		fpc.get(ch);
		if(iswhite(ch))
			break;
		token+=ch;
	}
	if(token=="agar")
		return IF;
	if(token=="ta")
		return WHILE;
	if(token=="Benevis")
		return PRINT;
	if(token=="Begir")
		return GET;
	if(isnvar())
		return NEWVAR;
	if(isvar())
		return VAR;
}
void makevar(){
cout<<sizeof(*lastv);
	lastv->name=token;
	lastv->nvar=varcode;
	lastv->next = new vari();
	nextv=lastv;
	lastv=lastv->next;
	cout<<" var "<<token<<endl;
}
void valuevar()
{
	
}
void getvalue()
{
	tok=getToken();
	if(tok==PO)
	{
		tok=getToken();
		if(tok==NOVAR)
		{
			if(token=="\"\%d\",")
			{
				
				tok=getToken();
				if(tok==VAR&&nextv->nvar==1)
				{
					cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<"get int : ";
					int te;
					cin>>te;
					nextv->vvar=te;
				}
				else
					cout<<token<<" ridi9 ";
			}
			else if(token=="\"\%f\",")
			{
				tok=getToken();
				if(tok==VAR&&nextv->nvar==2)
				{
					cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<"get float : ";
					double te;
					cin>>te;
					nextv->vvar=te;
				}
				else
					cout<<token<<" ridi9 ";
			}
			else if(token=="\"\%c\",")
			{
				tok=getToken();
				if(tok==VAR&&nextv->nvar==3)
				{
					cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<"get char : ";
					char te;
					cin>>te;
					nextv->vvar=te;
				}
				else
					cout<<token<<" ridi9 ";
			}
			else
				cout<<token<<" ridi8 ";
		}
		else
		cout<<" ridi7 ";
	}
	else 
		cout<<" ridi6 ";
}
