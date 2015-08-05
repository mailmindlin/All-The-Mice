package com.mindlin.make;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.ListIterator;
import java.util.Set;

import util.Properties;
import util.SymlinkResolver;
import util.SystemProperty;

public class Main {
	public final static String OS_VERSION="experimental alpha 0.0.25";
	public final static String VERSION="alpha 0.1.5";
	public final static Properties properties = new Properties();
	static Compiler compiler;
	public final static ArrayList<String> tasks = new ArrayList<String>();
	public final static Set<String> finished=new HashSet<String>();
	public static void main(String[] fred) throws IOException {
		parseArguments(fred);
		inferUnset();
		ListIterator<String> taskIterator = tasks.listIterator();
		while(taskIterator.hasNext())
			exec(taskIterator.next());
		System.out.println("Bye!");
	}
	public static void parseArguments(String[] argv) {
		for(int i=0;i<argv.length;i++) {
			String command = argv[i];
			if(command.equals("help")) {
				if(i+1<argv.length)
					printHelp(argv[++i]);
				else
					printStdHelp();
				System.exit(0);
			} else if(command.equals("-arch")) {
				properties.put("target.arch",argv[++i]);
			} else if(command.equals("-targ"))
				properties.put("target", argv[++i]);
			else if(command.equals("--src-asm"))
				properties.put("src.asm",new File(argv[++i]));
			else if(command.equals("--src-c++"))
				properties.put("src.cpp",new File(argv[++i]));
			else if(command.equals("--src-java"))
				properties.put("src.java",new File(argv[++i]));
			else if(command.equals("--src-ld"))
				properties.put("src.ld",new File(argv[++i]));
			else if(command.equals("--bin"))
				properties.put("bin",new File(argv[++i]));
			else if(command.equals("--bin-asm"))
				properties.put("bin.asm",new File(argv[++i]));
			else if(command.equals("--bin-c++"))
				properties.put("bin.cpp",new File(argv[++i]));
			else if(command.equals("--bin-java"))
				properties.put("bin.java",new File(argv[++i]));
			else if(command.equals("-o"))
				properties.put("out",new File(argv[++i]));
			else if(command.equals("-v"))
				properties.put("verbose", true);
			else
				tasks.add(argv[i]);
		}
	}
	public static void inferUnset() throws IOException {
		File bin = properties.getOrUse("bin", new File("bin").getAbsoluteFile());
		try {
			Compilers.loadClasses();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		properties
			.addInference("out",new File(bin, "kernel.img"))
			.addInference("bin",bin)
			.addInference("bin.asm",SymlinkResolver.resolve(new File(bin, "asm").getAbsoluteFile()))
			.addInference("bin.cpp", SymlinkResolver.resolve(new File(bin, "cpp").getAbsoluteFile()))
			.addInference("bin.java", SymlinkResolver.resolve(new File(bin, "java").getAbsoluteFile()))
			.addInference("src.asm",SymlinkResolver.resolve(new File("asm/rpi").getAbsoluteFile()))
			.addInference("src.ld",SymlinkResolver.resolve(new File("linker").getAbsoluteFile()))
			.addInference("src.cpp", SymlinkResolver.resolve(new File("Kernel").getAbsoluteFile()))
//			.addInference("src.java", SymlinkResolver.resolve(new File("java").getAbsoluteFile()))
			.addInference("bin.listing", new File(bin,"kernel.list"))
			.addInference("bin.elf", new File(bin,"kernel.elf"))
			.addInference("bin.map", new File(bin,"kernel.map"))
			.addInference("target.arch","armv7")//will default to RPIv2
			.addInference("CYGWIN",false)
			.addInference("CARCH",SystemProperty.OS_ARCH.get("x86_64"))
			.addInference("COS",SystemProperty.OS_NAME.get("Windows"))
			.addInference("verbose",false)
			.inferAllUnset()
			.clearInferences();
		compiler=Compilers.getCompiler(properties);
		if(properties.getBool("verbose"))
			properties.forEach((a,b)->{
				System.out.print("\t"+a.toString()+":"+b.toString());
				if(b instanceof File)
					System.out.print("->"+(((File) b).exists()?"exists":"doesn't exist"));
				System.out.println();
			});
	}
	public static void exec(String cmd) {
		final String command=cmd.toLowerCase().trim();
		Executor.runTask(properties, compiler, command);
		finished.add(command);
	}
	public static void printHelp(String command) {
		if(!printData("util/data/"+command+".txt")) {
			System.err.println("Unknown command: "+command);
		}
	}
	public static void printStdHelp() {
		printData("util/data/help.txt");
	}
	protected static boolean printData(String file) {
		BufferedReader br = new BufferedReader(new InputStreamReader(Main.class.getResourceAsStream(file)));
		String tmp;
		try {
			while((tmp=br.readLine())!=null)
				System.out.print(tmp);
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}
}