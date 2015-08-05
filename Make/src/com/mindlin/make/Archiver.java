package com.mindlin.make;

import java.nio.file.Path;

import org.json.JSONArray;
import org.json.JSONObject;

public abstract class Archiver<IMPL extends Archiver<IMPL>> implements StdCommand<IMPL>{
	protected Path base=null;
	protected JSONObject data = new JSONObject();
	private final IMPL self;
	@SuppressWarnings("unchecked")
	public Archiver() {
		self=(IMPL)this;
		data.put("flags", new JSONArray())
			.put("targets", new JSONArray())
			.put("options", new JSONObject()
			.put("includes", new JSONArray()));
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
	public IMPL addTarget(Path target) {
		data.getJSONArray("targets").put(resolve(target));
		return self;
	}
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
	public IMPL setBaseDir(Path other) {
		base=other;
		return self;
	}
	@Override
	public IMPL setArchitecture(String arch) {
		data.getJSONObject("options").put("arch", arch);
		return self;
	}
	@Override
	public Path getBaseDir() {
		return base;
	}
	@Override
	public IMPL setOutput(Path p) {
		data.put("output", p);
		return self;
	}
	@Override
	public IMPL includeDir(Path dir) {
		data.getJSONArray("includes").put(dir);
		return self;
	}
}
