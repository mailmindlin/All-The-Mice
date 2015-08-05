package com.mindlin.make;

import java.nio.file.Path;

import org.json.JSONArray;
import org.json.JSONObject;

public abstract class Linker<IMPL extends Linker<IMPL>> implements StdCommand<IMPL>{
	protected Path base=null;
	protected JSONObject data = new JSONObject();
	private final IMPL self;
	@SuppressWarnings("unchecked")
	public Linker() {
		this.self=(IMPL)this;
		data.put("flags", new JSONArray())
			.put("targets", new JSONArray())
			.put("options", new JSONObject()
			.put("includes", new JSONArray()));
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
	@Override
	public IMPL addTarget(Path target) {
		data.getJSONArray("targets").put(resolve(target));
		return self;
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
	public IMPL setLinkerScript(Path script) {
		data.getJSONObject("options").put("ldscript", script);
		return self;
	}
}
