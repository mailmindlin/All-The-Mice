package util;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.function.Function;

public class StrUtils {
	public static String concatWithSpaces(String... strings) {
		StringBuilder result = new StringBuilder();
		for (String string : strings) {
			result.append(string.trim().isEmpty() ? "" : (string.trim() + ' '));
		}
		return result.toString();
	}

	public static String concatWithSpaces(Function<String, String> modifier, String... strings) {
		StringBuilder result = new StringBuilder();
		for (String string : strings) {
			result.append(string.trim().isEmpty() ? "" : (modifier.apply(string).trim() + ' '));
		}
		return result.toString();
	}
	public static String concat(Function<String, String> modifier, String... strings) {
		StringBuilder result = new StringBuilder();
		for (String string : strings) {
			result.append(string.trim().isEmpty() ? "" : modifier.apply(string).trim());
		}
		return result.toString();
	}

	public static String concatWithSpaces(Collection<String> strings) {
		return concatWithSpaces(strings.toArray(new String[strings.size()]));
	}
	/**
	 * Casts a {@code List<T>} to a {@code R[]} by casting every element of {@code items} to an {@code R}.<br/>
	 * <b>{@code R} MUST be extend {@code T}.</b>
	 * @param items List to cast to T and fill result array
	 * @return casted 
	 */
	@SuppressWarnings("unchecked")
	public static <T, R extends T> R[] castArrayDown(List<T> items) {
		final ArrayList<R> result = new ArrayList<R>();
		items.forEach((t) -> result.add((R) t));
		return (R[]) result.toArray();
	}
	/**
	 * Casts a {@code List<T>} to a {@code R[]} by casting every element of {@code items} to an {@code R}.<br/>
	 * <b>{@code R} MUST be extend {@code T}.</b>
	 * @param items List to cast to T and fill result array
	 * @return casted 
	 */
	@SuppressWarnings("unchecked")
	public static <R, T extends R> R[] castArrayUp(List<T> items) {
		final ArrayList<R> result = new ArrayList<R>();
		items.forEach((t) -> result.add((R) t));
		return (R[]) result.toArray();
	}
	/**
	 * Convert a list to a {@code String[]} by calling
	 * {@code toString()} on each element of {@code T[] items}. {@code items}
	 * nor any of its elements should be modified.
	 * 
	 * @param items
	 *            list to convert
	 * @return array of strings created by calling {@code toString()} on each of the
	 *         elements in {@code items}. Should be the same size as
	 *         {@code items}.
	 */
	public static <T> String[] toStringArray(List<T> items) {
		final ArrayList<String> result = new ArrayList<String>();
		items.forEach((t) -> result.add(t.toString()));
		return result.toArray(new String[result.size()]);
	}
	/**
	 * Converts a {@code List<T>} to a {@code String[]} by calling applying function
	 * {@code converter} on each element of {@code T[] items}. {@code items} nor
	 * any of its elements should be modified.
	 * 
	 * @param converter
	 *            Function to convert {@code T} object to String object
	 * @param items
	 *            list to convert
	 * @return array of strings created by calling {@code converter.apply(T)} on
	 *         each of the elements in {@code items}. Should be the same size as
	 *         {@code items}.
	 */
	public static <T> String[] toStringArray(Function<T, String> converter, List<T> items) {
		final ArrayList<String> result = new ArrayList<String>();
		for (T item : items)
			result.add(converter.apply(item));
		return result.toArray(new String[result.size()]);
	}

	/**
	 * Converts a {@code T[]} to a {@code String[]} by calling
	 * {@code toString()} on each element of {@code T[] items}. {@code items}
	 * nor any of its elements should be modified.
	 * 
	 * @param items
	 *            array to convert
	 * @return array of strings created by calling {@code toString()} on each of the
	 *         elements in {@code items}. Should be the same size as
	 *         {@code items}.
	 */
	public static <T> String[] toStringArray(T[] items) {
		final ArrayList<String> result = new ArrayList<String>();
		for (T item : items)
			result.add(item.toString());
		return result.toArray(new String[result.size()]);
	}

	/**
	 * Converts a {@code T[]} to a {@code String[]} by calling applying function
	 * {@code converter} on each element of {@code T[] items}. {@code items} nor
	 * any of its elements should be modified.
	 * 
	 * @param converter
	 *            Function to convert {@code T} object to String object
	 * @param items
	 *            array to convert
	 * @return array of strings created by calling {@code converter.apply(T)} on
	 *         each of the elements in {@code items}. Should be the same size as
	 *         {@code items}.
	 */
	public static <T> String[] toStringArray(Function<T, String> converter, T[] items) {
		final ArrayList<String> result = new ArrayList<String>();
		for (T item : items)
			result.add(converter.apply(item));
		return result.toArray(new String[result.size()]);
	}

	/**
	 * Apply a function to each element of an array and return the resulting
	 * array. The input array should not be changed; it's references may be
	 * changed but hopefully is not.
	 * 
	 * @param modifier
	 *            Function to apply to array
	 * @param items
	 *            array that is modified
	 * @return modified copy of array
	 */
	public static <T> T[] applyToArray(Function<T, T> modifier, T[] items) {
		T[] cp = Arrays.copyOf(items, items.length);
		for (int i = 0; i < items.length; i++)
			cp[i] = modifier.apply(items[i]);
		return cp;
	}
	/**
	 * Apply a function to each element of a list and return the resulting
	 * array. The input array should not be changed; it's references may be
	 * changed but hopefully is not.
	 * 
	 * @param modifier
	 *            Function to apply to array
	 * @param items
	 *            list that is modified
	 * @return modified copy of array
	 */
	public static <T> List<T> applyToList(Function<T, T> modifier, List<T> items) {
		List<T> result = new ArrayList<T>();
		for (int i = 0; i < items.size(); i++)
			result.add(i,modifier.apply(items.get(i)));
		return result;
	}
	public static <T,R extends Object> List<R> convertList(Function<T, R> modifier, List<T> items) {
		ArrayList<R> cp = new ArrayList<R>();
		for (int i = 0; i < items.size(); i++)
			cp.add(i,modifier.apply(items.get(i)));
		return cp;
	}
	@SuppressWarnings("unchecked")
	public static <T,R extends Object> R[] convertArray(Function<T, R> modifier, T[] items) {
		ArrayList<R> cp = new ArrayList<R>();
		for (int i = 0; i < items.length; i++)
			cp.add(i,modifier.apply(items[i]));
		return (R[])cp.toArray();
	}
	public static String ofLength(char c, int length) {
		return ofLength(""+c,length);
	}
	public static String ofLength(CharSequence c, int length) {
		StringBuffer outputBuffer = new StringBuffer(length);
		for (int i = 0; i < length; i++){
		   outputBuffer.append(c);
		}
		return outputBuffer.toString();
	}
}
