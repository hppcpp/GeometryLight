/**/
#include<stdio.h>
#include<stdlib.h>

#ifndef CAP_file_h
#define CAP_file_h
char* CAP_readFile(const char* const);
int CAP_appendFile(const char* const,const char* const);
int CAP_writeFile(const char* const,const char* const);
#endif

#ifdef CAP_file
char* CAP_readFile(const char* const path)
{
	char *fileStr=0;
	int lth=0;
	FILE *fp=0;
	
	if(path==0){return 0;}
	
	fopen_s(&fp,path,"rb");
	if(fp==0){return 0;}
	
	fseek(fp,0,SEEK_END);
	lth=ftell(fp);
	fileStr=(char*)malloc((lth+1)*sizeof(char));
	if(fileStr==0){return 0;}
	
	fseek(fp,0,SEEK_SET);
	fread(fileStr,sizeof(char),lth,fp);
	fileStr[lth]='\0';
	
	fclose(fp);
	return fileStr;
}

int CAP_appendFile(const char* const path,const char* const fileStr)
{
	FILE *fp=0;
	
	if(path==0 || fileStr==0){return 1;}
	
	fopen_s(&fp,path,"ab");
	if(fp==0){return 1;}
	
	fprintf(fp,"%s", fileStr);
	
	fclose(fp);
	return 0;
}

int CAP_writeFile(const char* const path,const char* const fileStr)
{
	FILE *fp=0;
	
	if(path==0 || fileStr==0){return 1;}
	
	fopen_s(&fp,path,"wb");
	if(fp==0){return 1;}
	
	fprintf(fp,"%s", fileStr);
	
	fclose(fp);
	return 0;
}
#endif
