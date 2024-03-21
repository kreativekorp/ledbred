package com.kreative.ledbred;

import java.awt.Toolkit;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowEvent;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

public class LedBredMenuBar extends JMenuBar {
	private static final long serialVersionUID = 1L;
	
	public static final int SHORTCUT_KEY = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
	public static final boolean IS_MAC_OS;
	public static final boolean IS_WINDOWS;
	static {
		boolean isMacOS;
		boolean isWindows;
		try {
			String os = System.getProperty("os.name").toUpperCase();
			isMacOS = os.contains("MAC OS");
			isWindows = os.contains("WINDOWS");
		} catch (Exception e) {
			isMacOS = false;
			isWindows = false;
		}
		IS_MAC_OS = isMacOS;
		IS_WINDOWS = isWindows;
	}
	
	public LedBredMenuBar(LedBredFrame f) {
		add(new FileMenu(f));
		add(new EditMenu(f));
	}
	
	public static class FileMenu extends JMenu {
		private static final long serialVersionUID = 1L;
		public FileMenu(LedBredFrame f) {
			super("File");
			add(new NewMenuItem(f));
			add(new OpenMenuItem(f));
			add(new SaveMenuItem(f));
			addSeparator();
			add(new ImportMenuItem(f));
			add(new ExportMenuItem(f));
			addSeparator();
			add(new CloseMenuItem(f));
			if (!IS_MAC_OS) add(new ExitMenuItem());
		}
	}
	
	public static class NewMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public NewMenuItem(final LedBredFrame f) {
			super("New Picture");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					f.panel.leds.clearPixels();
				}
			});
		}
	}
	
	public static class OpenMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public OpenMenuItem(final LedBredFrame f) {
			super("Open Picture...");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					f.panel.leds.openPicture(null);
				}
			});
		}
	}
	
	public static class SaveMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public SaveMenuItem(final LedBredFrame f) {
			super("Save Picture...");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					f.panel.leds.savePicture(null);
				}
			});
		}
	}
	
	public static class ImportMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public ImportMenuItem(final LedBredFrame f) {
			super("Import Picture...");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					f.panel.leds.importPicture(null);
				}
			});
		}
	}
	
	public static class ExportMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public ExportMenuItem(final LedBredFrame f) {
			super("Export Picture...");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					f.panel.leds.exportPicture(null);
				}
			});
		}
	}
	
	public static class CloseMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public CloseMenuItem(final Window window) {
			super("Close Window");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					window.dispatchEvent(new WindowEvent(window, WindowEvent.WINDOW_CLOSING));
				}
			});
		}
	}
	
	public static class ExitMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public ExitMenuItem() {
			super("Exit");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					System.gc();
					for (Window window : Window.getWindows()) {
						if (window.isVisible()) {
							window.dispatchEvent(new WindowEvent(window, WindowEvent.WINDOW_CLOSING));
							if (window.isVisible()) return;
						}
					}
					System.exit(0);
				}
			});
		}
	}
	
	public static class EditMenu extends JMenu {
		private static final long serialVersionUID = 1L;
		public EditMenu(LedBredFrame f) {
			super("Edit");
			add(new CutMenuItem(f));
			add(new CopyMenuItem(f));
			add(new PasteMenuItem(f));
			add(new ClearMenuItem(f));
		}
	}
	
	public static class CutMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public CutMenuItem(final LedBredFrame f) {
			super("Cut");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (f.panel.leds.copyPicture()) {
						f.panel.leds.clearPixels();
					} else {
						Toolkit.getDefaultToolkit().beep();
					}
				}
			});
		}
	}
	
	public static class CopyMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public CopyMenuItem(final LedBredFrame f) {
			super("Copy");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (!f.panel.leds.copyPicture()) {
						Toolkit.getDefaultToolkit().beep();
					}
				}
			});
		}
	}
	
	public static class PasteMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public PasteMenuItem(final LedBredFrame f) {
			super("Paste");
			setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V, SHORTCUT_KEY));
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (!f.panel.leds.pastePicture()) {
						Toolkit.getDefaultToolkit().beep();
					}
				}
			});
		}
	}
	
	public static class ClearMenuItem extends JMenuItem {
		private static final long serialVersionUID = 1L;
		public ClearMenuItem(final LedBredFrame f) {
			super("Clear");
			addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					f.panel.leds.clearPixels();
				}
			});
		}
	}
}
