;;#############################################################################
;;! \file source/fpu32/memcpy_fast.asm
;;!
;;! \brief  Fast memcpy
;;! \author N/A  
;;! \date   N/A
;;
;;
;;DESCRIPTION:
;;
;;   This function does a fast memory copy
;;   Note: This function is not part of the normal RTS library.
;;
;;FUNCTIONS:
;;
;;   void memcpy_fast(void *dst, void *src, uint16_t num_bytes)
;;
;;ASSUMPTIONS:
;;
;;
;;ALGORITHM:
;;
;;             
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
;;
;;#############################################################################
;;
;;
;; $Copyright: $
;;#############################################################################

;;		dst: 		XAR4
;;		src: 		XAR5
;;		num_bytes:  AL

        .page
        .if __TI_EABI__
        .asg        memcpy_fast, _memcpy_fast
        .endif
        .global     _memcpy_fast
        .text
_memcpy_fast:
		MOVL XAR7, @XAR5
		RPT @AL
	||	PREAD *XAR4++, *XAR7
        LRETR
        .endasmfunc
    
;; End of File
