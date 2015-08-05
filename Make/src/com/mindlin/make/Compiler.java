package com.mindlin.make;

import java.nio.file.Path;

import util.Properties;


public interface Compiler {
	boolean accept(Properties props);
	Archiver<?> AR();
	Assembler<?> AS();
	CCompiler<?> CC();
	CCompiler<?> CC(String language);
	Linker<?> LD();
	boolean objdump(Path elf, Path listing);
	boolean objcopy(Path elf, Path image);
	boolean ranlib(Path library);
}
