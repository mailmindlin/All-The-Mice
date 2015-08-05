package com.mindlin.make;

import java.nio.file.Path;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONObject;

public abstract class CCompiler<IMPL extends CCompiler<IMPL>> implements StdCommand<IMPL>{
	protected Path base=null;
	protected JSONObject data = new JSONObject();
	private final IMPL self;
	@SuppressWarnings("unchecked")
	public CCompiler() {
		this.self=(IMPL)this;
		data.put("flags", new JSONArray())
			.put("targets", new JSONArray())
			.put("defines", new JSONObject())
			.put("options", new JSONObject()
				.put("warnings", new JSONObject()
					.put("suppress", false)
					.put("show", false)
					.put("max", -1)
					.put("suppressed", new JSONArray())
					.put("shown", new JSONArray())))
			.put("includes", new JSONArray())
			.put("libraries", new JSONArray());
	}
	@Override
	public Path getBaseDir() {
		return base;
	}
	@Override
	public IMPL setBaseDir(Path nb) {
		base=nb;
		return self;
	}
	/**
	 * Define the given symbol with the value of 1
	 * 
	 * @param definition
	 *            symbol to define
	 * @return self
	 */
	public IMPL define(String definition) {
		return define(definition,"1");
	}
	public IMPL ldFlag(String ...flags) {
		StringBuffer sb = new StringBuffer();
		for(String flag:flags) {
			sb.append(",");
			sb.append(flag.trim());
		}
		return flag("Wl"+sb.toString());
	}

	/**
	 * Define the given symbol as value
	 * 
	 * @param definition
	 *            symbol to define (should not contain spaces)
	 * @param value
	 *            value for symbol
	 * @return self
	 */
	public IMPL define(String definition, String value) {
		data.getJSONObject("defines").put(definition,value);
		return self;
	}
	@Override
	public IMPL addTarget(Path target) {
		data.getJSONArray("targets").put(resolve(target));
		return self;
	}
	@Override
	public IMPL setCPU(String cpuName) {
		data.getJSONObject("options").put("cpu", cpuName);
		return self;
	}
	@Override
	public IMPL setFPU(String fpuName) {
		data.getJSONObject("options").put("fpu", fpuName);
		return self;
	}
	@Override
	public IMPL setGPU(String gpuName) {
		data.getJSONObject("options").put("gpu", gpuName);
		return self;
	}
	@Override
	public IMPL setArchitecture(String arch) {
		data.getJSONObject("options").put("arch", arch);
		return self;
	}

	/**
	 * Explicitly suppress warnings of given type
	 * 
	 * @param type
	 * @return self
	 */
	public IMPL suppressWarning(String type) {
		data.getJSONObject("options").getJSONObject("warnings").getJSONArray("suppressed").put(type);
		return self;
	}

	/**
	 * Explicitly show warnings of given type
	 * 
	 * @param type
	 * @return self
	 */
	public IMPL showWarning(String type) {
		data.getJSONObject("options").getJSONObject("warnings").getJSONArray("shown").put(type);
		return self;
	}

	/**
	 * Whether explicitly show warnings
	 * 
	 * @param aflag
	 *            whether to show them
	 * @return self
	 */
	public IMPL showWarnings(boolean aflag) {
		data.getJSONObject("options").getJSONObject("warnings").put("show", aflag);
		return self;
	}

	/**
	 * Whether to explicitly suppress all warnings. May conflict with
	 * {@link #showWarnings(boolean)}.
	 * 
	 * @param aflag
	 *            whether to suppress them
	 * @return self
	 */
	public IMPL suppressWarnings(boolean aflag) {
		data.getJSONObject("options").getJSONObject("warnings").put("suppress", aflag);
		return self;
	}

	/**
	 * Whether to explicitly enable display of various data.
	 * 
	 * @param aflag
	 * @return self
	 */
	public IMPL enableStatistics(boolean aflag) {
		data.getJSONObject("options").put("statistics",aflag);
		return self;
	}

	/**
	 * Maximum warnings to show
	 * @param num
	 * @return self
	 */
	public IMPL maxWarnings(int num) {
		data.getJSONObject("options").getJSONObject("warnings").put("max",num);
		return self;
	}

	@Override
	public IMPL flag(String flag, String... arguments) {
		JSONArray consolidated = new JSONArray();
		consolidated.put(flag);
		for(String arg:arguments)
			consolidated.put(arg);
		data.getJSONArray("flags").put(consolidated);
		return self;
	}
	@Override
	public IMPL setOutput(Path output) {
		data.put("output", resolve(output));
		return self;
	}
	@Override
	public IMPL includeDir(Path dir) {
		data.getJSONArray("includes").put(resolve(dir));
		return self;
	}
	/**
	 * Add implementation-specific optimization. <br/>
	 * Calling this method multiple times may override which optimization is
	 * used, or use both, depending on the implementation.
	 * 
	 * @param optimization
	 *            to use
	 * @return self
	 */
	public abstract IMPL addOptimization(String optimization);

	/**
	 * Gets a set of available optimizations.
	 * 
	 * @return available optimizations
	 */
	public abstract Set<String> getOptimizations();

	public IMPL link(boolean aflag) {
		data.getJSONObject("options").put("link", aflag);
		return self;
	}
	
	public IMPL compile(boolean aflag) {
		data.getJSONObject("options").put("compile", aflag);
		return self;
	}
	
	public IMPL assemble(boolean aflag) {
		data.getJSONObject("options").put("assemble", aflag);
		return self;
	}

	public IMPL setLanguage(String lang) {
		data.getJSONObject("options").put("language", lang);
		return self;
	}

	public abstract IMPL setWorkingDirectory(Path nwd);

	public IMPL setWorkingDirectory(String nwd) {
		return setWorkingDirectory(resolve(nwd));
	}
	
	public IMPL addLibrary(String libname) {
		data.getJSONArray("libraries").put(libname);
		return self;
	}
	public IMPL setLinkerScript(Path script) {
		data.getJSONObject("options").put("ldscript", script);
		return self;
	}
}
