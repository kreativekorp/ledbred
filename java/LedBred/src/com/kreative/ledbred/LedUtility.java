package com.kreative.ledbred;

import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.File;
import java.net.URL;

public class LedUtility {
	public static int gammaCorrect(int color, int minLevel, int maxLevel, boolean wrgb) {
		double rl = ((color >> 16) & 0xFF) / 255.0;
		double gl = ((color >>  8) & 0xFF) / 255.0;
		double bl = ((color >>  0) & 0xFF) / 255.0;
		if (wrgb) {
			double wl = ((color >> 24) & 0xFF) / 255.0;
			rl += (1.0 - rl) * wl;
			gl += (1.0 - gl) * wl;
			bl += (1.0 - bl) * wl;
		}
		rl = minLevel + (maxLevel - minLevel) * Math.sqrt(rl);
		gl = minLevel + (maxLevel - minLevel) * Math.sqrt(gl);
		bl = minLevel + (maxLevel - minLevel) * Math.sqrt(bl);
		int r = (int)Math.round(rl);
		int g = (int)Math.round(gl);
		int b = (int)Math.round(bl);
		return (r << 16) | (g << 8) | (b << 0);
	}
	
	public static BufferedImage toBufferedImage(Image image) {
		if (image == null) return null;
		// Prepare
		Toolkit tk = Toolkit.getDefaultToolkit();
		boolean prepared = false;
		for (int attempts = 0; attempts < 10; attempts++) {
			prepared = tk.prepareImage(image, -1, -1, null);
			if (prepared) break;
			try { Thread.sleep(10); }
			catch (InterruptedException ie) { break; }
		}
		if (!prepared) return null;
		// Get Size
		int w = -1, h = -1;
		for (int attempts = 0; attempts < 10; attempts++) {
			w = image.getWidth(null);
			h = image.getHeight(null);
			if (w > 0 && h > 0) break;
			try { Thread.sleep(10); }
			catch (InterruptedException ie) { break; }
		}
		if (w < 1 || h < 1) return null;
		// Render
		BufferedImage bi = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
		Graphics2D g = bi.createGraphics();
		boolean drawn = false;
		for (int attempts = 0; attempts < 10; attempts++) {
			drawn = g.drawImage(image, 0, 0, null);
			if (drawn) break;
			try { Thread.sleep(10); }
			catch (InterruptedException ie) { break; }
		}
		g.dispose();
		if (!drawn) return null;
		// Return
		return bi;
	}
	
	public static File containingDirectory() {
		try {
			String url = LedUtility.class.getResource("LedUtility.class").toString();
			if (url.startsWith("jar:")) {
				url = url.substring(4, url.lastIndexOf("!/"));
				return new File(new URL(url).toURI()).getParentFile();
			}
			int offset = url.lastIndexOf("/bin/com/kreative/");
			if (offset > 0) {
				url = url.substring(0, offset);
				return new File(new URL(url).toURI());
			}
			offset = url.lastIndexOf("/com/kreative/");
			if (offset > 0) {
				url = url.substring(0, offset);
				return new File(new URL(url).toURI());
			}
			return null;
		} catch (Exception e) {
			return null;
		}
	}
	
	public static File saveDirectory() {
		File containing = containingDirectory();
		if (containing != null && containing.isDirectory()) {
			File save = new File(containing, "SAVE");
			if (save.isDirectory()) return save;
			return containing;
		}
		File save = new File("SAVE");
		if (save.isDirectory()) return save;
		return new File(".");
	}
	
	public static File configFile() {
		File containing = containingDirectory();
		if (containing != null && containing.isDirectory()) {
			return new File(containing, "LEDBRED.INI");
		}
		return new File("LEDBRED.INI");
	}
}
