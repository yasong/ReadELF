/* 
* @Author: Xiaokang Yin
* @Date:   2017-05-21 22:03:36
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-05-26 07:59:59
*/

#include <stdio.h>
#include <string.h>
#include "readELF.h"
#define MAX_LEN		60*1024*1024
const char software_name[] = "readELF";


u_char buf[MAX_LEN];

void show_usage();
void show_header(const u_char *data);
void show_program_header(const u_char *data);
void show_section_header(const u_char *data);
void show_section_name(const u_char *data);
void show_all(const u_char *data);
void show_version();

void show_usage()
{
	printf("Usage: ./%s [options] <elf file>\n\n", software_name);

	printf("Available options:\n"
		   "  -H : show the usage information\n\n"
		   "  -h <elf file> : display the header information\n\n"
		   "  -a <elf file> : display all the information\n\n"
		   "  -S <elf file> : display the section  header information\n\n"
		   "  -s <elf file>  : display symbol table\n\n"
		   "  -v : Displaye the version number of readELF\n\n"
		);
	printf("or\n\n");
	printf("Usage: ./%s<elf file>\n\n", software_name);
	printf("then after the 'cmd>' come\n");
	printf("you can input the command:\n"
		   "  H : show the usage information\n\n"
		   "  h : display the header information\n\n"
		   "  a : display all the information\n\n"
		   "  S : display the section  header information\n\n"
		   "  s : display symbol table\n\n"
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
	printf("\tMagic: \t");
	for (i = 0; i < EI_NIDENT; ++i)
	{
		printf("%x ",header->e_ident[i]);
	}
	printf("\n");
	printf("\tClass:\t\t\t\t");
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
	printf("\tData:\t\t\t\t");
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
	printf("\tVersion:\t\t\t");
	switch(header->e_ident[EI_VERSION])
	{
		case EV_NONE:
			printf("Invalid\n");
			break;
		case EV_CURRENT:
			printf("1 (current)\n");
	}
	printf("\tOS/ABI:\t\t\t\t");
	switch(header->e_ident[EI_OSABI])
	{
		case 0x00:
			printf("UNIX System V \n");
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
	printf("\tType:\t\t\t\t");
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
	printf("\tSystem Architecture:\t\t");
	switch(header->e_machine)
	{
		case EM_NONE:
			printf("Invalid\n");
			break;
		case EM_M32:
			printf("AT&T WE  32100\n");
			break;
		case EM_SPARC:
			printf("SPARC\n");
			break;
		case EM_386:
			printf("Intel 80386\n");
			break;
		case EM_68K:
			printf("Motorola 68000\n");
			break;
		case EM_88K:
			printf("Motorola 88000\n");
			break;
		case EM_860:
			printf("Intel 80860\n");
			break;
		case EM_MIPS:
			printf("MIPS RS3000\n");
		default:
			printf("Unknown\n");
	}
	printf("\tVersion:\t\t\t");
	switch(header->e_version)
	{
		case EV_NONE:
			printf("0x00\n");
			break;
		case EV_CURRENT:
			printf("0x01\n");
			break;
		default:
			printf("Unknown\n");
	}
	printf("\tEntry:\t\t\t\t0x%x\n", header->e_entry);
	printf("\tProgram Header:\t\t\t%d (bytes into file)\n", header->e_phoff);
	printf("\tsection Header:\t\t\t%d (bytes into file)\n", header->e_shoff);
	printf("\tFlag:\t\t\t\t0x%x\n", header->e_flags);
	printf("\tHeader size:\t\t\t%d (bytes)\n", header->e_ehsize);
	printf("\tProgram header size:\t\t%d (bytes)\n", header->e_phentsize);
	printf("\tProgram header number:\t\t%d\n", header->e_phnum);
	printf("\tSection header size:\t\t%d\n", header->e_shentsize);
	printf("\tSection header number:\t\t%d\n", header->e_shnum);
	printf("\tString index number:\t\t%d\n", header->e_shstrndx);
}
void show_program_header(const u_char *data)
{
	elf32_phdr *pheader;
	elf32_Ehdr *header;
	int i, j;
	int num;
	char flag[4] ={' ',' ',' ',' '};
	header = (elf32_Ehdr*)data;
	pheader = (elf32_phdr *) (data + sizeof(*header));
	num = header->e_phnum;
	printf("Program header number: \t%d,",num);
	printf("start at offset %d\n", sizeof(*header));
	printf("ELF file type:");
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
	printf("\tEntry:\t\t\t0x%x\n", header->e_entry);

	printf("Program header:\n");
	printf("\tType\t\tOffset\t VAddr\t    PAddr\tFSize\t MemSize   Flag  Align\n");
	for (i = 0; i < num; ++i)
	{
		printf("\t");
		switch(pheader->p_type)
		{	
			case PT_NULL:
				printf("Invalid\t");
				break;
			case PT_LOAD:
				printf("LOAD \t");
				break;
			case PT_DYNAMIC:
				printf("DYNAMIC\t");
				break;
			case PT_INTERP:
				printf("INTERP\t");
				break;
			case PT_NOTE:
				printf("NOTE \t");
				break;
			case PT_SHLIB:
				printf("SHLIB\t");
				break;
			case PT_PHDR:
				printf("PHDR\t");
				break;
			case PT_TLS:
				printf("TLS\t");
				break;
			case PT_NUM:
				printf("NUM\t");
				break;
			case PT_LOOS:
				printf("LOOS\t");
				break;
			case PT_GNU_EH_FRAME:
				printf("GNU_EH_FRAME   ");
				break;
			case PT_GNU_STACK:
				printf("GNU_STACK  ");
				break;
			case PT_GNU_RELRO:
				printf("GNU_RELRO  ");
				break;
			case PT_L4_STACK:
				printf("L4_STACK  ");
				break;
			case PT_L4_KIP:
				printf("L4_KIP  ");
				break;
			case PT_L4_AUX:
				printf("L4_AUX  ");
				break;
			default:
				printf("Unknown  ");
				break;
		}
		switch(pheader->p_flags)
		{
			case 0x01:
				flag[2]='X';
				break;
			case 0x02:
				flag[1]='W';
				break;
			case 0x03:
				flag[1]='W';
				flag[2]='X';
				break;
			case 0x04:
				flag[0]='R';
				break;
			case 0x05:
				flag[0]='R';
				flag[2]='X';
				break;
			case 0x06:
				flag[0]='R';
				flag[1]='W';
				break;
			case 0x07:
				flag[0]='R';
				flag[1]='W';
				flag[2]='X';
				break;
		}
		flag[3]='\0';
		printf("\t0x%06x 0x%08x 0x%08x  0x%06x 0x%06x", 
				pheader->p_offset,pheader->p_vaddr,pheader->p_paddr,pheader->p_filesz,pheader->p_memsz);
		printf("  %s",flag);
		printf("  0x%x\n",pheader->p_align);
		if(pheader->p_type == PT_INTERP)
		{
			printf("\t \t[Requesting program interpreter: /lib/ld-linux.so.2]\n");
		}
		pheader = (elf32_phdr*)(data + sizeof(*header)+ (i+1) * sizeof(*pheader));
		for(j = 0; j < 4;++j)
		{
			flag[j]=' ';
		}
	}
	

}
void show_section_header(const u_char *data)
{
	elf32_Ehdr *header;
	elf32_Shdr *sheader;
	int i, j;
	int num;
	int s_off;
	u_char *name;

	header = (elf32_Ehdr*)data;
	num =  header->e_shnum;
	s_off = header->e_shoff;
	printf("Total %d section header, start from address 0x%x:\n\n", num,s_off);
	//sheader = (elf32_Shdr*)(data + s_off);
	printf("Section header:\n");
	printf(" [Nr] %-19s%-9s%-9s%-7s%-5s%-5s%-3s%-4s%-4s%-3s\n","Name","Type","Addr","Off","Size","Flag","Lk","Inf","Ali","Es");
	sheader = (elf32_Shdr*)(data + s_off +  sizeof(*sheader) * (header->e_shstrndx));
	name = (u_char *)(data + sheader->sh_offset);
	for(i = 0; i < num; ++i)
	{	sheader = (elf32_Shdr*)(data + i * sizeof(*sheader) + s_off);
		//printf("%x\n",*(name + sheader->sh_name) );
		printf("[%2d] %-19s", i,name + sheader->sh_name );
		
		switch(sheader->sh_type)
		{
			case SHT_NULL:
				printf("%-9s","NULL");
				break;
			case SHT_PROGBITS:
				printf("%-9s","PROGBITS");
				break;
			case SHT_SYMTAB:
				printf("%-9s","SYMTAB");
				break;
			case SHT_STRTAB:
				printf("%-9s","STRTAB");
				break;
			case SHT_RELA:
				printf("%-9s","RELA");
				break;
			case SHT_HASH:
				printf("%-9s","HASH");
				break;
			case SHT_DYNAMIC:
				printf("%-9s","DYNAMIC");
				break;
			case SHT_NOTE:
				printf("%-9s","NOTE");
				break;
			case SHT_NOBITS:
				printf("%-9s","NOBITS");
				break;
			case SHT_REL:
				printf("%-9s","REL");
				break;
			case SHT_SHLIB:
				printf("%-9s","SHLIB");
				break;
			case SHT_DYNSYM:
				printf("%-9s","DYNSYM");
				break;
			case SHT_LOPROC:
				printf("%-9s","LOPROC");
				break;
			case SHT_HIPROC:
				printf("%-9s","HIPROC");
				break;
			case SHT_LOUSER:
				printf("%-9s","LOUSER");
				break;
			case SHT_HIUSER:
				printf("%-9s","HIUSER");
				break;
			default:
				printf("%-9s","Unknown");
				break;
		}
		printf("%08x %06x ",sheader->sh_addr ,sheader->sh_offset);
		printf("%06x ", sheader->sh_size);
		switch(sheader->sh_flags)
		{
			case SHF_WRITE:
				printf("%-4s"," W ");
				break;
			case SHF_ALLOC:
				printf("%-4s"," A ");
				break;
			case SHF_EXECINSTR:
				printf("%-4s"," E ");
				break;
			case SHF_MASKPROC:
				printf("%-4s"," M ");
				break;
			case SHF_WRITE | SHF_ALLOC:
				printf("%-4s"," WA " );
				break;
			case SHF_WRITE | SHF_EXECINSTR:
				printf("%-4s"," WE");
				break;
			case SHF_ALLOC | SHF_EXECINSTR:
				printf("%-4s"," AE");
				break;
			case SHF_WRITE | SHF_ALLOC | SHF_EXECINSTR:
				printf("%-4s"," WAE");
				break;
			default:
				printf("%-4s"," U ");
				break;
		}
		printf("%2d ", sheader->sh_link);
		printf("%3xd", sheader->sh_info);
		printf("%3x ", sheader->sh_addralign);
		printf("%2x\n", sheader->sh_entsize);
		
	}
}
void show_section_name(const u_char *data)
{
	elf32_Ehdr *header;
	elf32_Shdr *sheader;
	int i, j;
	int num;
	int s_off;
	u_char *name;
	header = (elf32_Ehdr*)data;
	num =  header->e_shnum;
	s_off = header->e_shoff;
	printf("Total %d section header, start from address 0x%x:\n\n", num,s_off);
	sheader = (elf32_Shdr*)(data + s_off +  sizeof(*sheader) * (header->e_shstrndx));
	name = (u_char *)(data + sheader->sh_offset);
	printf("%x\t", sheader->sh_name );
	printf("%06x\t%06x\n",sheader->sh_addr ,sheader->sh_offset);
	printf("offset %x\n",sheader->sh_offset );
	printf("name = %s\n", name+0x1b);

}
void show_symbol(const u_char *data)
{
	elf32_Ehdr *header;
	elf32_Shdr *sheader;
	elf32_sym    *symheader;
	int i, j;
	int num;
	int len;
	int s_off;
	u_char *secname;
	u_char *symname;
	header = (elf32_Ehdr*)data;
	num =  header->e_shnum;
	s_off = header->e_shoff;
	//printf("Total %d section header, start from address 0x%x:\n\n", num,s_off);
	sheader = (elf32_Shdr*)(data + s_off +  sizeof(*sheader) * (header->e_shstrndx ));
	secname = (u_char *)(data + sheader->sh_offset);
	for (i = 0; i < num; ++i)
	{
		sheader = (elf32_Shdr*)(data + i * sizeof(*sheader) + s_off);
		if (strcmp( secname+sheader->sh_name, ".strtab")== 0)
		{
			symname = (u_char *)(data + sheader->sh_offset);
		}
	}
	//printf("%x\t", sheader->sh_name );
	//printf("%06x\t%06x\n",sheader->sh_addr ,sheader->sh_offset);
	//printf("offset %x\n",sheader->sh_offset );
	for (i = 0; i < num; ++i)
	{
		sheader = (elf32_Shdr*)(data + i * sizeof(*sheader) + s_off);
		if (strcmp( secname+sheader->sh_name, ".dynsym")== 0)
		{
			len = (sheader->sh_size / sheader->sh_entsize);
			//printf("offset = %x\n",sheader->sh_offset );
			printf("Symbol table '.dynsym' contains %d entries:\n",len);
			printf("\t[Nr] \tValue\tSize\tBind\tType\tInfo\tName\n");
			for ( j = 0; j < len; ++j)
			{
				
				symheader = (elf32_sym*)(data + sheader->sh_offset + j * (sizeof(*symheader)));
				printf("\t%2d: ",j);
				printf(" %08x\t",symheader->st_value );
				printf("%4d\t",symheader->st_size );
				switch(ELF32_ST_TYPE(symheader->st_info))
				{
					case STT_NOTYPE:
						printf("NOTYPE\t");
						break;
					case STT_OBJECT:
						printf("OBJECT\t");
						break;
					case STT_FUNC:
						printf("FUNC\t");
						break;
					case STT_SECTION:
						printf("SECTION\t");
						break;
					case STT_FILE:
						printf("FILE\t");
						break;
					case STT_LOPROC:
						printf("OBJECT\t");
						break;
					case STT_HIPROC:
						printf("HIPROC");
						break;
					default:
						printf("Unknown\t");
						break;
				}
				switch(ELF32_ST_BIND(symheader->st_info))
				{
					case STB_LOCAL:
						printf("LOCAL\t");
						break;
					case STB_GLOBAL:
						printf("GLOBAL\t");
						break;
					case STB_WEAK:
						printf("WEAK\t");
						break;
					case STB_LOPROC:
						printf("OBJECT\t");
						break;
					case STB_HIPROC:
						printf("HIPROC");
						break;
					default:
						printf("Unknown\t");
						break;
				}
				printf("\t");
				printf(" %s\n",symname+symheader->st_name );
				//symbol table .dynsym
			}
			

		}
		if (strcmp( secname+sheader->sh_name, ".symtab")== 0)
		{
			len = (sheader->sh_size / sheader->sh_entsize);
			printf("Symbol table '.symtab' contains %d entries:\n",len);
			printf("\t[Nr] \tValue\tSize\tBind\tType\tInfo\tName\n");
			for ( j = 0; j < len; ++j)
			{
				
				symheader = (elf32_sym*)(data + sheader->sh_offset + j * (sizeof(*symheader)));
				printf("\t%-2d: ",j);
				printf(" %08x\t",symheader->st_value );
				printf("%4d\t",symheader->st_size );
				switch(ELF32_ST_TYPE(symheader->st_info))
				{
					case STT_NOTYPE:
						printf("NOTYPE\t");
						break;
					case STT_OBJECT:
						printf("OBJECT\t");
						break;
					case STT_FUNC:
						printf("FUNC\t");
						break;
					case STT_SECTION:
						printf("SECTION\t");
						break;
					case STT_FILE:
						printf("FILE\t");
						break;
					case STT_LOPROC:
						printf("OBJECT\t");
						break;
					case STT_HIPROC:
						printf("HIPROC");
						break;
					default:
						printf("Unknown\t");
						break;
				}
				switch(ELF32_ST_BIND(symheader->st_info))
				{
					case STB_LOCAL:
						printf("LOCAL\t");
						break;
					case STB_GLOBAL:
						printf("GLOBAL\t");
						break;
					case STB_WEAK:
						printf("WEAK\t");
						break;
					case STB_LOPROC:
						printf("OBJECT\t");
						break;
					case STB_HIPROC:
						printf("HIPROC");
						break;
					default:
						printf("Unknown\t");
						break;
				}
				printf("\t" );
				printf("%s\n",symname+symheader->st_name );
				//symbol table .dynsym
			}
		}


	}
	

}
void show_all(const u_char *data)
{
	show_header(data);
	printf("\n\n");
	show_program_header(data);
	printf("\n\n");
	show_section_header(data);
	printf("\n\n");
	show_symbol(data);
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
			show_usage();
			len = fread(buf,1,MAX_LEN,elf);
			buf[len] = '\0';
			printf("cmd> ");
			scanf("%s",&cmd);
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
					case 'p':
						show_program_header(buf);
						break;
					case 'S':
						show_section_header(buf);
						break;
					case 's':
						show_symbol(buf);
						break;
					case 'n':
						show_section_name(buf);
						break;
					case 'a':
						show_all(buf);
						break;
					case 'v':
						show_version();
						break;
					default:
						break;
				}
				printf("cmd> ");
				scanf("%s",&cmd);
				//scanf("%c",&cmd);
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
		case 'p':
			show_program_header(buf);
			break;
		case 'S':
			show_section_header(buf);
			break;
		case 's':
			show_symbol(buf);
			break;
		case 'n':
			show_section_name(buf);
			break;
		case 'a':
			show_all(buf);
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
