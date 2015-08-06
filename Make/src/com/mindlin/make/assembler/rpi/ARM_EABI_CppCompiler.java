package com.mindlin.make.assembler.rpi;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONObject;

import util.FileUtils;
import util.StrUtils;

import com.mindlin.make.CCompiler;

public class ARM_EABI_CppCompiler extends CCompiler<ARM_EABI_CppCompiler> {
	public ARM_EABI_CppCompiler(String ARMGNU) {
		super();
		data.put("cmd", new File(ARMGNU + "g++").getAbsolutePath());
	}

	@Override
	public String[] getCommand() {
		JSONArray result = new JSONArray();
//		System.out.println(data);
		result.put(0, data.getString("cmd"));
		// options
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
					} else if (k.equals("ldscript") && (v instanceof Path)) {
						String vstr=((Path)v).toString().trim();
//						System.out.println("Linker script: "+vstr);
						result.put("-Wl,-T,"+vstr);
					}
				} else {
					String vstr = (String) v;
					if (k.equals("cpu")) {
						result.put("-Wa,-mcpu="+vstr);
					} else if (k.equals("fpu")) {
						result.put("-Wa,-mfpu="+vstr);
						// force hard floats
						result.put("-Wa,-mfloat-abi=hard");
					} else if (k.equals("gpu")) {
						result.put("-Wa,-mgpu="+vstr);
					} else if (k.equals("arch")) {
						result.put("-Wa,-march="+vstr);
					} else if (k.equals("statistics")) {
						result.put("-time");
						result.put("-Wa,--statistics");
					} else if (k.equals("language")) {
						result.put("-std="+vstr);
					}
				}
			});
			if(!options.optBoolean("compile", true)) {
				result.put("-E");
			}else if(!options.optBoolean("assemble",true)) {
				result.put("-S");
			}else if(!options.optBoolean("link",true)) {
				result.put("-c");
			}
		}
		// add flags
		data.getJSONArray("flags").forEach((o)->{
			if (o instanceof JSONArray)
				result.addAll(1, StrUtils.convertList(
						(i) -> ("-"+((i instanceof String) ? (String) i : i.toString())), (JSONArray) o));
			else
				throw new IllegalStateException("Illegal flag type: " + o.getClass().getCanonicalName());
		});
		data.getJSONObject("defines").forEach((k,v)->{
			result.put("-Wa,--defsym,"+k+"="+v).put("-Wp,-D"+k+"="+v);
		});
		data.getJSONArray("includes").forEach((o) -> {
				if (o instanceof Path) {
					String p = ((Path) o).toFile().getPath();
					if (Files.isDirectory((Path) o))
						result.put("-Wl,-L," + p).put("-I").put(p);
//					else
//						result.put("-l " + ((Path) o).toFile().getPath());
				} else {
					throw new IllegalStateException("Illegal include type: "+ o.getClass().getCanonicalName());
				}
		});		
		data.getJSONArray("libraries").forEach((o)->{
			if(o.toString().isEmpty())
				return;
			if(o.toString().endsWith(".o"))
			 	data.getJSONArray("targets").add(new File((String)o).toPath());
			else {
				//libraries in format libNAME.a must be converted to NAME
				String libname = FileUtils.getNameExt(o.toString()).substring(3);
				libname = libname.substring(0, libname.length()-2);
				result.put("-Wl,--library,"+libname).put("-l").put(libname);
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
	public ARM_EABI_CppCompiler addOptimization(String optimization) {
		flag(optimization);
		return this;
	}

	@Override
	public Set<String> getOptimizations() {
		Set<String> result = new HashSet<String>();
		result.add("O1");
		result.add("O2");
		return result;
	}

	@Override
	public ARM_EABI_CppCompiler setWorkingDirectory(Path nwd) {
		flag("-working-directory",resolve(nwd).toString());
		return this;
	}
}