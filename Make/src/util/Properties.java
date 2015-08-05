package util;

import java.io.File;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicReference;

public class Properties extends ConcurrentHashMap<String, Object> {
	private static final long serialVersionUID = -1758256216528498773L;
	ArrayList<Inference<String, Object>> inferences = new ArrayList<Inference<String, Object>>();

	public Properties addInference(String s, Object o) {
		return addInference(new Inference<String, Object>(s, o));
	}

	public Properties addInference(Inference<String, Object> inf) {
		inferences.add(inf);
		return this;
	}

	public boolean infer(final String key) {
		final AtomicReference<Inference<String, Object>> inference = new AtomicReference<Inference<String, Object>>(
				null);
		inferences.forEach(inf -> {
			if (inference.get() == null && inf.getKey().equals(key))
				inference.weakCompareAndSet(null, inf);
		});
		if (inference.get() != null) {
			put(key, inference.get().getValue());
			return true;
		} else
			return false;
	}

	public Properties inferAllUnset() {
		inferences.forEach(inf -> {
			if (!this.containsKey(inf.getKey()))
				put(inf.getKey(), inf.getValue());
		});
		return this;
	}

	public Properties clearInferences() {
		inferences.clear();
		return this;
	}

	public boolean getBool(final String key) {
		return (boolean) this.get(key);
	}
	@SuppressWarnings("unchecked")
	public <TYPE> TYPE  getAs(String key) {
		return (TYPE)get(key);
	}
	public File getFile(String key) {
		return this.<File>getAs(key);
	}
	public Path getPath(String key) {
		Object o = get(key);
		if(o instanceof File)
			return ((File)o).toPath();
		else if(o instanceof Path)
			return (Path) o;
		else
			return null;
	}

	@SuppressWarnings("unchecked")
	public <TYPE> TYPE getOrUse(final String key, final TYPE value) {
		if (containsKey(key)) {
			try {
				return (TYPE) get(key);
			} catch (ClassCastException e) {
				//type of stored object isn't castable to <TYPE>
			}
		}
		put(key, value);
		return value;

	}

	public static class Inference<K, V> implements Entry<K, V> {
		protected K key;
		protected V value;

		public Inference(K key, V o) {
			this.key = key;
			this.value = o;
		}

		@Override
		public K getKey() {
			return key;
		}

		@Override
		public V getValue() {
			return value;
		}

		@Override
		public V setValue(V value) {
			V old = this.value;
			this.value = value;
			return old;
		}
	}

	public String getString(String string) {
		return this.<String>getAs(string);
	}
}
