#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
/*
����name���Ȳ���������Ҷ�ӵĸ�������count�����з���Ԫ�صĸ�������
name[j]��ŵ��ǵ�j��Ҷ�Ӷ�Ӧ�� ��ֵ��0-255֮�䣩������Ҫ������ķ���
�������ع�������Ҷ�ӵĸ��� 
*/ 
int readw(FILE* fp,int* name,int *count)//�״ζ�ȡ�ļ�,ͳ���ַ����ִ�����ΪȨ��
{
	fseek(fp,0,0);//�ض�λ�ļ�ָ�룬���ļ�ָ�븳ֵΪ0�����ļ���ͷ��ʼ
	memset(count,0,sizeof(int)*256); //��count�����е�Ԫ�����㣬�����·����ַ
    int c ;
	while((c=fgetc(fp))!=-1)//��ȡ�ļ�ָ��ָ���Ԫ�أ�������ֵ 
       ++count[c];
	int i,j=0;
	for(i=0;i<256;i++)
        if(count[i]) 
 		  name[j++]=i;	 	
	return j;
}
/*���������Ľ�㣬ֻ����name����short������ָ��Ҳ��short���±꣬-1��ʾ��ָ��*/ 
typedef struct  
{
	short parent,lchild,rchild;	// ˫�ס����Һ��ӵ��±�
	short name;	// Ԥ������ֽ�ֵ
	int weight;	// ����Ƶ��
}HNode,*HuffmanTree;
/*
��������������name��w���������൱�ڽ���������name������n��w������256����w��ֻ��
n������Ԫ�أ����Ե� w[name[i]]��һ�£����⣬Ҫ�����ָ��ȫ���±꣬-1��ʾ��ָ�롣 
*/
HuffmanTree Create_Huffman(int* name,int* w,int n,HNode* ht)
{
 	int i;
	for(i=0; i<n; ++i)
	{
		ht[i].name=name[i];
		ht[i].weight=w[name[i]]; 
		ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
	}
	for(; i<2*n-1; ++i)
	{
		int j,min=-1;
		for(j=0; j<i; ++j)
			if((ht[j].parent==-1)&&(min==-1||ht[j].weight<ht[min].weight))
				min=j;
		ht[min].parent=i;
		ht[i].lchild=min;
		for(j=0,min=-1; j<i; ++j)
			if((ht[j].parent==-1)&&(min==-1||ht[j].weight<ht[min].weight))
				min=j;
		ht[min].parent=i;
		ht[i].rchild=min;
		ht[i].weight=ht[ht[i].lchild].weight+ht[ht[i].rchild].weight;//���츸ĸ�ڵ�
		ht[i].parent=-1;
	}
	return ht+2*n-2;	
} 
/*
���ݹ�������ʹ��������������ֵ䣬�ֵ䳤��Ϊ256���ַ���
ִ����Ϻ� ,���Dict[i][0]==0,��ԭʼ�ļ���û��i������ Dict[i]�д��01��ɵ��ַ���
��������i��Ӧ�Ĺ��������� 
*/ 
void Create_Dict(HuffmanTree HT,int root,int level,char code,char Dict[][256])
{    
    static char str[256];
	if(root!=-1)
	{   
		if(level)
			str[level]=code;
		if( (HT+root)->lchild==-1)
		{
			int i=(HT+root)->name;
			str[level+1]='\0';
			strcpy(Dict[i],str+1);
		}
		Create_Dict(HT,(HT+root)->lchild,level+1,'0',Dict);
		Create_Dict(HT,(HT+root)->rchild,level+1,'1',Dict);
	}
}
/*дѹ���ļ���ͷ��ǰ�����ֽڴ�len��Ҷ�ӵĸ���������ĸ���������1�ֽڴ�0������Ҫ�ĳ�����*/ 
void WriteHead(FILE*wfp,HNode* t,short len)
{
	int i;
	fwrite(&len,sizeof(short),1,wfp);//д�ļ����洢��ַΪ&len���洢�ֽ�Ϊ1
	fputc(0,wfp);//wfpĬ��Ϊ��׼������������ַ�����
	for(i=0;i<len;++i)
	{
	    fwrite(&t[i].name,sizeof(short),1,wfp);
	    fwrite(&t[i].parent,sizeof(short),1,wfp);
	    fwrite(&t[i].lchild,sizeof(short),1,wfp);
	    fwrite(&t[i].rchild,sizeof(short),1,wfp);
    }
}
/*
�ڶ��ζ�Դ�ļ��������ֵ����ֽ�ת��Ϊ���������룬����һ����4�ֽڣ�����д�ļ�
��������µļ�λҲҪ����4�ֽ�д�룬��Ҫ������д��֮ǰ�����Ǹ��ֽ��� 
*/ 
void WriteBody(FILE*wfp,FILE* rfp,char Dict[ ][256])
{
	fseek(rfp,0,0);//�ض�λ�ļ�ָ�룬���ļ�ָ�븳ֵΪ0�����ļ���ͷ��ʼ
	int c;
	short i=0;//����short����
	unsigned tmp=0;//�����޷�����
	while((c=fgetc(rfp))!=-1)//��ȡ�ļ�ָ��ָ���Ԫ�أ�������ֵ
	{
		char* s=Dict[c];
		while(*s)//��Dict[]��������ʱ������ѭ��
		{
			if(*s=='1') tmp|=1<<i;//��λ���������ֵ
			++i;
			++s;
			if(i==32)
			{	
				i=0;
				fwrite(&tmp,sizeof(tmp),1,wfp);//�ļ���ȡ��ÿ���������СΪtmp,��ȡ������Ϊ1,��ȡ�ɹ��󷵻ص�rfp
				tmp=0;
			}
		}
				
	}
	if(i)
	{
		fwrite(&tmp,sizeof(tmp),1,wfp);
		fseek(wfp,2,0); //���ļ�ָ��ƫ�Ƶ�2λ�ã����ļ���ͷ��ʼ
		fputc(i,wfp);//���ַ�iд�뵽wfp��
	}
}
/*
ѹ���ļ��ĺ��������ǵ����������Щ���� 
*/ 
void encode(const char* sfilename,const char* dfilename)//һ����ѹ��ǰ�ļ�����һ����ѹ�����ļ���
{
	FILE* rfp=fopen(sfilename,"rb+");//�ļ���ȡ
	int name[256];
	int w[256];
	int i,j=readw(rfp,name,w);
	
	HNode* HT=(HNode*)malloc(sizeof(HNode)*(2*j-1));
	Create_Huffman(name,w,j,HT); 
	char Dict[256][256]={0};//��ʼ���ֵ�
	
	Create_Dict(HT,2*j-2,0,'0',Dict); 
	for(i=0;i<j;i++)
	   printf("%d %d %s\n",HT[i].name,HT[i].weight,Dict[HT[i].name]);
	FILE* wfp=fopen(dfilename,"wb");//ѹ������ļ�
	WriteHead(wfp,HT,2*j-1);//д���ļ�ͷ
	WriteBody( wfp,rfp,Dict);//д���ļ�
	free(HT);//�ͷ����Ŀռ�
	fclose(wfp);//�ͷ��ļ�ָ��
	fclose(rfp);
}
/*
��ѹ�������� ��195���Ƕ�ͷ���Ա�ָ�����������
195�к󣬶����������룬ÿ�ζ�4�ֽڣ����ݹ����������룬����ÿ���ֽ�д�뻹ԭ�ļ� 
*/  
void decode(const char* sfilename,const char* dfilename)
{
	FILE* rfp;
	rfp=fopen(sfilename,"rb+");//�ļ���ȡ��ʽΪ�������ƴ��ļ��������ȡ
	fseek(rfp,0,2);//�ض�λ�ļ�ָ�룬���ļ�ָ��ƫ�Ƶ�0λ�ã����ļ���β��ʼ
	int filelen=ftell(rfp); //��ȡ�ļ�ָ��λ��ƫ����
	fseek(rfp,0,0);//��ʼ���ļ�ָ��
	short len;
	fread(&len,sizeof(len),1,rfp);//�ļ���ȡ��ÿ���������СΪlen,��ȡ������Ϊ1����ȡ�ɹ��󷵻ص�rfp
	filelen-=3+len*8;	
	int rest=fgetc(rfp),i;//ָ����ȡrfp�е��ַ�
	HNode* HT=(HNode*)malloc(sizeof(HNode)*len);
	for(i=0;i<len;++i)
	{
		fread(&HT[i].name,sizeof(len),1,rfp);
		fread(&HT[i].parent,sizeof(len),1,rfp);
		fread(&HT[i].lchild,sizeof(len),1,rfp);
		fread(&HT[i].rchild,sizeof(len),1,rfp);
	}
	unsigned tmp; //�����ֽ�tmp
 	FILE* wfp=fopen(dfilename,"wb");
 	int cur=len-1;
    for(i=0;i<filelen;i+=4)
 	{
 		fread(&tmp,sizeof(tmp),1,rfp);
 		int j;
 		if(i<filelen-4) 
 		 	for(j=0;j<32;++j)
 		 	{
 		 		cur=tmp&(1<<j)?HT[cur].rchild:HT[cur].lchild;
 		 		if(HT[cur].lchild==-1)
				{
					fputc(HT[cur].name,wfp);//ָ����ȡname�е��ַ�
					cur=len-1;
				}
			}
	 	else
	 		for(j=0;j<rest;++j)
 		 	{
 		 		cur=tmp&(1<<j)?HT[cur].rchild:HT[cur].lchild;
 		 		if(HT[cur].lchild==-1)
				{
					fputc(HT[cur].name,wfp);					
					cur=len-1;
				}
			}
 	}

	fclose(wfp);
	free(HT);
	fclose(rfp);
}
int main()
{
	//encode("E:\\text.txt","E:\\text_Huffman.txt");
	decode("E:\\text_Huffman.txt","E:\\text_decode.txt");
	
}