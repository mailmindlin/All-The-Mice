package com.mindlin.make;

import java.nio.file.FileSystems;
import java.nio.file.Path;

import util.CmdUtil;
import util.CmdUtil.Result;

public interface StdCommand<IMPL extends StdCommand<IMPL>> {
	IMPL setOutput(Path output);
	IMPL addTarget(Path target);
	IMPL setArchitecture(String arch);
	IMPL setCPU(String cpuName);
	IMPL setFPU(String fpuName);
	IMPL setGPU(String gpuName);
	IMPL flag(String flag, String... arguments);
	IMPL includeDir(Path dir);
	IMPL setBaseDir(Path dir);
	Path getBaseDir();
	String[] getCommand();
	/**
	 * Set the output location
	 * @param output new file location
	 * @return self
	 */
	default IMPL setOutput(String output) {
		return setOutput(resolve(output));
	}
	default IMPL addTarget(String target) {
		return addTarget(resolve(target));
	}
	default IMPL includeDir(String dir) {
		return setBaseDir(resolve(dir));
	}
	default Path resolve(String s) {
		if(getBaseDir()!=null)
			return getBaseDir().resolve(s);
		else
			return FileSystems.getDefault().getPath(s);
	}
	default Path resolve(Path p) {
		if(getBaseDir()!=null &&(!p.isAbsolute()))
			return getBaseDir().resolve(p);
		else
			return p;
	}
	default boolean execute() {
		Result r = CmdUtil.exec(getCommand());
		r.printErrorLog();
		r.printLog();
		return r.wasSuccess();
	}
}
