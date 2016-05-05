namespace JVM {
	enum JavaBytecodeInstruction {
		NOP			 = 0x00,
		ACONST_NULL	 = 0x01,
		ICONST_M1	 = 0x02,
		
		ICONST_0	 = 0x03,
		ICONST_1	 = 0x04,
		ICONST_2	 = 0x05,
		ICONST_3	 = 0x06,
		ICONST_4	 = 0x07,
		ICONST_5	 = 0x08,
		
		LCONST_0	 = 0x09,
		LCONST_1	 = 0x0A,
		
		FCONST_0	 = 0x0B,
		FCONST_1	 = 0x0C,
		FCONST_2	 = 0x0D,
		
		DCONST_0	 = 0x0E,
		DCONST_1	 = 0x0F,
		
		BIPUSH		 = 0x10,
		SIPUSH		 = 0x11,
		
		LDC			 = 0x12,
		LDC_W		 = 0x13,
		LDC2_W		 = 0x14,
		
		ILOAD		 = 0x15,
		LLOAD		 = 0x16,
		FLOAD		 = 0x17,
		DLOAD		 = 0x18,
		ALOAD		 = 0x19,
		
		ILOAD_0		 = 0x1A,
		ILOAD_1		 = 0x1B,
		ILOAD_2		 = 0x1C,
		ILOAD_3		 = 0x1D,
		
		LLOAD_0		 = 0x1C,
		LLOAD_1		 = 0x1D,
		LLOAD_2		 = 0x1E,
		LLOAD_3		 = 0x1F,
		
		FLOAD_0		 = 0x20,
		FLOAD_1		 = 0x21,
		FLOAD_2		 = 0x22,
		FLOAD_3		 = 0x23,
		
		DLOAD_0		 = 0x24,
		DLOAD_1		 = 0x25,
		DLOAD_2		 = 0x26,
		DLOAD_3		 = 0x27,
		
		ALOAD_0		 = 0x28,
		ALOAD_1		 = 0x29,
		ALOAD_2		 = 0x2A,
		ALOAD_3		 = 0x2B,
		
		IALOAD		 = 0x2C,//2E
		LALOAD		 = 0x2D,
		FALOAD		 = 0x2E,
		DALOAD		 = 0x2F,
		AALOAD		 = 0x30,
		BALOAD		 = 0x31,
		CALOAD		 = 0x32,
		SALOAD		 = 0x33,
		
		ISTORE		 = 0x34,//36
		LSTORE		 = 0x35,
		FSTORE		 = 0x36,
		DSTORE		 = 0x37,
		ASTORE		 = 0x38,
		
		ISTORE_0	 = 0x39,
		ISTORE_1	 = 0x3A,
		ISTORE_2	 = 0x3B,
		ISTORE_3	 = 0x3C,
		
		LSTORE_0	 = 0x3D,//3F
		LSTORE_1	 = 0x3E,
		LSTORE_2	 = 0x3F,
		LSTORE_3	 = 0x40,
		
		FSTORE_0	 = 0x41,
		FSTORE_1	 = 0x42,
		FSTORE_2	 = 0x43,
		FSTORE_3	 = 0x44,
		
		DSTORE_0	 = 0x45,
		DSTORE_1	 = 0x46,
		DSTORE_2	 = 0x47,
		DSTORE_3	 = 0x48,
		
		ASTORE_0	 = 0x49//4B
		ASTORE_1	 = 0x4A
		ASTORE_2	 = 0x4B
		ASTORE_3	 = 0x4C
		
		IASTORE		 = 0x4D//4F
		LASTORE		 = 0x4E
		FASTORE		 = 0x4F
		DASTORE		 = 0x50
		AASTORE		 = 0x51
		BASTORE		 = 0x52
		CASTORE		 = 0x53
		SASTORE		 = 0x54
		
		POP			 = 0x55
		POP2		 = 0x56
		
		DUP			 = 0x57
		DUP_X1		 = 0x58
		DUP_X2		 = 0x59
		DUP2		 = 0x5A
		DUP2_X1		 = 0x5B
		DUP2_X2		 = 0x5C
		
		SWAP		 = 0x5D
		
		IADD		 = 0x5E
		LADD		 = 0x5F
		FADD
		DADD
		
		ISUB
		LSUB
		FSUB
		DSUB
		
		IMUL
		LMUL
		FMUL
		DMUL
		
		IDIV
		LDIV
		FDIV
		DDIV
		
		IREM
		LREM
		FREM
		DREM
		
		INEG
		LNEG
		FNEG
		DNEG
		
		ISHL
		LSHL
		
		ISHR
		LSHR
		
		IUSHR
		LUSHR
		
		IAND
		LAND
		
		IOR
		LOR
		
		IXOR
		LXOR
		
		IINC
		
		I2L
		I2F
		I2D
		
		L2I
		L2F
		L2D
		
		F2I
		F2L
		F2D
		
		D2I
		D2L
		D2F
		
		I2B
		I2C
		I2S
		
		LCMP
		FCMPL
		FCMPG
		DCMPL
		DCMPG
		
		IFEQ
		IFNE
		IFLT
		IFGE
		IFGT
		IFLE
		
		IF_ICMPEQ
		IF_ICMPNE
		IF_ICMPLT
		IF_ICMPGE
		IF_ICMPGT
		IF_ICMPLE
		
		IF_ACMPEQ
		IF_ACMPNE
		
		GOTO
		JSR
		RET
		
		TABLESWITCH
		LOOKUPSWITCH
		
		IRETURN
		LRETURN
		FRETURN
		DRETURN
		ARETURN
		RETURN
		
		GETSTATIC
		PUTSTATIC
		
		GETFIELD
		PUTFIELD
		
		INVOKEVIRTUAL
		INVOKESPECIAL
		INVOKESTATIC
		INVOKEINTERFACE
		INVOKEDYNAMIC
		
		NEW
		NEWARRAY
		ANEWARRAY
		ARRAYLENGTH
		
		ATHROW
		CHECKCAST
		INSTANCEOF
		
		MONITORENTER
		MONITOREXIT
		
		WIDE
		
		MULTIANEWARRAY
		
		IFNULL
		IFNONNULL
		
		GOTO_W
		JSR_W
		
		BREAKPOINT
		
		RSRV
		
		IMPDEP1
		IMPDEP2			
	}
	class JavaBytecodeInterperter {
		
	}
}

