/* 
* @Author: Xiaokang Yin
* @Date:   2017-05-21 22:03:36
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-05-21 22:04:49
*/
#include <stdlib.h>
#include <stdio.h>

/** e_ident identification indexes */
#define EI_NIDENT 	16		//Size of e_ident[]
#define EI_MAG0     0		//File identification 	0x7f
#define EI_MAG1     1		//File identification	'E'
#define EI_MAG2     2		//File identification	'L'
#define EI_MAG3     3		//File identification	'F'
#define EI_CLASS    4		//file class
#define EI_DATA		5		//Data encoding
#define EI_VERSION	6		//File version
#define EI_PAD		7		//Start of padding bytes

/** EI_CLASS */
#define ELFCLASSNONE	0		//Invalid class
#define ELFCLASS32		1		//32-bit objects
#define ELFCLASS64		2		//64-bit objects

/** EI_DATA */
#define ELFDATANONE		0		//Invalid data encoding
#define ELFDATA2LSB		1		//Little endian, the high bit is in low address
#define ELFDATA2MSB 	2		//Big endian, the high bit is in high address

/** EI_VERSION */
#define EV_NONE		0		//Invalid version
#define EV_CURRENT	1		//Current version

/** Common types */
/** 32-bit ELF base types */
typedef unsigned char 	u_char;  		//Unsigned small integer
typedef unsigned int 	elf32_Addr		//Unsigned program address
typedef unsigned short	elf32_Half;		//Unsigned medium integer
typedef	unsigned int 	elf32_Off;		//Unsigned file offset
typedef signed int 		elf32_Sword;	//Signed large interger
typedef unsigned int 	elf32_Word;		//Unsigned large integer

/** 64-bit ELF base types */
typedef unsigned long long 		elf64_Addr;
typedef	unsigned short 			elf64_Half;
typedef signed short			elf64_SHalf;
typedef unsigned long long		elf64_Off;
typedef signed int 				elf64_Sword;
typedef unsigned int 			elf64_Word;
typedef unsigned long long 		elf64_Xword;
typedef signed long long 		elf64_Sxword;

/** e_type */
#define ET_NONE		0		//No file type
#define ET_REL		1 		//Relocatable file
#define	ET_EXEC		2		//Executable file
#define	ET_DYN		3		//Shared object file
#define ET_CORE		4		//Core file
#define ET_LOPROC	0xff00	//Processor-specific
#define	ET_HIPROC	0xffff	//Processor-specofic

/** e_machine */
#define EM_NONE		0		//No machine
#define EM_M32		1		//AT&T WE 32100
#define EM_SPARC	2		//SPARC
#define	EM_386		3		//Intel 80386
#define	EM_68K		4		//Motorola 68000
#define EM_88K		5		//Motorola 88000
#define EM_860		7		//Intel 80860
#define EM_MIPS 	8  		//MIPS RS3000

/** section header tables */
#define	SHN_UNDEF		0			//Undefined, missing, irrelevant 
#define SHN_LORESERVE	0xff00		//The lower bound of the range of reserved indexes
#define SHN_LOPROC		0xff00		//Reserved for processor-specific semantics
#define SHN_HIPROC		0xff1f		//Reserved for processor-specific semantics
#define SHN_ABS			0xfff1		//This value specifies absolute values for the corresponding reference
#define SHN_COMMON		0xfff2		//Symbols defined relative to this section are common symbols
#define SHN_HIRESERVE	0xffff		//This value specifies the upper bound of the range of reserved indexes

/** sh_type */
#define SHT_NULL		0			//Marks the section header as inactive
#define SHT_PROGBITS	1			//Hold information defined by the program, whose format and meaning are determined solely
#define SHT_SYMTAB		2			//Hold a symbol table. Provides symblos for link editing
#define SHT_STRTAB		3			//
#define SHT_RELA		4			//
#define SHT_HASH		5			//
#define SHT_DYNAMIC		6			//
#define SHT_NOTE		7			//
#define SHT_NOBITS 		8			//
#define SHT_REL 		9			//
#define SHT_SHLIB		10			//
#define SHT_DYNSYM		11			//
#define SHT_LOPROC		0x70000000	//
#define SHT_HIPROC		0x7fffffff	//
#define SHT_LOUSER		0x80000000	//
#define SHT_HIUSER		0xffffffff	//

/** sh_flags */
#define SHF_WRITE		0x1
#define SHF_ALLOC		0x2
#define SHF_EXECINSTR	0x4
#define SHF_MASKPROC	0xf0000000

/** st_info */
#define ELF32_ST_BIND(i)		((i)>>4)
#define ELF32_ST_TYPE(i)		((i)&0xf)
#define ELF32_ST_INFO(b, t)		(((b)<<4) + ((t)&0xf))

/** stb bind type */
#define STB_LOCAL		0
#define STB_GLOBAL		1
#define STB_WEAK		2
#define STB_LOPROC		13
#define STB_HIPROC		15

/** ELF32_ST_TYPE */
#define STT_NOTYPE		0
#define STT_OBJECT		1
#define STT_SECTION		3
#define STT_FILE		4
#define STT_LOPROC		13
#define STT_HIPROC		15

/** 32-bit ELF Header */
typedef struct{
	u_char 			e_ident[EI_NIDENT];
	elf32_Half		e_type;				//Object file type
	elf32_Half		e_machine;			//Architecture
	elf32_Word 		e_version;			//Object file version
	elf32_Addr 		e_entry;			//Virtual address which the system first transfers control
	elf32_Off		e_phoff;			//Program header tables's file offset in bytes
	elf32_Off		e_shoff;			//Section header tables's file offset in bytes
	elf32_Word 		e_flags;
	elf32_Half 		e_ehsize;
	elf32_Half		e_phentsize;
	elf32_Half		e_phnum;
	elf32_Half		e_shentsize;
	elf32_Half		e_shnuml
	elf32_Half		e_shstrndx;
}elf32_Ehdr;

/** 32-bit ELF Section Header */
typedef struct{
	elf32_Word		sh_name;
	elf32_Word 		sh_type;
	elf32_Word   	sh_flags;
	elf32_Addr		sh_addr;
	elf32_Off		sh_offset;
	elf32_Word 		sh_size;
	elf32_Word  	sh_link;
	elf32_Word 		sh_info;
	elf32_Word 		sh_addralign;
	elf32_Word 		sh_entsize;
}elf32_Shdr;

/** 32-bit ELF Symbol Table */
typedef struct{
	elf32_Word 		st_name;
	elf32_Addr		st_value;
	elf32_Word 		st_size;
	u_char			st_info;
	u_char			st_other;
	elf32_Half		st_shndx;
}elf32_sym;

/** rellocate */
typedef struct{
	elf32_Addr 		r_offset;
	elf32_Word 		r_info;
}elf32_Rel;

typedef struct{
	elf32_Addr 		r_offset;
	elf32_Word 		r_info;
	elf32_Word 		r_addend;
}elf32_Rela;

/** Program Header */
typedef struct{
	elf32_Word 		p_type;
	elf32_Off		p_offset;
	elf32_Addr 		p_vaddr;
	elf32_Addr		p_paddr;
	elf32_Word 		p_filesz;
	elf32_Word 		p_memsz;
	elf32_Word 		p_flags;
	elf32_Word 		p_align;
}elf32_phdr;