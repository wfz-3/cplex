#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define MAX_E 99999
#define MAX_V 10000


int v_num;
int e_num;
int array[MAX_V][MAX_V];
int v_weight[MAX_V];



void build_instance(ifstream& infile){
     
     int i,j,v1,v2;
     int temp;
     string str1;
     string str2;
     string str3;
     
     e_num = 0;
     infile>>str1;
     infile>>str2;
     infile>>v_num;
     infile>>e_num;
     printf("%d  %d\n",v_num,e_num);
     infile>>str3;
     
     for(i=1;i<=v_num;i++){
     	for(j=1;j<=v_num;j++){
     		array[i][j]=0;
     	}
     }
     cout<<"v_num:"<<v_num<<endl;
     
     while(infile>>v1>>v2){
     	
		array[v1][v2]=1;
		infile>>str3;
     }
    
}

int main()
{
     
    FILE * in = fopen("wvcdata.txt","r");
    //FILE * out = fopen("nvc_10_10_01","w");
    
    char filename[100];
   	while(fgets(filename,100,in)){
      
         
        int i,j,l=strlen(filename);
        filename[l-1]='\0';
       
		printf("%s\n",filename);
        ifstream infile(filename);
       
        if(infile==NULL){
			printf("%s can't open\n",filename);
			break;
		}    
       
        build_instance(infile);
        
        char str[100] = "n";
        strcat(str,filename);
        cout<<str<<endl;
        FILE * out = fopen(str,"w");
        fprintf(out,"V_num = %d;\n",v_num);
        fprintf(out,"Edges = {\n");
        for(i=1;i<=v_num;i++)
        {
            for(j=i;j<=v_num;j++)
            {
                if(array[i][j]==1)  
                    fprintf(out,"<%d,%d>,\n",i,j);                 
            } 
            
        }   //fprintf(out,"\n"); 
        fprintf(out,"};\n");          
          
        fclose(out);
        
    }   
    
    fclose(in);  
    system("pause");
    return 0;    
}

