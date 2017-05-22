/* 
* @Author: Xiaokang Yin
* @Date:   2017-05-21 22:03:36
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-05-22 21:51:38
*/

#include <stdio.h>
#include "readELF.h"
#define MAX_LEN		1024*1024
const char software_name[] = "readELF";

void show_usage();
void show_header();
void show_section();
void show_all();
void show_version();

void show_usage()
{
    printf("Usage: ./%s [options] <elf file>\n\n", software_name);

    printf("Available options:\n"
           "  -H : show the usage information\n\n"
           "  -h <elf file> : display the header information\n\n"
           "  -a <elf file> : display all the information\n\n"
           "  -s <elf file> : display the section information\n\n"
           "  -v : Displaye the version number of readELF\n\n"
        );
    printf("or\n\n");
    printf("Usage: ./%s<elf file>\n\n", software_name);
    printf("then after the 'cmd>' come\n");
    printf("you can input the command:\n"
    	   "  H : show the usage information\n\n"
           "  h : display the header information\n\n"
           "  a : display all the information\n\n"
           "  s : display the section information\n\n"
           "  v : Displaye the version number of readELF"
           "  q: quit the command shell\n\n"
    	);

}
void show_header(const u_char *data)
{
	elf32_Ehdr *header;
	int i;

	header = (elf32_Ehdr *)data;
	printf("ELF Header:\n");
	printf(" 	Magic: 	");
	for (i = 0; i < EI_NIDENT; ++i)
	{
		printf("%x ",header->e_ident[i]);
	}
	printf("\n");
	printf("	Type: 				");
	switch(header->e_ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			printf("Unknown file type\n");
			break;
		case ELFCLASS32:
			printf("ELF32\n");
			break;
		case ELFCLASS64:
			printf("ELF64\n");
			break;
	}
	printf("	data				");
	switch(header->e_ident[EI_DATA])
	{
		case ELFDATANONE:
			printf("Invalid\n");
			break;
		case ELFDATA2LSB:
			printf("2' implemntation, little endian\n");
			break;
		case ELFDATA2MSB:
			printf("Big endian\n");
			break;
	}
}

void show_section()
{
	printf("section:\n");
}

void show_all()
{
	printf("all:\n");
}

void show_version()
{
	printf("readELF 0.1.1, build time 2017.5.22\n");
	printf("Copyright (C) YinXiaokang\n");
}

void read_elf(const u_char *data)
{

}
int main(int argc, char *argv[]) 
{
	char *option;
	char cmd;
	u_char buf[MAX_LEN];
	int len = 0;
	FILE  *elf;
	if (argc == 1)
	{
		show_usage();
		return 0;
	}
	if(argc > 3) return -1;
	if (argc == 2) 
	{
		if(strcmp(argv[1],"-H") == 0)
		{
			show_usage();
			return 0;
		}
		if(strcmp(argv[1],"-v") == 0)
		{
			show_version();
			return 0;
		}
		else
		{	printf("argc =  %d\n", argc);
			printf("file name %s\n",argv[1]);
			elf = fopen(argv[1], "rb+") ;
			if(elf == NULL)
			{
				printf("Open error\n");
				printf("File %s cannot be opened\n", argv[1]);
				exit(-1);
			}
			len = fread(buf,1,MAX_LEN,elf);
			buf[len] = '\0';
			printf("cmd> ");
			scanf("%c",&cmd);
			while(cmd != 'q')
			{
				switch(cmd)
				{
					case 'H':
						show_usage();
						break;
					case 'h':
						show_header(buf);
						break;
					case 's':
						show_section();
						break;
					case 'a':
						show_all();
						break;
					case 'v':
						show_version();
						break;
					default:
						break;
				}
				printf("cmd> ");
				scanf("%c",&cmd);
				scanf("%c",&cmd);
			}
			fclose(elf);
			return 0;

		}
		
	}
	option = argv[1];
	elf = fopen(argv[2], "rb+") ;
	if(elf == NULL)
	{
		printf("Open error\n");
		printf("FIle %s cannot be opened\n", argv[2]);
		exit(-1);
	}
	len = fread(buf,1,MAX_LEN,elf);
	buf[len] = '\0';
	switch(option[1])
	{
		case 'H':
			show_usage();
			break;
		case 'h':
			show_header(buf);
			break;
		case 's':
			show_section();
			break;
		case 'a':
			show_all();
			break;
		case 'v':
			show_version();
			break;
		default:
			break;
	}
	fclose(elf);
    return 0;
}
