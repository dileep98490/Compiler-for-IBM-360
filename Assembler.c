#include<stdio.h>
#include<string.h>
#include<conio.h>
int BR,IR;//Initialisation of Base register and index register
int LC;//Initialisation of location counter
char label[9],op[6],operand[20];

struct MOT
{char mnemonicop[4];
char binaryop[2];
int format;
};//Structure for Machine Operation Table(MOT)
struct ST
{char symbol[9];
int LCvalue;
char value[5];
int length;
};//Structure for Symbol Table(ST)
struct ST s;
int Potoutput()//To print output for only some POTs
{FILE *fpo;
fpo=fopen("Output.txt","a"); //To print output files

    fprintf(fpo,"%d\t",LC);
           //Printing the values for checking
           fprintf(fpo,"%s\t%s\n",s.value,"_");
           fclose(fpo);
}
//POTSearch

int Potsearch()
{
    
    FILE *fps;
char c[5];//Character string to hold the substrings so that they can be converted to ints for future
int i,sizes,k;//K is some extra variable to be used when ever needed

fps=fopen("ST.DIL","rb+");
if(fps==NULL)
fps=fopen("ST.DIL","wb+");
fseek(fps,0,SEEK_END);
sizes=sizeof(s);
s.length=0;

   if(strcmp(op,"START")==0)
                {strcpy(s.symbol,label);
                s.LCvalue=0;//It's LC value to be used in pass-2
                s.value[0]='_';
                s.length=0;//Length to incrment location counter
                fwrite(&s,sizes,1,fps);//To store in ST(table)
                }
                
   else if(strcmp(op,"DS")==0)
                {strcpy(s.symbol,label);
                s.LCvalue=LC;
                s.value[0]='-';
                i=0;//For Character string initialisation 
                if(strcmp(operand,"F")==0)//ASCII value for F
                s.length=4;
                           else
                {while(operand[i]!='F')
                c[i++]=operand[i];
                if(i!=4)
                c[i]='\0';
                s.length=atoi(c);
                        s.length=4*s.length;        //Convert string C to int here and assign it to s.length
                }
                fwrite(&s,sizes,1,fps);
                Potoutput();
                }
            
   else if(strcmp(op,"DC")==0)
                {strcpy(s.symbol,label);
                s.LCvalue=LC;
                //Limitation is we are accepting only F'' or C'' and only one character or int in between those double quotes
                i=0;

          
                while((operand[i]!='F') && (operand[i]!='C'))
                               i++;
                k=i;

    while(operand[i+2]!=39)
                {s.value[i]=operand[i+2];
                i++;}
                
                s.value[i]='\0';
                 if(operand[k]=='F')
                s.length=4;
                else
                s.length=1;
               fwrite(&s,sizes,1,fps);
                     Potoutput();

                }
  else if(strcmp(op,"EQU")==0)
                {strcpy(s.symbol,label);
            strcpy(s.value,operand);
                s.LCvalue=5000;
                s.length=0;
                fwrite(&s,sizes,1,fps);
                }
  else if(strcmp(op,"END")==0)
                {strcpy(s.symbol,label);
                s.value[0]='\0';
                s.LCvalue=0;
                s.length=0;
                fwrite(&s,sizes,1,fps);//WRITE here the code needed to go to pass-2
                }
                
  else if(strcmp(op,"USING")==0)
               {
                       i=0;
                               while(operand[i+2]!='\0')
                c[i++]=operand[i+2];
                c[i]='\0';
               BR=atoi(c);
                
                }
  else if(strcmp(op,"DROP")==0)
               {
                     
              BR=1;
   
              }
           fclose(fps);
          

    
            //Incrementing the location counter
           LC=LC+s.length;
             

    
}

//MOTSearch


int Motsearch()
{int LCC;
LCC=LC;

    FILE *fpo;
fpo=fopen("Output.txt","a"); //To print output files

    FILE *fpm;

struct MOT m;

FILE *fps;
struct ST s;
if(strcmp(operand,"LOOP")==0)
{fps=fopen("ST.DIL","wb");
strcpy(s.symbol,operand);
s.LCvalue=LC;
s.value[0]='\0';
s.length=0;
fwrite(&s,sizeof(s),1,fps);
close(fps);
}
if(strcmp(op,"SLDL")==0|| strcmp(op,"SRDL")==0 || strcmp(op,"BALR")==0 || strcmp(op,"BCTR")==0)
{if(strcmp(op,"SLDL")==0 || strcmp(op,"SRDL")==0)
{
               strcpy(m.mnemonicop,op);
LC=LC+4;}
else
{strcpy(m.mnemonicop,op);
LC=LC+2;
}

}
  else
  {            
fpm=fopen("MOT.DIL","rb");
while(fread(&m,sizeof(m),1,fpm)==1)
if(strcmp(op,m.mnemonicop)==0)
break;
fclose(fpm);

switch(m.format)
{case 0:LC=LC+2;break;
case 1||2||3:LC=LC+4;break;
case 4:LC=LC+6;
                break;
                }
}
fprintf(fpo,"%d\t",LCC);
fprintf(fpo,"%s\t%s\n",m.mnemonicop,operand);

fclose(fpo);
    
}

//Pass_1



int Pass_1()
{
    if(strcmp(op,"START")==0 || strcmp(op,"DC")==0 || strcmp(op,"DS")==0 ||strcmp(op,"EQU")==0 || strcmp(op,"END")==0 ||strcmp(op,"USING")==0 ||strcmp(op,"DROP")==0)
Potsearch();
else
Motsearch();
    
}



//Pass-2



int Pass_2()
{int k;//for second string
int i;//for first string
FILE *fps,*fpo2;
char temp[4];
struct ST s;
fps=fopen("ST.DIL","rb");
fpo2=fopen("Output2.txt","a");
if(fpo2==NULL)
printf("There is a problem\n");
if(strcmp(operand,"_")!=0)
{
    char c1[10],c2[10];//Two strings c1 and c2 to hold the strings before and after ',', so that they can be replaced with appropriate values from symbol table
i=0;

while(operand[i]!=44)
    c1[i++]=operand[i];
    c1[i]='\0';
    k=0;
    i++;
    while(operand[i]!='\0')
    {c2[k++]=operand[i];i++;}
    c2[k]='\0';

    while(fread(&s,sizeof(s),1,fps)==1)
    {
                                       if(strcmp(s.symbol,c1)==0)
    {if(s.LCvalue!=5000)
    {   itoa(s.LCvalue,temp,10);
                        strcpy(c1,strcat(temp,"("));
    itoa(IR,temp,10);
    strcpy(c1,strcat(c1,temp));
      strcpy(c1,strcat(c1,","));
     itoa(BR,temp,10);
      strcpy(c1,strcat(c1,temp));
        strcpy(c1,strcat(c1,")"));}
        else
        strcpy(c1,s.value);                  
                               }
                               if(strcmp(s.symbol,c2)==0)
    {if(s.LCvalue!=5000)
    {itoa(s.LCvalue,temp,10);
                        strcpy(c2,strcat(temp,"("));
    itoa(IR,temp,10);
    strcpy(c2,strcat(c2,temp));
      strcpy(c2,strcat(c2,","));
     itoa(BR,temp,10);
      strcpy(c2,strcat(c2,temp));
        strcpy(c2,strcat(c2,")"));}
        else
        strcpy(c2,s.value);                  
                               }
                                       
                                       }
                                      
                                                                              strcpy(operand,strcat(c1,","));
                                        strcpy(operand,strcat(operand,c2));
                                        }
                                        fprintf(fpo2,"%d\t%s\t%s\n",LC,op,operand);
                                        fclose(fpo2);
    return 0;
}


//MAIN


int main()
{int count=0;
    FILE *fpi,*fpi2,*fpo,*fpo2,*fp;
    fp=fopen("ST.DIL","wb+");
    fpo2=fopen("Output2.txt","w+");
    fpo=fopen("Output.txt","w+"); 
    fclose(fpo);
    fclose(fpo2);
fclose(fp);
fpi=fopen("Input.txt","r");

    IR=0;
BR=1;
LC=0;
//printf("Enter the three strings\n");
//scanf("%s%s%s",label,op,operand);
while(!feof(fpi))
{
fscanf(fpi,"%s",label);
fscanf(fpi,"%s",op);
fscanf(fpi,"%s",operand);
Pass_1();
count++;

}
fclose(fpi);
//fpimod=fopen("Output.txt","a");
//fprintf(fpimod,"%s","EOF");
//fclose(fpimod);
getche();
fpi2=fopen("Output.txt","r");


while(count!=2)
{
fscanf(fpi2,"%d",&LC);
fscanf(fpi2,"%s",op);
fscanf(fpi2,"%s",operand);

Pass_2();
count--;

}
fclose(fpi2);
//printf("Enter the three strings\n");
//scanf("%s%s",op,operand);
//strcpy(op,"A");
//strcpy(operand,"3,DATA");
//Pass_2();


getche();
}


