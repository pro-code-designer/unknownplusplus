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
#define IFSYMB 13
#define IFVAR 14
#define EQ 15			//  =
#define FL 16			//  ^
#define PO 17			//  (
#define PC 18			//  )
#define DD 19			//  "
#define OD 20			//  '
#define PE 21			//  %
#define AN 22			//  ,
#define AO 23			//  {
#define AC 24			//  }
#define FO 25			//  [
#define FC 26			//  ]
//--------------------------------------------------------------------------------------------------------------------------------------------------
// all var we have

class vari
{
	public:
	string name="";
	int nvar=0;
	double vvar;
	vari *next;
}firstv,*lastv,*nextv,check1,check2;

//--------------------------------------------------------------------------------------------------------------------------------------------------
//Open code

char code[1000]="D:\\unknownpp\\code.dat",t[100];

//--------------------------------------------------------------------------------------------------------------------------------------------------
//global var

char ch,tok,toksym,tokerr;
int varcode=0,ifcode=0,fcode=0,tellg,tellx=0,tells;
string token; 
ifstream fpc;
bool bsym=0,berr=0,bwhile=0;


//--------------------------------------------------------------------------------------------------------------------------------------------------
bool iswhite(char c);
bool isnvar();
bool isvar();
bool isif();
bool issymb(char s);
char getToken(bool w);
void makevar();
void valuevar();
int getvalue();
int putout();
int runif();
void runwhile();
void lvl1();
void error(int e);
void program();
int main()
{
	lastv=&firstv;
	fpc.open(code);
	while(!fpc.eof())
	{	
		fpc.getline(t,100);
		tellx++;
	}
	fpc.close();
	fpc.open(code);
	program();
	if(!fpc.eof())
	error(13);
}
void program()
{
	bool bpro=1;
	while(!fpc.eof()&&bpro)
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
			case IF:error(runif()); cout<<" if";
			 break;
			case WHILE: cout<<" while "<<tellx; tellg=fpc.tellg()-tellx;bwhile=1;runwhile();
			 break;
			case FC: bpro=0; 
			 break;
			case FINISH: exit(0); 
			 break;
			default :error(18);
			 break;
		}
			cout<<endl;
	}
}
bool iswhite(char c)
{
	if(c=='\0'||c=='\t'||c==' ')
	{
		return 1;
	}
	else if(c=='\n')
	{
		tellx--;
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
//NEW
bool isif()
{
	if(token=="&B")
	{
		ifcode=1;
		return 1;
	}
	else if(token=="&BM")
	{
		ifcode=2;
		return 1;
	}
	else if(token=="&MM")
	{
		ifcode=3;
		return 1;
	}
	else if(token=="&KM")
	{
		ifcode=4;
		return 1;
	}
	else if(token=="&K")
	{
		ifcode=5;
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
	else if(s=='[')
	{
		toksym=FO;
		fcode++;
	}
	else if(s==']')
	{
		toksym=FC;
		fcode--;
	}
	else if(s=='{')
		toksym=AO;
	else if(s=='}')
		toksym=AC;
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
	if(isif())
		return IFSYMB;
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
//--------------------------------------------------------------------------------------------------------------------------------------------------
int runif()
{
	int scode=fcode;
	tok=getToken(0);
	if(tok==AO)
	{
		
		tok=getToken(0);
		if(tok==VAR)
		{
			check1.vvar=nextv->vvar;
			tok=IFVAR;
		}
		else if(tok==DELIM)
		{
			tok=IFVAR;
		}
		if(tok==IFVAR)
		{
			tok=getToken(0);
			if(tok==IFSYMB)
			{
				tok=getToken(0);
				if(tok==VAR)
				{
					check2.vvar=nextv->vvar;
					tok=IFVAR;
				}
				else if(tok==DELIM)
				{
					tok=IFVAR;
				}
				if(tok==IFVAR)
				{
					tok=getToken(0);
					if(tok==AC)
					{
						if(ifcode==1)
						{	
							tok=getToken(0);
							if(tok==FO)
							{
								cout<<"************"<<check1.vvar<<"   "<<check2.vvar<<endl;	
								if(!(check1.vvar>check2.vvar))
								{
									bwhile=0;
									scode=fcode-1;
									tok=getToken(0);
									while(fcode>scode)
									{
										if(fpc.eof())
											return 13;
										tok=getToken(0);
									}
									return 0;
								}
								else if(fcode==scode+1)
								{
									program();
									return 0;
								}
								return 13;
							}
							else
								return 13;
						}
						else if(ifcode==2)
						{	
							tok=getToken(0);
							if(tok==FO)
							{
								if(!(check1.vvar>=check2.vvar))
								{
									bwhile=0;
									scode=fcode-1;
									tok=getToken(0);
									while(fcode>scode)
									{
										if(fpc.eof())
											return 13;
										tok=getToken(0);
									}
									return 0;
								}
								else if(fcode==scode+1)
								{
									program();
									return 0;
								}
								return 13;
							}
							else
								return 13;
						}
						else if(ifcode==3)
						{
							tok=getToken(0);
							if(tok==FO)
							{
								if(!(check1.vvar==check2.vvar))
								{
									bwhile=0;
									scode=fcode-1;
									tok=getToken(0);
									while(fcode>scode)
									{
										if(fpc.eof())
											return 13;
										tok=getToken(0);
									}
									return 0;
								}
								else if(fcode==scode+1)
								{
									program();
									return 0;
								}
								return 13;
							}
							else
								return 13;
						}
						else if(ifcode==4)
						{
							tok=getToken(0);
							if(tok==FO)
							{
								if(!(check1.vvar<=check2.vvar))
								{
									bwhile=0;
									scode=fcode-1;
									tok=getToken(0);
									while(fcode>scode)
									{
										if(fpc.eof())
											return 13;
										tok=getToken(0);
									}
									return 0;
								}
								else if(fcode==scode+1)
								{
									program();
									return 0;
								}
								return 13;
							}
							else
								return 13;
						}
						else if(ifcode==5)
						{
							tok=getToken(0);
							if(tok==FO)
							{
								if(!(check1.vvar<check2.vvar))
								{
									bwhile=0;
									scode=fcode;
									tok=getToken(0);
									while(fcode>scode)
									{
										if(fpc.eof())
											return 13;
										tok=getToken(0);
									}
									return 0;
								}
								else if(fcode==scode+1)
								{
									return 0;
								}
								return 13;
							}
							else
								return 13;
						}
					}
					else 
						return 15;
				}
				else
					return 16;
			}
			else
				return 17;
		}
		else
			return 16;	
	}
	else
		return 14;	
			
}
//----------------------------------------------------------------------------------------------------------------------------------------
void runwhile()
{
	tells=tellx;
	error(runif());
	if(bwhile)
	{
		fpc.seekg(tellg);
	//	tok=getToken(0);
	//	cout<<"----------h-gbsgs------"<<token<<endl;
	//	exit(0);
	tellx=tells;
		runwhile();
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------
void error(int e)
{
	switch(e)
	{
		case 1:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (^) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 2:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find ()) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 3:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (name of var) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 4:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (,) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 5:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (\") -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 6:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (type of var) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 7:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (\%) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 8:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (() -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 9:
			cout<<endl<<" -/-/-/-/-/-/-/- this var is not sahih -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 10:
			cout<<endl<<" -/-/-/-/-/-/-/- this var is not ashari -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 11:
			cout<<endl<<" -/-/-/-/-/-/-/- this var is not char -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		case 12:
			cout<<endl<<" -/-/-/-/-/-/-/- you made this var later -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
			break;
		case 13:
			cout<<endl<<" -/-/-/-/-/-/-/- we have problem with your (]) or ([) number -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		 case 14:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find ({) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		 case 15:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find (}) -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		 case 16:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find any type of var or delim -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
		 case 17:
			cout<<endl<<" -/-/-/-/-/-/-/- we dont find type of your condition -\\-\\-\\-\\-\\-\\-\\- ";berr=1;exit(0);
		 break;
	}
	
}


