%{
#define LETTER 257
extern char yylval;
%}

%%

[a-z]	{
		yylval = *yytext;
		return LETTER;
	    }
[|()*\n]	return *yytext;
