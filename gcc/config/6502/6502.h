#include "6502-opts.h"

#define TARGET_6502 1
#define TARGET_6502X (m65x_cpu_option == m6502x || m65x_cpu_option == m6502)
#define TARGET_NMOS (m65x_cpu_option == m6502x || m65x_cpu_option == m6502)
#define TARGET_65C02 (m65x_cpu_option == m6502 || m65x_cpu_option == w65sc02 \
		      || m65x_cpu_option == w65c02)
#define TARGET_65SC02 (m65x_cpu_option == m6502 || m65x_cpu_option == w65sc02)
#define TARGET_HUC6280 (m65x_cpu_option == m6502 \
			|| m65x_cpu_option == w65sc02 \
			|| m65x_cpu_option == w65c02 \
			|| m65x_cpu_option == huc6280)
#define TARGET_CMOS (m65x_cpu_option == w65sc02 || m65x_cpu_option == w65c02 \
		     || m65x_cpu_option == huc6280)

/* Target features: index register pushes/pops  */
#define TARGET_PHX TARGET_CMOS
/* Store zero.  */
#define TARGET_STZ TARGET_CMOS
/* ZP-indirect addressing mode.  */
#define TARGET_ZPIND TARGET_CMOS
/* Accumulator increment/decrement.  */
#define TARGET_INCA TARGET_CMOS
/* TRB/TSB opcodes.  */
#define TARGET_TRB_TSB TARGET_CMOS

/*****************************************************************************
 * Run-time target.
 *****************************************************************************/

#define TARGET_CPU_CPP_BUILTINS()		\
  do {						\
    if (TARGET_6502)				\
      builtin_define ("__6502__");		\
    if (TARGET_6502X)				\
      builtin_define ("__6502X__");		\
    if (TARGET_65C02)				\
      builtin_define ("__65C02__");		\
    if (TARGET_65SC02)				\
      builtin_define ("__65SC02__");		\
    if (TARGET_HUC6280)				\
      builtin_define ("__HUC6280__");		\
    if (TARGET_NMOS)				\
      builtin_define ("__NMOS__");		\
    if (TARGET_CMOS)				\
      builtin_define ("__CMOS__");		\
  } while (0)

#define TARGET_OS_CPP_BUILTINS()			\
  do {							\
    if (m65x_machine_option == mach_semi65x)		\
      builtin_define ("__SEMI65X__");			\
    else if (m65x_machine_option == mach_bbcb		\
	     || m65x_machine_option == mach_bbcmaster)	\
      builtin_define ("__BBCMICRO__");			\
    else if (m65x_machine_option == mach_c64)		\
      builtin_define ("__C64__");			\
  } while (0)

/*****************************************************************************
 * Storage layout.
 *****************************************************************************/

#define BITS_BIG_ENDIAN			0
#define BYTES_BIG_ENDIAN		0
#define WORDS_BIG_ENDIAN		0
/*#define LIBGCC2_WORDS_BIG_ENDIAN 	WORDS_BIG_ENDIAN*/

/*#define BITS_PER_UNIT			8*/
#define UNITS_PER_WORD			1
#define POINTER_SIZE			16
#define POINTERS_EXTEND_UNSIGNED	1

#define STACK_BOUNDARY			8
#define BIGGEST_ALIGNMENT		8

#define STRICT_ALIGNMENT		0

#define FUNCTION_BOUNDARY		8
#define PARM_BOUNDARY			8

/*****************************************************************************
 * Layout of source language data types.
 *****************************************************************************/

#define SHORT_TYPE_SIZE			16
#define INT_TYPE_SIZE			16
#define LONG_TYPE_SIZE			32
#define LONG_LONG_TYPE_SIZE		32
#define CHAR_TYPE_SIZE			8
#define FLOAT_TYPE_SIZE			32
#define DOUBLE_TYPE_SIZE		32
#define LONG_DOUBLE_TYPE_SIZE		32

#define DEFAULT_SIGNED_CHAR		0

#define WCHAR_TYPE "int"
#define WCHAR_TYPE_SIZE INT_TYPE_SIZE

#define INTMAX_TYPE "long int"
#define UINTMAX_TYPE "long unsigned int"

#define PTRDIFF_TYPE "int"
#define SIZE_TYPE "unsigned int"

#define LIBGCC2_HAS_DF_MODE 0

/*****************************************************************************
 * Registers.
 *****************************************************************************/

/* 0 : A (real accumulator)
   1 : ah (zp)
   2 : ah2 (zp)
   3 : ah3 (zp)
   4 : X (real X register)
   5 : xh (zp)
   6 : xh2 (zp)
   7 : xh3 (zp)
   8 : Y (real Y register)
   9 : yh (zp)
   10 : yh2 (zp)
   11 : yh3 (zp)
   12 : sp/lo (zp)
   13 : sp/hi (zp)
   14 : fp/lo (zp)
   15 : fp/hi (zp)
   16 : r0 (argument regs)
   17 : r1
   18 : r2
   19 : r3
   20 : r4
   21 : r5
   22 : r6
   23 : r7
   24 : s0 (callee-saved regs)
   25 : s1
   26 : s2
   27 : s3
   28 : s4
   29 : s5
   30 : s6
   31 : s7
   32 : virtual FP/lo
   33 : virtual FP/hi
   34 : virtual AP/lo
   35 : virtual AP/hi
   36 : virtual NZ reg. CCMODE is always 4 bytes!
   37: "
   38: "
   39: "
   40: virtual carry reg.
   41: "
   42: "
   43: "
   44: virtual overflow reg.
   45: "
   46: "
   47: "
   48: hard SP register
   49: "
   50: fixed/local tmp0 (zp)
   51: fixed/local tmp1 (zp)
*/

#define ACC_REGNUM 0
#define X_REGNUM 4
#define Y_REGNUM 8
#define SP_REGNUM 12
#define FP_REGNUM 14
#define FIRST_ARG_REGISTER 16
#define LAST_ARG_REGISTER (FIRST_ARG_REGISTER + 7)
#define FIRST_CALLER_SAVED 24
#define LAST_CALLER_SAVED (FIRST_CALLER_SAVED + 7)
#define FIRST_ZP_REGISTER SP_REGNUM
#define LAST_ZP_REGISTER LAST_CALLER_SAVED
#define NZ_REGNUM 36
#define CARRY_REGNUM 40
#define OVERFLOW_REGNUM 44
/* We pretend this is 2 bytes because it is used as a pointer, and pointers are
   supposed to be HImode.  It's an opaque quantity anyway so it doesn't matter
   if it's a lie.  */
#define HARDSP_REGNUM 48
#define TMP0_REGNUM 50
#define TMP1_REGNUM 51

#define IS_ZP_REGNUM(X)						\
  (((X) < 12 && (((X) % 4) != 0))				\
   || ((X) >= FIRST_ZP_REGISTER && (X) <= LAST_ZP_REGISTER)	\
   || (X) == TMP0_REGNUM || (X) == TMP1_REGNUM)

#define IS_HARD_REGNUM(X)					\
  ((X) == ACC_REGNUM || (X) == X_REGNUM || (X) == Y_REGNUM)

#define FIXED_REGISTERS		\
  { 0, 0, 0, 0, 0, 0, 0, 0,	\
    0, 0, 0, 0, 1, 1, 1, 1,	\
    /* arg regs.  */		\
    0, 0, 0, 0, 0, 0, 0, 0,	\
    /* callee-saved regs.  */	\
    0, 0, 0, 0, 0, 0, 0, 0,	\
    /* fp, ap, cc regs.  */	\
    1, 1, 1, 1, 1, 1, 1, 1,	\
    1, 1, 1, 1, 1, 1, 1, 1,	\
    1, 1, 1, 1 }

#define CALL_USED_REGISTERS	\
  { 1, 1, 1, 1, 1, 1, 1, 1,	\
    1, 1, 1, 1, 1, 1, 1, 1,	\
    /* arg regs.  */		\
    1, 1, 1, 1, 1, 1, 1, 1,	\
    /* callee-saved regs.  */	\
    0, 0, 0, 0, 0, 0, 0, 0,	\
    /* fp, ap, cc regs.  */	\
    1, 1, 1, 1, 1, 1, 1, 1,	\
    1, 1, 1, 1, 1, 1, 1, 1,	\
    1, 1, 1, 1 }

#define FIRST_PSEUDO_REGISTER 52

#define REG_ALLOC_ORDER \
  { 0, 1, 2, 3, 4, 5, 6, 7, \
    8, 9, 10, 11, 12, 13, 14, 15, \
    16, 17, 18, 19, 20, 21, 22, 23, \
    24, 25, 26, 27, 28, 29, 30, 31, \
    32, 33, 34, 35, 36, 37, 38, 39, \
    40, 41, 42, 43, 44, 45, 46, 47, \
    48, 49, 50, 51 }

#define HARD_REGNO_NREGS(REGNO, MODE) \
  m65x_hard_regno_nregs ((REGNO), (MODE))

#define HARD_REGNO_MODE_OK(REGNO, MODE) \
  m65x_hard_regno_mode_ok ((REGNO), (MODE))

#if 1
#define MODES_TIEABLE_P(MODE1, MODE2) 1
#else
#define MODES_TIEABLE_P(MODE1, MODE2) \
  (GET_MODE_SIZE (MODE1) != 1 && GET_MODE_SIZE (MODE2) != 1)
#endif

#if 0
#define CANNOT_CHANGE_MODE_CLASS(FROM, TO, CLASS) \
  ((HARD_REG_CLASS_P (CLASS) || HARDISH_REG_CLASS_P (CLASS)) \
   && GET_MODE_SIZE (FROM) != GET_MODE_SIZE (TO))
#endif

#define AVOID_CCMODE_COPIES

/*****************************************************************************
 * Register classes.
 *****************************************************************************/

enum reg_class
{
  NO_REGS,
  HARD_ACCUM_REG,
  /*WORD_ACCUM_REGS,
  ACCUM_REGS,*/
  HARD_X_REG,
  /*WORD_X_REGS,
  X_REGS,*/
  HARD_Y_REG,
  /*WORD_Y_REGS,
  Y_REGS,*/
  HARD_INDEX_REGS,
  /*WORD_INDEX_REGS,
  INDEX_REGS,*/
  ACTUALLY_HARD_REGS,
  /*WORD_HARD_REGS,
  HARD_REGS,*/
  STACK_REG,
  ARG_REGS,
  CALLEE_SAVED_REGS,
  CC_REGS,
  GENERAL_REGS,
  HARD_ZP_REGS,
  VFP_REG,
  VAP_REG,
  ALL_REGS,
  LIM_REG_CLASSES
};

#define N_REG_CLASSES	(int) LIM_REG_CLASSES

#define REG_CLASS_NAMES		\
{				\
  "NO_REGS",			\
  "HARD_ACCUM_REG",		\
  /*"WORD_ACCUM_REGS",		\
  "ACCUM_REGS",*/			\
  "HARD_X_REG",			\
  /*"WORD_X_REGS",		\
  "X_REGS",*/			\
  "HARD_Y_REG",			\
  /*"WORD_Y_REGS",		\
  "Y_REGS",*/			\
  "HARD_INDEX_REGS",		\
  /*"WORD_INDEX_REGS",		\
  "INDEX_REGS",*/			\
  "ACTUALLY_HARD_REGS",		\
  /*"WORD_HARD_REGS",		\
  "HARD_REGS",*/			\
  "STACK_REG",			\
  "ARG_REGS",			\
  "CALLEE_SAVED_REGS",		\
  "CC_REGS",			\
  "GENERAL_REGS",		\
  "HARD_ZP_REGS",		\
  "VFP_REG",			\
  "VAP_REG",			\
  "ALL_REGS"			\
}

#define REG_CLASS_CONTENTS	\
{				\
  { 0x00000000, 0x00000 },	\
  { 0x00000001, 0x00000 },	\
  /*{ 0x00000003, 0x000 },	\
  { 0x0000000f, 0x000 },*/	\
  { 0x00000010, 0x00000 },	\
  /*{ 0x00000030, 0x000 },	\
  { 0x000000f0, 0x000 },*/	\
  { 0x00000100, 0x00000 },	\
  /*{ 0x00000300, 0x000 },	\
  { 0x00000f00, 0x000 },*/	\
  { 0x00000110, 0x00000 },	\
  /*{ 0x00000330, 0x000 },	\
  { 0x00000ff0, 0x000 },*/	\
  { 0x00000111, 0x00000 },	\
  /*{ 0x00000333, 0x000 },	\
  { 0x00000fff, 0x000 },*/	\
  { 0x0000f000, 0x00000 },	\
  { 0x00ff0000, 0x00000 },	\
  { 0xff000000, 0x00000 },	\
  { 0x00000000, 0x0fff0 },	\
  { 0xfffff000, 0xc0000 },	\
  { 0xfffff111, 0x00000 },	\
  { 0x00000000, 0x00003 },	\
  { 0x00000000, 0x0000c },	\
  { 0xffffffff, 0xffff0 },	\
}

#define REGNO_REG_CLASS(REGNO)						\
  ((REGNO) == ACC_REGNUM ? HARD_ACCUM_REG :				\
   /*(REGNO) == (ACC_REGNUM + 1) ? WORD_ACCUM_REGS :			\
   (REGNO) >= (ACC_REGNUM + 2) && (REGNO) < (ACC_REGNUM + 4)		\
    ? ACCUM_REGS :*/							\
   (REGNO) == X_REGNUM ? HARD_X_REG :					\
   /*(REGNO) == (X_REGNUM + 1) ? WORD_X_REGS :				\
   (REGNO) >= (X_REGNUM + 2) && (REGNO) < (X_REGNUM + 4)		\
     ? X_REGS :*/							\
   (REGNO) == Y_REGNUM ? HARD_Y_REG :					\
   /*(REGNO) == (Y_REGNUM + 1) ? WORD_Y_REGS :				\
   (REGNO) >= (Y_REGNUM + 2) && (REGNO) < (Y_REGNUM + 4)		\
     ? Y_REGS :	*/							\
   (REGNO) >= SP_REGNUM && (REGNO) < (SP_REGNUM + 4) ? STACK_REG :	\
   (REGNO) >= FIRST_ARG_REGISTER && (REGNO) <= LAST_ARG_REGISTER	\
     ? ARG_REGS :							\
   (REGNO) >= FIRST_CALLER_SAVED && (REGNO) <= LAST_CALLER_SAVED	\
     ? CALLEE_SAVED_REGS :						\
   (REGNO) >= FIRST_ZP_REGISTER && (REGNO) <= LAST_ZP_REGISTER		\
     ? GENERAL_REGS :							\
   (REGNO) == TMP0_REGNUM || (REGNO) == TMP1_REGNUM			\
     ? GENERAL_REGS :							\
   (REGNO) >= FRAME_POINTER_REGNUM && (REGNO) < (ARG_POINTER_REGNUM + 2) \
     ? GENERAL_REGS :							\
   (REGNO) >= NZ_REGNUM && (REGNO) <= (OVERFLOW_REGNUM + 3) ? CC_REGS : NO_REGS)

/*#define BASE_REG_CLASS	GENERAL_REGS*/

#define MODE_CODE_BASE_REG_CLASS(MODE, AS, OUTER, INDEX)		\
  ((AS) == ADDR_SPACE_GENERIC ? GENERAL_REGS				\
   : (AS) == ADDR_SPACE_ZP ? HARD_INDEX_REGS				\
   : NO_REGS)

#define INDEX_REG_CLASS	HARD_Y_REG

/*#define REGNO_OK_FOR_BASE_P(NUM) (IS_ZP_REGNUM (NUM))*/

#define REGNO_MODE_CODE_OK_FOR_BASE_P(NUM, MODE, AS, OUTER, INDEX)	 \
  m65x_regno_mode_code_ok_for_base_p ((NUM), (MODE), (AS), (OUTER), (INDEX))

#define REGNO_OK_FOR_INDEX_P(NUM) ((NUM) == Y_REGNUM)

#define PREFERRED_RELOAD_CLASS(X, CLASS) CLASS

/*#define SMALL_REGISTER_CLASSES		1*/

#define CLASS_MAX_NREGS(CLASS, MODE)		\
  (GET_MODE_SIZE (MODE))

/*#define SECONDARY_MEMORY_NEEDED(CLASS1, CLASS2, MODE) \
  ((MODE) == QImode && ZP_REG_CLASS_P (CLASS1) && ZP_REG_CLASS_P (CLASS2))*/

#define HARD_REG_CLASS_P(CLASS)					\
  ((CLASS) == HARD_ACCUM_REG || (CLASS) == HARD_X_REG		\
   || (CLASS) == HARD_Y_REG || (CLASS) == HARD_INDEX_REGS	\
   || (CLASS) == ACTUALLY_HARD_REGS)

/*#define HARDISH_REG_CLASS_P(CLASS)				\
  ((CLASS) == WORD_ACCUM_REGS || (CLASS) == ACCUM_REGS		\
   || (CLASS) == WORD_X_REGS || (CLASS) == X_REGS		\
   || (CLASS) == WORD_Y_REGS || (CLASS) == Y_REGS		\
   || (CLASS) == WORD_INDEX_REGS || (CLASS) == INDEX_REGS	\
   || (CLASS) == WORD_HARD_REGS || (CLASS) == HARD_REGS)*/

#define ZP_REG_CLASS_P(CLASS) \
  ((CLASS) == ARG_REGS || (CLASS) == CALLEE_SAVED_REGS \
   || (CLASS) == GENERAL_REGS || (CLASS) == STACK_REG)

/*****************************************************************************
 * Stack layout/calling conventions.
 *****************************************************************************/

#define STACK_GROWS_DOWNWARDS

/* Hardware stack has "empty" discipline.  */

#define STACK_PUSH_CODE			POST_DEC
#define FRAME_GROWS_DOWNWARDS		0
#define STARTING_FRAME_OFFSET		0

#define FIRST_PARM_OFFSET(FNDECL)	0

/* Registers accessing stack frame.  */

#define STACK_POINTER_REGNUM		SP_REGNUM
#define FRAME_POINTER_REGNUM		32
#define ARG_POINTER_REGNUM		34
#define HARD_FRAME_POINTER_REGNUM	FP_REGNUM

/* Eliminating frame pointer/arg pointer.  */

#define ELIMINABLE_REGS					\
  { { ARG_POINTER_REGNUM, STACK_POINTER_REGNUM },	\
    { ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM },	\
    { ARG_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM },	\
    { FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM },	\
    { FRAME_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM } }

/* FIXME: This needs fixing.  */

#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET)	\
  do { (OFFSET) = m65x_elimination_offset ((FROM), (TO)); } while (0)

/* Passing function arguments on the stack.  */

#define PUSH_ARGS 0
#define ACCUMULATE_OUTGOING_ARGS 1

#define FUNCTION_ARG_REGNO_P(REGNO) \
  ((REGNO) >= FIRST_ARG_REGISTER && (REGNO) <= LAST_ARG_REGISTER)

#define FUNCTION_VALUE_REGNO_P(REGNO) \
  ((REGNO) >= FIRST_ARG_REGISTER && (REGNO) < (FIRST_ARG_REGISTER + 4))

/* Scalar return.  */

#define LIBCALL_VALUE(MODE)		0

/* Dummy definition.  */

typedef int CUMULATIVE_ARGS;

#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, FNDECL, N_NAMED_ARGS) \
  do { (CUM) = 0; } while (0)

/* Profiling.  */

#define FUNCTION_PROFILER(FILE, LABELNO) \
  do { /* Unimplemented.  */ } while (0)

/*****************************************************************************
 * Trampolines.
 *****************************************************************************/

#define TRAMPOLINE_SIZE			0

#if 0
#define INITIALIZE_TRAMPOLINE(ADDR, FNADDR, STATIC_CHAIN) \
  do { /* Unimplemented.  */ } while (0)
#endif

/*****************************************************************************
 * Library calls.
 *****************************************************************************/

/* Testing a tristate (<0, ==0, >0) result from these functions is quite
   inefficient.  */
#define FLOAT_LIB_COMPARE_RETURNS_BOOL(MODE, COMPARISON) true

/*****************************************************************************
 * Addressing modes.
 *****************************************************************************/

#define MAX_REGS_PER_ADDRESS		2

#define LEGITIMIZE_RELOAD_ADDRESS(X, MODE, OPNUM, TYPE, IND_L, WIN)	\
  do {									\
    rtx new_x = m65x_legitimize_reload_address (&(X), (MODE), (OPNUM),	\
						(TYPE), (IND_L));	\
    if (new_x)								\
      {									\
        (X) = new_x;							\
	goto WIN;							\
      }									\
  } while (0)

#define HAVE_PRE_INCREMENT 1
#define HAVE_POST_INCREMENT 0
#define HAVE_PRE_DECREMENT 0
#define HAVE_POST_DECREMENT 1

/*****************************************************************************
 * Costs.
 *****************************************************************************/

#define SLOW_BYTE_ACCESS		0

/* Calling functions via a register is disastrous.  */

#define NO_FUNCTION_CSE

/*****************************************************************************
 * Sections.
 *****************************************************************************/

#define TEXT_SECTION_ASM_OP		"\t.code"
#define DATA_SECTION_ASM_OP		"\t.data"
#define READONLY_DATA_SECTION_ASM_OP	"\t.rodata"
#define BSS_SECTION_ASM_OP		"\t.bss"

/*****************************************************************************
 * Assembler format.
 *****************************************************************************/

#define ASM_APP_OFF			""
#define ASM_APP_ON			""

/* Data Output.  */

#define ASM_OUTPUT_ASCII(STREAM, PTR, LEN) \
  m65x_output_ascii ((STREAM), (PTR), (LEN))

#define ASM_OUTPUT_LABEL(STREAM, NAME)	\
  do {					\
    assemble_name ((STREAM), (NAME));	\
    fputs (":\n", (STREAM));		\
  } while (0)

/* The ca65 assembler does not like single-character labels (especially ones
   which look like the a,x,y registers).  Suffix such names with "$".  */

#define ASM_OUTPUT_LABELREF(STREAM, NAME) \
  fprintf ((STREAM), "%s%s", (NAME), strlen (NAME) == 1 ? "$" : "")

#define ASM_GENERATE_INTERNAL_LABEL(LABEL, PREFIX, NUM) \
  sprintf (LABEL, "%s@%u", PREFIX, (unsigned) (NUM))

/* Instruction Output.  */

#define REGISTER_NAMES						\
  {								\
    "a", "ah", "ah2", "ah3",					\
    "x", "xh", "xh2", "xh3",					\
    "y", "yh", "yh2", "yh3",					\
    "sp0", "sp1", "fp0", "fp1",					\
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",		\
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",		\
    "?vfpl", "?vfph", "?vapl", "?vaph",				\
    "?nz0", "?nz1", "?nz2", "?nz3",				\
    "?carry0", "?carry1", "?carry2", "?carry3",			\
    "?ovf0", "?ovf1", "?ovf2", "?ovf3",				\
    "?hardsp0", "?hardsp1", "tmp0", "tmp1"			\
  }

#define PRINT_OPERAND(STREAM, X, CODE) \
  m65x_print_operand ((STREAM), (X), (CODE))

#define PRINT_OPERAND_ADDRESS(STREAM, X) \
  m65x_print_operand_address ((STREAM), (X))

#define ASM_OUTPUT_ALIGN(STREAM, POWER) \
  fprintf ((STREAM), ".align %d", 1 << (POWER))

#define ASM_FPRINTF_EXTENSIONS(FILE, ARGS, P)			\
  case 'r':							\
    fprintf (FILE, "_%s", reg_names [va_arg (ARGS, int)]);	\
    break;

/* Output of uninitialized variables.  */

#define ASM_OUTPUT_COMMON(STREAM, NAME, SIZE, ROUNDED)		\
  do {								\
    bool needs_dollar = strlen (NAME) == 1;			\
    fprintf ((STREAM), "\t.global ");				\
    assemble_name ((STREAM), (NAME));				\
    fprintf ((STREAM), "\n%s%s:\n\t.res %d\n", (NAME),		\
	     needs_dollar ? "$" : "", (int) (SIZE));		\
  } while (0)

#define ASM_OUTPUT_LOCAL(STREAM, NAME, SIZE, ROUNDED)		\
  do {								\
    assemble_name ((STREAM), (NAME));				\
    fprintf ((STREAM), ":\n");					\
    fprintf ((STREAM), "\t.res %d\n", (int) (SIZE));		\
  } while (0)

#define ASM_OUTPUT_SKIP(STREAM, NBYTES)				\
  do {								\
    fprintf ((STREAM), ".res %d,$00\n", (int) (NBYTES));	\
  } while (0)

/* Prevent emission of call to __main.  */

#define HAS_INIT_SECTION

#undef NO_DOLLAR_IN_LABEL

#define NO_DOT_IN_LABEL

/*****************************************************************************
 * Named Address Spaces
 *****************************************************************************/

#define ADDR_SPACE_ZP 1

#define REGISTER_TARGET_PRAGMAS()			\
  do {							\
    c_register_addr_space ("__zp", ADDR_SPACE_ZP);	\
  } while (0)

/*****************************************************************************
 * Misc.
 *****************************************************************************/

#define HAS_LONG_COND_BRANCH		0
#define HAS_LONG_UNCOND_BRANCH		1

#undef WORD_REGISTER_OPERATIONS
#define MOVE_MAX			2

//#define MAX_FIXED_MODE_SIZE		32

#define Pmode				HImode
#define FUNCTION_MODE			QImode
#define CASE_VECTOR_MODE		HImode

#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1

/* ca65 can't handle "# ..." line directives.  This is a really crude way of
   fixing that.  FIXME.  */

#undef CC1_SPEC
#define CC1_SPEC "-P %<g*"

#undef LIB_SPEC
#define LIB_SPEC "-L%R/usr/lib libtinyc.a"

#undef LIBGCC_SPEC
#define LIBGCC_SPEC "libgcc.a"

/* Hard-wire the semi65x linker script for now.  */
#undef LINK_SPEC
#define LINK_SPEC \
  "%{mmach=bbcb:--config %R/lib/cc65/cfg/bbcb.cfg;"		\
  "  mmach=bbcmaster:--config %R/lib/cc65/cfg/bbcmaster.cfg;"	\
  "  mmach=c64:--config %R/lib/cc65/cfg/c64.cfg;"		\
  "  mmach=semi65x:--config %R/lib/cc65/cfg/semi65x.cfg;"	\
  "  :--config %R/lib/cc65/cfg/semi65x.cfg}"

#undef SYSROOT_SUFFIX_SPEC
#define SYSROOT_SUFFIX_SPEC \
  "%{mmach=bbcb:/bbcb} " \
  "%{mmach=bbcmaster:/bbcm} " \
  "%{mmach=c64:/c64} " \
  "%{mmach=semi65x:}"

extern const char *m65x_fix_dash_l_libs (int argc, const char **argv);

#define EXTRA_SPEC_FUNCTIONS \
  { "fix_dash_l_libs", m65x_fix_dash_l_libs },

/* A simplified version of LINK_COMMAND_SPEC in gcc.c: the principal
   difference, other than removing things which aren't interesting for 6502,
   is the fix_dash_l_libs wrapping the %o specifier.  */

#define LINK_COMMAND_SPEC "\
%{!fsyntax-only:%{!c:%{!M:%{!MM:%{!E:%{!S:\
    %(linker) \
    %l %X %{o*} %{e*} %{N} %{n} %{r}\
    %{s} %{t} %{u*} %{z} %{Z} %{!nostdlib:%{!nostartfiles:%S}} \
    %{static:} %{L*} %(mfwrap) %(link_libgcc)  %:fix_dash_l_libs(%o) \
    %{fprofile-arcs|fprofile-generate*|coverage:-lgcov}  \
    %{!nostdlib:%{!nodefaultlibs:%(link_gcc_c_sequence)}}\
    %{!nostdlib:%{!nostartfiles:%E}} %{T*} }}}}}}"
