#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
/*
数组name长度不定，等于叶子的个数（即count数组中非零元素的个数），
name[j]存放的是第j个叶子对应的 数值（0-255之间），就是要被编码的符号
函数返回哈夫曼树叶子的个数 
*/ 
int readw(FILE* fp,int* name,int *count)//首次读取文件,统计字符出现次数作为权重
{
	fseek(fp,0,0);//重定位文件指针，把文件指针赋值为0，从文件开头开始
	memset(count,0,sizeof(int)*256); //对count数组中的元素清零，并重新分配地址
    int c ;
	while((c=fgetc(fp))!=-1)//读取文件指针指向的元素，并返回值 
       ++count[c];
	int i,j=0;
	for(i=0;i<256;i++)
        if(count[i]) 
 		  name[j++]=i;	 	
	return j;
}
/*哈夫曼树的结点，只不过name用了short，各种指针也是short存下标，-1表示空指针*/ 
typedef struct  
{
	short parent,lchild,rchild;	// 双亲、左右孩子的下标
	short name;	// 预编码的字节值
	int weight;	// 出现频率
}HNode,*HuffmanTree;
/*
创建哈夫曼树，name和w两个数组相当于结点的数据域，name长度是n，w长度是256，但w中只有
n个非零元素，所以得 w[name[i]]找一下，另外，要这里的指针全是下标，-1表示空指针。 
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
		ht[i].weight=ht[ht[i].lchild].weight+ht[ht[i].rchild].weight;//构造父母节点
		ht[i].parent=-1;
	}
	return ht+2*n-2;	
} 
/*
根据哈夫曼树使用先序遍历创建字典，字典长度为256的字符串
执行完毕后 ,如果Dict[i][0]==0,则原始文件中没有i，否则 Dict[i]中存的01组成的字符串
就是整数i对应的哈夫曼编码 
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
/*写压缩文件的头，前两个字节存len即叶子的个数（编码的个数），再1字节存0，将来要改成余数*/ 
void WriteHead(FILE*wfp,HNode* t,short len)
{
	int i;
	fwrite(&len,sizeof(short),1,wfp);//写文件，存储地址为&len，存储字节为1
	fputc(0,wfp);//wfp默认为标准输出流，返回字符本身
	for(i=0;i<len;++i)
	{
	    fwrite(&t[i].name,sizeof(short),1,wfp);
	    fwrite(&t[i].parent,sizeof(short),1,wfp);
	    fwrite(&t[i].lchild,sizeof(short),1,wfp);
	    fwrite(&t[i].rchild,sizeof(short),1,wfp);
    }
}
/*
第二次读源文件，根据字典逐字节转换为哈夫曼编码，凑齐一个（4字节），就写文件
，最后，余下的几位也要凑齐4字节写入，但要把余数写到之前留的那个字节中 
*/ 
void WriteBody(FILE*wfp,FILE* rfp,char Dict[ ][256])
{
	fseek(rfp,0,0);//重定位文件指针，把文件指针赋值为0，从文件开头开始
	int c;
	short i=0;//定义short类型
	unsigned tmp=0;//定义无符号型
	while((c=fgetc(rfp))!=-1)//读取文件指针指向的元素，并返回值
	{
		char* s=Dict[c];
		while(*s)//当Dict[]中有数据时，进行循环
		{
			if(*s=='1') tmp|=1<<i;//按位”或“运算后赋值
			++i;
			++s;
			if(i==32)
			{	
				i=0;
				fwrite(&tmp,sizeof(tmp),1,wfp);//文件读取，每个数据项大小为tmp,读取数据项为1,读取成功后返回到rfp
				tmp=0;
			}
		}
				
	}
	if(i)
	{
		fwrite(&tmp,sizeof(tmp),1,wfp);
		fseek(wfp,2,0); //把文件指针偏移到2位置，从文件开头开始
		fputc(i,wfp);//将字符i写入到wfp中
	}
}
/*
压缩文件的函数，就是调用上面的那些函数 
*/ 
void encode(const char* sfilename,const char* dfilename)//一个是压缩前文件名，一个是压缩后文件名
{
	FILE* rfp=fopen(sfilename,"rb+");//文件读取
	int name[256];
	int w[256];
	int i,j=readw(rfp,name,w);
	
	HNode* HT=(HNode*)malloc(sizeof(HNode)*(2*j-1));
	Create_Huffman(name,w,j,HT); 
	char Dict[256][256]={0};//初始化字典
	
	Create_Dict(HT,2*j-2,0,'0',Dict); 
	for(i=0;i<j;i++)
	   printf("%d %d %s\n",HT[i].name,HT[i].weight,Dict[HT[i].name]);
	FILE* wfp=fopen(dfilename,"wb");//压缩后的文件
	WriteHead(wfp,HT,2*j-1);//写入文件头
	WriteBody( wfp,rfp,Dict);//写入文件
	free(HT);//释放树的空间
	fclose(wfp);//释放文件指针
	fclose(rfp);
}
/*
解压缩函数， 到195行是读头，以便恢复哈夫曼树，
195行后，读哈夫曼编码，每次读4字节，根据哈夫曼树解码，解码每个字节写入还原文件 
*/  
void decode(const char* sfilename,const char* dfilename)
{
	FILE* rfp;
	rfp=fopen(sfilename,"rb+");//文件读取方式为：二进制打开文件，允许读取
	fseek(rfp,0,2);//重定位文件指针，把文件指针偏移到0位置，从文件结尾开始
	int filelen=ftell(rfp); //获取文件指针位置偏移量
	fseek(rfp,0,0);//初始化文件指针
	short len;
	fread(&len,sizeof(len),1,rfp);//文件读取，每个数据项大小为len,读取数据项为1，读取成功后返回到rfp
	filelen-=3+len*8;	
	int rest=fgetc(rfp),i;//指定读取rfp中的字符
	HNode* HT=(HNode*)malloc(sizeof(HNode)*len);
	for(i=0;i<len;++i)
	{
		fread(&HT[i].name,sizeof(len),1,rfp);
		fread(&HT[i].parent,sizeof(len),1,rfp);
		fread(&HT[i].lchild,sizeof(len),1,rfp);
		fread(&HT[i].rchild,sizeof(len),1,rfp);
	}
	unsigned tmp; //定义字节tmp
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
					fputc(HT[cur].name,wfp);//指定读取name中的字符
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