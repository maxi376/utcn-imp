expresii regulate


E->E'|' T|T
T->TF | F
F->P | P*
P->e | (E)

->

E->T '|' E | T
T->FT | F
F->P | P*
P->e | (E)

(a | bb) * ba  


typedef truct _no{
	char cheie;
	srtuct _nod *st,dr;
}




AST(abstract synthax tree)


nod *E(){
	nod *rez;
	nod *t=T();
	if(symbol=='i'){
		next_symbol();
		
		rez=(nod*)malloc(sizeof(nod));
		
		rez->cheie='|';
		rez->st=t;
		rez->dr=E();
		return rez;
	}	else	
		return t;
}

%%
[a-z]

yyval=*yytext;



return LETTER;

%%
