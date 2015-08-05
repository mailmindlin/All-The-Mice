package com.mindlin.make;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;
import java.util.Map.Entry;

import org.json.JSONArray;
import org.json.JSONObject;

import util.FileUtils;
import util.Properties;
import util.StrUtils;
import util.SystemProperty;

public class Executor {
	public static void emptyDir(File dir) {
		if (!dir.exists())
			return;
		for (File child : dir.listFiles()) {
			if (child.isDirectory())
				emptyDir(child);
			child.delete();
		}
	}

	public static Path makePath(Path src, String... after) {
		String tmp = StrUtils.concat((i) -> (i + File.separator), after);
		return src.resolve(tmp.substring(0, tmp.length() - File.separator.length()));
	}

	public static boolean init(Properties props) {
		props.getFile("bin").mkdirs();
		props.getFile("bin.asm").mkdirs();
		props.getFile("bin.cpp").mkdirs();
		props.getFile("bin.java").mkdirs();
		return true;
	}

	public static boolean clean(Properties props) {
		List<File> bins = Arrays.asList(props.getFile("bin.cpp"), props.getFile("bin.asm"));
		for (File bin : bins)
			emptyDir(bin);
		File me = SystemProperty.whereAmI();
		FileUtils.deleteIfMatches((f) -> ((!f.isDirectory()) && (!f.equals(me))), props.getFile("bin"));
		return true;
	}

	public static boolean runTask(Properties props, Compiler compiler, String command) {
		System.out.println(":" + command.trim());
		if (command.equals("about")) {
			System.out
					.println("Version " + Main.OS_VERSION + " of MMOS, written by Mailmindlin, 2015.");
			System.out.println("Compiler (this piece of software) version " + Main.VERSION);
			System.out.println("Assembly source: " + props.getFile("src.asm"));
			System.out.println("C++ source: " + props.getFile("src.cpp"));
			System.out.println("Java source: " + props.getFile("src.java"));
			System.out.println("Assembly bin: " + props.getFile("bin.asm"));
			System.out.println("C++ bin: " + props.getFile("bin.cpp"));
			System.out.println("Java bin: " + props.getFile("bin.java"));
			System.out.println("\nSystem properties: ");
			for (Entry<Object, Object> prop : (System.getProperties().entrySet())) {
				System.out.println(prop.getKey() + ": " + prop.getValue());
			}
			System.out.println();
			System.out.println("Options:");
			props.forEach((k, v) -> System.out.println(k + StrUtils.ofLength(' ', 20 - k.length())
					+ v.toString()));
		} else if (command.equals("clean"))
			return clean(props);
		else if (command.equals("compileASM"))
			return compileAsm(props, compiler);
		else if (command.equals("compile"))
			return compile(props, compiler);
		else if (command.equals("build"))
			return runTask(props, compiler, "init") && runTask(props, compiler, "compile")
					&& runTask(props, compiler, "link");
		else if (command.equals("link"))
			return link(props, compiler);
		else if (command.equals("init"))
			return init(props);
		else if (command.equals("check"))
			return check(props);
		return false;
	}

	public static boolean compileAsm(Properties props, Compiler compiler) {
		if (!props.containsKey("libraries"))
			props.put("libraries", new JSONArray());
		JSONArray libraries = props.<JSONArray> getAs("libraries");
		String[] targets = {
				"memset",
				"memcpy",
				"mailbox",
				"framebuffer",
//				"postman",
				"armmodes",
				//"scheduler",
				//"vectors",
				//"xscheduler"
				};
		Path tmp;
		for(String target:targets)
			if ((tmp=assemble(compiler, props, target)) != null)
				if (!libraries.contains(tmp))
					libraries.put(tmp);
				else {
					System.err.println("Error compiling library: "+target);
					return false;
				}
		System.out.println("Successfully made libraries: "
				+ StrUtils.concatWithSpaces(StrUtils.toStringArray(libraries)));
		return true;
	}

	public static boolean compile(Properties props, Compiler compiler) {
		boolean success = true;
		success = success | runTask(props, compiler, "compileASM");
		JSONArray libraries = props.<JSONArray> getAs("libraries");
		/** //TODO fix
		{
			Path stdLib = makePath(props.getPath("bin.cpp"), "libstd.a");
			if (_compileLibrary(compiler, "std",
					makePath(props.getPath("src.cpp"), "std", "manifest.json"),
					makePath(props.getPath("bin.cpp"), "stdlib"), stdLib, new Path[] {},
					props.getBool("verbose")))
				if (!libraries.contains(stdLib))
					libraries.put(stdLib);
				else {
					System.err.println("Error compiling library: std");
					return false;
				}
		}
		/**/
		{
			Path newLib = makePath(props.getPath("bin.cpp"), "newlib.o");
			if (compileCLibrary(compiler, "newlib",
					makePath(props.getPath("src.cpp"), "newlib", "newlib.c"),
					makePath(props.getPath("bin.cpp"), "newlib.o"), newLib, new Path[] {},
					props.getBool("verbose")))
				if (!libraries.contains(newLib))
					libraries.put(newLib);
				else {
					System.err.println("Error compiling library: newlib");
					return false;
				}
		}/**/
		{
			Path bootloader = makePath(props.getPath("bin.asm"), "bootloader.o");
			if (assemble(compiler, makePath(props.getPath("src.asm"), "start.s"), bootloader,
					props.getBool("verbose")))
				if (!libraries.contains(bootloader))
					libraries.put(bootloader);
				else {
					System.err.println("Error compiling bootloader");
					return false;
				}
		}
		return success;
	}

	public static boolean link(Properties props, Compiler compiler) {
		// compile kernel (ELF)
		Path elf = props.getPath("bin.elf");
		CCompiler<?> cc = compiler.CC().enableStatistics(true).setLanguage("gnu++11")
				.define("__REALCOMP__")
				.setBaseDir(props.getPath("src.cpp"))
				.addTarget(makePath(props.getPath("src.cpp"), "Kernel.cpp"))
				.setOutput(elf)
				.includeDir(props.getPath("bin.cpp"))
//				.includeDir(makePath(props.getPath("src.cpp"),"std"))
				.includeDir(props.getPath("bin.asm"))
				.flag("fPIC")
				//.suppressWarnings(true)
				.showWarnings(true)
//				.addOptimization("O3") //Optimizations are risky, but you can get like 10.15% file size decreases
				.flag("ffreestanding")
				.flag("fno-rtti")
				.flag("Wextra")
				.flag("nostartfiles")
				.flag("fexceptions")
				.setLinkerScript(makePath(props.getPath("src.ld"), "rpi.ld"))
				.ldFlag("-Map", props.getPath("bin.map").toString())
				.ldFlag("-static")
				.ldFlag("--gc-sections")
		// .ldFlag("--no-undefined")
		;
		if (props.getBool("verbose")) {
			cc.flag("v").ldFlag("--verbose");
		}

		props.<JSONArray> getAs("libraries").forEach((l) -> (cc.addLibrary(((Path) l).toFile().toString())));
		if (!cc.execute())
			return false;
		compiler.objcopy(elf, props.getPath("out"));
		compiler.objdump(elf, props.getPath("bin.listing"));
		return true;
	}

	public static boolean check(Properties props) {
		JSONArray libraries = props.<JSONArray> getAs("libraries");
		libraries.forEach((lib)-> {
			Path p = (Path)lib;
			if (!Files.exists(p)) {
				System.err.println("\tError: library "+p.toFile().getName()+" not generated!");
				System.exit(-1);
			} else {
				try {
					System.out.println("\tLibrary "+p.toFile().getName()+" appears to have been generated correctly at "
							+ p.toString() + " ("
							+ (Files.size(p) / 1024.0) + " Kb)");
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		});
		if (!Files.exists(props.getPath("out"))) {
			System.err.println("\tError: image not generated!");
			System.exit(-1);
		} else {
			try {
				System.out.println("\tThe image appears to have been generated correctly at "
						+ props.getPath("out").toString() + " ("
						+ (Files.size(props.getPath("out")) / 1024.0) + " Kb)");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return true;
	}

	protected static boolean assemble(Compiler compiler, Path input, Path output, boolean verbose) {
		System.out.println("Assembling: " + output.toFile().getName());
		Assembler<?> assembler = compiler.AS();
		assembler.addTarget(input).setOutput(output).flag("fpic").define("__REALCOMP__");
		if (verbose) {
			assembler.flag("v");
		}
		return assembler.execute();
	}
	protected static Path assemble(Compiler compiler, Properties props, String name) {
		Path output = makePath(props.getPath("bin.asm"), name+".o");
		Path input = makePath(props.getPath("src.asm"), name+".s");
		if(assemble(compiler,input,output,props.getBool("verbose")))
			return output;
		return null;
	}

	protected static boolean compileLibrary(Compiler compiler, String name, Path input, Path temp,
			Path output, Path[] includes, boolean verbose) {
		System.out.println("Compiling library: " + name);
		CCompiler<?> cc = compiler.CC().define("__LIB_" + name).define("__REALCOMP__").addTarget(input)
			.setOutput(temp)
			.setLanguage("gnu++11")
			.showWarnings(true)
			.flag("ffreestanding")// b/c library
			.flag("fPIC")// b/c library
			.flag("Wextra")// it's an OS, so you probably want to know about *every* warning
			.flag("nostartfiles")// because it's a library
			.flag("fexceptions")// I use exceptions, so allow it
			.flag("static")// static library (custom OS, so no libraries there to link to)
//			.addOptimization("O3")
			.link(false);
		for (Path include : includes)
			cc.addTarget(include);
		if (verbose) {
			cc.flag("v").ldFlag("--verbose");
		}
		boolean success = cc.execute();
		if (!success)
			return false;
		success = compiler.AR().setOutput(output).addTarget(temp).execute();
		return success;
	}
	protected static boolean _compileLibrary(Compiler compiler, String name, Path manifest, Path temp, Path output, Path[] includes, boolean verbose) {
		JSONObject json;
		//read file
		{
			StringBuffer sb = new StringBuffer();
			BufferedReader br;
			try {
				br = Files.newBufferedReader(manifest);
				String line;
				while((line=br.readLine())!=null)
					sb.append(line);
			} catch (IOException e) {
				e.printStackTrace();
				return false;
			}
			json = new JSONObject(sb.toString());
		}
		System.out.println(json);
		JSONArray targets = json.getJSONArray("files");
		JSONArray objects = new JSONArray();
		temp.toFile().mkdirs();
		boolean success;
		for(Object o:targets) {
			System.out.println("Compiling: "+o);
			Path tout=makePath(temp,FileUtils.getName(new File((String)o).toPath())+".o");
			CCompiler<?> cc = compiler.CC()
				.define("__LIB_" + name)
				.define("__REALCOMP__")
				.addTarget(makePath(manifest.getParent(),(String)o))
				.setOutput(tout)
				.setLanguage("gnu++11")
				.showWarnings(true)
				.flag("ffreestanding")// b/c library
				.flag("fPIC")// b/c library
				.flag("Wextra")// it's an OS, so you probably want to know about *every* warning
				.flag("nostartfiles")// because it's a library
				.flag("fexceptions")// I use exceptions, so allow it
				.flag("static")// static library (custom OS, so no libraries there to link to)
				.link(false);
			if (verbose)
				cc.flag("v").ldFlag("--verbose");
			for (Path include : includes)
				cc.addTarget(include);
			success = cc.execute();
			if (!success)
				return false;
			objects.add(tout);
		}
		System.out.println("Gluing library: " + name);
		//glue them together
		Archiver<?> ar = compiler.AR()
			.setOutput(output);
		objects.forEach((o)->ar.addTarget((Path)o));
		success = ar.execute();
		if (!success)
			return false;
		success = compiler.ranlib(output);
		return success;
	}

	protected static boolean compileCLibrary(Compiler compiler, String name, Path input, Path temp,
			Path output, Path[] includes, boolean verbose) {
		System.out.println("Compiling library: " + name);
		CCompiler<?> cc = compiler.CC("C")// get C compiler
			.define("__LIB_" + name)
			.define("__REALCOMP__")
			.addTarget(input)
			.setOutput(temp)
			.setLanguage("c11")
			.flag("ffreestanding")
			// because it's a library
			.flag("fPIC")//position-independent code
			.flag("nostartfiles")//not the main executable
			.flag("fexceptions")//enable exceptions
			.flag("static")//static library
//			.suppressWarnings(true)// they got annoying after a while. Feel free to change this.
			.flag("Wextra")
			.showWarnings(true)
//			.addOptimization("O3")
			.suppressWarning("unused-parameter")
			.link(false);
		for (Path include : includes)
			cc.addTarget(include);
		if (verbose) {
			cc.flag("v").ldFlag("--verbose");
		}
		boolean success = cc.execute();
		if (!success)
			return false;
		/*
		 * success=compiler.AR() .setOutput(output) .addTarget(temp) .execute();
		 */
		return success;
	}

	/**
	 * Display a file size in a human-readable format. (i.e., 1048576 -> "1MB")
	 * 
	 * @param size
	 *            size in bytes
	 * @return human-readable string
	 */
	protected static String fileSize(long size) {
		String[] sizes = { "B", "KB", "MB", "GB", "TB" };
		int order = (int) Math.floor(Math.log(size) / Math.log(1024));
		if (order == 0)
			return String.format("%d %s", size, sizes[order]);
		return String.format("%.5g %s", size / Math.pow(1024, order), sizes[order]);
	}
}
