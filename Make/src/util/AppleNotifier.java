package util;

import java.io.IOException;

public class AppleNotifier {
	public static final String STD_SOUND = "Display Notification.wflow";
	public static void main(String... argv) {
		if (argv.length > 0)
			displayNotification(argv[0], argv.length >= 2 ? argv[1] : null,
					argv.length >= 3 ? argv[2] : null,
					argv.length >= 4 ? argv[3] : STD_SOUND);
	}

	public static boolean displayNotification(String message, String title,
			String subtitle, String sound) {
		StringBuffer cmd = new StringBuffer("display notification \"").append(
				message).append('"');
		if ((title != null && title.length() > 0)
				|| (subtitle != null && subtitle.length() > 0)) {
			cmd.append(" with");
			if (title != null && title.length() > 0)
				cmd.append(" title \"").append(title).append('"');
			if (subtitle != null && subtitle.length() > 0)
				cmd.append(" subtitle \"").append(subtitle).append('"');
		}
		if (sound != null && sound.length() > 0)
			cmd.append(" sound name \"").append(sound).append('"');
		try {
			Runtime.getRuntime().exec(
					new String[] { "osascript", "-e", cmd.toString() });
		} catch (IOException e) {
			//probably because it's not a mac
			return false;
		}
		return true;
	}
}
