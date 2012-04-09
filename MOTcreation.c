#include<stdio.h>
#include<string.h>
#include<conio.h>
struct MOT
{char mnemonicop[4];
char binaryop[2];
int format;
};

int main()
{int size,n,l;
char temp[8];
struct MOT m;


    FILE *fp;
  
    fp=fopen("MOT.DIL","rb+");
    if(fp==NULL)
    fp=fopen("MOT.DIL","wb+");
    if(fp==NULL)
    {printf("\nCannot open the file");
    return 0;
    

}
size=sizeof(m);
while(1)
{printf("\nEnter what u want to do\n1.Insert\t2.Display\t3.Modify\t4.Exit:");
scanf("%d",&n);
if(n==4)
{break;
fclose(fp);}
switch(n)
{
         case 1:l=1;
         while(l==1)
         {printf("\nEnter the Mnemonic opcode, Binary Opcode and Instruction format\n");
         scanf("%s%s%d",m.mnemonicop,m.binaryop,&m.format);
         fseek(fp,0,SEEK_END);
         fwrite(&m,size,1,fp);l=2;
         printf("\nAnother\t1.Yes:");
              scanf("%d",&l);
              }
              break;
         case 2:
              rewind(fp);
                
              while(fread(&m,size,1,fp)==1)
              printf("\n%s\t%s\t%d",m.mnemonicop,m.binaryop,m.format);
             
     
              break;
         case 3:l=1;
         while(l==1)
         {
              rewind(fp);
              printf("\nEnter the mnemonic op, you want to modify:");
              scanf("%s",temp);
                  while(fread(&m,size,1,fp)==1)
                  {if(strcmp(temp,m.mnemonicop)==0)
                  {fseek(fp,-size,SEEK_CUR);
                  printf("\nEnter the new mnemonic opcode, binary opcode and instruction format\n");
                  scanf("%s%s%d",m.mnemonicop,m.binaryop,&m.format);
      
                  fwrite(&m,size,1,fp);
                  break;
                  }
                  }
                  l=2;
         printf("\nAnother\t1.Yes:");
              scanf("%d",&l);
              
              }   
              break;
          default:break;
          }
          } 
 
          return 0;
          }
              
              
              
