package util;

import java.io.Closeable;
import java.io.File;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;
import java.util.function.Consumer;

public class SymlinkResolver {
	public static File resolve(File input) throws IOException {
		File result = input.getCanonicalFile();
		return result;
//		return resolve(input.toPath()).toFile();
	}
	public static Path resolve(final Path input) throws IOException {
		System.out.println("Resolving "+input.toString());
		if (Files.isSymbolicLink(input)) {
			Path result = Files.readSymbolicLink(input);
			System.out.println("\tResult: "+input.toString());
			return result;
		}
		final AtomicReference<Path> result = new AtomicReference<Path>();
		result.set(input);
		if (!result.updateAndGet((cv) -> {
			try {
				Path np = input.toRealPath();
				if (!np.equals(input))
					return np;
			} catch (Exception e) {
				e.printStackTrace();
			}
			return cv;
		}).equals(input)) {
			System.out.println("\tResult1: "+input.toString());
			return result.get();
		}

		getChildren(input).forEach((child) -> {
			result.updateAndGet((cv) -> {
				try {
					System.out.println("\tTrying: "+child.toString());
					Path np = child.toRealPath().getParent();
					System.out.println("\t\t"+np.toString());
					if (!np.equals(input)) {
						System.out.println("\t\tYep.");
						return np;
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
				System.out.println("\t\tSame.");
				return cv;
			});
		});

		System.out.println("\tResult: " + result.toString());
		return result.get();
	}

	public static List<Path> getChildren(Path dir) throws IOException {
		// if it doesn't exist or isn't a directory, then return an empty list
		if ((!Files.exists(dir))){
			System.out.println("File "+dir.toString()+" dne.");
			return Collections.<Path> emptyList();
		}
		DirectoryStream<Path> ds = null;
		final List<Path> result;
		try {
			ds = Files.newDirectoryStream(dir);
			result = Collections.synchronizedList(new ArrayList<Path>());
			ds.iterator().forEachRemaining(result::add);
		} finally {
			if (ds != null)
				ds.close();
		}
		System.out.println("Children: "+Arrays.toString(result.toArray()));
		return result;
	}

	/**
	 * Convert a Closeable to a Runnable by converting checked IOException to
	 * UncheckedIOException
	 */
	public static Runnable asUncheckedRunnable(Closeable c) {
		return () -> {
			try {
				c.close();
			} catch (IOException e) {
				throw new UncheckedIOException(e);
			}
		};
	}
	public static void talkAbout(Path p) throws IOException {
		System.out.println("About: "+p.toString());
		Consumer<String> c = (s)->(System.out.println("\t"+s));
		c.accept("Path "+(Files.isDirectory(p)?"is":"isn't")+" a directory");
		c.accept("Path "+(Files.exists(p)?"exists":"doesn't exist"));
		c.accept("Path "+(Files.isSymbolicLink(p)?"is":"isn't")+" a symlink.");
		File f=p.toFile();
		c.accept("File "+(f.isDirectory()?"is":"isn't")+" a directory");
		c.accept("File "+(f.exists()?"exists":"doesn't exist"));
		c.accept("File cannonical: "+f.getCanonicalPath().toString());
		c.accept("File absolute: "+f.getAbsolutePath().toString());
	}
}
