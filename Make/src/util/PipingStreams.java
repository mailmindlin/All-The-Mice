package util;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

public class PipingStreams {
	public static class PipingInputStream extends InputStream {
		public static final int BUFFER_SIZE = 1024;
		protected ArrayList<PipingOutputStream> osList = new ArrayList<PipingOutputStream>();
		protected final InputStream is;

		public PipingInputStream(InputStream is) {
			this.is = is;
		}

		public PipingInputStream(InputStream is, PipingOutputStream os) {
			this(is);
			addOutput(os);
		}

		@Override
		public int read() throws IOException {
			return is.read();
		}

		public byte[] readAll(int maximum) throws IOException {
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			byte[] buffer = new byte[BUFFER_SIZE];
			int length = -1;
			int toread = maximum;
			if (toread > 0)
				while ((length = is.read(buffer, 0, Math.min(BUFFER_SIZE, toread))) > 0) {
					baos.write(buffer, 0, length);
					toread -= length;
				}
			else
				while ((length = is.read(buffer, 0, BUFFER_SIZE)) > 0)
					baos.write(buffer, 0, length);
			return baos.toByteArray();
		}

		public void addOutput(PipingOutputStream os) {
			this.connect(os);
			os.connect(this);
		}

		public void removeOutput(PipingOutputStream os) {
			this.disconnect(os);
			os.disconnect(this);
		}

		public void pipe(int max) throws IOException {
			final byte[] buffer = readAll(max);
			// System.out.println("Read "+buffer.length+"/"+max+" bytes");
			osList.forEach(pos -> {
				try {
					pos.write(buffer);
				} catch (Exception e) {
					throw new RuntimeException(e);
				}
			});
		}

		protected void connect(PipingOutputStream os) {
			osList.add(os);
		}

		protected void disconnect(PipingOutputStream os) {
			osList.remove(os);
		}

		@Override
		public void finalize() throws Throwable {
			super.finalize();
			close();
		}

		@Override
		public void close() throws IOException {
			super.close();
			osList.forEach(pos -> pos.disconnect(this));
		}

		public void closeAll() {
			osList.forEach(pis -> {
				try {
					pis.close();
				} catch (Exception e) {
				}
			});
			try {
				close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	public static class PipingOutputStream extends OutputStream {
		protected final OutputStream os;
		protected ArrayList<PipingInputStream> isList = new ArrayList<PipingInputStream>();
		public PipingOutputStream(OutputStream os) {
			this.os=os;
		}
		public PipingOutputStream(PipingInputStream is, OutputStream os) {
			this(os);
			addInput(is);
		}
		@Override
		public void write(int b) throws IOException {
			os.write(b);
		}
		public void pipe(int max) {
			isList.forEach(pis-> {
				try {
					os.write(pis.readAll(max));
				} catch (Exception e) {
					throw new RuntimeException(e);
				}});
		}
		public void addInput(PipingInputStream is) {
			this.connect(is);
			is.connect(this);
		}
		public void removeInput(PipingInputStream is) {
			this.disconnect(is);
			is.disconnect(this);
		}
		protected void connect(PipingInputStream is) {
			isList.add(is);
		}
		protected void disconnect(PipingInputStream is) {
			isList.remove(is);
		}
		@Override
		public void finalize() throws Throwable {
			super.finalize();
			close();
		}
		@Override
		public void close() throws IOException {
			super.close();
			isList.forEach(pis->pis.disconnect(this));
		}
		public void closeAll() {
			isList.forEach(pis->{try{pis.close();}catch(Exception e){}});
			try {
				close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}