/* 
* @Author: Xiaokang Yin
* @Date:   2017-05-21 22:03:36
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-05-23 08:49:42
*/

#include <stdio.h>
#include "readELF.h"
#define MAX_LEN		60*1024*1024
const char software_name[] = "readELF";


u_char buf[MAX_LEN];

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
	printf("	Class: 				");
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
	printf("	Data				");
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
	printf("	Version				");
	switch(header->e_ident[EI_VERSION])
	{
		case EV_NONE:
			printf("Invalid\n", );
			break;
		case EV_CURRENT:
			printf("1 (current)\n", );
	}
	printf("	OS/ABI				");
	switch(header->e_ident[EI_OSABI])
	{
		case 0x00:
			printf("System V\n");
			break;
		case 0x01:
			printf("HP-UX\n");
			break;
		case 0x02:
			printf("NetBSD\n");
			break;
		case 0x03:
			printf("Linux\n");
			break;
		case 0x04:
			printf("GNU Hurd\n");
			break;
		case 0x06:
			printf("Solaris\n");
			break;
		case 0x07:
			printf("AIX\n");
			break;
		case 0x08:
			printf("IRIX\n");
			break;
		case 0x09:
			printf("FreeBSD\n");
			break;
		case 0x0A:
			printf("Tru64\n");
			break;
		case 0x0B:
			printf("Novell Modesto\n");
			break;
		case 0x0C:
			printf("Open BSD\n");
			break;
		case 0x0D:
			printf("OpenVMS\n");
			break;
		case 0x0E:
			printf("NonStop Kernel\n");
			break;
		case 0x0F:
			printf("AROS\n");
			break;
		case 0x10:
			printf("Fenix OS\n");
			break;
		case 0x11:
			printf("CloudABI\n");
			break;
		case 0x53:
			printf("Sortix\n");
			break;
		default:
			printf("Unknown\n");
			break;
	}
	printf("	Type				");
	switch(header->e_type)
	{
		case ET_NONE:
			printf("Invalid\n");
			break;
		case ET_REL:
			printf("Relocatable file\n");
			break;
		case ET_EXEC:
			printf("Executable file\n");
			break;
		case ET_DYN:
			printf("Shared object file\n");
			break;
		case ET_CORE:
			printf("Core file\n");
			break;
		case ET_LOPROC:
			printf("Processor-specific\n");
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
	//u_char buf[MAX_LEN];
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
