package com.kreative.ledbred;

import java.awt.FileDialog;
import java.awt.Frame;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Scanner;
import javax.imageio.ImageIO;
import javax.swing.JOptionPane;
import javax.swing.UIManager;

public class Main {
	public static void main(String[] args) {
		try { System.setProperty("com.apple.mrj.application.apple.menu.about.name", "Led·Bred"); } catch (Exception e) {}
		try { System.setProperty("apple.laf.useScreenMenuBar", "true"); } catch (Exception e) {}
		try { UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName()); } catch (Exception e) {}
		
		try {
			Method getModule = Class.class.getMethod("getModule");
			Object javaDesktop = getModule.invoke(Toolkit.getDefaultToolkit().getClass());
			Object allUnnamed = getModule.invoke(Main.class);
			Class<?> module = Class.forName("java.lang.Module");
			Method addOpens = module.getMethod("addOpens", String.class, module);
			addOpens.invoke(javaDesktop, "sun.awt.X11", allUnnamed);
		} catch (Exception e) {}
		
		try {
			Toolkit tk = Toolkit.getDefaultToolkit();
			Field aacn = tk.getClass().getDeclaredField("awtAppClassName");
			aacn.setAccessible(true);
			aacn.set(tk, "Led·Bred");
		} catch (Exception e) {}
		
		File save = LedUtility.saveDirectory();
		lastOpenDirectory = save.getAbsolutePath();
		lastSaveDirectory = save.getAbsolutePath();
		
		LedCanvas canvas = new LedCanvas();
		boolean autoHint = true;
		boolean configHint = false;
		boolean pictureHint = false;
		boolean parseOptions = true;
		for (String arg : args) {
			if (parseOptions && arg.startsWith("-")) {
				if (arg.equals("--")) {
					parseOptions = false;
				} else if (arg.equals("-a")) {
					autoHint = true;
					configHint = false;
					pictureHint = false;
				} else if (arg.equals("-c")) {
					autoHint = false;
					configHint = true;
					pictureHint = false;
				} else if (arg.equals("-p")) {
					autoHint = false;
					configHint = false;
					pictureHint = true;
				} else {
					System.err.println("Unknown option: " + arg);
				}
			} else {
				File file = new File(arg);
				String nn = file.getName().toLowerCase();
				if (configHint || (autoHint && nn.endsWith(".ini"))) {
					try {
						Scanner scan = new Scanner(file);
						canvas.clear();
						canvas.add(scan);
						scan.close();
					} catch (IOException e) {
						System.err.println("Cannot load " + file + ": " + e);
					}
					autoHint = true;
					configHint = false;
					pictureHint = false;
					continue;
				}
				if (pictureHint || (autoHint && nn.endsWith(".led"))) {
					checkConfig(canvas);
					try {
						FileInputStream in = new FileInputStream(file);
						canvas.read(in);
						in.close();
					} catch (IOException e) {
						System.err.println("Cannot load " + file + ": " + e);
					}
					autoHint = true;
					configHint = false;
					pictureHint = false;
					continue;
				}
				System.err.println("Unknown file type: " + file);
			}
		}
		
		checkConfig(canvas);
		new LedBredFrame(canvas).setVisible(true);
	}
	
	private static void checkConfig(LedCanvas canvas) {
		if (canvas.isEmpty()) {
			try {
				File file = LedUtility.configFile();
				Scanner scan = new Scanner(file);
				canvas.add(scan);
				scan.close();
			} catch (IOException e) {
				System.err.println("Cannot load LEDBRED.INI: " + e);
			}
			if (canvas.isEmpty()) {
				canvas.add(new LedPanel(0, 0, 8, 8, WindingOrder.LTR_TTB));
			}
		}
	}
	
	private static String lastOpenDirectory = null;
	public static File getOpenFile() {
		Frame frame = new Frame();
		FileDialog fd = new FileDialog(frame, "Open", FileDialog.LOAD);
		if (lastOpenDirectory != null) fd.setDirectory(lastOpenDirectory);
		fd.setVisible(true);
		String ds = fd.getDirectory(), fs = fd.getFile();
		fd.dispose();
		frame.dispose();
		if (ds == null || fs == null) return null;
		return new File((lastOpenDirectory = ds), fs);
	}
	
	public static boolean openPicture(LedCanvas canvas, File file) {
		if (file == null) {
			file = getOpenFile();
			if (file == null) return false;
		}
		try {
			FileInputStream in = new FileInputStream(file);
			canvas.read(in);
			in.close();
			return true;
		} catch (IOException e) {
			JOptionPane.showMessageDialog(
				null, "An error occurred while opening this file.",
				"Open", JOptionPane.ERROR_MESSAGE
			);
			return false;
		}
	}
	
	public static boolean importPicture(LedCanvas canvas, File file) {
		if (file == null) {
			file = getOpenFile();
			if (file == null) return false;
		}
		try {
			BufferedImage rendered = ImageIO.read(file);
			if (rendered == null) return false;
			Rectangle bounds = canvas.getBounds();
			if (bounds == null) return false;
			BufferedImage scaled = new BufferedImage(bounds.width, bounds.height, BufferedImage.TYPE_INT_ARGB);
			Graphics2D g = scaled.createGraphics();
			g.drawImage(rendered, 0, 0, bounds.width, bounds.height, null);
			g.dispose();
			canvas.fromBufferedImage(scaled, 0, 0);
			return true;
		} catch (IOException e) {
			JOptionPane.showMessageDialog(
				null, "An error occurred while opening this file.",
				"Open", JOptionPane.ERROR_MESSAGE
			);
			return false;
		}
	}
	
	private static String lastSaveDirectory = null;
	public static File getSaveFile(String suffix) {
		Frame frame = new Frame();
		FileDialog fd = new FileDialog(frame, "Save", FileDialog.SAVE);
		if (lastSaveDirectory != null) fd.setDirectory(lastSaveDirectory);
		fd.setVisible(true);
		String ds = fd.getDirectory(), fs = fd.getFile();
		fd.dispose();
		frame.dispose();
		if (ds == null || fs == null) return null;
		if (!fs.toLowerCase().endsWith(suffix.toLowerCase())) fs += suffix;
		return new File((lastSaveDirectory = ds), fs);
	}
	
	public static boolean savePicture(LedCanvas canvas, File file) {
		if (file == null) {
			file = getSaveFile(".LED");
			if (file == null) return false;
		}
		try {
			FileOutputStream out = new FileOutputStream(file);
			canvas.write(out);
			out.close();
			return true;
		} catch (IOException e) {
			JOptionPane.showMessageDialog(
				null, "An error occurred while saving this file.",
				"Save", JOptionPane.ERROR_MESSAGE
			);
			return false;
		}
	}
	
	public static boolean exportPicture(LedCanvas canvas, File file) {
		if (file == null) {
			file = getSaveFile(".png");
			if (file == null) return false;
		}
		try {
			BufferedImage image = canvas.toBufferedImage(null, 0, 0);
			if (image == null) return false;
			ImageIO.write(image, "png", file);
			return true;
		} catch (IOException e) {
			JOptionPane.showMessageDialog(
				null, "An error occurred while saving this file.",
				"Save", JOptionPane.ERROR_MESSAGE
			);
			return false;
		}
	}
}
