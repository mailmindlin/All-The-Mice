package com.mindlin.make.assembler.rpi;

import java.io.File;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONObject;

import util.CmdUtil;
import util.CmdUtil.Result;
import util.StrUtils;

import com.mindlin.make.Assembler;

public class ARM_EABI_Assembler extends Assembler<ARM_EABI_Assembler> {

	public ARM_EABI_Assembler(String ARMGNU) {
		super();
		data.put("cmd", new File(ARMGNU + "as").getAbsolutePath());
	}

	@Override
	public ARM_EABI_Assembler addOptimization(String optimization) {
		if (optimization.equals("memory"))
			flag("-reduce-memory-overheads");
		return this;
	}

	@Override
	public Set<String> getOptimizations() {
		Set<String> result = new HashSet<String>();
		result.add("memory");
		return result;
	}

	@Override
	public String[] getCommand() {
		JSONArray result = new JSONArray();
		result.put(0, data.getString("cmd"));
		// options
		{
			JSONObject options = data.getJSONObject("options");
			options.forEach((k, v) -> {
				if (!(v instanceof String)) {
					if (k.equals("warnings") && (v instanceof JSONObject)) {
						JSONObject warnings = (JSONObject) v;
						if (warnings.getBoolean("suppress")) {
							result.add("--no-warn");
						} else if (warnings.getBoolean("show")) {
							result.add("--warn");
						}
						warnings.getJSONArray("shown").forEach(
								(tmp) -> {
									if (!(tmp instanceof String))
										throw new IllegalArgumentException("Argument '"
												+ tmp.getClass().getCanonicalName()
												+ "' isn't a string!\n" + tmp.toString());
									String warning = tmp.toString();
									if (warning.isEmpty()) {
										// do nothing
									} else {
										System.out.println("Unknown warning: " + warning);
									}
								});
						warnings.getJSONArray("suppressed").forEach(
								(tmp) -> {
									if (!(tmp instanceof String))
										throw new IllegalArgumentException("Argument '"
												+ tmp.getClass().getCanonicalName()
												+ "' isn't a string!\n" + tmp.toString());
									String warning = tmp.toString();
									if (warning.equals("deprecated")) {
										result.add("-mno-warn-deprecated");
									} else {
										System.out.println("Unknown warning: " + warning);
									}
								});
						if (warnings.getInt("max") > -1)
							result.put("-fmax-errors="+warnings.getInt("max"));
					}
				} else {
					String vstr = (String) v;
					if (k.equals("cpu")) {
						result.put("-mcpu="+vstr);
					} else if (k.equals("fpu")) {
						result.put("-mfpu="+vstr);
						// force hard floats
						result.put("-mfloat-abi=hard");
					} else if (k.equals("gpu")) {
						result.put("-mgpu="+vstr);
					} else if (k.equals("arch")) {
						result.put("-march="+vstr);
					} else if (k.equals("statistics")) {
						result.put("--statistics");
					}
				}
			});
		}
		// add flags
		data.getJSONArray("flags").forEach((o)->{
			if (o instanceof JSONArray) {
				result.addAll(1, StrUtils.convertList(
						(i) -> {
							String out = ("-"+((i instanceof String) ? (String) i : i.toString()));
							if(out.equalsIgnoreCase("-fpic"))
								return "-k";
							return out;
						}, (JSONArray) o));
			}
			else
				throw new IllegalStateException("Illegal flag type: " + o.getClass().getCanonicalName());
		});
		data.getJSONObject("defines").forEach((k,v)->{
			result.put("--defsym").put(k+"="+v);
		});
		data.getJSONArray("includes").forEach((o)->{
			if (o instanceof Path) {
				result.put("-I").put(((Path) o).toFile().getPath());
			} else {
				throw new IllegalStateException("Illegal include type: " + o.getClass().getCanonicalName());
			}
		});
		data.getJSONArray("targets").forEach((o)->{
			if (o instanceof Path) {
				result.put(((Path) o).toFile().getPath());
			} else {
				throw new IllegalStateException("Illegal target type: " + o.getClass().getCanonicalName());
			}
		});
		if (data.has("output"))
			result.put("-o").put(data.<Path>getAs("output").toString());
		return StrUtils.toStringArray(result);
	}
	@Override
	public boolean execute() {
		Result r = CmdUtil.exec(getCommand());
		r.printErrorLog(2);
		r.printLog(2);
		boolean success=r.wasSuccess();
		if(!success) {
			for(Exception e:r.getExceptions())
				e.printStackTrace();
			return false;
		}
		return true;
	}
}
