package util;

public class Timer {
	protected long startTime=-1,endTime=-1;
	public Timer() {
		startTime=System.currentTimeMillis();
	}
	public void mark() {
		endTime=System.currentTimeMillis();
	}
	public long ms() {
		return endTime-startTime;
	}
	public double sec() {
		return ms()/1000.0;
	}
}
