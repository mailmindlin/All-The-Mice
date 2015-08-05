package util;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.LinkedList;
import java.util.List;

import util.PipingStreams.PipingInputStream;
import util.PipingStreams.PipingOutputStream;

public class CmdUtil {
	public static void exec(Properties props, String... commands) throws IOException,
			InterruptedException {
		exec(props, StrUtils.concatWithSpaces(commands));
	}

	public static void exec(Properties props, File output, String... commands) throws IOException,
			InterruptedException {
		exec(props, StrUtils.concatWithSpaces(commands), output);
	}

	public static void exec(Properties props, String command) throws IOException, InterruptedException {
		PipingOutputStream procStdOut = null, procErrOut = null;
		PipingInputStream procStdIn = null;
		procStdOut = new PipingOutputStream(System.out);
		procErrOut = new PipingOutputStream(System.err);
		procStdIn = new PipingInputStream(System.in);
		exec(props, command, procStdOut, procErrOut, procStdIn);
	}

	public static void exec(Properties props, String command, File output) throws IOException,
			InterruptedException {
		PipingOutputStream procStdOut = null, procErrOut = null;
		PipingInputStream procStdIn = null;
		//speeds up by >90% on one test
		BufferedOutputStream os = new BufferedOutputStream(new FileOutputStream(output),1048576);
		procStdOut = new PipingOutputStream(os);
		procErrOut = new PipingOutputStream(System.err);
		procStdIn = new PipingInputStream(System.in);
		exec(props, command, procStdOut, procErrOut, procStdIn);
		os.flush();
		os.close();
		System.out.println("Wrote "+output.length()/1024+" KB");
	}

	public static void exec(Properties props, String command, PipingOutputStream procStdOut,
			PipingOutputStream procErrOut, PipingInputStream procStdIn) throws IOException,
			InterruptedException {
		Timer t=new Timer();
		if ((props.<Integer> getOrUse("debug", 2)) > 1)
			System.out.println('\t'+command);
		Process proc = null;
		PipingOutputStream stdOut = null;
		PipingInputStream stdIn = null, errIn = null;
		try {
			proc = props.<Runtime> getOrUse("runtime", Runtime.getRuntime()).exec(command);
			stdIn = new PipingInputStream(proc.getInputStream(), procStdOut);
			errIn = new PipingInputStream(proc.getInputStream(), procErrOut);
			stdOut = new PipingOutputStream(procStdIn, proc.getOutputStream());
			do {
				stdIn.pipe(-1);
				errIn.pipe(-1);
				// stdOut.pipe(-1);
				Thread.sleep(50);// don't hog all the CPU power
			} while (proc.isAlive());
			procStdOut.close();
			procErrOut.close();
			stdIn.close();
			errIn.close();
			procStdIn.close();
			stdOut.close();
		} finally {
			if (proc != null)
				proc.destroyForcibly();
			if (procStdOut != null)
				try {
					procStdOut.closeAll();
				} catch (Exception e) {
				}
			if (procErrOut != null)
				try {
					procErrOut.closeAll();
				} catch (Exception e) {
				}
			if (stdOut != null)
				try {
					stdOut.closeAll();
				} catch (Exception e) {
				}
			if (procStdIn != null)
				try {
					procStdIn.closeAll();
				} catch (Exception e) {
				}
			if (stdIn != null)
				try {
					stdIn.closeAll();
				} catch (Exception e) {
				}
			if (errIn != null)
				try {
					errIn.closeAll();
				} catch (Exception e) {
				}
			t.mark();
			System.out.println("\tCommand took "+t.sec()+"s");
		}
	}

	public static Result exec(String... command) {
		final Timer t=new Timer();
		final List<String> log = new LinkedList<String>(), errLog = new LinkedList<String>();
		final List<Exception> errs = new LinkedList<Exception>();
		System.out.println("\tRunning: " + StrUtils.concatWithSpaces(command));
		Process proc = null;
		try {
			proc = Runtime.getRuntime().exec(command);
		} catch (Exception e) {
			errs.add(e);
			if (proc == null)
				return new Result(false, log, errLog, errs);
		}

		BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
		BufferedReader stdError = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
		try {
			while(stdInput.ready() || stdError.ready() || proc.isAlive()) {
				boolean read=false;
				if(read=stdInput.ready())
					log.add(stdInput.readLine());
				if(read|=stdError.ready())
					errLog.add(stdError.readLine());
				if(!read)
					Thread.sleep(50);
			}
		} catch (Exception e) {
			errs.add(e);
		}
		try {
			stdInput.close();
		} catch (IOException e) {
			errs.add(e);
		}
		try {
			stdError.close();
		} catch (IOException e) {
			errs.add(e);
		}
		t.mark();
		System.out.println("\tCommand took "+t.sec()+"s");
		proc.destroyForcibly();
		return new Result(true,log,errLog,errs);
	}

	public final static class Result {
		protected final boolean success;
		protected final String[] errorLog;
		protected final String[] log;
		protected final Exception[] errors;

		public Result(List<String> errorLog, List<String> log, List<Exception> exceptions) {
			this(exceptions.size() == 0, errorLog, log, exceptions);
		}

		public Result(boolean success, List<String> errorLog, List<String> log,
				List<Exception> exceptions) {
			this(success, errorLog.toArray(new String[log.size()]),
					log.toArray(new String[log.size()]), exceptions.toArray(new Exception[exceptions
							.size()]));
		}

		public Result(String[] errorLog, String[] log, Exception... exceptions) {
			this(exceptions.length == 0, errorLog, log, exceptions);
		}

		public Result(boolean success, String[] errorLog, String[] log, Exception... exceptions) {
			this.success = success;
			errors = exceptions;
			this.errorLog = errorLog;
			this.log = log;
		}

		public boolean wasSuccess() {
			return success;
		}

		public String[] getErrorLog() {
			return errorLog;
		}

		public String[] getLog() {
			return log;
		}

		public Exception[] getExceptions() {
			return errors;
		}

		public Result printErrorLog() {
			return printErrorLog(0, System.err);
		}

		public Result printErrorLog(int tabs) {
			return printErrorLog(tabs, System.err);
		}

		public Result printLog() {
			return printLog(0, System.out);
		}

		public Result printLog(int tabs) {
			return printLog(tabs, System.out);
		}

		public Result printLog(int tabs, PrintStream os) {
			String prefix = StrUtils.ofLength('\t', tabs);
			for (String line : log) {
				if(line==null)
					continue;
				os.print(prefix + line);
				if(!line.endsWith("\n"))
					os.println();
			}
			return this;
		}

		public Result printErrorLog(int tabs, PrintStream os) {
			String prefix = StrUtils.ofLength('\t', tabs);
			for (String line : errorLog) {
				if(line==null)
					continue;
				os.print(prefix + line);
				if(!line.endsWith("\n"))
					os.println();
			}
			return this;
		}
	}
}
