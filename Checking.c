#include<stdio.h>
#include<string.h>
#include<conio.h>
int main()
{FILE *fpi;
char ch[10];
fpi=fopen("Input.txt","r");
FILE *fpo;
fpo=fopen("Output.txt","w+");
if(fpi==NULL)
return 0;
while(!feof(fpi))
{fscanf(fpi,"%s",ch);
fprintf(fpo,"%s",ch);
printf("%s\n",ch);
}
fclose(fpi);
fclose(fpo);
getche();

}
