importClass("java.nio.file.Path");
function emptyDir(dir) {
	if(!dir.exists())
		return;
	for (var child in dir.listFiles()) {
		if (child.isDirectory())
			emptyDir(child);
		child.delete();
	}
}
function mapPath(props, input) {
	if(input.
}
function assemble(compiler, input, output) {
	return compiler.AS()
		.addTarget(input)
		.setOutput(output)
		.flag('fpic')
		.define('__REALCOMP__')
		.execute();
}
function compileCpp(compiler, input, output) {
	return compiler.CC()
		.addTarget(input)
		.setOutput(output)
		.define("__REALCOMP__")
		.setLanguage("gnu++11")
		.showWarnings(true)
		.flag("ffreestanding")
		.flag("fPIC")
		.flag("Wextra")
		.flag("nostartfiles")
		.flag("fexceptions")
		.flag("static")
		.link(false)
		.execute();
}
function clean(props, compiler) {
	var bins = [props.getFile("bin.cpp"), props.getFile("bin.asm")];
	for(var bin in bins)
		emptyDir(bin);
}
function foo(props, compiler) {
	console.println("Hello!");
}
function getAvailableTasks() {
	return {"foo":foo};
}