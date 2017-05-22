/* 
* @Author: Xiaokang Yin
* @Date:   2017-05-21 22:03:36
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-05-22 19:52:03
*/

#include <stdio.h>
//#include "readELF.h"
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
           "  -v : Displaye the version number of readELF"
        );
    printf("or\n\n");
    printf("Usage: ./%s<elf file>\n\n", software_name);
    printf("then after the 'cmd>' come\n", );
    printf("you can input the command:\n"
    	   "  H : show the usage information\n\n"
           "  h : display the header information\n\n"
           "  a : display all the information\n\n"
           "  s : display the section information\n\n"
           "  v : Displaye the version number of readELF"
           "  e : exit the command shell"
    	);

}
void show_header(FILE *elf)
{
	u_char ei_indent[EI_NIDENT];
	int i;
	printf("ELF Header:\n");
	printf(" 	Magic: 	");
	for (i = 0; i < EI_NIDENT; ++i)
	{
		printf("%x ",ei_indent[i]);
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

void read_elf(FILE *elf)
{

}
int main(int argc, char *argv[]) 
{
	char *option;
	char cmd;
	FILE *elf;
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
		else
		{
			if(elf = fopen(argv[1], "wb") == NULL)
			{
				printf("Open error\n");
				printf("FIle %s cannot be opened\n", argv[1]);
				exit();
			}
			printf("cmd> ");
			scanf("%c",cmd);
			while(cmd != 'e')
			{
				switch(cmd)
				{
					case 'H':
						show_usage();
						break;
					case 'h':
						show_header();
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
			}
			fclose(elf);
			return 0;

		}
		
	}
	option = argv[1];
	if(elf = fopen(argv[1], "wb") == NULL)
	{
		printf("Open error\n");
		printf("FIle %s cannot be opened\n", argv[1]);
		exit();
	}
	switch(option[1])
	{
		case 'H':
			show_usage();
			break;
		case 'h':
			show_header();
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
