package util;

import java.io.File;
import java.nio.file.Path;

import org.apache.tools.ant.DirectoryScanner;
import org.json.JSONArray;

public class WildcardExpander {
	public static JSONArray expandAll(final Path cd, JSONArray targets) {
		JSONArray result = new JSONArray();
		targets.forEach((target)->{
			if(target instanceof File) {
				result.add(((File)target).toPath());
				return;
			}
			if(target instanceof Path) {
				if(((Path) target).isAbsolute())
					result.add(((Path) target).normalize());
				else
					result.add(cd.resolve(((Path)target)).normalize());
				return;
			}
			result.addAll(expand(cd, (String)target));
		});
		return result;
	}
	public static JSONArray expand(Path cd, String target) {
		DirectoryScanner scanner = new DirectoryScanner();
		scanner.setIncludes(new String[]{target});
		scanner.setBasedir(cd.toFile());
		scanner.scan();
		return StrUtils.map(new JSONArray(scanner.getIncludedFiles()),(f)->(cd.resolve((String)f)));
	}
}
