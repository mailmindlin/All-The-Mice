package com.mindlin.make.assembler.rpi;

import java.io.File;
import java.nio.file.Path;

import org.json.JSONArray;

import util.CmdUtil;
import util.CmdUtil.Result;
import util.StrUtils;

import com.mindlin.make.Archiver;

public class ARM_EABI_Archiver extends Archiver<ARM_EABI_Archiver> {

	public ARM_EABI_Archiver(String ARMGNU) {
		super();
		data.put("cmd", new File(ARMGNU+"ar").getAbsolutePath());
	}

	@Override
	public String[] getCommand() {
		JSONArray result = new JSONArray();
		result.put(0, data.get("cmd")).put(1, "rcvS");
		if (data.has("output"))
			result.put(data.<Path>getAs("output").toString());
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
		data.getJSONArray("targets").forEach(
				(o) -> {
					if (o instanceof Path) {
						result.put(((Path) o).toFile().getPath());
					} else {
						throw new IllegalStateException("Illegal target type: "
								+ o.getClass().getCanonicalName());
					}
				});
		return StrUtils.toStringArray(result);
	}
	@Override
	public boolean execute() {
		Result r = CmdUtil.exec(getCommand());
		//parse errors
		{
			String[] errors = r.getErrorLog();
			for (int i = 0; i < errors.length; i++) {
				String tmp = errors[i];
				if(tmp==null)
					continue;
				//snip the prefix
				if(tmp.startsWith(data.getString("cmd")+": "))
					tmp=tmp.substring(data.getString("cmd").length()+2);
				else {
//					System.out.println("Didn't start with '"+data.getString("cmd")+'\'');
				}
				if(tmp.startsWith("creating "))
					//ignore this one, it's a warning
					continue;
//				if(tmp.startsWith("a - "+(data.getJSONArray("targets").get(0).toString())))
				if(tmp.startsWith("a - "))
					continue;
				System.out.println("a - "+(data.getJSONArray("targets").get(0).toString()));
				System.err.println(errors[i]);
				if(!errors[i].endsWith("\n"))
					System.err.println();
			}
		}
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