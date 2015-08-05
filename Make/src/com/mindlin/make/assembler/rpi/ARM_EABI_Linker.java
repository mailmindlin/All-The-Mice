package com.mindlin.make.assembler.rpi;

import java.nio.file.Path;

import org.json.JSONArray;
import org.json.JSONObject;

import util.StrUtils;

import com.mindlin.make.Linker;

public class ARM_EABI_Linker extends Linker<ARM_EABI_Linker> {
	public ARM_EABI_Linker(String ARMGNU) {
		super();
		data.put("armgnu", ARMGNU);
		flag("nostdlib");
	}
	@Override
	public String[] getCommand() {
		JSONArray result = new JSONArray();
		result.put(0, data.get("armgnu") + "gcc");
		{
			JSONObject options = data.getJSONObject("options");
			options.forEach((k, v) -> {
				if (!(v instanceof String)) {
					if (k.equals("warnings") && (v instanceof JSONObject)) {
						JSONObject warnings = (JSONObject) v;
						if (warnings.getBoolean("suppress")) {
							result.add("-w");
						} else if (warnings.getBoolean("show")) {
							result.add("-Wall");
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
					}
				} else {
					String vstr = (String) v;
					if (k.equals("cpu")) {
						result.put("-mcpu").put(vstr);
					} else if (k.equals("fpu")) {
						result.put("-mfpu").put(vstr);
						// force hard floats
						result.put("-m-float-abi=hard");
					} else if (k.equals("gpu")) {
						result.put("-mgpu").put(vstr);
					} else if (k.equals("arch")) {
						result.put("-march").put(vstr).put("-arch").put(vstr);
					} else if (k.equals("statistics")) {
						result.put("-time");
					} else if (k.equals("ldscript")) {
						result.put("-T").put(options.<Path>getAs("ldscript").toString());
					}
				}
			});
		}
		// add flags
		data.getJSONArray("flags").forEach(
				(o) -> {
					if (o instanceof JSONArray)
						result.addAll(1, StrUtils.convertList(
								(i) -> ("-" + ((i instanceof String) ? (String) i : i.toString())),
								(JSONArray) o));
					else
						throw new IllegalStateException("Illegal flag type: "
								+ o.getClass().getCanonicalName());
				});
		data.getJSONObject("defines").forEach((k,v)->{
			result.put("-Wa,--defsym,"+k+"="+v).put("-Wp,-D"+k+"="+v);
		});
		data.getJSONArray("includes").forEach(
				(o) -> {
					if (o instanceof Path) {
						result.put("-B").put(((Path) o).toFile().getPath());
					} else {
						throw new IllegalStateException("Illegal include type: "
								+ o.getClass().getCanonicalName());
					}
				});
		data.getJSONArray("targets").forEach(
				(o) -> {
					if (o instanceof Path) {
						result.put(((Path) o).toFile().getPath());
					} else {
						throw new IllegalStateException("Illegal target type: "
								+ o.getClass().getCanonicalName());
					}
				});
		if (data.has("output"))
			result.put("-o").put(data.<Path>getAs("output").toString());
		return StrUtils.toStringArray(result);
	}

}
