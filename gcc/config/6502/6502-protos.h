#ifndef GCC_6502_PROTOS_H
#define GCC_6502_PROTOS_H

#ifdef RTX_CODE
extern void m65x_print_operand (FILE *, rtx, int);
extern void m65x_print_branch (enum machine_mode, rtx, rtx, bool);
extern const char *m65x_print_movqi (int, rtx *, bool);
extern unsigned int m65x_mov_length (rtx_insn *, bool);
extern void m65x_print_operand_address (FILE *, rtx);
extern void m65x_output_ascii (FILE *, const char *, int);
extern int m65x_mode_dependent_address_p (rtx);
extern bool m65x_valid_mov_operands (enum machine_mode mode, rtx *operands,
				     bool);
extern bool m65x_valid_zp_mov_operands (enum machine_mode mode, rtx *operands);
extern bool m65x_indirect_indexed_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_indirect_offset_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_absolute_indexed_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_absolute_x_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_absolute_y_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_zeropage_indexed_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_zeropage_x_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_zeropage_y_addr_p (enum machine_mode, rtx, bool);
extern bool m65x_legitimate_address_p (enum machine_mode mode, rtx, bool);
extern rtx m65x_adjust_address (rtx, enum machine_mode, HOST_WIDE_INT);
extern rtx m65x_gen_subreg (enum machine_mode, rtx, enum machine_mode, int);
extern void m65x_emit_qimode_comparison (enum rtx_code cond, rtx op0, rtx op1,
					 rtx dest, rtx scratch);
extern void m65x_emit_himode_comparison (enum rtx_code cond, rtx op0, rtx op1,
					 rtx dest, rtx scratch, basic_block bb);
extern HOST_WIDE_INT m65x_elimination_offset (int from, int to);

extern rtx m65x_push (enum machine_mode mode, rtx src);
extern rtx m65x_pop (enum machine_mode mode, rtx dest);
extern void m65x_expand_addsub (enum machine_mode, bool, rtx[]);
extern void m65x_emit_movqi (rtx, rtx, bool);
extern bool m65x_peep_load (rtx dst, rtx base, rtx index, bool);
extern bool m65x_peep_store (rtx base, rtx index, rtx src, bool);

extern bool m65x_regno_mode_code_ok_for_base_p (int regno,
    enum machine_mode mode, addr_space_t as, enum rtx_code outer,
    enum rtx_code index);

extern rtx m65x_return_addr_rtx (int count, rtx frameaddr);
extern machine_mode m65x_select_cc_mode (rtx_code op, rtx x, rtx y);
#endif

extern void m65x_expand_prologue (void);
extern void m65x_expand_epilogue (void);

extern bool m65x_peephole_find_temp_regs (int, int, ...);

extern bool m65x_real_insns_ok (void);
extern bool m65x_virt_insns_ok (void);

#endif
