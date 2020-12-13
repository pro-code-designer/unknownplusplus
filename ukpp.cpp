#include<iostream>
#include<fstream>
#include <stdlib.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------------------------------------------------------
#define AZAD 0 
#define NEWVAR 1 		//New varieble
#define VAR 2 			//Old varieble
#define DELIM 3
#define NUM 4			//Number
#define PRINT 5
#define GET 6
#define IF 7
#define WHILE 8
#define ERROR 9
#define FINISH 10
#define STRING 11
#define CHAR 12
#define EQ 13			//  =
#define FL 14			//  ^
#define PO 15			//  (
#define PC 16			//  )
#define DD 17			//  "
#define OD 18			//  '
#define PE 19			//  %
#define AN 20			//  ,
//--------------------------------------------------------------------------------------------------------------------------------------------------
// all var we have

class vari
{
	public:
	string name="";
	int nvar=0;
	double vvar;
	vari *next;
}firstv,*lastv,*nextv;

//--------------------------------------------------------------------------------------------------------------------------------------------------
//Open code

char code[100]="D:\\unknownpp\\code.dat";

//--------------------------------------------------------------------------------------------------------------------------------------------------
//global var

char ch,tok,toksym,tokerr;
int varcode=0;
string token; 
ifstream fpc;
bool bsym=0,berr=0;

//--------------------------------------------------------------------------------------------------------------------------------------------------
bool iswhite(char c);
bool isnvar();
bool isvar();
bool issymb(char s);
char getToken(bool w);
void makevar();
void valuevar();
int getvalue();
int putout();
void lvl1();
void error(int e);
int main()
{
	lastv=&firstv;
	fpc.open(code);
	while(!fpc.eof())
	{

		tok=getToken(0);
		cout<<token;
		switch(tok)
		{
			case NEWVAR: 
				cout<<" new";
				tok=getToken(0);
				if(tok==AZAD)
				{
					makevar();
					tok=getToken(0);
					//if(tok==EQ)
					
					if(tok!=FL)
						error(5);
				}	
				else
					error(12);
			 break;
			case VAR:
				cout<<" var"; 
			 break;
			case PRINT:error(putout()); cout<<" print"; 
			 break;
			case GET:error(getvalue()); cout<<" get";
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

bool issymb(char s)
{
	if(s=='\"')
		toksym=DD;
	else if(s=='\'')
		toksym=OD;
	else if(s==',')
		toksym=AN;
	else if(s=='\%')
		toksym=PE;
	else if(s=='(')
		toksym=PO;
	else if(s==')')
		toksym=PC;
	else if(s=='^')
		toksym=FL;
	else if(s=='=')
		toksym=EQ;
	else
		return 0;
	return 1;
}


char getToken(bool w)
{
	tokerr=tok;
	if(berr)
	{
		berr=0;
		return tokerr;
	}
	if(bsym)
	{
		bsym=0;
		return toksym;
	}
	tok=AZAD;
	token="";	
	while(!fpc.eof())
	{
		fpc.get(ch);
		if(!iswhite(ch)||w)
		{
			token+=ch;
			break;
		}
		
	}
	if (issymb(ch))
		return toksym;
	while(!fpc.eof())
	{
		fpc.get(ch);
		if (issymb(ch))
		{
			bsym=1;
			break;
		}
		if(iswhite(ch)&&!w)
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
int getvalue()
{
	tok=getToken(0);
	if(tok==PO)
	{
		tok=getToken(0);
		if(tok==DD)
		{
			tok=getToken(0);
			if(tok==PE)
			{
				tok=getToken(0);
				if(token=="d")
				{
					tok=getToken(0);
					if(tok==DD)
					{
						tok=getToken(0);
						if(tok==AN)
						{
							tok=getToken(0);
							if(tok==VAR)
							{
								if(nextv->nvar==1)
								{
									tok=getToken(0);
									if(tok==PC)
									{
										tok=getToken(0);
										if(tok==FL)
										{
											cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<"get int : ";
											int te;
											cin>>te;
											nextv->vvar=te;
										}
										else 
											return 1;
									}
									else
										return 2;
								}
								else
									return 9;
							}
							else
								return 3;
						}
						else
							return 4;	
					}
					else
						return 5;	
				}
				else if(token=="f")
				{
					tok=getToken(0);
					if(tok==DD)
					{
						tok=getToken(0);
						if(tok==AN)
						{
							tok=getToken(0);
							if(tok==VAR)
							{
								if(nextv->nvar==2)
								{
									tok=getToken(0);
									if(tok==PC)
									{
										tok=getToken(0);
										if(tok==FL)
										{
											cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<"get float : ";
											double te;
											cin>>te;
											nextv->vvar=te;
										}
										else 
											return 1;
									}
									else
										return 2;
								}
								else
									return 10;
							}
							else
								return 3;
						}
						else
							return 4;	
					}
					else
						return 5;
				}
				else if(token=="c")
				{
					tok=getToken(0);
					if(tok==DD)
					{
						tok=getToken(0);
						if(tok==AN)
						{
							tok=getToken(0);
							if(tok==VAR)
							{
								if(nextv->nvar==3)
								{
									tok=getToken(0);
									if(tok==PC)
									{
										tok=getToken(0);
										if(tok==FL)
										{
											cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<"get char : ";
											char te;
											cin>>te;
											nextv->vvar=te;
										}
										else 
											return 1;
									}
									else
										return 2;
								}
								else 
									return 11;
							}
							else
								return 3;
						}
						else
							return 4;	
					}
					else
						return 5;
				}
				else
					return 6;	
			}
			else
				return 7;
		}
		else
			return 5;
	}
	else 
		return 8;
	return 0;
}
int putout()
{
	tok=getToken(0);
	if(tok==PO)
	{
		tok=getToken(0);
		if(tok==DD)
		{
			tok=getToken(0);
			if(tok==PE)
			{
				tok=getToken(0);
				if(token=="d")
				{
					tok=getToken(0);
					if(tok==DD)
					{
						tok=getToken(0);
						if(tok==AN)
						{
							tok=getToken(0);
							if(tok==VAR)
							{
								if(nextv->nvar==1)
								{
									tok=getToken(0);
									if(tok==PC)
									{
										tok=getToken(0);
										if(tok==FL)
										{
											int te;
											te=nextv->vvar;
											cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<te<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x";
										}
										else 
											return 1;
									}
									else
										return 2;
								}
								else
									return 9;
							}
							else
								return 3;
						}
						else
							return 4;	
					}
					else
						return 5;	
				}
				else if(token=="f")
				{
					tok=getToken(0);
					if(tok==DD)
					{
						tok=getToken(0);
						if(tok==AN)
						{
							tok=getToken(0);
							if(tok==VAR)
							{
								if(nextv->nvar==2)
								{
									tok=getToken(0);
									if(tok==PC)
									{
										tok=getToken(0);
										if(tok==FL)
										{
											double te;
											te=nextv->vvar;
											cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<te<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x";
										}
										else 
											return 1;
									}
									else
										return 2;
								}
								else
									return 10;
							}
							else
								return 3;
						}
						else
							return 4;	
					}
					else
						return 5;
				}
				else if(token=="c")
				{
					tok=getToken(0);
					if(tok==DD)
					{
						tok=getToken(0);
						if(tok==AN)
						{
							tok=getToken(0);
							if(tok==VAR)
							{
								if(nextv->nvar==3)
								{
									tok=getToken(0);
									if(tok==PC)
									{
										tok=getToken(0);
										if(tok==FL)
										{
											char te;
											te=nextv->vvar;
											cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<te<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x";
										}
										else 
											return 1;
									}
									else
										return 2;
								}
								else 
									return 11;
							}
							else
								return 3;
						}
						else
							return 4;	
					}
					else
						return 5;
				}
				else
					return 6;	
			}
			else
			{
				string schap=token;
				tok=getToken(1);
				if(tok!=DD)
					schap+=" ";
				while(tok!=DD)
				{
					if(fpc.eof())
						return 5;
					schap+=token;
					tok=getToken(1);
				}
				tok=getToken(0);
				if(tok==PC)
				{
					tok=getToken(0);
					if(tok==FL)
					{
						cout<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<schap<<endl<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x";
					}
					else 
						return 1;
				}
				else
					return 2;
			}
			
		}
		else
			return 5;
	}
	else 
		return 8;
	return 0;
}
void error(int e)
{
	switch(e)
	{
		case 1:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (^) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 2:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find ()) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 3:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (name of var) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 4:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (,) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 5:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (\") -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 6:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (type of var) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 7:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (\%) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 8:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (() -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 9:
			cout<<endl<<" -/-/-/-/-/-/-/- this var is not sahih -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 10:
			cout<<endl<<" -/-/-/-/-/-/-/- this var is not ashari -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 11:
			cout<<endl<<" -/-/-/-/-/-/-/- this var is not char -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
		case 12:
			cout<<endl<<" -/-/-/-/-/-/-/- you made this var later -\\-\\-\\-\\-\\-\\-\\- ";berr=1;
		 break;
	}
}
