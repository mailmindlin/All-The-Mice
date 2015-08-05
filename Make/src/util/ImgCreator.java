package util;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ImgCreator {
	final static int outMb = 34;
	public ImgCreator() {
		
	}
	public void run(Properties props) throws IOException, InterruptedException {
		int outB = outMb*1048576;//1024^2
		int cylinders = outB/8225280;//255*63*512
		int outBlockCount = outB*2048;
		File tmp = new File(props.<File>getAs("bin"),"tmp");
		File outDir = new File(props.<File>getAs("bin"),"output");
		tmp.mkdirs();
		tmp.deleteOnExit();
		outDir.mkdirs();
		File kern = props.<File>getAs("output.file");
		String sh = FileUtils.readInternal("/util/data/rpi-compile.sh");
		sh.replaceAll("$OUTPUTBLOCKCOUNT", ""+outBlockCount)
			.replaceAll("$OUTPUT",kern.getAbsolutePath())
			.replaceAll("$OUTPUTCYLINDERS", ""+cylinders);
		
		//write to file
		File exec = new File(tmp,"exec.sh");
		exec.createNewFile();
		exec.setExecutable(true);
		exec.deleteOnExit();
		FileWriter fw = new FileWriter(exec);
		fw.write(sh);
		fw.close();
		
		Runtime.getRuntime().exec("./"+exec.getAbsolutePath()).waitFor();
		
	}
}
