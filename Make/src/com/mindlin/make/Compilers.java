package com.mindlin.make;
import java.util.ArrayList;

import util.Properties;


public class Compilers {
	public static void loadClasses() throws ClassNotFoundException {
		Class.forName("com.mindlin.make.assembler.rpi.RPI");
		Class.forName("com.mindlin.make.assembler.rpi.RPI2");
	}
	protected static ArrayList<Compiler> compilers = new ArrayList<Compiler>();
	public static void register(Compiler c) {
		compilers.add(c);
	}
	public static Compiler getCompiler(Properties props) {
		for(Compiler c : compilers) {
			if(c.accept(props)) {
				System.out.println("Using compiler '"+c.getClass().getName()+"'");
				return c;
			}
		}
		return null;
	}
}
