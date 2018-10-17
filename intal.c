#include "intal.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
	short int* point;
	short int num;
}al;

void* intal_create(const char* str)
{
	al* temp;
	temp=(al*)malloc(sizeof(al));
	if(str[0]-48>9||str[0]-48<0)
	{
		temp->num=1;
		temp->point=(short int*)malloc(sizeof(short int)*temp->num);
		temp->point[0]=0;
		return temp;
	}
	temp->num=strlen(str);
	int i=0;
	while(str[i]==48&&temp->num>1)
	{
		temp->num--;
		i++;
	}
	temp->point=(short int*)malloc(sizeof(short int)*temp->num);
	int j;
	for(j=temp->num-1;j>=0;j--)
	{
		if(str[temp->num-j-1+i]-48>9||str[temp->num-j-1+i]-48<0)
			return NULL;
		temp->point[j]=str[temp->num-j-1+i]-48;
	}
	return temp;
}

char* intal2str(void* intal)
{
	if(intal==NULL)
		return "NaN";
	al* temp=intal;
	while(temp->point[temp->num-1]==0&&temp->num>1)
		temp->num--;
	char* a=(char*)malloc(sizeof(char)*(temp->num+1));
	int j;
	for(j=0;j<temp->num;j++)
	{
		a[temp->num-j-1]=temp->point[j]+48;
	}
	a[j]=0;
	return a;
}

void intal_destroy(void* intal)
{
	if(intal==NULL)
		return ;
	al* temp=intal;
	free(temp->point);
	free(temp);
}

void* intal_increment(void* intal)
{
	if(intal==NULL)
		return NULL;
	al* temp=intal;
	int i=0;
	if(temp->point[0]!=9)
		temp->point[0]++;
	else
	{	
		temp->point[i]++;
		while((temp->point[i]==10)&&i<temp->num)
		{
			temp->point[i]=0;
			temp->point[i+1]++;
			i++;
		}
		if(i==temp->num)
		{
			temp->point=(short int*)realloc(temp->point,sizeof(short int)*(temp->num+1));
			temp->point[temp->num]=1;
			temp->num++;
		}
	}
	return temp;
}

void* intal_decrement(void* intal)
{
	if(intal==NULL)
		return NULL;
	al* temp=intal;
	int i=0;
	if(temp->point[0]!=0)
		temp->point[0]--;
	else if(temp->num!=1)
	{	
		temp->point[i]--;
		while((temp->point[i]==-1)&&i<temp->num)
		{
			temp->point[i]=9;
			temp->point[i+1]--;
			i++;
		}
		if(temp->point[temp->num-1]==0)
		{
			temp->point=(short int*)realloc(temp->point,sizeof(short int)*(temp->num-1));
			temp->num--;
		}
	}
	return temp;
}

void* intal_add(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return NULL;
	al* max=(intal_compare(intal1, intal2) > 0)?intal1:intal2;
	al* min=(intal_compare(intal1, intal2) > 0)?intal2:intal1;
	al* temp=intal_create("0");
	int len=max->num;
	temp->point=(short int*)realloc(temp->point,sizeof(short int)*(len+1));
	int i=0;
	int sum;
	while(i<(min->num))
	{
		sum=(temp->point[i]+max->point[i]+min->point[i]);
		temp->point[i]=sum%10;
		temp->point[i+1]=sum/10;
		i++;
	}
	while(i<(max->num))
	{
		sum=(temp->point[i]+max->point[i]);
		temp->point[i]=sum%10;
		temp->point[i+1]=sum/10;
		i++;
	}
	temp->num=(temp->point[len]==0)?len:len+1;
	return temp;
}

int intal_compare(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return -2;
	if((((al*)intal1)->num)>(((al*)intal2)->num))
		return 1;
	if((((al*)intal1)->num)<(((al*)intal2)->num))
		return -1;
	int j;
	for(j=(((al*)intal1)->num)-1;j>=0;j--)
	{
		if((((al*)intal1)->point[j])>(((al*)intal2)->point[j]))
			return +1;
		if((((al*)intal1)->point[j])<(((al*)intal2)->point[j]))
			return -1;
	}
	return 0;
}

void* intal_diff(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return NULL;
	al* max=(intal_compare(intal1, intal2) > 0)?intal1:intal2;
	al* min=(intal_compare(intal1, intal2) > 0)?intal2:intal1;
	al* temp=intal_create("0");
	int len=max->num;
	temp->point=(short int*)realloc(temp->point,sizeof(short int)*(len+1));
	int carry=0;
	int sub;
	int i;
	for(i=0;i<(min->num);i++)
	{
		sub=(max->point[i])-(min->point[i])-carry;
		if(sub<0)
		{
			sub+=10;
			carry=1;
		}
		else carry=0;
		temp->point[i]=sub;
	}
	for(i=(min->num);i<(max->num);i++)
	{
		sub=(max->point[i])-carry;
		if(sub<0)
		{
			sub+=10;
			carry=1;
		}
		else carry=0;
		temp->point[i]=sub;
	}
	temp->num=len;
	return temp;
} 

static int EqualLen(void* intal1, void* intal2)
{
	al* in1=intal1;
	al* in2=intal2;
	int len1=in1->num;
	int len2=in2->num;
	if (len1<len2)
	{
		in1->point=(short int*)realloc(in1->point,sizeof(short int)*(len2));
		for(int i=0;i<(len2-len1);i++)
		{
			in1->point[i+len1]=0;
		}
		return len2;
	}
	else if (len1>len2)
	{
		in2->point=(short int*)realloc(in2->point,sizeof(short int)*(len1));
		for(int i=0;i<(len1-len2);i++)
		{
			in2->point[i+len2]=0;
		}
	}
	return len1;
}
			
void* intal_multiply(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return NULL;
	al* in1=intal1;
	al* in2=intal2;
	int len1=in1->num;
	int len2=in2->num;
	int len=EqualLen(intal1, intal2);
	if((in1->point[0]==0&&in1->num==1)||(in2->point[0]==0&&in2->num==1)||len==0)
	{
		al* temp=intal_create("0");
		return temp;
	}	
	if(len==1)
	{
		int mul=in1->point[0]*in2->point[0];
		char a[3];
		snprintf(a,3,"%d",mul);
		al* temp=intal_create(a);
		return temp;
	} 
	int fh=len/2;
	int sh=(len-fh);
	in1->num=sh;
	char *a=intal2str(in1);
	al* Xr=intal_create(a);
	free(a);
	in1->num=len1;
	in2->num=sh;
	char *b=intal2str(in2);
	al* Yr=intal_create(b);
	free(b);
	in2->num=len2;
	al* Xl=intal_create("0");
	Xl->point=(short int*)realloc(Xl->point,sizeof(short int)*(fh));
	Xl->num=fh;
	int i;
	for(i=0;i<fh;i++)
	{
		Xl->point[i]=in1->point[i+sh];
	}
	al* Yl=intal_create("0");
	Yl->point=(short int*)realloc(Yl->point,sizeof(short int)*(fh));
	Yl->num=fh;
	for(i=0;i<fh;i++)
	{
		Yl->point[i]=in2->point[i+sh];
	}
	al* P1=intal_multiply(Xl,Yl);
	al* P2=intal_multiply(Xr,Yr);
	al* s1=intal_add(Xl,Xr);
	al* s2=intal_add(Yl,Yr);
	al* P3=intal_multiply(s1,s2);
	intal_destroy(s1);
	intal_destroy(s2);
	while(P1->point[P1->num-1]==0&&P1->num>1)
		P1->num--;
	while(P2->point[P2->num-1]==0&&P2->num>1)
		P2->num--;
	while(P3->point[P3->num-1]==0&&P3->num>1)
		P3->num--;
	al* P4=intal_diff(P3,P2);
	while(P4->point[P4->num-1]==0&&P4->num>1)
		P4->num--;
	al* P5=intal_diff(P4,P1);
	while(P5->point[P5->num-1]==0&&P5->num>1)
		P5->num--;
	if(len%2!=0)
	{
		len++;
		fh=len/2;
	}
	P1->point=(short int*)realloc(P1->point,sizeof(short int)*(P1->num+len));
	for(i=P1->num-1;i>=0;i--)
	{
		P1->point[i+len]=P1->point[i];
	}
	for(i=0;i<len;i++)
	{
		P1->point[i]=0;
	}
	P1->num+=len;
	P5->point=(short int*)realloc(P5->point,sizeof(short int)*(P5->num+fh));
	for(i=P5->num-1;i>=0;i--)
	{
		P5->point[i+fh]=P5->point[i];
	}
	for(i=0;i<fh;i++)
	{
		P5->point[i]=0;
	}
	P5->num+=fh;
	al* P6=intal_add(P5,P2);
	al* P7=intal_add(P6,P1);
	intal_destroy(Xl);
	intal_destroy(Xr);
	intal_destroy(Yl);
	intal_destroy(Yr);
	intal_destroy(P1);
	intal_destroy(P2);
	intal_destroy(P3);
	intal_destroy(P4);
	intal_destroy(P5);
	intal_destroy(P6);
	return P7;
}

void* intal_divide(void* intal1, void* intal2)
{
	al* in1=intal1;
	al* in2=intal2;
	if(intal1==NULL||intal2==NULL||in2->point[0]==0&&in2->num==1)
	{
		return NULL;
	}
	al* temp=intal_create("0");
	al* quotient=intal_create("0");
	if(intal_compare(intal1,intal2)==0)
	{
		quotient->point[0]=1;
		return quotient;
	}
	else if(intal_compare(intal1,intal2)==-1)
	{
		return quotient;
	}
	temp->point=(short int*)realloc(temp->point,sizeof(short int)*(in1->num));
	temp->num=1;
	temp->point[0]=in1->point[in1->num-1];
	int j=in1->num-2;
	int y=in1->num-1;
	quotient->point=(short int*)realloc(quotient->point,sizeof(short int)*(in1->num));
	quotient->num=0;
	while(intal_compare(temp,in2)==-1 &&j>0)
	{
		for(int i=temp->num-1;i>=0;i--)
			temp->point[i+1]=temp->point[i];
		temp->point[0]=in1->point[j--];
		temp->num++;
	}
	while(j>-1)
	{
		int k=0;
		if(intal_compare(temp,in2)==-1)
		{
			quotient->point[y--]=0;
			quotient->num++;
		}
		else
		{
			while(intal_compare(temp,in2)==1||intal_compare(temp,in2)==0)
			{
				k++;
				al* temp1;
				temp1=intal_diff(temp,in2);
				intal_destroy(temp);
				temp=temp1;
				while(temp->point[temp->num-1]==0&&temp->num>1)
					temp->num--;
			}
			quotient->point[y--]=k;
			quotient->num++;
		}
		for(int i=temp->num-1;i>=0;i--)
			temp->point[i+1]=temp->point[i];
		temp->point[0]=in1->point[j--];
		temp->num++;
		while(temp->point[temp->num-1]==0&&temp->num>1)
			temp->num--;
	}
	int k=0;
	while(intal_compare(temp, in2)==1 || intal_compare(temp, in2)==0)
	{
		k++;
		al* temp1;
		temp1=intal_diff(temp,in2);
		intal_destroy(temp);
		temp=temp1;
		while(temp->point[temp->num-1]==0&&temp->num>1)
			temp->num--;
	}
	quotient->point[y--]=k;
	quotient->num++;
	intal_destroy(temp);
	for(int i=0;i<quotient->num;i++)
		quotient->point[i]=quotient->point[in1->num-quotient->num+i];
	return quotient;
}

void* intal_pow(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return NULL;
	al* in1=intal1;
	al* in2=intal2;
	if((in1->point[0]==0&&in1->num==1))
	{
		al* temp3=intal_create("0");
		return temp3;
	}
	else if (in2->point[0]==0&&in2->num==1)
	{
		al* temp4=intal_create("1");
		return temp4;
	}	
	al* temp;
	al* temp1;
	al* temp2;
	al* test2=intal_create("2");
	al* fact=intal_divide(in2, test2);
	while(fact->point[fact->num-1]==0&&fact->num>1)
		fact->num--;
	intal_destroy(test2);
	temp=intal_pow(in1,fact);
	intal_destroy(fact);
	while(temp->point[temp->num-1]==0&&temp->num>1)
		temp->num--;
	temp1=intal_multiply(temp,temp);
	intal_destroy(temp);
	if(in2->point[0]%2==1)
	{
		temp2=intal_multiply(temp1,in1);
		intal_destroy(temp1);
		return temp2;
	}
	return temp1;
}